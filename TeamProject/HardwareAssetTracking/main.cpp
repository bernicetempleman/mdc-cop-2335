/*
    COP 2335 Team Project - Hardware Asset Tracking
    Team: NULL Terminators
    Members:
        Steve Hirabayashi
        Chris Girala
        Carlos Baltodano
        Julien Laurent
        Bernice Templeman
        Shoaib Khan
*/
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <ctime>

#include "Person.h"
#include "Record.h"

using namespace std;

// Function Prototypes
int menu();
void addNewAsset();
void displayAllAssets();
long searchAssetByID(long);
long searchAssetByStatusAndType(char*, char);
void deleteAsset();
void changeAsset(Asset, long);
int findAssetFileAmount();
int findAssetAvailableAmount(char*);
Asset getAsset(long);
Person getPerson(long);
Person getPersonalInfo();
void getUserPersonalInfo();
long searchPerson(char*);
void changePerson(Person, long);
int findPersonFileAmount();
char* getCurrentDate();
char* getFutureDate(char*, int);
int compareDates(char*, char*);

void displayAllPersons();
void updateDatabase();
void checkIfLate(Asset, int);
void searchAvailableTypes(char*);
char* getAssetType();

//record functions
void addNewRecord(long, char*, char*);
long searchRecord(long);
Record getRecord(long);
void changeRecord(Record, long);
int findRecordFileAmount();

void inventoryMenu();
void addOrRemoveAsset();
void outstandingIssues();
void displayAllRecords();
void inputReservationRequest();
void inputBorrowRequest();
void inputReturnRequest();
void viewUserReservation();
void changeUserReservation(int);

int main()
{
    // Use this to truncate the binary files, use if you wish to clear AssetFile.dat
        /*
    fstream assetFile;
    assetFile.open("AssetInfo.dat", ios::out|ios::binary);
    assetFile.close();
    fstream personFile;
    personFile.open("PersonInfo.dat", ios::out|ios::binary);
    personFile.close();
    fstream recordFile;
    recordFile.open("RecordInfo.dat", ios::out|ios::binary);
    recordFile.close();
        */

    updateDatabase();

    int userChoice;

    cout << "\nWelcome to Hardware Asset Tracking" << endl;
    while(true)
    {
        userChoice = menu();
        if(userChoice == 1)
        {
            inventoryMenu();
            continue;
        }
        else if(userChoice == 2)
        {
            addOrRemoveAsset();
            continue;
        }
        else if(userChoice == 3)
        {
            outstandingIssues();
            continue;
        }
        else if(userChoice == 4)
        {
            displayAllRecords();
            continue;
        }
        else if(userChoice == 5)
        {
            inputReservationRequest();
            continue;
        }
        else if(userChoice == 6)
        {
            inputBorrowRequest();
            continue;
        }
        else if(userChoice == 7)
        {
            inputReturnRequest();
            continue;
        }
        else if(userChoice == 8)
        {
            viewUserReservation();
            continue;
        }
        else
        {
            cout << "\nThank you for using this program. Have a nice day!" << endl;
            break;
        }
    }
    return 0;
}

int menu()
{
    int choice;
    bool condition = false;

    cout << "\nPlease enter one of the following options:" << endl
         << "\t1. View Inventory Status" << endl
         << "\t2. Update Inventory" << endl
         << "\t3. View List of Current Outstanding Issues" << endl
         << "\t4. View History of Borrowed/Reserved" << endl
         << "\t5. Input Reservation Request" << endl
         << "\t6. Input Borrow Request" << endl
         << "\t7. Input Return Request" << endl
         << "\t8. View/Change EnTeC Class Reserved Amount" << endl
         << "\t9. Exit" << endl
         << "Your Choice: ";
    // Defensive programming
    do {
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.sync();
            cout << "\nInvalid input. Please enter a number between 1 to 9." << endl;
        }
        else if (choice < 1 || choice > 9)
            cout << "\nInvalid input. Please enter a number between 1 to 9." << endl;
        else
            condition = true;
    } while (!condition);

    cin.ignore();
    cin.sync();

    return choice;
}

// print assets that are broken or late
void outstandingIssues()
{
    Asset asset;
    char status[MAX_LENGTH];

    int bCounter = 0;
    int lCounter = 0;

    fstream assetFile;
    assetFile.open("AssetInfo.dat", ios::in|ios::binary);

     if (!assetFile)
    {
        cout << "Error locating file. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    do {
        assetFile.read(reinterpret_cast<char *>(&asset), sizeof(asset));
        strcpy(status, asset.Getstatus());
        if (status[0] == 'L')
        {
            asset.printInfo();
            lCounter++;
        }

        if (status[0] == 'B')
        {
            asset.printInfo();
            bCounter++;
        }
    } while(!(assetFile.eof()));
    cout << "Amount of late assets: " << lCounter << endl
         << "Amount of broken assets: " << bCounter << endl;

    assetFile.close();
}

