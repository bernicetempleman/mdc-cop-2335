#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
using namespace std;

// Constants for array size
const int NUM_BINS = 10;

// Declaration of the InventoryBin structure
struct InventoryBin
{
   string description; // Item description
   int num;            // Number of parts in a bin
};

// Function prototypes
void selectBin(InventoryBin [], int);
void addParts(InventoryBin&, int);
void removeParts(InventoryBin&, int);

int main()
{
   // The user's menu choice
   int choice;
   
   // Array of InventoryBins
   InventoryBin bins[NUM_BINS] = {
                       {"Valve", 10},
                       {"Bearing", 5},
                       {"Bushing", 15},
                       {"Coupling", 21},
                       {"Flange", 7},
                       {"Gear", 5},
                       {"Gear Housing", 5},
                       {"Vacuum Gripper", 25},
                       {"Cable", 18},
                       {"Rod", 12}};
   

   do
   {
      // Display the contents of each bin as a menu.
      for (int count = 0; count < 10; count++)
      {
         cout << "Bin #" << setw(3) << (count+1);
         cout << ",  Part: " << bins[count].description;
         cout << ", Quantity: " << bins[count].num << endl;
      }
      
      // Get the user's choice of bins.
      cout << "\nEnter 0 to quit, or choose a bin Number: ";
      cin >> choice;
      
      // Validate the user's choice
      while (choice < 0 || choice > NUM_BINS)
      {
         cout << "\nEnter 0 to quit, or choose a bin Number: ";
         cin >> choice;
      }

      // Process the choice.
      if (choice != 0)
         selectBin(bins, choice - 1);
         
   } while (choice != 0);

   return 0;
}

//***********************************************************************
// Function    : selectBin                                              *
// Description : This function lets the user choose whether to add or   *
//               remove parts from the bin b[Choice].                   *
//***********************************************************************
void selectBin(InventoryBin b[], int choice)
{
   int numParts;  // Number of parts
   char aorr;     // Add or remove

   // Get the user's desired action (A or R)
   cout << "Add or Remove Parts (A or R)? ";
   cin >> aorr;
   
   // Validate the input.
   while (toupper(aorr) != 'A' && toupper(aorr) != 'R')
   {
      cout << "Enter A or R: ";
      cin >> aorr;
   }

   // Process the selection. 'A' means Add,
   // 'R' means Remove.
   if (toupper(aorr) == 'A')
   {
      // Get the number of parts to add.
      cout << "How many parts to add? ";
      cin >> numParts;
      
      // Okay, add the parts.
      addParts(b[choice], numParts);
   }
   else
   {
      // Get the number of parts to remove.
      cout << "How many parts to remove? ";
      cin >> numParts;
      
      // Okay, remove the parts.
      removeParts(b[choice], numParts);
   }
}

//************************************************************************
// Function   : addParts                                                 *
// Description: This function adds the value passed to numAdd to the     *
//              num member of the bin structure. The value is validated. *
//************************************************************************
void addParts(InventoryBin &bin, int numAdd)
{
   // Validate the number of parts and add them
   // if the number is valid.
   if (numAdd < 0)
      cout << "\nError: use positive values.\n";
   else if (numAdd + bin.num > 30)
      cout << "\nError:The bin can only hold 30 parts.\n";
    else
      bin.num += numAdd;
}

//*************************************************************************
// Function   :   removePar       ts                                      *
// Description: This function subtracts the value passed to numRem to the *
// num member of the bin structure. The value is validated.               *
//*************************************************************************
void removeParts(InventoryBin &bin, int numRem)
{
   // Validate the number of parts and remove them
   // if the number is valid.
   if (numRem < 0)
      cout << "\nError: use positive values.\n";
   else if (bin.num - numRem < 0)
   {
      cout << "\nError:You are attempting to remove more parts than ";
      cout << "the bin is holding.\n";
   }
   else
      bin.num -= numRem;
}
