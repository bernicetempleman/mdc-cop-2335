/* Programmer : Bernice Templeman

Write a program that simulates inventory bins in a warehouse.
Each bin holds a number of the same type of parts.

The program should use a structure that keeps the following data:
• Description of the part kept in the bin
• Number of parts in the bin

The program should have an array of 10 bins, initialized with the following data:
Part Description    Number of parts in the Bin
Valve              10
Bearing            5
Bushing            15
Coupling           21
Flange             7
Gear               5
Gear Housing       5
Vacuum Gripper     25
Cable              18
Rod                12

The program should have the following functions:
• addParts
• removeParts
• selectBin

When the program runs, it should repeat a loop that performs the following steps:
• The user should see a list of what each bin holds and how many parts are in each bin
• The user can choose to either quit the program or select a bin.
• When a bin is selected, the user can either add parts to it or remove parts from it.
• The loop then repeats showing the updated bin data on the screen.

Input Validation: No bin can hold more than 30 parts,
so don’t let the user add more than a bin can hold.

Also, don’t accept negative values for the number of parts being added or removed.
Your code should be modular (use functions) and pass variables (by value/by reference) where appropriate.
Also, use named constants where appropriate.
*/

#include <iostream>

using namespace std;

const int NUM_BINS = 10;

struct BinInfo
{
    string partDescription;  // description
    int numberOfParts;        // number
};

//function prototypes
void loadBins(BinInfo [], int);
void displayBins (const BinInfo [], int);
void menu(const BinInfo [], int );
void updateMenu(BinInfo [], int , int);
void addParts(BinInfo [], int, int);
void removeParts(BinInfo [], int, int);
void selectBin (const BinInfo [], int);

int main()
{

    BinInfo bins[NUM_BINS];             // memory allocated for an array of structures
    int userChoice;                     // to hold user choice
    int updateChoice;                   // to hold update choice

    //initialize structs
    loadBins(bins, NUM_BINS);

    /*loop
    • The user should see a list of what each bin holds and how many parts are in each bin
    • The user can choose to either quit the program or select a bin.
    • When a bin is selected, the user can either add parts to it or remove parts from it.
    • The loop then repeats showing the updated bin data on the screen
    */
    do
    {
            //display menu
            selectBin(bins, NUM_BINS);

            //get choice
            cin >>userChoice;

            switch (userChoice)
            {
            case 1:
                // update menu
                updateMenu(bins, NUM_BINS, 0);

                cin >> updateChoice;
                switch (updateChoice)
                {
                case 1:
                    addParts(bins,NUM_BINS, 0);
                    break;
                case 2:
                    removeParts(bins,NUM_BINS, 0);
                    break;
                default:
                    cout << "Invalid Choice" << endl;
                    break;

                }

                break;

            case 2:
                updateMenu(bins, NUM_BINS, 1);
                cin >> updateChoice;
                switch (updateChoice)
                {
                case 1:
                    addParts(bins,NUM_BINS, 1);
                    break;
                case 2:
                    removeParts(bins,NUM_BINS, 1);
                    break;
                default:
                    cout << "Invalid Choice" << endl;
                    break;

                }
                break;


            case 3:
                updateMenu(bins, NUM_BINS, 2);
                cin >> updateChoice;
                switch (updateChoice)
                {
                case 1:
                    addParts(bins,NUM_BINS, 2);
                    break;
                case 2:
                    removeParts(bins,NUM_BINS, 2);
                    break;
                default:
                    cout << "Invalid Choice" << endl;
                    break;

                }
                break;

            case 4:
                updateMenu(bins, NUM_BINS,3);
                cin >> updateChoice;
                switch (updateChoice)
                {
                case 1:
                    addParts(bins,NUM_BINS, 3);
                    break;
                case 2:
                    removeParts(bins,NUM_BINS, 3);
                    break;
                default:
                    cout << "Invalid Choice" << endl;
                    break;

                }
                break;

            case 5:
                updateMenu(bins, NUM_BINS,4);
                cin >> updateChoice;
                switch (updateChoice)
                {
                case 1:
                    addParts(bins,NUM_BINS, 4);
                    break;
                case 2:
                    removeParts(bins,NUM_BINS, 4);
                    break;
                default:
                    cout << "Invalid Choice" << endl;
                    break;

                }
                break;

            case 6:
                updateMenu(bins, NUM_BINS,5);
                cin >> updateChoice;
                switch (updateChoice)
                {
                case 1:
                    addParts(bins,NUM_BINS, 5);
                    break;
                case 2:
                    removeParts(bins,NUM_BINS, 5);
                    break;
                default:
                    cout << "Invalid Choice" << endl;
                    break;

                }
                break;

            case 7:
                updateMenu(bins, NUM_BINS,6);
                cin >> updateChoice;
                switch (updateChoice)
                {
                case 1:
                    addParts(bins,NUM_BINS, 6);
                    break;
                case 2:
                    removeParts(bins,NUM_BINS, 6);
                    break;
                default:
                    cout << "Invalid Choice" << endl;
                    break;

                }
                break;

            case 8:
                updateMenu(bins, NUM_BINS, 7);
                cin >> updateChoice;
                switch (updateChoice)
                {
                case 1:
                    addParts(bins,NUM_BINS, 7);
                    break;
                case 2:
                    removeParts(bins,NUM_BINS, 7);
                    break;
                default:
                    cout << "Invalid Choice" << endl;
                    break;

                }
                break;

            case 9:
                updateMenu(bins, NUM_BINS,8);
                cin >> updateChoice;
                switch (updateChoice)
                {
                case 1:
                    addParts(bins,NUM_BINS, 8);
                    break;
                case 2:
                    removeParts(bins,NUM_BINS, 8);
                    break;
                default:
                    cout << "Invalid Choice" << endl;
                    break;

                }
                break;

            case 10:
                updateMenu(bins, NUM_BINS,9);
                cin >> updateChoice;
                switch (updateChoice)
                {
                case 1:
                    addParts(bins,NUM_BINS, 9);
                    break;
                case 2:
                    removeParts(bins,NUM_BINS, 9);
                    break;
                default:
                    cout << "Invalid Choice" << endl;
                    break;

                }
                break;

            case 11:
                break;


            default:
                cout << "Invalid Choice" <<endl;
                break;

            }

        }while (userChoice != 11);

    return 0;
}