// return the cstring of asset type
char* getAssetType()
{
    int aChoice;
    char aType[MAX_LENGTH];
    do
    {
        cout << "What type of asset?" << endl
                 << "\t1. iPad" << endl
                 << "\t2. iPad Charger" << endl
                 << "\t3. Android tablet" << endl
                 << "\t4. Android Charger" << endl
                 << "\t5. Windows tablet" << endl
                 << "\t6. Windows Charger" << endl
                 << "\t7. Other" << endl;
            cin >> aChoice;
        if (cin.fail())
        {
            cin.clear();
            cin.sync();
            cout << "\nInvalid input. Please enter a number between 1 to 7." << endl;
        }
        else if (aChoice < 1 || aChoice > 7)
            cout << "\nInvalid input. Please enter a number between 1 to 7." << endl;
        else
            break;
    } while(true);

    if (aChoice == 1)
    {
        strcpy(aType, "iPad");
    }
    else if (aChoice == 2)
    {
        strcpy(aType, "iPad Charger");
    }
    else if (aChoice == 3)
    {
        strcpy(aType, "Android tablet");
    }
    else if (aChoice == 4)
    {
        strcpy(aType, "Android Charger");
    }
    else if (aChoice == 5)
    {
        strcpy(aType, "Windows tablet");
    }
    else if (aChoice == 6)
    {
        strcpy(aType, "Windows Charger");
    }
    else if (aChoice == 7)
    {
        strcpy(aType, "Other");
    }

    return aType;
}
// updates In use and regular reserved assets
void updateDatabase()
{
    Asset asset;
    Person aPerson;
    char status[MAX_LENGTH];

    fstream assetFile;
    assetFile.open("AssetInfo.dat", ios::in|ios::out|ios::binary);
    if (!assetFile)
    {
        cout << "Error locating file. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    fstream personFile;
    personFile.open("PersonInfo.dat", ios::in | ios::out | ios::binary);
    if (!personFile)
    {
        cout << "Error locating file. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    do {
        assetFile.read(reinterpret_cast<char *>(&asset), sizeof(asset));
        strcpy(status, asset.Getstatus());

        if(!(assetFile.eof()))
        {
            if (status[0] == 'I')
            {
                checkIfLate(asset, 1);
            }

            else if (status[0] == 'R')
            {
            checkIfLate(asset, 2);
            }
        }
    } while(!(assetFile.eof()));

    personFile.close();
}

void addNewAsset()
{
    long idNum, idFound;
    char type[MAX_LENGTH], location[MAX_LENGTH], status[MAX_LENGTH];
    string st = "Available";
    strncpy(status, st.c_str(), MAX_LENGTH);

    fstream assetFile;
    assetFile.open("AssetInfo.dat", ios::in|ios::out|ios::binary);
    if (!assetFile)
    {
        cout << "Error locating file. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    cout << "\nEnter the new asset ID number: ";
    do {
        cin >> idNum;
        idFound = searchAssetByID(idNum);
        if (idFound != -1)
            cout << "\nPlease enter a unique ID number: ";
    } while (idFound != -1);

    cin.ignore();
    cin.sync();
    cout << "\nEnter the asset location: ";
    cin.getline(location, MAX_LENGTH);

    strcpy(type, getAssetType());

    Asset asset;
    asset.SetID(idNum);
    asset.Setlocation(location);
    asset.SetassetType(type);
    asset.Setstatus(status);

    assetFile.seekp(0L, ios::end);
    assetFile.write(reinterpret_cast<char *>(&asset), sizeof(asset));
    assetFile.close();

    char currentTime[MAX_LENGTH], recNote[MAX_STRING_LENGTH];
    strcpy(currentTime, getCurrentDate());
    strcpy(recNote, "Asset added on ");
    strcat(recNote, currentTime);
    strcat(recNote, "\n");
    addNewRecord(idNum, type, recNote);
}
// check if asset is late
void checkIfLate(Asset item, int type)
{
    char rNoteL[MAX_STRING_LENGTH], rNoteR[MAX_STRING_LENGTH], currentDate[MAX_LENGTH];
    strcpy(currentDate, getCurrentDate());
    strcpy(rNoteL, "Asset is late on ");
    strcpy(rNoteR, "Asset is no longer reserved on ");
    strcat(rNoteL, currentDate);
    strcat(rNoteR, currentDate);
    strcat(rNoteL, "\n");
    strcat(rNoteR, "\n");

    long assetID = item.GetID();
    long recNum = searchRecord(assetID);
    Record aRecord = getRecord(recNum);

    int ifLate = -1;
    char status[MAX_LENGTH];

    if (type == 1)
    {
        ifLate = compareDates(item.GetreturnDate(), getCurrentDate());

        if  (ifLate == 1)
        {
            strcpy(status, "Late");
            item.Setstatus(status);

            Person person = getPerson(recNum);

            long itemID = item.GetID();

            for(int i=0; i<person.Getamount(); i++)
            {
                Asset asset = person.GetassetListMember(i);
                long idCmp = asset.GetID();

                if (itemID == idCmp)
                {
                    long assetNum = searchAssetByID(itemID);

                    person.SetassetList(item.GetID(), item.Getlocation(), item.GetassetType(), status,
                                         item.GetborrowDate(), item.GetreturnDate(), item.GetreservationDate(), i);

                    changeAsset(item, assetNum);
                    changePerson(person, recNum);

                    long recNum = searchRecord(itemID);
                    Record aRecord = getRecord(recNum);
                    aRecord.checkIfRecIsFull();
                    aRecord.addRecordNote(rNoteL);
                    changeRecord(aRecord, recNum);
                }
            }
        }
    }

    // see if the reservation has past
    else if (type ==2)
    {
        char clearReservation[MAX_LENGTH];
        ifLate = compareDates(item.GetreservationDate(),getCurrentDate());

        if  (ifLate == 1)
        {
            for(int z=0; z<MAX_LENGTH; z++)
                clearReservation[z] = '\0';

            item.SetreservationDate(clearReservation);

            Person person = getPerson(recNum);

            long itemID = item.GetID();

            for(int i=0; i<person.Getamount(); i++)
            {
                Asset asset = person.GetassetListMember(i);
                long idCmp = asset.GetID();

                if (itemID == idCmp)
                {
                    long assetNum = searchAssetByID(itemID);

                    person.SetassetList(item.GetID(), item.Getlocation(), item.GetassetType(), status,
                                         item.GetborrowDate(), item.GetreturnDate(), clearReservation, i);

                    changeAsset(item, assetNum);
                    changePerson(person, recNum);

                    long recNum = searchRecord(itemID);
                    aRecord.checkIfRecIsFull();
                    aRecord.addRecordNote(rNoteR);
                    changeRecord(aRecord, recNum);
                }
            }
        }
    }

}
// see what assets are available by type
void searchAvailableTypes(char* type)
{
    Asset asset;
    char* status;
    char correctType[MAX_LENGTH];
    strcpy(correctType, type);

    fstream assetFile;
    assetFile.open("AssetInfo.dat", ios::in|ios::out|ios::binary);
    if (!assetFile)
    {
        cout << "Error locating file. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    do {
        assetFile.read(reinterpret_cast<char *>(&asset), sizeof(asset));
        status = asset.Getstatus();
        char assetType[MAX_LENGTH];
        strcpy(assetType, asset.GetassetType());

        if (!(assetFile.eof()) && status[0] == 'A' && strcmp(assetType, correctType) == 0)
            asset.printInfo();
    } while(!(assetFile.eof()));

    assetFile.close();
}
//new function menu to get the history and the inventory status
void inventoryMenu()
{
    char assetType[MAX_LENGTH];
    int menuChoice;
    do{
        cout << "Would you like to view the:" << endl
            << "\t1. View inventory status of all assets" << endl
            << "\t2. View all available assets" << endl
            << "\t3. Search assets currently rented by person" << endl
            << "\t4. Exit" << endl;
        cin >> menuChoice;

        switch (menuChoice)
        {
        case 1:
            displayAllAssets();
            break;
        case 2:
            strcpy(assetType, getAssetType());
            searchAvailableTypes(assetType);
            break;
        case 3:
            displayAllPersons();
            break;
        default:
            break;
        }
    }
    while (menuChoice != 4);
}

void displayAllAssets()
{
    Asset asset;
    int counter = 0;
    int continueOrNo;

    fstream assetFile;
    assetFile.open("AssetInfo.dat", ios::in|ios::out|ios::binary);
    if (!assetFile)
    {
        cout << "Error locating file. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    do {
        assetFile.read(reinterpret_cast<char *>(&asset), sizeof(asset));
        if(!(assetFile.eof()))
        {

            asset.printInfo();
            counter++;

            if(counter == 4)
            {
                cout << "Do you wish to continue printing list? Enter '1' for Yes or '2' for No ";
                cin >> continueOrNo;
                if (continueOrNo == 1)
                    counter =0;
                else
                    break;
            }
        }
    } while(!(assetFile.eof()));

    assetFile.close();
}

long searchAssetByID(long num)
{
    Asset asset;
    bool found = false;
    long counter = 0;

    fstream assetFile;
    assetFile.open("AssetInfo.dat", ios::in|ios::out|ios::binary);
    if (!assetFile)
    {
        cout << "Error locating file. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    do {
        assetFile.read(reinterpret_cast<char *>(&asset), sizeof(asset));
        if(asset.GetID() == num)
        {
            found = true;
            break;
        }
        else
            counter++;
    } while(!(assetFile.eof()));

    assetFile.close();

    if (!found)
        counter = -1;

    return counter;
}

long searchAssetByStatusAndType(char* type, char st)
{
    Asset asset;
    bool found = false;
    long counter = 0;
    char* status;
    char correctType[MAX_LENGTH];
    strcpy(correctType, type);

    fstream assetFile;
    assetFile.open("AssetInfo.dat", ios::in|ios::out|ios::binary);
    if (!assetFile)
    {
        cout << "Error locating file. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    do {
        assetFile.read(reinterpret_cast<char *>(&asset), sizeof(asset));
        status = asset.Getstatus();
        char assetType[MAX_LENGTH];
        strcpy(assetType, asset.GetassetType());

        if(status[0] == st && strcmp(assetType, correctType) == 0)
        {
            found = true;
            break;
        }
        else
            counter++;
    } while(!(assetFile.eof()));

    assetFile.close();

    if (!found)
        counter = -1;

    return counter;
}

void deleteAsset()
{
    fstream assetFile;

    long idNum;
    cout << "\nEnter ID number of asset you wish to remove: ";
    cin >> idNum;
    long recNum = searchAssetByID(idNum);
    if (recNum == -1)
        cout << "\nAsset with ID number " << idNum << " could not be found." << endl;
    else
    {
        int totalRecNum = findAssetFileAmount();
        if (totalRecNum == 1)
        {
            remove("AssetInfo.dat"); // Deletes old file
            // Create new file
            assetFile.open("AssetInfo.dat", ios::out|ios::binary);
            cout << "\nCustomer's record has been deleted." << endl;
            cout << "\nThere are no more records left in the database." << endl;
            assetFile.close();
        }
        else
        {
            Asset asset;
            Asset oldAssets[totalRecNum];

            assetFile.open("AssetInfo.dat", ios::in|ios::out|ios::binary);
            if (!assetFile)
            {
                cout << "Error locating file. Exiting..." << endl;
                exit(EXIT_FAILURE);
            }

            for(int i=0; i<totalRecNum; i++)
            {
                assetFile.read(reinterpret_cast<char *>(&asset), sizeof(asset));
                oldAssets[i] = asset;
            }

            assetFile.close();
            remove("AssetInfo.dat");

            assetFile.open("AssetInfo.dat", ios::out|ios::binary);

            for(int j=0; j<totalRecNum; j++)
            {
                if (j != recNum)
                {
                    asset = oldAssets[j];
                    assetFile.write(reinterpret_cast<char *>(&asset), sizeof(asset));
                }
            }
            assetFile.close();
        }

        char currentDate[MAX_LENGTH], rNoteR[MAX_STRING_LENGTH];
        strcpy(currentDate, getCurrentDate());
        strcpy(rNoteR, "Asset was removed on ");
        strcat(rNoteR, currentDate);
        strcat(rNoteR, "\n");

        long recNum = searchRecord(idNum);
        Record aRecord = getRecord(recNum);
        aRecord.checkIfRecIsFull();
        aRecord.addRecordNote(rNoteR);
        changeRecord(aRecord, recNum);
    }
}

void changeAsset(Asset asset, long rNum)
{
    fstream assetFile;

    int totalRecNum = findAssetFileAmount();
    if (totalRecNum == 1)
    {
        assetFile.open("AssetInfo.dat", ios::in|ios::out|ios::binary);
        assetFile.write(reinterpret_cast<char *>(&asset), sizeof(asset));
        assetFile.close();
    }
    else
    {
        Asset tempAsset;
        Asset oldAssetList[totalRecNum];

        assetFile.open("AssetInfo.dat", ios::in|ios::out|ios::binary);
        if (!assetFile)
        {
            cout << "Error locating file. Exiting..." << endl;
            exit(EXIT_FAILURE);
        }

        for(int i=0; i<totalRecNum; i++)
        {
            assetFile.read(reinterpret_cast<char *>(&tempAsset), sizeof(tempAsset));
            oldAssetList[i] = tempAsset;
        }

        assetFile.seekp(0L, ios::beg);

        for(int j=0; j<totalRecNum; j++)
        {
            if (j != rNum)
            {
                tempAsset = oldAssetList[j];
                assetFile.write(reinterpret_cast<char *>(&tempAsset), sizeof(tempAsset));
            }
            else
                assetFile.write(reinterpret_cast<char *>(&asset), sizeof(asset));
        }
        assetFile.close();
    }
}

int findAssetFileAmount()
{
    Asset asset;
    int counter = 0;

    fstream assetFile;
    assetFile.open("AssetInfo.dat", ios::in|ios::out|ios::binary);
    if (!assetFile)
    {
        cout << "Error locating file. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    do {
        assetFile.read(reinterpret_cast<char *>(&asset), sizeof(asset));
        if (!(assetFile.eof()))
            counter++;
    } while(!(assetFile.eof()));

    assetFile.close();

    return counter;
}

int findAssetAvailableAmount(char* type)
{
    Asset asset;
    int counter = 0;
    char* status;
    char correctType[MAX_LENGTH];
    strcpy(correctType, type);

    fstream assetFile;
    assetFile.open("AssetInfo.dat", ios::in|ios::out|ios::binary);
    if (!assetFile)
    {
        cout << "Error locating file. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    do {
        assetFile.read(reinterpret_cast<char *>(&asset), sizeof(asset));
        status = asset.Getstatus();
        char assetType[MAX_LENGTH];
        strcpy(assetType, asset.GetassetType());

        if (!(assetFile.eof()) && status[0] == 'A' && strcmp(assetType, correctType) == 0)
            counter++;
    } while(!(assetFile.eof()));

    return counter;
}

Asset getAsset(long rNum)
{
    Asset asset;

    fstream assetFile;
    assetFile.open("AssetInfo.dat", ios::in|ios::out|ios::binary);
    if (!assetFile)
    {
        cout << "Error locating file. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    assetFile.seekg((rNum*sizeof(asset)), ios::beg);
    assetFile.read(reinterpret_cast<char *>(&asset), sizeof(asset));

    return asset;
}

Person getPerson(long rNum)
{
    Person aPerson;

    fstream personFile;
    personFile.open("PersonInfo.dat", ios::in|ios::out|ios::binary);
    if (!personFile)
    {
        cout << "Error locating file. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    personFile.seekg((rNum*sizeof(aPerson)), ios::beg);
    personFile.read(reinterpret_cast<char *>(&aPerson), sizeof(aPerson));

    personFile.close();

    return aPerson;
}

Person getPersonalInfo()
{
    int choice;
    bool conditionA = false, conditionB = true, conditionC = false;
    Person aPerson;
    char firstN[MAX_LENGTH], lastN[MAX_LENGTH], id[MAX_LENGTH], phoneN[MAX_LENGTH], email[MAX_LENGTH], department[MAX_LENGTH], user[MAX_LENGTH];
    string us = "USER";
    strncpy(user, us.c_str(), MAX_LENGTH);

    cout << "Faculty (Enter 1) or Student (Enter 2)?: ";
    do {
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.sync();
            cout << "\nInvalid input. Please enter either 1 or 2." << endl;
        }
        else if (choice < 1 || choice > 2)
            cout << "\nInvalid input. Please enter either 1 or 2." << endl;
        else
            conditionA = true;
    } while (!conditionA);

    cin.ignore();
    cin.sync();

    if (choice == 2)
    {
        string st = "Student";
        strncpy(department, st.c_str(), MAX_LENGTH);
    }
    else
    {
        cout << "Enter Department of Faculty: ";
        do {
            cin.getline(department, MAX_LENGTH);
            for(int i=0; i<MAX_LENGTH; i++)
            {
                if (department[i] != '\0')
                    department[i] = toupper(department[i]);

            }
            if ( strcmp(department, user) == 0)
            {
                conditionB = false;
                cout << "Cannot enter USER as a department, please try again:" << endl;
            }
            else
                conditionB = true;
        } while(!conditionB);
    }
    cout << "Enter First Name: ";
    cin.getline(firstN, MAX_LENGTH);

    cout << "Enter Last Name: ";
    cin.getline(lastN, MAX_LENGTH);

    cout << "Enter ID Number: ";
    do {
        cin.getline(id, MAX_LENGTH);
        for(int i=0; i<MAX_LENGTH; i++)
        {
            if (id[i] != '\0')
                id[i] = toupper(id[i]);

        }
        if ( strcmp(id, user) == 0)
        {
            conditionB = false;
            cout << "Cannot enter USER as an ID, please try again:" << endl;
        }
        long recNum = searchPerson(id);
        if (recNum != -1)
            cout << "A person already exists for that ID, please try again:" << endl;
        else
            conditionC = true;
    } while(!conditionC);

    cout << "Enter Phone Number: ";
    cin.getline(phoneN, MAX_LENGTH);

    cout << "Enter Email: ";
    cin.getline(email, MAX_LENGTH);

    aPerson.Setdepartment(department);
    aPerson.SetfirstName(firstN);
    aPerson.SetlastName(lastN);
    aPerson.SetcollegeID(id);
    aPerson.SetphoneNum(phoneN);
    aPerson.Setemail(email);

    fstream personFile;
    personFile.open("PersonInfo.dat", ios::in | ios::out | ios::app | ios::binary);
    if (!personFile)
    {
        cout << "Error locating file. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    personFile.write(reinterpret_cast<char *>(&aPerson), sizeof(aPerson));
    personFile.close();

    return aPerson;
}

void getUserPersonalInfo()
{
    Person user;
    char firstN[MAX_LENGTH], lastN[MAX_LENGTH], temp[MAX_LENGTH], department[MAX_LENGTH];
    string us = "USER";
    strncpy(department, us.c_str(), MAX_LENGTH);

    for (int i=0; i<MAX_LENGTH; i++)
        temp[i] = '\0';

    cout << "Enter First Name: ";
    cin.getline(firstN, MAX_LENGTH);

    cout << "Enter Last Name: ";
    cin.getline(lastN, MAX_LENGTH);

    user.Setdepartment(department);
    user.SetfirstName(firstN);
    user.SetlastName(lastN);
    user.SetcollegeID(department);
    user.SetphoneNum(temp);
    user.Setemail(temp);

    fstream personFile;
    personFile.open("PersonInfo.dat", ios::in | ios::out | ios::app | ios::binary);
    if (!personFile)
    {
        cout << "Error locating file. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    personFile.write(reinterpret_cast<char *>(&user), sizeof(user));
    personFile.close();
}

long searchPerson(char* id)
{
    Person aPerson;
    bool found = false;
    long counter = 0;

    fstream personFile;
    personFile.open("PersonInfo.dat", ios::in | ios::out | ios::binary);
    if (!personFile)
    {
        cout << "Error locating file. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    do {
        personFile.read(reinterpret_cast<char *>(&aPerson), sizeof(aPerson));
        if(strcmp(aPerson.GetcollegeID(), id) == 0)
        {
            found = true;
            break;
        }
        else
            counter++;
    } while(!(personFile.eof()));

    personFile.close();

    if (!found)
        counter = -1;

    return counter;
}

void changePerson(Person aPerson, long rNum)
{
    fstream personFile;

    int totalRecNum = findPersonFileAmount();
    if (totalRecNum == 1)
    {
        personFile.open("PersonInfo.dat", ios::in|ios::out|ios::binary);
        personFile.write(reinterpret_cast<char *>(&aPerson), sizeof(aPerson));
        personFile.close();
    }
    else
    {
        Person tempPerson;
        Person oldPersonList[totalRecNum];

        personFile.open("PersonInfo.dat", ios::in|ios::out|ios::binary);
        if (!personFile)
        {
            cout << "Error locating file. Exiting..." << endl;
            exit(EXIT_FAILURE);
        }

        for(int i=0; i<totalRecNum; i++)
        {
            personFile.read(reinterpret_cast<char *>(&tempPerson), sizeof(tempPerson));
            oldPersonList[i] = tempPerson;
        }

        personFile.seekp(0L, ios::beg);

        for(int j=0; j<totalRecNum; j++)
        {
            if (j != rNum)
            {
                tempPerson = oldPersonList[j];
                personFile.write(reinterpret_cast<char *>(&tempPerson), sizeof(tempPerson));
            }
            else
                personFile.write(reinterpret_cast<char *>(&aPerson), sizeof(aPerson));
        }
        personFile.close();
    }
}

int findPersonFileAmount()
{
    Person aPerson;
    int counter = 0;

    fstream personFile;
    personFile.open("PersonInfo.dat", ios::in | ios::out | ios::binary);
    if (!personFile)
    {
        cout << "Error locating file. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    do {
        personFile.read(reinterpret_cast<char *>(&aPerson), sizeof(aPerson));
        if (!(personFile.eof()))
            counter++;
    } while(!(personFile.eof()));

    personFile.close();

    return counter;
}

void displayAllPersons()
{
    Person aPerson;
    int counter = 0;
    int continueOrNo;

    fstream personFile;
    personFile.open("PersonInfo.dat", ios::in|ios::out|ios::binary);
    if (!personFile)
    {
        cout << "Error locating file. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    do {
        personFile.read(reinterpret_cast<char *>(&aPerson), sizeof(aPerson));
        if(!(personFile.eof()))
        {
            aPerson.printInfo();
            counter++;

            if(counter == 4)
            {
                cout << "Do you wish to continue printing list? Enter '1' for Yes or '2' for No ";
                cin >> continueOrNo;
                if (continueOrNo == 1)
                    counter =0;
                else
                    break;
            }
        }
    } while(!(personFile.eof()));

    personFile.close();
}

char* getCurrentDate()
{
    time_t currentTime;
    struct tm * timeinfo;

    time(&currentTime);
    timeinfo = localtime(&currentTime);

    char time[MAX_LENGTH];

    for(int i=10; i<MAX_LENGTH; i++)
        time[i] = '\0';

    strftime (time, MAX_LENGTH, "%m/%d/%Y", timeinfo);

    return time;
}

char* getFutureDate(char* date, int num)
{
    char mon[3], day[3], year[5];
    mon[0] = date[0];
    mon[1] = date[1];
    mon[2] = '\0';
    day[0] = date[3];
    day[1] = date[4];
    day[2] = '\0';
    year[0] = date[6];
    year[1] = date[7];
    year[2] = date[8];
    year[3] = date[9];
    year[4] = '\0';

    int m = atoi(mon);
    int d = atoi(day);
    int y = atoi(year);

    tm time = {};
    time.tm_year = y-1900;
    time.tm_mon  = m-1;
    time.tm_mday = d;

    time.tm_mday += num;
    mktime(&time);

    char futureDate[MAX_LENGTH];

    for(int i=10; i<MAX_LENGTH; i++)
        futureDate[i] = '\0';

    strftime (futureDate, MAX_LENGTH, "%m/%d/%Y", &time);

    return futureDate;
}

int compareDates(char* dateCheck, char* dateCmp)
{
    int value;
    char monCheck[3], dayCheck[3], yearCheck[5];
    monCheck[0] = dateCheck[0];
    monCheck[1] = dateCheck[1];
    monCheck[2] = '\0';
    dayCheck[0] = dateCheck[3];
    dayCheck[1] = dateCheck[4];
    dayCheck[2] = '\0';
    yearCheck[0] = dateCheck[6];
    yearCheck[1] = dateCheck[7];
    yearCheck[2] = dateCheck[8];
    yearCheck[3] = dateCheck[9];
    yearCheck[4] = '\0';

    char monCmp[3], dayCmp[3], yearCmp[5];
    monCmp[0] = dateCmp[0];
    monCmp[1] = dateCmp[1];
    monCmp[2] = '\0';
    dayCmp[0] = dateCmp[3];
    dayCmp[1] = dateCmp[4];
    dayCmp[2] = '\0';
    yearCmp[0] = dateCmp[6];
    yearCmp[1] = dateCmp[7];
    yearCmp[2] = dateCmp[8];
    yearCmp[3] = dateCmp[9];
    yearCmp[4] = '\0';

    int mCh = atoi(monCheck);
    int dCh = atoi(dayCheck);
    int yCh = atoi(yearCheck);
    int mCmp = atoi(monCmp);
    int dCmp = atoi(dayCmp);
    int yCmp = atoi(yearCmp);

    if(yCh > yCmp)
        value = 1;
    else if(yCh < yCmp)
        value = -1;
    else
    {
        if(mCh > mCmp)
            value = 1;
        else if(mCh < mCmp)
            value = -1;
        else
        {
            if(dCh > dCmp)
                value = 1;
            else if(dCh < dCmp)
                value = -1;
            else if (dCh == dCmp)
                value = 0;
        }
    }

    return value;
}

void addNewRecord(long id, char* type, char* note)
{
    Record newRecord;

    char rNote[MAX_STRING_LENGTH];
    strcpy(rNote, note);

    fstream recordFile;
    recordFile.open("RecordInfo.dat", ios::in|ios::out|ios::app|ios::binary);
    if (!recordFile)
    {
        cout << "Error locating file. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    newRecord.SetID(id);
    newRecord.SetassetType(type);
    newRecord.addRecordNote(rNote);

    recordFile.write(reinterpret_cast<char *>(&newRecord), sizeof(newRecord));

    recordFile.close();
}

long searchRecord(long id)
{
    Record record;
    bool found = false;
    long counter = 0;

    fstream recordFile;
    recordFile.open("RecordInfo.dat", ios::in|ios::out|ios::app|ios::binary);
    if (!recordFile)
    {
        cout << "Error locating file. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    do {
        recordFile.read(reinterpret_cast<char *>(&record), sizeof(record));

        if(record.GetID() == id)
        {
            found = true;
            break;
        }
        else
            counter++;
    } while(!(recordFile.eof()));

    recordFile.close();

    if (!found)
        counter = -1;

    return counter;
}

Record getRecord(long rNum)
{
    Record record;

    fstream recordFile;
    recordFile.open("RecordInfo.dat", ios::in|ios::out|ios::app|ios::binary);
    if (!recordFile)
    {
        cout << "Error locating file. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    recordFile.seekg((rNum*sizeof(record)), ios::beg);
    recordFile.read(reinterpret_cast<char *>(&record), sizeof(record));

    return record;
}

void changeRecord(Record aRecord, long rNum)
{
    fstream recordFile;

    int totalRecNum = findRecordFileAmount();
    if (totalRecNum == 1)
    {
        recordFile.open("RecordInfo.dat", ios::in|ios::out|ios::binary);
        recordFile.write(reinterpret_cast<char *>(&aRecord), sizeof(aRecord));

        recordFile.close();
    }
    else
    {
        Record tempRecord;
        Record oldRecordList[totalRecNum];

        recordFile.open("RecordInfo.dat", ios::in|ios::out|ios::binary);
        if (!recordFile)
        {
            cout << "Error locating file. Exiting..." << endl;
            exit(EXIT_FAILURE);
        }

        for(int i=0; i<totalRecNum; i++)
        {
            recordFile.read(reinterpret_cast<char *>(&tempRecord), sizeof(tempRecord));
            oldRecordList[i] = tempRecord;
        }

        recordFile.seekp(0L, ios::beg);

        for(int j=0; j<totalRecNum; j++)
        {
            if (j != rNum)
            {
                tempRecord = oldRecordList[j];
                recordFile.write(reinterpret_cast<char *>(&tempRecord), sizeof(tempRecord));
            }
            else
            {
                recordFile.write(reinterpret_cast<char *>(&aRecord), sizeof(aRecord));
            }
        }
        recordFile.close();
    }
}

int findRecordFileAmount()
{
    Record record;
    int counter = 0;

    fstream recordFile;
    recordFile.open("RecordInfo.dat", ios::in|ios::out|ios::binary);
    if (!recordFile)
    {
        cout << "Error locating file. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    do {
        recordFile.read(reinterpret_cast<char *>(&record), sizeof(record));
        if (!(recordFile.eof()))
            counter++;
    } while(!(recordFile.eof()));

    recordFile.close();

    return counter;
}

void displayAllRecords()
{
    Record record;

    int counter = 0;
    int continueOrNo;


    fstream recordFile;
    recordFile.open("RecordInfo.dat", ios::in|ios::out|ios::binary);
    if (!recordFile)
    {
        cout << "Error locating file. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    do {
        recordFile.read(reinterpret_cast<char *>(&record), sizeof(record));
        if(!(recordFile.eof()))
        {
            record.printInfo();
            counter++;

            if(counter == 4)
            {
                cout << "Do you wish to continue printing list? Enter '1' for Yes or '2' for No ";
                cin >> continueOrNo;
                if (continueOrNo == 1)
                    counter =0;
                else
                    break;
            }
        }
    } while(!(recordFile.eof()));

    recordFile.close();
}

void addOrRemoveAsset()
{
    int addOrRemove;
    bool condition = false;
    cout << "\nDo you wish to add (enter 1) or remove (enter 2) an asset? (enter 3 to cancel): ";
    do {
        cin >> addOrRemove;
        if (cin.fail())
        {
            cin.clear();
            cin.sync();
            cout << "\nInvalid input. Please enter either 1, 2 or 3." << endl;
        }
        else if (addOrRemove < 1 || addOrRemove > 3)
            cout << "\nInvalid input. Please enter either 1, 2 or 3." << endl;
        else
            condition = true;
    } while (!condition);

    if (addOrRemove == 1)
        addNewAsset();
    else if (addOrRemove == 2)
        deleteAsset();
}

void inputReservationRequest()
{
    int amountToRsv, daysToRsv;
    bool conditionA = false, conditionB = false, conditionC = false;
    char user[MAX_LENGTH];
    char colID[MAX_LENGTH], assetType[MAX_LENGTH], temp[MAX_LENGTH], rsvD[MAX_LENGTH], status[MAX_LENGTH];
    string st = "Reserved";
    strncpy(status, st.c_str(), MAX_LENGTH);
    string us = "USER";
    strncpy(user, us.c_str(), MAX_LENGTH);

    cout << "\nPlease enter the college ID of the client who wishes to make\nthe reservation request (Press Enter to exit):" << endl;

    do {
        cin.getline(colID, MAX_LENGTH);
        for(int i=0; i<MAX_LENGTH; i++)
        {
            if (colID[i] != '\0')
                colID[i] = toupper(colID[i]);

        }
        if ( strcmp(colID, user) == 0)
        {
            cout << "Cannot enter USER as an ID, please try again:" << endl;
        }
        long recNum = searchPerson(colID);
        if (recNum != -1)
            cout << "A person already exists for that ID, please try again:" << endl;
        else
            conditionC = true;
    } while(!conditionC);

    if (strlen(colID) != 0)
    {
        long recNum = searchPerson(colID);
        Person reserver;
        if (recNum == -1)
        {
            cout << "ID of client not found, please enter contact information:" << endl;
            reserver = getPersonalInfo();
            recNum = searchPerson(reserver.GetcollegeID());
        }
        else
        {
            cout << "ID of client has been found" << endl;
            reserver = getPerson(recNum);
        }

        strcpy(assetType, getAssetType());

        int currentAvailableNum = findAssetAvailableAmount(assetType);
        cout << "Current Available Assets: " << currentAvailableNum << endl;

        if(currentAvailableNum == 0)
            cout << "There are not enough available assets of that type to reserve" << endl;
        else
        {
            int reservedAmt = reserver.Getamount();
            cout << "How many assets does the client wish to reserve?\n(MAX is 30, The client already has " << reservedAmt << " assets):" << endl;
            do {
                cin >> amountToRsv;
                if (cin.fail())
                {
                    cin.clear();
                    cin.sync();
                    cout << "\nInvalid input. Please enter a non-negative number smaller than " << (MAX_LIMIT_ASSET-reservedAmt) << endl;
                }
                else if (amountToRsv < 1 || amountToRsv > (MAX_LIMIT_ASSET-reservedAmt))
                    cout << "\nInvalid input. Please enter a non-negative number smaller than " << (MAX_LIMIT_ASSET-reservedAmt) << endl;
                else if (amountToRsv > currentAvailableNum)
                {
                    cout << "\nInvalid input. There are not enough available assets to borrow" << endl
                        << "Enter a non-negative number smaller than " << currentAvailableNum << endl;
                }
                else
                    conditionA = true;
            } while (!conditionA);

            cout << "For how many days will the asset(s) be reserved for? (MAX is 180):" << endl;
            do {
                cin >> daysToRsv;
                if (cin.fail())
                {
                    cin.clear();
                    cin.sync();
                    cout << "\nInvalid input. Please enter a non-negative number smaller than " << MAX_LIMIT_DATE << endl;
                }
                else if (daysToRsv < 1 || daysToRsv > MAX_LIMIT_DATE)
                    cout << "\nInvalid input. Please enter a non-negative number smaller than " << MAX_LIMIT_DATE << endl;
                else
                    conditionB = true;
            } while (!conditionB);

            strcpy(temp, getCurrentDate());
            strcpy(rsvD, getFutureDate(temp, daysToRsv));

            char rNoteR1[MAX_STRING_LENGTH], rNoteR2[MAX_STRING_LENGTH];
            strcpy(rNoteR1, "Asset was reserved by client: ");
            strcat(rNoteR1, reserver.GetfirstName());
            strcpy(rNoteR2, " ");
            strcat(rNoteR1, rNoteR2);
            strcat(rNoteR1, reserver.GetlastName());
            strcpy(rNoteR2, " on ");
            strcat(rNoteR1, rNoteR2);
            strcat(rNoteR1, temp);
            strcat(rNoteR1, "\n");


            for (int i=0; i<amountToRsv; i++)
            {
                long assetNum = searchAssetByStatusAndType(assetType, 'A');
                Asset asset = getAsset(assetNum);

                Person rsver = getPerson(recNum);
                int amount = rsver.Getamount();

                rsver.SetassetList(asset.GetID(), asset.Getlocation(), asset.GetassetType(), status,
                                    asset.GetborrowDate(), asset.GetreturnDate(), rsvD, amount);

                rsver.Setamount(amount+1);

                asset.Setstatus(status);
                asset.SetreservationDate(rsvD);

                changeAsset(asset, assetNum);
                changePerson(rsver, recNum);

                long recNum = searchRecord(asset.GetID());
                Record aRecord = getRecord(recNum);
                aRecord.checkIfRecIsFull();
                aRecord.addRecordNote(rNoteR1);
                changeRecord(aRecord, recNum);
            }

            cout << endl << amountToRsv << " Assets of type ";
            for(int j=0; j<MAX_LENGTH; j++)
                cout << assetType[j];
            cout << "\nhave been reserved." << endl;
            cout << "The asset(s) needs to be borrowed by:" << endl;
            for(int k=0; k<MAX_LENGTH; k++)
                cout << rsvD[k];
            cout << endl;
        }
    }
}

void inputBorrowRequest()
{
    int amountToBrw, daysToBrw;
    bool conditionA = false, conditionB = false, conditionC = false, rsvCondition = false, typeCondition = false;
    char user[MAX_LENGTH];
    char colID[MAX_LENGTH], assetType[MAX_LENGTH], borrowD[MAX_LENGTH], returnD[MAX_LENGTH],
         borrowL[MAX_LENGTH], rsvD[MAX_LENGTH], status[MAX_LENGTH], checkType[MAX_LENGTH], checkStatus[MAX_LENGTH];

    string st = "In Use";
    strncpy(status, st.c_str(), MAX_LENGTH);

    string us = "USER";
    strncpy(user, us.c_str(), MAX_LENGTH);

    cout << "\nPlease enter the college ID of the client who wishes to make the borrow request (Press Enter to exit):" << endl;
    do {
        cin.getline(colID, MAX_LENGTH);
        for(int i=0; i<MAX_LENGTH; i++)
        {
            if (colID[i] != '\0')
                colID[i] = toupper(colID[i]);

        }
        if ( strcmp(colID, user) == 0)
        {
            cout << "Cannot enter USER as an ID, please try again:" << endl;
        }
        else
            conditionC = true;
    } while(!conditionC);

    if (strlen(colID) != 0)
    {
        long recNum = searchPerson(colID);
        Person borrower;
        if (recNum == -1)
        {
            cout << "ID of client not found, please enter contact information:" << endl;
            borrower = getPersonalInfo();
            recNum = searchPerson(borrower.GetcollegeID());
        }
        else
        {
            cout << "ID of client has been found" << endl;
            borrower = getPerson(recNum);
            for(int i=0; i<borrower.Getamount(); i++)
            {
                Asset asset = borrower.GetassetListMember(i);
                strcpy(rsvD, asset.GetreservationDate());
                if (rsvD[0] != '\0')
                    rsvCondition = true;
            }
        }

        if (rsvCondition)
        {
            cout << "A reservation has been found for this client" << endl;

            strcpy(assetType, getAssetType());

            int rsvCounter = 0;
            for(int i=0; i<borrower.Getamount(); i++)
            {
                Asset asset = borrower.GetassetListMember(i);
                strcpy(checkType, asset.GetassetType());
                strcpy(checkStatus, asset.Getstatus());
                if (strcmp(assetType, checkType) == 0 && checkStatus[0] == 'R')
                {
                    typeCondition = true;
                    rsvCounter++;
                }
            }
            if (!typeCondition)
                cout << "\nCould not find any reservations for that asset type" << endl;
            else
            {
                typeCondition = true;
                cout << "\nFor how many days will the asset(s) be borrowed for? (MAX is 180):" << endl;
                do {
                    cin >> daysToBrw;
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.sync();
                        cout << "\nInvalid input. Please enter a non-negative number smaller than " << MAX_LIMIT_DATE << endl;
                    }
                    else if (daysToBrw < 1 || daysToBrw > MAX_LIMIT_DATE)
                        cout << "\nInvalid input. Please enter a non-negative number smaller than " << MAX_LIMIT_DATE << endl;
                    else
                        conditionB = true;
                } while (!conditionB);

                cout << "Please enter the location where the client will use the asset(s):" << endl;
                cin.clear();
                cin.sync();
                cin.getline(borrowL, MAX_LENGTH);

                strcpy(borrowD, getCurrentDate());
                strcpy(returnD, getFutureDate(borrowD, daysToBrw));
                for(int i=0; i<MAX_LENGTH; i++)
                    rsvD[i] = '\0';

                char rNoteR1[MAX_STRING_LENGTH], rNoteR2[MAX_STRING_LENGTH];
                strcpy(rNoteR1, "Asset was borrowed by client: ");
                strcat(rNoteR1, borrower.GetfirstName());
                strcpy(rNoteR2, " ");
                strcat(rNoteR1, rNoteR2);
                strcat(rNoteR1, borrower.GetlastName());
                strcpy(rNoteR2, " on ");
                strcat(rNoteR1, rNoteR2);
                strcat(rNoteR1, borrowD);
                strcat(rNoteR1, "\n");

                for(int i=0; i<borrower.Getamount(); i++)
                {
                    Asset asset = borrower.GetassetListMember(i);
                    strcpy(checkType, asset.GetassetType());
                    strcpy(checkStatus, asset.Getstatus());
                    if (strcmp(assetType, checkType) == 0 && checkStatus[0] == 'R')
                    {
                        long assetID = asset.GetID();
                        long assetNum = searchAssetByID(assetID);

                        Person brwer = getPerson(recNum);

                        brwer.SetassetList(asset.GetID(), borrowL, asset.GetassetType(), status, borrowD, returnD, rsvD, i);

                        asset.Setstatus(status);
                        asset.Setlocation(borrowL);
                        asset.SetborrowDate(borrowD);
                        asset.SetreturnDate(returnD);
                        asset.SetreservationDate(rsvD);

                        changeAsset(asset, assetNum);
                        changePerson(brwer, recNum);

                        long recNum = searchRecord(assetID);
                        Record aRecord = getRecord(recNum);
                        aRecord.checkIfRecIsFull();
                        aRecord.addRecordNote(rNoteR1);
                        changeRecord(aRecord, recNum);
                    }
                }
                amountToBrw = rsvCounter;
            }
        }
        else
        {
            typeCondition = true;
            int amountBorrowed = borrower.Getamount();
            strcpy(assetType, getAssetType());

            int currentAvailableNum = findAssetAvailableAmount(assetType);
            cout << "Current Available Assets: " << currentAvailableNum << endl;

            if(currentAvailableNum == 0)
                cout << "There are not enough available assets of that type to borrow" << endl;
            else
            {
                cout << "How many assets does the client wish to borrow?\n(MAX is 30, the client has already has " << amountBorrowed << " assets):" << endl;
                do {
                    cin >> amountToBrw;
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.sync();
                        cout << "\nInvalid input. Please enter a non-negative number smaller than " << (MAX_LIMIT_ASSET-amountBorrowed) << endl;
                    }
                    else if (amountToBrw < 1 || amountToBrw > (MAX_LIMIT_ASSET-amountBorrowed))
                        cout << "\nInvalid input. Please enter a non-negative number smaller than " << (MAX_LIMIT_ASSET-amountBorrowed) << endl;
                    else if (amountToBrw > currentAvailableNum)
                    {
                        cout << "\nInvalid input. There are not enough available assets to borrow" << endl
                             << "Enter a non-negative number smaller than " << currentAvailableNum << endl;
                    }
                    else
                        conditionA = true;
                } while (!conditionA);

                cout << "For how many days will the asset(s) be borrowed for? (MAX is 180):" << endl;
                do {
                    cin >> daysToBrw;
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.sync();
                        cout << "\nInvalid input. Please enter a non-negative number smaller than " << MAX_LIMIT_DATE << endl;
                    }
                    else if (daysToBrw < 1 || daysToBrw > MAX_LIMIT_DATE)
                        cout << "\nInvalid input. Please enter a non-negative number smaller than " << MAX_LIMIT_DATE << endl;
                    else
                        conditionB = true;
                } while (!conditionB);

                cout << "Please enter the location where the client will use the asset(s):" << endl;
                cin.clear();
                cin.sync();
                cin.getline(borrowL, MAX_LENGTH);

                strcpy(borrowD, getCurrentDate());
                strcpy(returnD, getFutureDate(borrowD, daysToBrw));

                char rNoteR1[MAX_STRING_LENGTH], rNoteR2[MAX_STRING_LENGTH];
                strcpy(rNoteR1, "Asset was borrowed by client: ");
                strcat(rNoteR1, borrower.GetfirstName());
                strcpy(rNoteR2, " ");
                strcat(rNoteR1, rNoteR2);
                strcat(rNoteR1, borrower.GetlastName());
                strcpy(rNoteR2, " on ");
                strcat(rNoteR1, rNoteR2);
                strcat(rNoteR1, borrowD);
                strcat(rNoteR1, "\n");

                for (int i=0; i<amountToBrw; i++)
                {
                    long assetNum = searchAssetByStatusAndType(assetType, 'A');
                    Asset asset = getAsset(assetNum);

                    Person brwer = getPerson(recNum);
                    int amount = brwer.Getamount();

                    brwer.SetassetList(asset.GetID(), borrowL, asset.GetassetType(), status, borrowD, returnD, asset.GetreservationDate(), amount);
                    brwer.Setamount(amount+1);

                    asset.Setstatus(status);
                    asset.Setlocation(borrowL);
                    asset.SetborrowDate(borrowD);
                    asset.SetreturnDate(returnD);

                    changeAsset(asset, assetNum);
                    changePerson(brwer, recNum);

                    long recNum = searchRecord(asset.GetID());
                    Record aRecord = getRecord(recNum);
                    aRecord.checkIfRecIsFull();
                    aRecord.addRecordNote(rNoteR1);
                    changeRecord(aRecord, recNum);
                }
            }
        }
        if (typeCondition)
        {
            cout << endl << amountToBrw << " Assets of type ";
            for(int j=0; j<MAX_LENGTH; j++)
                cout << assetType[j];
            cout << "\nhave been borrowed." << endl;
            cout << "The borrow Date was:" << endl;
            for(int j=0; j<MAX_LENGTH; j++)
                cout << borrowD[j];
            cout << endl;
            cout << "The asset(s) needs to be returned by:" << endl;
            for(int k=0; k<MAX_LENGTH; k++)
                cout << returnD[k];
            cout << endl;
        }
    }
}

void inputReturnRequest()
{
    bool conditionA = false, conditionB = false, conditionC = false, conditionD = false;
    char colID[MAX_LENGTH], status[MAX_LENGTH], statusCheck[MAX_LENGTH], borrowL[MAX_LENGTH],
         temp[MAX_LENGTH], user[MAX_LENGTH];
    int assetCount = 0, returnChoice, ifBroken, lateCounter = 0;
    Asset returnList[MAX_LIMIT_ASSET];
    long recNum, returnID;
    string us = "USER";
    strncpy(user, us.c_str(), MAX_LENGTH);

    Person returner;

    cout << "\nPlease enter the college ID of the client who wishes to make the return request (Press Enter to exit):" << endl;
    do {
        cin.getline(colID, MAX_LENGTH);
        for(int i=0; i<MAX_LENGTH; i++)
        {
            if (colID[i] != '\0')
                colID[i] = toupper(colID[i]);

        }
        if ( strcmp(colID, user) == 0)
        {
            cout << "Cannot enter USER as an ID, please try again:" << endl;
        }
        else
            conditionA = true;
    } while(!conditionA);

    if (strlen(colID) != 0)
    {
        recNum = searchPerson(colID);
        if (recNum == -1)
            cout << "\nID of client not found, please enter contact information:" << endl;
        else
        {
            cout << "\nID of client has been found" << endl;
            returner = getPerson(recNum);
            for(int i=0; i<returner.Getamount(); i++)
            {
                Asset asset = returner.GetassetListMember(i);
                strcpy(statusCheck, asset.Getstatus());
                if (statusCheck[0] == 'I' || statusCheck[0] == 'L')
                {
                    returnList[assetCount] = asset;
                    assetCount++;
                }
            }
        }
    }

    if (assetCount != 0)
    {
        cout << "\nHere is a list of all Returnable Assets:" << endl;
        for (int i=0; i<assetCount; i++)
            returnList[i].printInfo();

        for (int i=0; i<assetCount; i++)
        {
            strcpy(statusCheck, returnList[i].Getstatus());
            if (statusCheck[0] == 'L')
                lateCounter++;
        }
        cout << "There are " << assetCount << " assets, of which " << lateCounter << " are late" << endl
             << "\nDo you wish to return all assets above listed (enter 1)\nor return a specific asset (enter 2)?\n(Press 3 to quit): ";
        do {
            cin >> returnChoice;
            if (cin.fail())
            {
                cin.clear();
                cin.sync();
                cout << "\nInvalid input. Please enter a number between 1 to 3." << endl;
            }
            else if (returnChoice < 1 || returnChoice > 3)
                cout << "\nInvalid input. Please enter a number between 1 to 3." << endl;
            else
                conditionB = true;
        } while (!conditionB);

        if (returnChoice != 3)
        {
            if(returnChoice == 1)
            {
                cout << "Please enter the location where the assets will be returned to:" << endl;
                cin.ignore();
                cin.sync();
                cin.getline(borrowL, MAX_LENGTH);

                for (int i=0; i<MAX_LENGTH; i++)
                    temp[i] = '\0';

                char rNoteR1[MAX_STRING_LENGTH], rNoteR2[MAX_STRING_LENGTH], currentDate[MAX_LENGTH];
                strcpy(currentDate, getCurrentDate());
                strcpy(rNoteR1, "Asset was returned by client: ");
                strcat(rNoteR1, returner.GetfirstName());
                strcpy(rNoteR2, " ");
                strcat(rNoteR1, rNoteR2);
                strcat(rNoteR1, returner.GetlastName());
                strcpy(rNoteR2, " on ");
                strcat(rNoteR1, rNoteR2);
                strcat(rNoteR1, currentDate);
                strcat(rNoteR1, "\n");
                char recNoteStatus[MAX_STRING_LENGTH], recNoteTiming[MAX_STRING_LENGTH];

                for (int j=0; j<assetCount; j++)
                {
                    cout << "Is asset: " << returnList[j].GetID() << "\ndamaged, broken or malfunctioning? (enter 1, other wise enter 0)" << endl;
                    do {
                        cin >> ifBroken;
                        if (cin.fail())
                        {
                            cin.clear();
                            cin.sync();
                            cout << "\nInvalid input. Please enter either 0 or 1" << endl;
                        }
                        else if (ifBroken < 0 || ifBroken > 1)
                            cout << "\nInvalid input. Please enter either 0 or 1" << endl;
                        else
                            conditionD = true;
                    } while (!conditionD);

                    if (ifBroken)
                    {
                        string st = "Broken";
                        strncpy(status, st.c_str(), MAX_LENGTH);
                        strcpy (recNoteStatus, "It was returned broken");
                    }
                    else
                    {
                        string st = "Available";
                        strncpy(status, st.c_str(), MAX_LENGTH);
                        strcpy (recNoteStatus, "It was returned safely");
                    }

                    strcpy(statusCheck, returnList[j].Getstatus());
                    if (statusCheck[0] == 'L')
                        strcpy (recNoteTiming, " and it was returned late");
                    else
                        strcpy (recNoteTiming, " and it was returned on time");

                    strcat(recNoteStatus, recNoteTiming);
                    strcat(recNoteStatus, "\n");

                    long assetNum = searchAssetByID(returnList[j].GetID());
                    Asset asset = getAsset(assetNum);

                    asset.Setstatus(status);
                    asset.Setlocation(borrowL);
                    asset.SetborrowDate(temp);
                    asset.SetreturnDate(temp);
                    asset.SetreservationDate(temp);

                    changeAsset(asset, assetNum);

                    long recNum = searchRecord(asset.GetID());
                    Record aRecord = getRecord(recNum);
                    aRecord.checkIfRecIsFull();
                    aRecord.addRecordNote(rNoteR1);
                    aRecord.addRecordNote(recNoteStatus);
                    changeRecord(aRecord, recNum);
                }

                Person rtner = getPerson(recNum);
                rtner.removeAllAssetsFromList();
                changePerson(rtner, recNum);

                cout << "\nAll assets has been returned, with " << lateCounter << " of them being late" << endl;
            }
            else
            {
                cout << "Enter the asset ID the client wishes to return: " << endl;
                do {
                    cin >> returnID;
                    cin.clear();
                    cin.sync();
                    for (int i=0; i<assetCount; i++)
                    {
                        if (returnList[i].GetID() == returnID)
                            conditionC = true;
                    }
                    if(!conditionC)
                        cout << "Could not find asset with that ID, please try again:" << endl;
                } while (!conditionC);

                cout << "Please enter the location where the asset will be returned to:" << endl;
                cin.getline(borrowL, MAX_LENGTH);

                cout << "Is the asset damaged, broken or malfunctioning? (enter 1, other wise enter 0)" << endl;
                do {
                    cin >> ifBroken;
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.sync();
                        cout << "\nInvalid input. Please enter either 0 or 1" << endl;
                    }
                    else if (ifBroken < 0 || ifBroken > 1)
                        cout << "\nInvalid input. Please enter either 0 or 1" << endl;
                    else
                        conditionD = true;
                } while (!conditionD);

                char rNoteR1[MAX_STRING_LENGTH], rNoteR2[MAX_STRING_LENGTH], currentDate[MAX_LENGTH];
                strcpy(currentDate, getCurrentDate());
                strcpy(rNoteR1, "Asset was returned by client: ");
                strcat(rNoteR1, returner.GetfirstName());
                strcpy(rNoteR2, " ");
                strcat(rNoteR1, rNoteR2);
                strcat(rNoteR1, returner.GetlastName());
                strcpy(rNoteR2, " on ");
                strcat(rNoteR1, rNoteR2);
                strcat(rNoteR1, currentDate);
                strcat(rNoteR1, "\n");
                char recNoteStatus[MAX_STRING_LENGTH], recNoteTiming[MAX_STRING_LENGTH];

                if (ifBroken)
                {
                    string st = "Broken";
                    strncpy(status, st.c_str(), MAX_LENGTH);
                    strcpy (recNoteStatus, "It was returned broken");
                }
                else
                {
                    string st = "Available";
                    strncpy(status, st.c_str(), MAX_LENGTH);
                    strcpy (recNoteStatus, "It was returned safely");
                }

                for (int i=0; i<MAX_LENGTH; i++)
                    temp[i] = '\0';

                long assetNum = searchAssetByID(returnID);

                Asset asset = getAsset(assetNum);
                strcpy(statusCheck, asset.Getstatus());
                if (statusCheck[0] == 'L')
                {
                    lateCounter = 1;
                    strcpy (recNoteTiming, " and it was returned late");
                }
                else
                {
                    lateCounter = 0;
                    strcpy (recNoteTiming, " and it was returned on time");
                }

                strcat(recNoteStatus, recNoteTiming);
                strcat(recNoteStatus, "\n");

                Person rtner = getPerson(recNum);

                int assetListNum = rtner.findAssetListNum(returnID);

                rtner.removeAnAssetFromList(assetListNum);

                asset.Setstatus(status);
                asset.Setlocation(borrowL);
                asset.SetborrowDate(temp);
                asset.SetreturnDate(temp);
                asset.SetreservationDate(temp);

                changeAsset(asset, assetNum);
                changePerson(rtner, recNum);

                long recNum = searchRecord(returnID);
                Record aRecord = getRecord(recNum);
                aRecord.checkIfRecIsFull();
                aRecord.addRecordNote(rNoteR1);
                aRecord.addRecordNote(recNoteStatus);
                changeRecord(aRecord, recNum);

                cout << "\nThe asset has been returned, and it was ";
                if (!lateCounter)
                    cout << "on time" << endl;
                else
                    cout << "returned late" << endl;
            }
        }
    }
    else
        cout << "\nThis client has no assets to return" << endl;
}

void viewUserReservation()
{
    int userC, ifAdd, addOrRmv;
    bool conditionA = false, conditionB = false, conditionC = false;
    char userName[MAX_LENGTH];
    string us = "USER";
    strncpy(userName, us.c_str(), MAX_LENGTH);
    long recNum = searchPerson(userName);

    if (recNum == -1)
    {
        cout << "\nUser Information cannot be found.\nWould you like to add User Information? (1 to enter, 0 to exit):" << endl;
        do {
            cin >> userC;
            if (cin.fail())
            {
                cin.clear();
                cin.sync();
                cout << "\nInvalid input. Please enter either 0 or 1." << endl;
            }
            else if (userC < 0 || userC > 1)
                cout << "\nInvalid input. Please enter either 0 or 1." << endl;
            else
                conditionA = true;
        } while (!conditionA);

        cin.clear();
        cin.ignore();

        if (userC)
        {
            getUserPersonalInfo();
            cout << "You have no assets currently reserved\nDo you wish to add assets to your reserve? (1 to enter, 0 to exit):" << endl;
            do {
                cin >> ifAdd;
                if (cin.fail())
                {
                    cin.clear();
                    cin.sync();
                    cout << "\nInvalid input. Please enter either 0 or 1." << endl;
                }
                else if (ifAdd < 0 || ifAdd > 1)
                    cout << "\nInvalid input. Please enter either 0 or 1." << endl;
                else
                    conditionB = true;
            } while (!conditionB);

            cin.clear();
            cin.ignore();

            if (ifAdd)
                changeUserReservation(ifAdd);
        }
    }
    else
    {
        Person user = getPerson(recNum);
        int amountRsv = user.Getamount();
        cout << "\nUser Information has been found.\nYou currently have " << amountRsv << " assets reserved." << endl
             << "Would you like to change your reservations? (1 to add, 0 to remove, -1 to exit):" << endl;
        do {
            cin >> addOrRmv;
            if (cin.fail())
            {
                cin.clear();
                cin.sync();
                cout << "\nInvalid input. Please enter either -1, 0, or 1." << endl;
            }
            else if (addOrRmv < -1 || addOrRmv > 1)
                cout << "\nInvalid input. Please enter either -1, 0, or 1." << endl;
            else
                conditionC = true;
        } while (!conditionC);

        cin.clear();
        cin.ignore();

        if (addOrRmv == 1)
            changeUserReservation(addOrRmv);
        else if (addOrRmv == 0)
            changeUserReservation(addOrRmv);
    }
}

void changeUserReservation(int addOrRemove)
{
    bool conditionA = false, conditionB = false;
    int changeRsv;
    char assetType[MAX_LENGTH], checkAssetType[MAX_LENGTH], userName[MAX_LENGTH], status[MAX_LENGTH], statusRtoA[MAX_LENGTH];
    string us = "USER";
    strncpy(userName, us.c_str(), MAX_LENGTH);
    string uR = "User Reserved";
    strncpy(status, uR.c_str(), MAX_LENGTH);
    string uA = "Available";
    strncpy(statusRtoA, uA.c_str(), MAX_LENGTH);

    long recNum = searchPerson(userName);

    if (recNum == -1)
        recNum = 0;
    Person user = getPerson(recNum);

    strcpy(assetType, getAssetType());

    if (addOrRemove)
    {
        int amountRsv = user.Getamount();
        int currentAvailableNum = findAssetAvailableAmount(assetType);
        cout << "\nCurrent Available Assets: " << currentAvailableNum << endl;

        if(currentAvailableNum == 0)
            cout << "There are not enough available assets of that type to reserve" << endl;
        else
        {
            cout << "How many assets do you wish to add to your reserve?\n(MAX is 30, you have already reserved " << amountRsv << " assets):" << endl;
            do {
                cin >> changeRsv;
                if (cin.fail())
                {
                    cin.clear();
                    cin.sync();
                    cout << "\nInvalid input. Please enter a non-negative number smaller than " << (MAX_LIMIT_ASSET-amountRsv) << endl;
                }
                else if (changeRsv < 1 || changeRsv > (MAX_LIMIT_ASSET-amountRsv))
                    cout << "\nInvalid input. Please enter a non-negative number smaller than " << (MAX_LIMIT_ASSET-amountRsv) << endl;
                else if (changeRsv > currentAvailableNum)
                {
                    cout << "\nInvalid input. There are not enough available assets to reserve" << endl
                         << "Enter a non-negative number smaller than " << currentAvailableNum << endl;
                }
                else
                    conditionA = true;
            } while (!conditionA);

            char rNoteR1[MAX_STRING_LENGTH], rNoteR2[MAX_STRING_LENGTH], currentDate[MAX_LENGTH];
            strcpy(currentDate, getCurrentDate());
            strcpy(rNoteR1, "Asset was reserved by USER");
            strcpy(rNoteR2, " on ");
            strcat(rNoteR1, rNoteR2);
            strcat(rNoteR1, currentDate);
            strcat(rNoteR1, "\n");

            for (int i=0; i<changeRsv; i++)
            {
                long assetNum = searchAssetByStatusAndType(assetType, 'A');
                Asset asset = getAsset(assetNum);

                Person userC = getPerson(recNum);
                int amount = userC.Getamount();

                userC.SetassetList(asset.GetID(), asset.Getlocation(), asset.GetassetType(), status,
                                    asset.GetborrowDate(), asset.GetreturnDate(), asset.GetreservationDate(), amount);

                userC.Setamount(amount+1);

                asset.Setstatus(status);

                changeAsset(asset, assetNum);
                changePerson(userC, recNum);

                long recNum = searchRecord(asset.GetID());
                Record aRecord = getRecord(recNum);
                aRecord.checkIfRecIsFull();
                aRecord.addRecordNote(rNoteR1);
                changeRecord(aRecord, recNum);
            }

            cout << endl << changeRsv << " Assets of type ";
            for(int j=0; j<MAX_LENGTH; j++)
                cout << assetType[j];
            cout << "\nhave been added to your user reserve." << endl;
        }
    }
    else
    {
        int totalRsv = user.Getamount();
        int amountRsv = 0;
        for (int i=0; i<totalRsv; i++)
        {
            Asset checkAsset = user.GetassetListMember(i);
            strcpy(checkAssetType, checkAsset.GetassetType());
            if ( strcmp(assetType, checkAssetType) == 0)
                amountRsv++;
        }

        cout << "\nCurrent Assets Reserved by User: " << amountRsv << endl;
        if(amountRsv == 0)
            cout << "There are no more assets to remove" << endl;
        else
        {
            cout << "How many assets do you wish to remove from your reserve?\n(MAX is " << amountRsv << " assets):" << endl;
            do {
                cin >> changeRsv;
                if (cin.fail())
                {
                    cin.clear();
                    cin.sync();
                    cout << "\nInvalid input. Please enter a non-negative number smaller than " << amountRsv << endl;
                }
                else if (changeRsv < 1 || changeRsv > amountRsv)
                    cout << "\nInvalid input. Please enter a non-negative number smaller than " << amountRsv << endl;
                else if (changeRsv > amountRsv)
                {
                    cout << "\nInvalid input. There are not enough available assets to remove" << endl
                         << "Enter a non-negative number smaller than " << amountRsv << endl;
                }
                else
                    conditionB = true;
            } while (!conditionB);

            char rNoteR1[MAX_STRING_LENGTH], rNoteR2[MAX_STRING_LENGTH], currentDate[MAX_LENGTH];
            strcpy(currentDate, getCurrentDate());
            strcpy(rNoteR1, "USER stopped reserving the asset");
            strcpy(rNoteR2, " on ");
            strcat(rNoteR1, rNoteR2);
            strcat(rNoteR1, currentDate);
            strcat(rNoteR1, "\n");

            for (int i=0; i<changeRsv; i++)
            {
                Person userC = getPerson(recNum);

                long assetNum = searchAssetByStatusAndType(assetType, 'U');
                Asset asset = getAsset(assetNum);

                int assetListNum = userC.findAssetListNum(assetNum);

                userC.removeAnAssetFromList(assetListNum);

                asset.Setstatus(statusRtoA);

                changeAsset(asset, assetNum);
                changePerson(userC, recNum);

                long recNum = searchRecord(asset.GetID());
                Record aRecord = getRecord(recNum);
                aRecord.checkIfRecIsFull();
                aRecord.addRecordNote(rNoteR1);
                changeRecord(aRecord, recNum);
            }

            cout << endl << changeRsv << " Assets of type ";
            for(int j=0; j<MAX_LENGTH; j++)
                cout << assetType[j];
            cout << "\nhave been removed to your user reserve." << endl;
        }

    }
}
