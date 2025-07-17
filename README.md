<h1 align="center">Smart Home Energy Management System (SHEMS)</h1>
<br>
<h2>Project Overview</h2>
The Smart Home Energy Management System (SHEMS) project aims to simulate intelligent control over household appliances to manage electricity usage efficiently based on user-defined profiles. This system models appliance scheduling, energy consumption, and cost calculation using core object-oriented programming (OOP) concepts in C++. Key topics covered include:
<ul>
  <li><b>Classes and Objects:</b> To model real-world appliances.</li>
  <li><b>Inheritance and Polymorphism:</b> Enable future extensibility for different appliance types.</li>
  <li><b>Operator Overloading:</b> For comparing energy usage between appliances.</li>
  <li><b>Templates:</b> To build a generic appliance list management system.</li>
  <li><b>Control Structures:</b> Used for scheduling logic based on time-of-use tariffs.</li>
</ul>
<br>
<h2>Objectives</h2>
<ul>
  <li>Efficiently add, remove, and search appliances.</li>
  <li>Display appliance details.</li>
  <li>Schedule appliances based on predefined user energy profiles (Comfort-first/Cost-first/Balanced).</li>
  <li>Calculate and display energy usage and cost reports.</li>
  <li>Warn users if energy consumption exceeds a defined threshold.</li>
</ul>
<br>
<h2>Key Features</h2>
<ol>
  <li><b>Appliance class: -</b></li>
    <ul>
      <li>Models appliance with attributes like Name, Category (HVAC/Lighting/Kitchen), Power (in KWh), and Status (ON/OFF).</li>
      <li>Provides input/output and energy calculation functions.</li>
    </ul>
  <li><b>ApplianceList<T> Class: -</b></li>
    <ul>
      <li>Stores up to 100 appliances.</li>
      <li>Provides functions to:</li>
        <ul>
          <li>Add, remove, search, and display appliances</li>
          <li>Schedule appliance usage with hour-by-hour cost breakdown</li>
          <li>Sort and display report by energy usage</li>
        </ul>
      <li>Scheduler Function:</li>
        <ul>
          <li>Iterates over hours of each appliance's operation.</li>
          <li>Calculates hourly cost using tariff based on profile and time.</li>
          <li>Tracks total energy and cost, and issues warnings if limits exceeded.</li>
        </ul>
    </ul>
  <li><b>Constraints: -</b></li>
    <ul>
      <li>Max number of appliances: 100 </li>
      <li>Operation hours must be in 0–23</li>
      <li>Consumption limit: 20 kWh</li>
      <li>Tariff varies based on time and profile</li>
    </ul>
</ol>
<br>
<h2>Repository Structure</h2>
Smart-Home-Energy-Management-System/
<br>
├── Smart_Home_Energy_Management_System.cpp ---> Main C++ source file
<br>
├── README.md ---> Project documentation
