/* Programmer   : Bernice Templeman
 * MidTerm Exam : Number Array Class
 * Date         : 03/05/2015
 *
 */

#include <iostream>
#include "NumberArray.h"

using namespace std;

//function prototype
char displayMenu();

int main()
{
    int arraySize;      //size of array
    char choice;        // user choice
    int numStored = 0;  // number of numbers stored inn array
    float number;       // number to add to array

    // ask user for number of elements
    cout << "How many numbers in the array? ";
    cin >> arraySize;

    // check size
    while (arraySize < 0)
    {
        cout <<"  Size must be positive." <<endl;
        cout << "How many numbers in the array? ";
        cin >> arraySize;

    }

    //define an instance of the class
    NumberArray  numArray(arraySize);

    do
    {
        //display menu
        choice = displayMenu();

        switch (choice)
        {
        case '1': //add number to array
            if (numStored < arraySize)
            {
                cout << "Enter the number to add to array: ";
                cin>> number;
                numArray.StoreNumber(number, numStored);
                numStored++;
            }
            else
            {
                cout << "Error: Array Full"<< endl;
            }
            break;


        case '2': //display all numbers
            for (int i = 0; i < numStored; i++)
            {
                cout << numArray.RetrieveNumber(i)<< endl;
            }
            cout << endl;
            break;

        case '3': //Display the highest value
            cout << "The highest number is: " << numArray.HighestNumber(numStored) <<endl<<endl;
            break;

        case '4': //display the lowest value
            cout << "The lowest number is: "<<numArray.LowestNumber(numStored) << endl<<endl;
            break;

        case '5': // display the average

            cout << "The average is: " << numArray.AverageNumber(numStored) <<endl<<endl;
            break;
        case '6':
            break;

        default: //exit
            break;
        }//end switch
    }while (choice !='6');

    return 0;
}

char displayMenu()
{
    char choice;
    int intChoice;

    bool flag = true;

    while (flag)
    {
        flag = false;

        cout << "1. Add a number to the array" <<endl;
        cout << "2. Display all numbers in the array"<< endl;
        cout << "3. Display the highest value stored in the array" << endl;
        cout << "4. Display the lowest value stored int the array"<< endl;
        cout << "5. Display the average of all numbers stored in the array"<< endl;
        cout << "6. Exit" << endl << endl;
        cout << "Your Choice: ";
        cin >> choice;

        switch (choice)
        {
        case '1':
            break;
        case '2':
            break;
        case '3':
            break;
        case '4':
            break;
        case '5':
            break;
        case '6':
            break;
        default:
            cout << "Invalid Choice." <<endl;
            flag = true;
            break;

        }//end switch
    }//end while
    return choice;
}

