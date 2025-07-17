#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

const int MAX = 100, PEAK_START = 16, PEAK_END = 22;
const float LIMIT = 20.0f;

class Appliance {
protected:
    char Name[50], Category[50];
    int PowerRating, PreferredHours, StartHour;
    bool Status;

public:
    Appliance() {
        strcpy(Name, "N/A");
        strcpy(Category, "N/A");
        PowerRating = 0;
        PreferredHours = 0;
        StartHour = 0;
        Status = false;
    }

    virtual void Input() {
        cin.ignore();
        cout << "\nEnter Appliance Name: ";
        cin.getline(Name, 50);

        cout << "Enter Category (HVAC/Lighting/Kitchen): ";
        cin.getline(Category, 50);

        cout << "Enter Power Rating (Watts): ";
        cin >> PowerRating;

        cout << "Enter Preferred Hours of Operation: ";
        cin >> PreferredHours;

        cout << "Enter Starting Hour (0 - 23): ";
        cin >> StartHour;

        cout << "Is it ON? (1 for yes, 0 for no): ";
        cin >> Status;
    }

    virtual void Display() const {
        cout << Name << " | " << Category << " | Power: " << PowerRating << "W | Hours: " << PreferredHours
            << " | Start: " << StartHour << " | Status: " << (Status ? "ON" : "OFF") << endl;
    }

    float EnergyUsed() const {
        return (PowerRating * PreferredHours) / 1000.0f;
    }

    const char* getName() const { return Name; }
    const char* getCategory() const { return Category; }
    int getPower() const { return PowerRating; }
    int getPreferredHours() const { return PreferredHours; }
    int getStartHour() const { return StartHour; }
    bool getStatus() const { return Status; }

    bool operator>(const Appliance& other) const {
        return EnergyUsed() > other.EnergyUsed();
    }
};

template <typename T>
class ApplianceList {
private:
    T Appliances[MAX];
    int Count;

public:
    ApplianceList() : Count(0) {}

    void Add() {
        if (Count >= MAX) {
            cout << "List is full!\n";
            return;
        }
        Appliances[Count].Input();
        cout << "\nAppliance added successfully!\n";
        Appliances[Count].Display();
        Count++;
    }

    void Remove(const char* Name) {
        for (int i = 0; i < Count; i++) {
            if (strcmp(Appliances[i].getName(), Name) == 0) {
                for (int j = i; j < Count - 1; j++) {
                    Appliances[j] = Appliances[j + 1];
                }
                Count--;
                cout << "\nAppliance removed!\n";
                return;
            }
        }
        cout << "\nAppliance not found.\n";
    }

    void Search(const char* Name) const {
        for (int i = 0; i < Count; i++) {
            if (strcmp(Appliances[i].getName(), Name) == 0) {
                Appliances[i].Display();
                return;
            }
        }
        cout << "\nAppliance not found.\n";
    }

    void DisplayAll() const {
        if (Count == 0) {
            cout << "\nNo appliances added.\n";
            return;
        }
        for (int i = 0; i < Count; i++) {
            Appliances[i].Display();
        }
    }

    void Schedule(const char* Profile) const {
        cout << "\n------ Scheduling Appliances for Profile: " << Profile << " ------\n";
        float TotalEnergy = 0.0f;

        for (int i = 0; i < Count; i++) {
            if (!Appliances[i].getStatus()) continue;

            int Start = Appliances[i].getStartHour();
            int Duration = Appliances[i].getPreferredHours();
            int Power = Appliances[i].getPower();

            float TotalCost = 0.0f;
            float Energy = Power / 1000.0f;
            cout << "\n" << Appliances[i].getName() << " Schedule:\n";

            for (int h = 0; h < Duration; ++h) {
                int Hour = (Start + h) % 24;
                bool IsPeak = (Hour >= PEAK_START && Hour < PEAK_END);

                float Tariff;

                if (strcmp(Profile, "Comfort-first") == 0) {
                    if (IsPeak)
                        Tariff = 25.0f;
                    else
                        Tariff = 20.0f;
                }
                else if (strcmp(Profile, "Cost-first") == 0) {
                    if (IsPeak)
                        Tariff = 15.0f;
                    else
                        Tariff = 5.0f;
                }
                else {
                    if (IsPeak)
                        Tariff = 20.0f;
                    else
                        Tariff = 10.0f;
                }

                float Cost = Energy * Tariff;
                TotalCost += Cost;

                cout << "Hour " << Hour << " | Tariff: Rs. " << Tariff << " | Energy: " << Energy
                    << " kWh | Cost: Rs. " << Cost << "\n";
            }

            cout << "Total Estimated Cost for " << Appliances[i].getName() << ": Rs. " << TotalCost << "\n";
            TotalEnergy += Energy * Duration;
        }

        cout << "\nTotal Energy Consumed: " << TotalEnergy << " kWh\n";
        if (TotalEnergy > LIMIT)
            cout << "\nWARNING: Consumption exceeded limit of " << LIMIT << " kWh!\n";
    }

    void SortedReport() {
        for (int i = 0; i < Count - 1; i++) {
            for (int j = 0; j < Count - i - 1; j++) {
                if (Appliances[j + 1] > Appliances[j]) {
                    T temp = Appliances[j];
                    Appliances[j] = Appliances[j + 1];
                    Appliances[j + 1] = temp;
                }
            }
        }

        cout << "\n------ Appliance Report (Sorted by Consumption) ------\n";
        for (int i = 0; i < Count; i++) {
            cout << Appliances[i].getName() << " | Usage: " << Appliances[i].EnergyUsed() << " kWh\n";
        }
    }
};

int main() {
    ApplianceList<Appliance> List;
    int Choice;
    char Name[50], Profile[20];

    do {
        cout << "\nSmart Home Energy Management System\n";
        cout << "1. Add Appliance\n2. Remove Appliance\n3. Search Appliance\n";
        cout << "4. Display All\n5. Schedule\n6. Report\n0. Exit\n";
        cout << "Enter Choice: "; cin >> Choice;

        switch (Choice) {
        case 1:
            List.Add(); break;
        case 2:
            cout << "Enter Name to Remove: "; cin.ignore(); cin.getline(Name, 50);
            List.Remove(Name); break;
        case 3:
            cout << "Enter Name to Search: "; cin.ignore(); cin.getline(Name, 50);
            List.Search(Name); break;
        case 4:
            List.DisplayAll(); break;
        case 5:
            cout << "Select Profile (Comfort-first / Cost-first / Balanced): ";
            cin.ignore(); cin.getline(Profile, 20);
            List.Schedule(Profile); break;
        case 6:
            List.SortedReport(); break;
        case 0:
            cout << "Exiting...\n"; break;
        default:
            cout << "Invalid Choice!\n"; break;
        }
    } while (Choice != 0);

    return 0;
}
