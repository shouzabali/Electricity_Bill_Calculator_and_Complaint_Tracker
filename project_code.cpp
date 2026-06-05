#include <iostream>
#include <fstream>

using namespace std;

class Tariff {
protected:
    double slabRates[8];

public:
    Tariff() {
        for (int i = 0; i < 8; i++) {
            slabRates[i] = 0;
        }
    }

    virtual double calculateRate(int units) = 0;

    virtual ~Tariff() {}
};

class User {
private:
    string userName;
    int userId;

protected:
    int unitsConsumed;

    double energyCharges;
    double fixedCharges;
    double fcSurcharge;
    double electricityDuty;
    double gst;
    double totalBill;

public:
    User(string name, int id, int units) {

        userName = name;
        userId = id;
        unitsConsumed = units;

        energyCharges = 0;
        fixedCharges = 0;
        fcSurcharge = 0;
        electricityDuty = 0;
        gst = 0;
        totalBill = 0;
    }

    void setUserName(string name) {
        userName = name;
    }

    void setUserId(int id) {
        userId = id;
    }

    string getUserName() const {
        return userName;
    }

    int getUserId() const {
        return userId;
    }

    int getUnitsConsumed() const {
        return unitsConsumed;
    }

    double getEnergyCharges() const {
        return energyCharges;
    }

    double getFixedCharges() const {
        return fixedCharges;
    }

    double getFCSurcharge() const {
        return fcSurcharge;
    }

    double getElectricityDuty() const {
        return electricityDuty;
    }

    double getGST() const {
        return gst;
    }

    double getTotalBill() const {
        return totalBill;
    }

    virtual double calculateBill() = 0;

    virtual void displayTariffType() = 0;

    virtual ~User() {}
};

class ResidentialUser : public User, public Tariff {
private:
    bool isProtected;

public:
    ResidentialUser(string name, int id, int units, bool protectionStatus)
        : User(name, id, units) {

        isProtected = protectionStatus;
    }

    double calculateRate(int units) {

        double amount = 0;

        if (isProtected) {

            if (units <= 50) {
                amount = units * 7;
            }

            else if (units <= 100) {
                amount = (50 * 7) + ((units - 50) * 11.68);
            }

            else if (units <= 200) {
                amount = (50 * 7) + (50 * 11.68) + ((units - 100) * 15.75);
            }

            else {
                amount = (50 * 7) + (50 * 11.68) + (100 * 15.75) + ((units - 200) * 18.07);
            }
        }

        else {

            if (units <= 100) {
                amount = units * 22;
            }

            else if (units <= 200) {
                amount = (100 * 22) + ((units - 100) * 32);
            }

            else if (units <= 300) {
                amount = (100 * 22) + (100 * 32) + ((units - 200) * 37);
            }

            else if (units <= 400) {
                amount = (100 * 22) + (100 * 32) + (100 * 37) + ((units - 300) * 43);
            }

            else if (units <= 500) {
                amount = (100 * 22) + (100 * 32) + (100 * 37) + (100 * 43) + ((units - 400) * 47);
            }

            else if (units <= 600) {
                amount = (100 * 22) + (100 * 32) + (100 * 37) + (100 * 43) + (100 * 47) + ((units - 500) * 49);
            }

            else if (units <= 700) {
                amount = (100 * 22) + (100 * 32) + (100 * 37) + (100 * 43) + (100 * 47) + (100 * 49) + ((units - 600) * 52);
            }

            else {
                amount = (100 * 22) + (100 * 32) + (100 * 37) + (100 * 43) + (100 * 47) + (100 * 49) + (100 * 52) + ((units - 700) * 65);
            }
        }

        return amount;
    }

    double calculateBill() {

        energyCharges = calculateRate(unitsConsumed);

        fixedCharges = 0;

        fcSurcharge = unitsConsumed * 3.23;

        electricityDuty = 0.015 * (energyCharges + fcSurcharge);

        gst = 0.18 * (energyCharges + fixedCharges + electricityDuty);

        totalBill = energyCharges + fixedCharges + fcSurcharge + electricityDuty + gst;

        return totalBill;
    }
    void displayTariffType() {

        if (isProtected) {
            cout << "Residential Protected" << endl;
        }

        else {
            cout << "Residential Unprotected" << endl;
        }
    }
};

