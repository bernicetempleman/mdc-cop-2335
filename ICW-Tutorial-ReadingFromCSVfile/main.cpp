/* Programmer   : Bernice Templeman
 * Class        : C++ /COP 2335
 * ICW          : Tutorial - Reading From A CSV file
 * Date         : 02/24/2015
 *
 * Description:
 * This program reads data  2 different ways:
 * 1.) Using string Objects to read the data
 * 2.) Using the C-Style Strings (char arrays) to Read the Data
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;


// Global Constants
const int NUM_CARS = 5;     // for both ways
const int MAX_SIZE = 50;    // for using C-style strings to read data

// Programmer defined data types
struct CarInfo              // for  Using string Objects to read the data
{
    string make;
    string model;
    int year;
    double mpg;
};

struct CarInfo2             // for Using the C-Style String (char arrays) to Read the Data
{
    char make[MAX_SIZE];
    char model[MAX_SIZE];
    int year;
    double mpg;
};

//function prototypes
bool getCars(CarInfo [], int );
void displayCars(CarInfo [], int );

bool getCars2(CarInfo2 [], int );
void displayCars2(const CarInfo2 [], int );

int main()
{
    CarInfo myCars[5]; // declare an array of 5 structures

    //Using the string Objects to Read the Data
    cout << "******************************************"<< endl;
    cout << "Using string Objects to read the data:" << endl;
    cout << "******************************************"<< endl;
    if (!getCars(myCars, NUM_CARS))
    {
        cout << "Trouble reading from input file.";
        cout << "\nExiting...";
        system("PAUSE");
        return EXIT_FAILURE;
    }
    displayCars(myCars, NUM_CARS);

    cout << "******************************************"<< endl;
    cout << "Using the C-Style String to Read the data:" << endl;
    cout << "******************************************"<< endl;

    CarInfo2 myCars2[5];

    if (!getCars2(myCars2, NUM_CARS))
    {
        cout << "Trouble reading from input file.";
        cout << "\nExiting...";
        system("PAUSE");
        return EXIT_FAILURE;
    }
    displayCars2(myCars2, NUM_CARS);

    system("PAUSE");
    return EXIT_SUCCESS;
}

/************************************************
 * function to use string Objects to read the data
 ************************************************/

void displayCars(CarInfo cars[], int size)
{
    for (int i=0; i<size; i++)
    {
    cout << "Make: " << cars[i].make << endl;
    cout << "Model: " << cars[i].model << endl;
    cout << "Year: " << cars[i].year << endl;
    cout << "MPG: " << cars[i].mpg << endl;
    cout << endl;
    }
}
bool getCars(CarInfo cars[], int size)
{
    ifstream inFile;
    string temp;
    inFile.open("Cars.txt");
    if (!inFile)
    {
        return false;
    }
    else
    {
        for (int i=0; i<size; i++)
        {
            getline(inFile, cars[i].make, ',');
            getline(inFile, cars[i].model,',');
            getline(inFile, temp, ','); // read as a temp string
            cars[i].year = atoi(temp.c_str()); // convert to integer
            getline(inFile, temp);
            cars[i].mpg = atof(temp.c_str());
        }
        return true;
    }
}

/****************************************************
 * functions Using the C-Style String to Read the Data
 ****************************************************/

void displayCars2(const CarInfo2 cars[], int size)
{
    for (int i=0; i<size; i++)
    {
        cout << "Make: " << cars[i].make << endl;
        cout << "Model: " << cars[i].model << endl;
        cout << "Year: " << cars[i].year << endl;
        cout << "MPG: " << cars[i].mpg << endl;
        cout << endl;
    }
}

bool getCars2(CarInfo2 cars[], int size)
{
    ifstream inFile;
    char temp[MAX_SIZE]; // temp char array
    inFile.open("Cars.txt");
    if (!inFile)
    {
        return false;
    }
    else
    {
        for (int i=0; i<size; i++)
        {
            inFile.getline(cars[i].make, MAX_SIZE, ',');
            inFile.getline(cars[i].model, MAX_SIZE, ',');

            inFile.getline(temp, MAX_SIZE, ',');

            // convert to an integer
            cars[i].year = atoi(temp);

            // read as a temp C_Style string
            inFile.getline(temp, MAX_SIZE, '\n');

            // convert to a double
            cars[i].mpg = atof(temp);
        }
        return true;
    }
}


