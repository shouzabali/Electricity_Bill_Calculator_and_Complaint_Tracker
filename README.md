# Electricity_Bill_Calculator_and_Complaint_Tracker
Electricity Bill Calculator & Complaint Tracker
A console-based C++ application that calculates electricity bills based on HAZECO tariff rates and allows users to file and track complaints.

Developed By
Name Shouzab Ali Kayani Role Developer
Name Mahrij Mir Role Developer
Subject: Object Oriented Programming (OOP)
Semester: 2 — PAF-IAST Haripur

📋 Features

🏠 Residential Users — Protected & Unprotected slab-rate billing
🏢 Commercial Users — Load-based billing with fixed charges
🏭 Industrial Users — High-load billing with per-KW fixed charges
🧾 Detailed Bill Breakdown — Energy charges, FC surcharge, electricity duty, GST
📝 Complaint Filing — File, update, and track complaint status
💾 File Storage — Bills and complaints saved to .txt files


🧮 Tariff Structure
Residential Protected (≤100 units)
SlabRate1–50 unitsRs. 7/unit
51–100 unitsRs. 11.68/unit
101–200 unitsRs. 15.75/unit
201+ unitsRs. 18.07/unit

Residential Unprotected (>100 units)
SlabRate1–100 unitsRs. 22/unit
101–200 unitsRs. 32/unit
201–300 unitsRs. 37/unit
301–400 unitsRs. 43/unit
401–500 unitsRs. 47/unit
501–600 unitsRs. 49/unit
601–700 unitsRs. 52/unit
701+ unitsRs. 65/unit

Commercial
LoadRate
< 5 KWRs. 38.82/unit
≥ 5 KWRs. 40.26/unit

Industrial
LoadRate
≤ 500 KWRs. 38/unit> 
500 KWRs. 42/unit

🔢 Bill Calculation Formula
Energy Charges     = Units × Rate per unit
Fixed Charges      = Load KW × 500  (Commercial & Industrial only)
FC Surcharge       = Units × 3.23   (Residential only)
Electricity Duty   = 1.5% of (Energy Charges + FC Surcharge)
GST                = 18% of (Energy Charges + Fixed Charges + Electricity Duty)
Total Bill         = All of the above added together

🏗️ OOP Concepts Used

1.Inheritance — ResidentialUser, CommercialUser, IndustrialUser extend User and Tariff
2.Abstract Classes — User and Tariff have pure virtual functions
3.Polymorphism — calculateBill() and displayTariffType() overridden in each class
4.Encapsulation — Private/protected data members with getters/setters
5.File Handling — FileManager class for saving bills and complaints
6.Operator Overloading — > operator for comparing bill amounts
7.Dynamic Memory — new and delete for user objects


🚀 How to Run
Requirements

g++ compiler (MinGW or GCC)
Windows / Linux / Mac

Compile & Run
bashg++ main_code.cpp -o main_code
.\main_code # Windows
./main_code # Linux/Mac

📁 Output Files
FileContentsbills.txt Saved bill amounts 
complaints.txt Filed complaint records