class CommercialUser : public User, public Tariff {
private:
    double loadKW;

public:
    CommercialUser(string name, int id, int units, double load)
        : User(name, id, units) {

        loadKW = load;
    }

    double calculateRate(int units) {

        if (loadKW < 5) {
            return units * 38.82;
        }

        else {
            return units * 40.26;
        }
    }

    double calculateBill() {

        energyCharges = calculateRate(unitsConsumed);

        fixedCharges = 2000;

        fcSurcharge = 0;

        electricityDuty = 0.015 * energyCharges;

        gst = 0.18 * (energyCharges + fixedCharges + electricityDuty);

        totalBill = energyCharges + fixedCharges + electricityDuty + gst;
    
        return totalBill;
    }

    void displayTariffType() {
        cout << "Commercial User" << endl;
    }
};

class IndustrialUser : public User, public Tariff {
private:
    double loadKW;

public:
    IndustrialUser(string name, int id, int units, double load) : User(name, id, units) {
        loadKW = load;
    }

    double calculateRate(int units) {
        
        if (loadKW <= 500) {
            return units * 38;
        }
        else {
            return units * 42;
        }
    }

    double calculateBill() {

        energyCharges = calculateRate(unitsConsumed);

        fixedCharges = loadKW * 500;

        fcSurcharge = 0;

        electricityDuty = 0.015 * energyCharges;

        gst = 0.18 * (energyCharges + fixedCharges + electricityDuty);
            
        totalBill =  energyCharges + fixedCharges + electricityDuty + gst;      

        return totalBill;
    }

    void displayTariffType() {
        cout << "Industrial User" << endl;
    }
};

class Bill {
private:

    string month;
    double amount;

public:
    User* billUser;

    Bill(int units = 0, string m = "") {

        month = m;
        amount = 0;

        billUser = nullptr;
    }

    void getBillDetails() {

        string name;
        int id;
        int choice;
        int units;

        cout << "Enter User Name: ";
        getline(cin, name);

        cout << "Enter User ID: ";
        cin >> id;
        cin.ignore();

        cout << "Select Tariff Type" << endl;
        cout << "1. Residential" << endl;
        cout << "2. Commercial" << endl;
        cout << "3. Industrial" << endl;
        cout << "Choice: ";
        cin >> choice;

        cout << "Enter Month: ";
        cin >> month;

        cout << "Enter Units Consumed: ";
        cin >> units;

        if (choice == 1) {

            bool status;

            if (units <= 100) {
                status = true;
            }
            else{
                status = false;
            }
           
            billUser =  new ResidentialUser( name, id, units, status);
        }

        else if (choice == 2) {

            double load;

            cout << "Enter Load in KW: ";
            cin >> load;

            billUser = new CommercialUser(name, id, units, load);
        }

        else if (choice == 3) {

            double load;

            cout << "Enter Load in KW: ";
            cin >> load;

            billUser = new IndustrialUser(name, id, units, load);
            
        }

        else {
            cout << "Invalid Choice!" << endl;
            return;
        }

        amount = billUser->calculateBill();
    }

