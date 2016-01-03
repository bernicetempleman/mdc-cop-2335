/***********************************************
 * Programmer : Bernice Templeman
 * COP 2335
 * Ex.02      : Customer Service Portal
 * Date Due   : 5:40PM, February 26th, 2015
 * Description:
 * Write a program that uses a structure
 * to store the following data about a customer account:
        • Name
        • Address (number, street name, unit number if any)
        • City, State, and ZIP
        • Telephone Number
        • Account Balance
        • Date of Last Payment

 * The structure should be used to store customer account records in a binary ﬁle.
 * The program should have a menu that lets the user perform the following operations:
        1. Enter new records into the file. (Create New Customer Account)
        2. Search for a particular customer’s record and display it. (Display Customer Account)
        3. Search for a particular customer’s record and delete it. (Delete Customer Account)
        4. Search for a particular customer’s record and change it. (Change Customer Account)
        5. Display the contents of the entire file. (Display All Customer Accounts)
        6. Exit
 * When searching for a particular customer record, search by name (or portion of a name).
 * Hint: You may want to brush up on string functions (strstr, etc).
 * Input Validation:
        When the data for a new account is entered,
        be sure the user enters data for all the ﬁelds.
        No negative account balances should be entered.
 * Submit your work as Ex.02-LastNameFirstNameInitial.cpp - i.e. Ex.02-ZejnilovicA.cpp
 *
 **********************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//constants
const int NAME_SIZE = 51;           // namesize
const int ADDR_SIZE = 51;           // address size
const int PHONE_SIZE = 14;          // phone size
const int DATE_SIZE = 11;           // date size
const int NUM_SIZE = 35;            // num size
const int CITY_SIZE = 35;           // city size
const int ZIP_SIZE = 35;             // zip size
const int STATE_SIZE = 35;           // state size

struct Address
{
    char address1[ADDR_SIZE];           // Address (number, street name)
    char unit[NUM_SIZE];                // Apt or unit number
    char city[CITY_SIZE];               // City
    char state[STATE_SIZE];             // state
    char zip[ZIP_SIZE];                 // zip
};

struct Account
{
    char name[NAME_SIZE];                // Name
    Address address;                     // Address struct
    char phone[PHONE_SIZE];              // Telephone Number
    double balance;                      // Account Balance
    char LastPaymentDate[DATE_SIZE];     // Date of Last Payment
};

//function prototypes
int displayMenu();
void enterRecord(fstream &);
void displayRecord(fstream &);
void deleteRecord(fstream &);
void updateRecord(fstream &);
void displayAllRecords(fstream &);
long byteNum(int);
void showRec(Account);
void getRecordInfo(Account &);
void rewindFile(fstream &);
bool openFile(fstream &, string);
void clearInputBuffer();
void pressAnyKey();

int main()
{
    //variable declarations
    int choiceInt;      // holds user's menu choice
    fstream accounts;

    //open file
    if (openFile(accounts, "accounts.dat"))
    {
        do
        {
            choiceInt = displayMenu();

            cout <<endl<<endl;

            switch (choiceInt)
            {
            case 1:     // Enter new records
                rewindFile(accounts);
                enterRecord(accounts);
                break;//case 1

            case 2:     // display
                rewindFile(accounts);
                displayRecord(accounts);
                break;//case 2

            case 3:     // delete
                rewindFile(accounts);
                deleteRecord(accounts);
                break;

            case 4:     // Update
                rewindFile(accounts);
                updateRecord(accounts);
                break;//end case 4

            case 5:     // display all
                rewindFile(accounts);
                displayAllRecords(accounts);
                break;

            case 6:     // exit
                cout <<"Exiting"<< endl;
                break;

            }
        }while(choiceInt !=6);

        //close the file
        accounts.close();
    }//end if open

    cout << "Thank You." << endl;
    return 0;
}

//****************************************************
int displayMenu()
{
    char choice;
    int choiceInt = 0;

    do
    {
        cout << "\n\n1. Enter new records into the file.\n"
            << "    (Create New Customer Account) " << endl;
        cout << "2. Search for a particular customer's record and display it.\n"
            <<"    (Display Customer Account)" << endl;
        cout << "3. Search for a particular customer's record and delete it.\n"
            << "    (Delete Customer Account)" << endl;
        cout << "4. Search for a particular customer's record and change it.\n"
            <<"    (Change Customer Account)"<< endl;
        cout << "5. Display the contents of the entire file. \n"
            << "    (Display All Customer Accounts)" << endl;
        cout << "6. Exit " << endl;
        cout << "Your Choice: ";
        cin >> choice;
        cin.sync();
        cin.clear();

        switch (choice)
        {
        case '1':
            choiceInt =1;
            break;
        case '2':
            choiceInt = 2;
            break;
        case '3':
            choiceInt = 3;
            break;
        case '4':
            choiceInt = 4;
            break;
        case '5':
            choiceInt = 5;
            break;
        case '6':
            choiceInt = 6;
            break;
        default:
            cout << "Invalid Choice" << endl;
            break;
        }
    }while (choiceInt == 0);
    return choiceInt;
}
//****************************************************
long byteNum(int recNum)
{
    return sizeof(Account) * recNum;
}
//****************************************************
void enterRecord(fstream &accounts )
{
    Account record;
    char again;
    bool found;
    char *pchar;
    string balanceString;
    double balance;

    accounts.read(reinterpret_cast<char *>(&record),sizeof(record));

    do
    {
        found = false;

        //check for available record
        while(!accounts.eof() && !found)
        {
            //check availability
            if(strlen(record.name) == 0)
            {
                //move back to beginning of current record
                accounts.seekg(byteNum(-1),ios::cur);

                //set found to true to exit while loop
                found = true;
            }
            if (!found)
            {
                //read next record to continue while loop
                accounts.read(reinterpret_cast<char *>(&record),sizeof(record));
            }
        }//end while

        cout << "Enter a new record\n";

        getRecordInfo(record);

        if (found)
        {
            accounts.write(reinterpret_cast<char *>(&record),sizeof(record));
        }
        else
        {
            accounts.close();
            accounts.clear();
            accounts.open("accounts.dat", ios::out |ios::app | ios::binary);
            accounts.write(reinterpret_cast<char *>(&record),sizeof(record));
            cout <<"Record Created"<<endl;
        }

        cout << "Do you want to enter another record? y or n:  ";
        cin >> again;
        cin.ignore();
        cin.clear();

    }while(again == 'Y'|| again =='y');

    accounts.close();
    accounts.clear();
    accounts.open("accounts.dat", ios::in | ios::out | ios::binary);
    return;
}

//****************************************************

void displayRecord(fstream &accounts )
{
    Account record;
    string name1;
    char *pchar;
    char correctRecord;

    cin.sync();
    cin.clear();

    cout << "Enter name to display: ";
    getline(cin, name1);

    accounts.read(reinterpret_cast<char *>(&record),sizeof(record));

    //search array for name
    while(!accounts.eof())
    {
        pchar = strstr(record.name,name1.c_str());

        if( pchar != NULL )
        {
            showRec(record);
            cout << endl;

            pressAnyKey();

        }//end if
        accounts.read(reinterpret_cast<char *>(&record),sizeof(record));
    }//END WHILE

    return;
}

//****************************************************

void deleteRecord(fstream &accounts )
{

    Account record;
    string name1;
    char *pchar;
    char correctRecord;

    cin.sync();
    cin.clear();

    cout << "Enter name to delete: ";
    getline(cin, name1);

    //search array for name
    accounts.seekg(byteNum(0),ios::beg);

    accounts.read(reinterpret_cast<char *>(&record),sizeof(record));

    while(!accounts.eof())
    {
        pchar = std::strstr(record.name,name1.c_str());

        if( pchar != NULL)
        {
            showRec(record);

            do
            {
                cout << "\n\nIs this the record you want to delete? y or n: ";
                cin >> correctRecord;
                cin.sync();
                cin.clear();
            }while (!(correctRecord == 'y'|| correctRecord =='n'));

            if (correctRecord == 'y')
            {
                //move back to beginning of current record
                accounts.seekg(byteNum(-1),ios::cur);

                record.name[0]= '\0';
                record.address.address1[0] = '\0';
                record.address.unit[0] = '\0';
                record.address.city[0] = '\0';
                record.address.state[0] = '\0';
                record.address.zip[0] = '\0';
                record.phone[0]='\0';
                record.balance = 0.0;
                record.LastPaymentDate[0]='\0';

                cout <<"Record deleted"<<endl;

                accounts.write(reinterpret_cast<char *>(&record),sizeof(record));

                pressAnyKey();

            }//end if correct record
        }//end if not NULL
        accounts.read(reinterpret_cast<char *>(&record),sizeof(record));
    }//end while not eof

    return;
}
//***************************************************

void updateRecord(fstream &accounts )
{
    Account record;
    string name1;
    char *pchar;
    char correctRecord;
    double balance;
    string balanceString;

    cin.sync();
    cin.clear();

    cout << "Enter name to update: ";
    getline(cin, name1);

    //search array for name
    accounts.seekg(byteNum(0),ios::beg);

    accounts.read(reinterpret_cast<char *>(&record),sizeof(record));

    while(!accounts.eof())
    {
        pchar = std::strstr(record.name,name1.c_str());

        if( pchar != NULL)
        {
            showRec(record);

            do
            {
                cout << "\n\nIs this the record you want to update? y or n: ";
                cin >> correctRecord;
                cin.sync();
                cin.clear();
            }while (!(correctRecord == 'y'|| correctRecord =='n'));


            if (correctRecord == 'y')
            {
                //move back to beginning of current record
                accounts.seekg(byteNum(-1),ios::cur);
                cin.sync();
                cin.clear();

                cout << "Enter the  following data: "<<endl;

                getRecordInfo(record);

                accounts.write(reinterpret_cast<char *>(&record),sizeof(record));
                cout <<"Record Updated"<<endl;

                pressAnyKey();
            }
        }
        accounts.read(reinterpret_cast<char *>(&record),sizeof(record));
    }
    return ;
}
//****************************************************
void displayAllRecords(fstream &accounts )
{
    Account record;

    cout << "Displaying all records" << endl << endl;

    accounts.read(reinterpret_cast<char *>(&record),sizeof(record));

    while(!accounts.eof())
    {
        if( record.name[0] != NULL && record.name[0] != '0' )
        {
            showRec(record);

            pressAnyKey();
        }

        accounts.read(reinterpret_cast<char *>(&record),sizeof(record));
    }
    return;
}

//****************************************************
void showRec(Account record)
{
    cout << "Name: ";
    cout << record.name <<endl;
    cout << "Address: " ;
    cout << record.address.address1 << endl;
    cout << "Unit: ";
    cout << record.address.unit << endl;
    cout << "City: ";
    cout << record.address.city << endl;
    cout << "State: ";
    cout << record.address.state << endl;
    cout << "ZIP: ";
    cout << record.address.zip << endl;
    cout << "Phone: ";
    cout << record.phone << endl;
    cout << "Balance: ";
    cout << record.balance << endl;
    cout << "Last Payment: ";
    cout << record.LastPaymentDate <<endl <<endl;

    return;
}

//****************************************************
void getRecordInfo(Account &record)
{
    double balance;
    string balanceString;

    cout << "Name: ";
    cin.getline(record.name,NAME_SIZE);
    while (strlen(record.name) == 0)
    {
        cout << "Error: Name can not be empty" <<endl;
        cout << " Re-Enter Name: ";
        cin.getline(record.name,NAME_SIZE);
    }

    cout << "Address (number and street): ";
    cin.getline(record.address.address1,ADDR_SIZE);
    while (strlen(record.address.address1) == 0)
    {
        cout << "Error: Address can not be empty" <<endl;
        cout << " Re-Enter Address: ";
        cin.getline(record.address.address1,ADDR_SIZE);
    }

    cout << "Unit  or Apartment number: ";
    cin.getline(record.address.unit,NUM_SIZE);
    while (strlen(record.address.unit) == 0)
    {
        cout << "Error: Unit can not be empty" <<endl;
        cout << " Re-Enter Unit: ";
        cin.getline(record.address.unit,NUM_SIZE);
    }

    cout << "City: ";
    cin.getline(record.address.city,CITY_SIZE);
    while (strlen(record.address.city) == 0)
    {
        cout << "Error: City can not be empty" <<endl;
        cout << " Re-Enter City: ";
        cin.getline(record.address.city,CITY_SIZE);
    }

    cout << "State: ";
    cin.getline(record.address.state,STATE_SIZE);
    while (strlen(record.address.state) == 0)
    {
        cout << "Error: State can not be empty" <<endl;
        cout << " Re-Enter STATE: ";
        cin.getline(record.address.state,STATE_SIZE);
    }

    cout << "ZIP: ";
    cin.getline(record.address.zip,ZIP_SIZE);
    while (strlen(record.address.zip) == 0)
    {
        cout << "Error: ZIP can not be empty" <<endl;
        cout << " Re-Enter ZIP: ";
        cin.getline(record.address.zip,ZIP_SIZE);
    }

    cout << "Phone: ";
    cin.getline(record.phone,PHONE_SIZE);
    while (strlen(record.phone) == 0)
    {
        cout << "Error: Phone can not be empty" <<endl;
        cout << " Re-Enter Phone: ";
        cin.getline(record.phone,PHONE_SIZE);
    }

    cout << "Balance: ";
    getline(cin,balanceString);
    balance = atof(balanceString.c_str());
    while (balance <= 0)
    {
        cout << "Balance must be greater than 0. " <<endl;
        cout << "RE-ENTER Balance: ";
        cin >>balanceString;
        balance = atof(balanceString.c_str());
    }
    record.balance = balance;

    cout << "Last Payment Date: ";
    cin.getline(record.LastPaymentDate,DATE_SIZE);
    while (strlen(record.LastPaymentDate) == 0)
    {
        cout << "Error: Last Payment Date can not be empty" <<endl;
        cout << " Re-Enter Last Payment Date: ";
        cin.getline(record.LastPaymentDate,DATE_SIZE);
    }

}
//****************************************************
void rewindFile(fstream &accounts)
{
    accounts.clear();
    accounts.seekg(0L, ios::beg);
}
//****************************************************
bool openFile(fstream &accounts, string name)
{
    bool status;

    accounts.open(name.c_str(), ios::in | ios::binary);
    if(accounts.fail())
    {
        //the file DNE so create it.
        accounts.open(name.c_str(), ios::out | ios::binary);
    }

    //close the file
    accounts.close();
    accounts.clear();

    //open the binary file for input and output
    accounts.open(name.c_str(), ios::in | ios::out | ios::binary);

    //test for errors
    if (!accounts)
    {
        cout << "Error opening file. Exiting...\n"<<endl;
        status = false;
    }
    else
    {
        status = true;
    }

    return status;

}
//****************************************************
void clearInputBuffer()
{
    cin.ignore();
    cin.sync();
    clearInputBuffer();
}
//****************************************************

void pressAnyKey()
{
        //pause bet each record
        cout << "Press any key to continue...";
        cin.get();
}