//gunction to load bins
void loadBins(BinInfo bins[], int size)
{
    bins[0].partDescription = "Valve";
    bins[0].numberOfParts = 10;
    bins[1].partDescription = "Bearing";
    bins[1].numberOfParts = 5;
    bins[2].partDescription = "Bushing";
    bins[2].numberOfParts = 15;
    bins[3].partDescription = "Coupling";
    bins[3].numberOfParts = 21;
    bins[4].partDescription = "Flange";
    bins[4].numberOfParts = 7;
    bins[5].partDescription = "Gear";
    bins[5].numberOfParts = 5;
    bins[6].partDescription = "Gear Housing";
    bins[6].numberOfParts = 5;
    bins[7].partDescription = "Vacuum Gripper";
    bins[7].numberOfParts = 25;
    bins[8].partDescription = "Cable";
    bins[8].numberOfParts = 18;
    bins[9].partDescription = "Rod ";
    bins[9].numberOfParts = 12;
}

//function to display bins
void displayBins(const BinInfo bins[], int size)
{
    for (int i=0; i<size; i++)
    {
        cout << "Name: " << bins[i].partDescription << "   "
            << "Number In Bin: " << bins[i].numberOfParts << endl;
    }
}

//function to select bin
void selectBin(const BinInfo bins[], int size)
{
    cout << endl;
    cout << "  M E N U" << endl;
    cout << "1 " << bins[0].partDescription << "   "<< bins[0].numberOfParts << endl;
    cout << "2 " << bins[1].partDescription << "   "<< bins[1].numberOfParts << endl;
    cout << "3 " << bins[2].partDescription << "   "<< bins[2].numberOfParts << endl;
    cout << "4 " << bins[3].partDescription << "   "<< bins[3].numberOfParts << endl;
    cout << "5 " << bins[4].partDescription << "   "<< bins[4].numberOfParts << endl;
    cout << "6 " << bins[5].partDescription << "   "<< bins[5].numberOfParts << endl;
    cout << "7 " << bins[6].partDescription<< "   "<< bins[6].numberOfParts << endl;
    cout << "8 " << bins[7].partDescription << "   "<< bins[7].numberOfParts << endl;
    cout << "9 " << bins[8].partDescription << "   "<< bins[8].numberOfParts << endl;
    cout << "10 " << bins[9].partDescription << "   "<< bins[9].numberOfParts << endl;
    cout << "11 Quit" << endl;
    cout << "Select a part to update or quit. Your choice: ";
}

//function to display  update choice
void updateMenu(BinInfo bins[], int size, int bin)
{
    cout << endl;
    cout << " Update  M E N U" << endl;
    cout << "1. Add Part"<< endl;
    cout << "2. Remove Part" << endl;
    cout << "Your choice: ";

}

//function to add a part
void addParts(BinInfo bins[], int size, int bin)
{
    bins[bin].numberOfParts ++;
}

// function to remove a part
void removeParts(BinInfo bins[], int size, int bin)
{
    bins[bin].numberOfParts--;
}