    void displayBill() {

        cout << "\n**************************************" << endl;
        cout << "            ELECTRICITY BILL            " << endl;
        cout << "****************************************" << endl;
        cout << "User Name       : " << billUser->getUserName() << endl;
        cout << "User ID         : " << billUser->getUserId() << endl; 
        cout << "Units Consumed  : " << billUser->getUnitsConsumed() << endl;  
        cout << "Month           : " << month << endl;
        cout << "Tariff Type     : "; billUser->displayTariffType();
        cout << endl;
        cout << "-----------------------------------------" << endl;

        cout << "**********BILL BREAKDOWN**********" << endl;
        cout << endl;
        cout << "Energy Charges  : Rs. " << billUser->getEnergyCharges() << endl;
        cout << "Fixed Charges   : Rs. " << billUser->getFixedCharges() << endl;
        cout << "FC Surcharge    : Rs. " << billUser->getFCSurcharge() << endl;
        cout << "Electricity Duty: Rs. " << billUser->getElectricityDuty() << endl;
        cout << "GST (18%)       : Rs. " << billUser->getGST() << endl;
        cout << endl;
        cout << "-----------Formula calculation sheet-----------" << endl;
        cout << endl;
        cout << "Energy charges                                       = units * rate per unit" << endl;
        cout << "Fixed charges (for commercial and industrial users)  = loadkw x 500" << endl;
        cout << "FC Surcharge (for residential users)                 = units * 3.23" << endl;
        cout << "Electricity Duty                                     = 1.5% of (Energy Charges + FC Surcharge)" << endl;
        cout << "GST                                                  = 18% of (Energy Charges + Fixed Charges + Electricity Duty)" << endl;
        cout << endl;
        cout << "-----------------------------------------" << endl;
        cout << endl;
        cout << "TOTAL BILL      : Rs. " << billUser->getTotalBill() << endl;
        cout << endl;
        cout << "********************************************" << endl;
    }

    double getAmount() const {
        return amount;
    }

    bool operator>(const Bill& rhs) {
        return this->amount > rhs.amount;
    }

    ~Bill() {
        delete billUser;
    }
};

class Complaint {

private:
    int complaintId;
    string description;
    string status;

public:

    Complaint() {

        complaintId = 0;
        description = "";
        status = "Pending";
    }

    void fileComplaint() {

        cout << "\nEnter Complaint ID: ";
        cin >> complaintId;

        cin.ignore();

        cout << "Enter Complaint Description: ";
        getline(cin, description);

        status = "Pending";

        cout << "\nComplaint Filed Successfully!" << endl;
    }

    void updateStatus() {

        int choice;

        cout << "\nUpdate Complaint Status" << endl;
        cout << "1. Pending" << endl;
        cout << "2. Resolved" << endl;

        cout << "Enter Choice: ";
        cin >> choice;

        if (choice == 1) {
            status = "Pending";
        }

        else if (choice == 2) {
            status = "Resolved";
        }

        else {
            cout << "Invalid Choice!" << endl;
        }
    }

    void displayComplaint() {

        cout << "\n********** COMPLAINT **********" << endl;
        cout << "Complaint ID: " << complaintId << endl;  
        cout << "Description: " << description << endl;
        cout << "Status: " << status << endl;
             
    }

    int getComplaintId() const {
        return complaintId;
    }

    string getDescription() const {
        return description;
    }

    string getStatus() const {
        return status;
    }
};

class FileManager {

public:

    void saveBill(Bill& bill) {

        ofstream file("bills.txt", ios::app);

        if (file.is_open()) {

            file << "Bill Amount: " << bill.getAmount() << endl;
            file << "----------------------" << endl;
            file.close();
            cout << "Bill Saved Successfully"  << endl;
                
        }
        else {
            cout << "File Error!" << endl;
        }
    }

    void saveComplaint(Complaint& complaint) {

        ofstream file("complaints.txt", ios::app);

        if (file.is_open()) {

            file << complaint.getComplaintId() << endl;
            file << complaint.getDescription() << endl;
            file << complaint.getStatus() << endl;
            file << "----------------------" << endl;
            file.close();
            cout << "Complaint Saved Successfully" << endl;
                
        }
        else {
            cout << "File Error!" << endl;
        }
    }
};

int main() {

    Bill bill1;

    FileManager fm;

    bill1.getBillDetails();

    bill1.displayBill();

    Complaint c1;

    char choice;

    cout << endl;

    cout << "Do you want to file a complaint? (1 for Yes, 0 for No): ";
    cin >> choice;

    if (choice == '1') {

        c1.fileComplaint();

        c1.displayComplaint();

        c1.updateStatus();

        c1.displayComplaint();

        fm.saveComplaint(c1);
    }

    else if (choice == '0') {

        cout << "No complaint filed." << endl;
    }

    else {

        cout << "Invalid choice." << endl;
    }

    fm.saveBill(bill1);

    return 0;
}