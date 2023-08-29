/*
--CRUD COMMANDS:
--Kriti
--STUDENT ID: 170513212
--EMAIL: kriti@myseneca.ca
*/

#include <iostream>
#include <occi.h>
#include <iomanip>
#include <string>

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

//CODE TO INSERT OWNER
void insertOwners(Connection* conn)
{
    string o_Name, o_EmailId, o_PaymentDate, o_Phone;
    double o_Id = 0, o_UnitNumber = 0, o_MaintenanceId = 0;
    int errCode = 0;

    cout << "Enter Owner ID: ";
    cin >> o_Id;
    cout << "Enter Owner Name: ";
    cin.ignore();
    getline(cin, o_Name);
    cout << "Enter Owner Email Id: ";
    cin.sync();
    getline(cin, o_EmailId);
    cout << "Enter Owner Phone: ";
    cin >> o_Phone;
    cout << "Enter Unit Number: ";
    cin >> o_UnitNumber;
    cout << "Enter Maintenance Id:";
    cin >> o_MaintenanceId;
    cout << "Enter Owner Payment Date:";
    cin.ignore();
    getline(cin, o_PaymentDate);

    try {
        Statement* stmt = conn->createStatement();
        stmt->setSQL("BEGIN SPownerINSERT(:1, :2, :3, :4, :5, :6, :7, :8); END;");
        stmt->registerOutParam(1, Type::OCCIINT);
        stmt->setDouble(2, o_Id);
        stmt->setString(3, o_Name);
        stmt->setString(4, o_EmailId);
        stmt->setString(5, o_Phone);
        stmt->setDouble(6, o_UnitNumber);
        stmt->setDouble(7, o_MaintenanceId);
        stmt->setString(8, o_PaymentDate);

        stmt->executeUpdate();
        errCode = stmt->getInt(1);

        if (errCode == 1) {
            cout << "\nSUCCESS: New owner inserted.\n\n";
        }
        else
        {
            cout << "\ERROR: Failed to insert owner.\n\n";
        }
        conn->terminateStatement(stmt);
    }
    catch (SQLException& sqlExcp)
    {
        cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
    }
};

//CODE TO REMOVE OWNER
void deleteOwners(Connection* conn) {
    double o_Id;
    int errCode = 0;

    cout << "Enter Owner Id to remove the owner: ";
    cin >> o_Id;

    Statement* stmt = conn->createStatement();
    stmt->setSQL("BEGIN SPownerDELETE(:1, :2); END;");
    stmt->registerOutParam(1, Type::OCCIINT);
    stmt->setDouble(2, o_Id);
    stmt->executeUpdate();

    errCode = stmt->getInt(1);
    if (errCode == 1) {
        cout << "Owner deleted successfully!" << endl;
    }
    else {
        cout << "Error: Owner not deleted!" << endl;
    }
}

//CODE TO UPDATE OWNER INFORMATION
void updateOwners(Connection* conn) {
    string o_Phone;
    double o_Id;
    int errCode = 0;

    cout << "Enter Owner ID to update: ";
    cin >> o_Id;
    cout << "Enter New Owner Phone: ";
    cin.ignore();
    getline(cin, o_Phone);

    Statement* stmt = conn->createStatement();
    stmt->setSQL("BEGIN SPownerUPDATE(:1, :2, :3); END;");
    stmt->registerOutParam(1, Type::OCCIINT);
    stmt->setDouble(2, o_Id);
    stmt->setString(3, o_Phone);

    errCode = stmt->getInt(1);
    if (errCode == 1) {
        cout << "Owner Phone Information updated successfully!" << endl;
    }
    else {
        cout << "Error: Owner Information not updated!" << endl;
    }
}

//CODE TO SELECT OWNER
void selectOwners(Connection* conn) {
    string o_Name, o_EmailId, o_PaymentDate, o_Phone;
    double o_Id, o_UnitNumber = 0, o_MaintenanceId = 0;
    int errCode = 0;

    cout << "Enter Owner ID to select: ";
    cin >> o_Id;

    Statement* stmt = conn->createStatement();
    stmt->setSQL("BEGIN SPownerSELECT(:1, :2, :3, :4, :5, :6, :7, :8); END;");
    stmt->registerOutParam(1, Type::OCCIINT);
    stmt->setDouble(2, o_Id);
    stmt->registerOutParam(3, Type::OCCISTRING, 20);
    stmt->registerOutParam(4, Type::OCCISTRING, 20);
    stmt->registerOutParam(5, Type::OCCISTRING, 20);
    stmt->registerOutParam(6, Type::OCCIDOUBLE, 50);
    stmt->registerOutParam(7, Type::OCCIDOUBLE, 50);
    stmt->registerOutParam(8, Type::OCCISTRING, 50);
    stmt->executeUpdate();
    errCode = stmt->getInt(1);
    if (errCode == 1) {
        o_Name = stmt->getString(3);
        o_EmailId = stmt->getString(4);
        o_Phone = stmt->getString(5);
        o_UnitNumber = stmt->getDouble(6);
        o_MaintenanceId = stmt->getDouble(7);
        o_PaymentDate = stmt->getString(8);
        cout << "Owner Name: " << o_Name << endl;
        cout << "Owner Email Id: " << o_EmailId << endl;
        cout << "Owner Phone: " << o_Phone << endl;
        cout << "Owner Unit Number: " << o_UnitNumber << endl;
        cout << "Maintenance Id: " << o_MaintenanceId << endl;
        cout << "Owner Payment Date: " << o_PaymentDate << endl;
    }
    else {
        cout << "Error: Owner not found!" << endl;
    }

}

int menu() {
    int selection = 0;
    do {
        cout << "Please select an option:" << endl;
        cout << "1) Insert new Owner" << endl;
        cout << "2) Delete existing Owner" << endl;
        cout << "3) Update existing Owner" << endl;
        cout << "4) Display an Owner" << endl;
        cout << "5) Exit" << endl << endl;
        cout << "Enter selection: ";

        if (!(cin >> selection)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (selection < 1 || selection > 5) {
            cout << "Invalid selection. Please enter a number between 1 and 5." << endl;
        }
    } while (selection < 1 || selection > 5);
    return selection;
}


int main(void)
{
    /* OCCI Variables */
    Environment* env = nullptr;
    Connection* conn = nullptr;
    /* Used Variables */
    / Member - 1 /
        string str;
    string usr = "dbs311_231zbb36";
    string pass = "28485866";
    string srv = "myoracle12c.senecacollege.ca:1521/oracle12c";


    try {
        env = Environment::createEnvironment(Environment::DEFAULT);
        conn = env->createConnection(usr, pass, srv);
        cout << "Connection is Successful!" << endl;
        cout << "Group 4" << endl << endl;
        cout << "Project Topic - High Rise Condo" << endl << endl;
        cout << "Group Members -" << endl;
        cout << endl;

        int selection = 0;
        while (selection != 5) {
            cout << endl;
            cout << "******** Menu ********" << endl;

            selection = menu();
            switch (selection) {
            case 1:
                insertOwners(conn);
                break;
            case 2:
                deleteOwners(conn);
                break;
            case 3:
                updateOwners(conn);
                break;
            case 4:
                selectOwners(conn);
                break;
            case 5:
                cout << "Exiting the program..." << endl;
                break;
            }
        }
        env->terminateConnection(conn);
        Environment::terminateEnvironment(env);
    }

    catch (SQLException& sqlExcp) {
        cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
    }
    return 0;
}