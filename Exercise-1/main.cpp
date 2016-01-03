/* Programmer : Bernice Templeman
 * Class      : C++ /COP 2335
 * Homework 1 : Temperatures
 *
 * Description:
 *
 * Write a program that uses a structure (CityTempInfo) to store the following data about temperatures:
 *       • cityName
 *       • TempInfo

 * Your program should read the data from an input file
 *      • The first number (4) is the number of cities
 *      • The second number (12) is the number of months.
 *      • Followed by City name and 12 low Fahrenheit temperatures, one for each month
 *      • Followed by City name and 12 high Fahrenheit temperatures, one for each month
 *
 * Note: There are two rows for each city, one with low temperatures and one with high temperatures.
 *
 * Use this information to dynamically allocate an array of CityTempInfo structures.
 * For each city structure,
   dynamically allocate an array TempInfo structures with members that can hold high and low temperatures as well as the temperature scale:

    struct TemperatureInfo
    {
        char scale; // F for Fahrenheit, or C for Celsius
        double low;
        double high;
        string monthName;
    };

The program should have a menu that lets the user perform the following operations:
Welcome to COP 2335 Temperature Wizard Program. Please select one of the following cities:
1. Miami
2. Key West
3. Jacksonville
4. Pensacola
5. Exit
Note: Choosing “Exit” terminates the program.

When the user selects a city, they should be prompted to select one of the following menu options:

Please choose one of the following options:
1. Degrees Celsius
2. Degrees Fahrenheit
3. Exit this menu

Note: Choosing “Exit this menu” does not cause the program to terminate, it simply displays the previous menu for the user to choose another city, accomplish this with nested loops.

If the user chooses option 1 or option 2, then the program needs to present the following menu:
What would you like to do?
1. View low and high temperatures
2. Find out what is the warmest month
4. Find out what is the coldest month
5. Exit this menu

Note: Choosing “Exit this menu” does not cause the program to terminate,
it simply displays the previous menu for the user to choose another temperature choice, accomplish this with nested loops.

See an example of a neatly formatted output for Pensacola low and high temperatures in degrees Fahrenheit:
To accomplish this, you will need to use manipulators from the <iomanip> header.

Should the user select the option to view the coldest and warmest month, the program needs to display the month name – i.e. January.

The temperature conversion formulas are:

c = 5/9*(f-32)
f = 9/5*C +32

Your program needs to be modular (use functions).
Use defensive programming practices.
Pass the data by value, reference, and/or pointers, as you deem appropriate.
Since you will be allocating memory dynamically,
be sure to de-allocate memory accordingly…..no memory leaks!

Submit your work as Ex.01-LastNameFirstNameInitial.cpp - i.e. Ex.01-ZejnilovicA.cpp

*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

// Global Constants
const int TEMP_EXIT = 3;
const int TEMP_CHOICE_EXIT = 4;


// Programmer defined data types
struct TemperatureInfo
{
    char scale;             // F for Fahrenheit, or C for Celsius
    double low;
    double high;
    string monthName;
};

struct CityTempInfo
{
    string cityName;
    TemperatureInfo *TempInfo;
};

//Function Prototypes
bool openFileIn(fstream &, string);
void showContents(fstream &, int &, int &);

void getCityTemps(fstream &, CityTempInfo  *, int, int);
int displayMenu(CityTempInfo *,int);
int displayTempMenu();
int displayTempChoiceMenu();

void displayCityTempInfo(const CityTempInfo *,int, char);
void displayColdestMonth(const CityTempInfo *,int);
void displayWarmestMonth(const CityTempInfo *,int);
double fahrenheitToCelsius(double);
double celsiusToFahrenheit(double);

int main()
{

    int num_city = 0;
    int num_months = 0;
    fstream dataFile;


    if(!openFileIn(dataFile,"citytemps.txt"))
    {
        cout << "File open error!" << endl;
                cout << "Exiting...";

        system ("PAUSE");   // Windows only
        exit(0);
    }

    //get city number & month number
    showContents(dataFile, num_city, num_months);
    if((num_city < 1 )||(num_months < 1))
    {
        cout << "File data error"<< endl;
        system ("PAUSE");   // Windows only
        exit(0);
    }

    //dynamically allocate an array of sructs

    CityTempInfo *cityTempPtr, *ptrCity1;      // struct pointer
    cityTempPtr = new CityTempInfo[num_city];

    // safe programming practice
    if (!cityTempPtr)
    {
        cout << "Unable to successfully allocate required memory...";
        cout << "Exiting...";
        system ("PAUSE");   // Windows only
        exit(0);
    }

    //we have a good pointer
    getCityTemps(dataFile, cityTempPtr,num_city, num_months);

    dataFile.close();

    int userCityChoice;
    int userTemp;
    int userTempChoice;
    char scale;

    do
    {
        //display main menu
        userCityChoice = displayMenu(cityTempPtr,num_city);

        if (userCityChoice == num_city+1 )
        {
            cout << "Exiting...";
            system ("PAUSE");   // Windows only
            exit(0);
        }

    int index = userCityChoice-1;
        //set pointer to city
        ptrCity1 = &cityTempPtr[index];  // pointing to the location
                                            // in the array

        // display temp choice
        do
        {
            //display temp choice menu
            userTemp = displayTempMenu();
            //1 = celsius
            //2 = fahrenheit
            if ( userTemp == 1)
                scale = 'C';
            else if (userTemp == 2)
                scale = 'F';

            if (userTemp != TEMP_EXIT)
            {
                do
                {
                    //display temp choice menu
                    userTempChoice = displayTempChoiceMenu();

                    switch(userTempChoice)
                    {
                    case 1:
                        displayCityTempInfo(ptrCity1, num_months, scale);
                        break;
                    case 2:
                        displayWarmestMonth(ptrCity1, num_months);
                        break;
                    case 3:
                        displayColdestMonth(ptrCity1, num_months);
                        break;

                    }


                }while(userTempChoice != TEMP_CHOICE_EXIT);

            }//if valid choice

        }while (userTemp != TEMP_EXIT);
    }while (userCityChoice != num_city);

    // deallocate the memory
    CityTempInfo* ptrCity;
    for (int i=0; i<num_city; i++)
    {
        ptrCity = &cityTempPtr[i];
        delete []ptrCity->TempInfo;
    }
    delete []cityTempPtr;
    delete ptrCity1;
    return 0;

}


/**********************************************
* function to show contents (number of cities & number of months)
***********************************************/
void showContents(fstream &inFile, int &numCities, int &numMonths)
{
    string line;
    string temp;

    getline(inFile,temp);
    numCities = atoi(temp.c_str());

    //read second line
    getline(inFile,temp);
    numMonths = atoi(temp.c_str());

}
/**********************************************
* function to read data into array of structs
***********************************************/
void getCityTemps(fstream &inFile, CityTempInfo *city, int numCity, int numMonths )
{
    CityTempInfo *ptrCity;  // one structure
    string temp;

    for (int i=0; i<numCity; i++)
    {
        ptrCity = &city[i];  // pointing to the first location
                             // in the array

        if (i == 0 )
        {
            //read first city line = Lows
            getline(inFile, city[i].cityName,',');
        }

        // dynamically allocate memory for exercises
        ptrCity->TempInfo = new TemperatureInfo[numMonths];

        for(int j = 0; j< numMonths-1;j++)
        {
                getline(inFile, temp,',');
                city[i].TempInfo[j].low = atof(temp.c_str());
        }

        //read last temp and second city line = Highs
        string temp1;
        getline(inFile, temp1,',');
        istringstream ss( temp1 );
        string s;
        getline(ss,s,'\n');

        city[i].TempInfo[11].low = atof(s.c_str());

        getline(ss,city[i].cityName, '\n');

        for(int j = 0; j< numMonths-1;j++)
        {
                getline(inFile, temp,',');
                city[i].TempInfo[j].high = atof(temp.c_str());

                switch (j)
                {
                case 0:
                    city[i].TempInfo[j].monthName = "January";
                    break;
                case 1:
                    city[i].TempInfo[j].monthName = "February";
                    break;
                case 2:
                    city[i].TempInfo[j].monthName = "March";
                    break;
                case 3:
                    city[i].TempInfo[j].monthName = "April";
                    break;
                case 4:
                    city[i].TempInfo[j].monthName = "May";
                    break;
                case 5:
                    city[i].TempInfo[j].monthName = "June";
                    break;
                case 6:
                    city[i].TempInfo[j].monthName = "July";
                    break;
                case 7:
                    city[i].TempInfo[j].monthName = "August";
                    break;
                case 8:
                    city[i].TempInfo[j].monthName = "September";
                    break;
                case 9:
                    city[i].TempInfo[j].monthName = "October";
                    break;
                case 10:
                    city[i].TempInfo[j].monthName = "November";
                    break;
                case 11:
                    city[i].TempInfo[j].monthName = "December";
                    break;
                }
                city[i].TempInfo[j].scale = 'F';

        }//end for j

        //read last temp and next city line
        getline(inFile, temp1,',');
        istringstream ss2( temp1 );

        getline(ss2,s,'\n');

        city[i].TempInfo[11].high = atof(s.c_str());

        if ((i+1) < numCity)
        {
            getline(ss2,city[i+1].cityName, '\n');
        }
        city[i].TempInfo[numMonths-1].monthName = "December";
        city[i].TempInfo[numMonths-1].scale = 'F';
    }//end for loop



}


/**********************************************
* function to display the Main menu
***********************************************/

int displayMenu(CityTempInfo *city, int num)
{
    char choice;
    int choiceInt = 0;

    do
    {

    cout << "Welcome to COP 2335 Temperature Wizard Program." << endl;
    cout << "Please select one of the following cities:" << endl;

    for(int i=0; i< num; i++)
    {
        cout << i+1 << ". " << city[i].cityName << endl;
    }
    cout << num + 1 << ". Exit" << endl;
    cin >> choice;
    cin.sync();
    cin.clear();

   // if (isdigit(choice))
    if (choice >= '0' && choice <= '9')
    {
        choiceInt = choice-'0';

        if(choiceInt > num+1)
        {
            cout <<"Invalid choice." << endl;
            choiceInt = 0;
        }
    }
    else
    {
        cout <<"Invalid choice." << endl;
        choiceInt = 0;
    }
    }while( choiceInt == 0);

    return choiceInt;
}
/**********************************************
* function to display the Temp menu
***********************************************/
int displayTempMenu()
{
    char choice;
    int choiceInt;
    do
    {

        cout << "Please choose one of the following options:" << endl;
        cout << "1. Degrees Celsius" << endl;
        cout << "2. Degrees Fahrenheit" << endl;
        cout << "3. Exit this menu" << endl;
        cin >> choice;
        cin.sync();
        cin.clear();

        switch(choice)
        {
        case '1':
            choiceInt = 1;
            break;
        case '2':
            choiceInt = 2;
            break;
        case '3':
            choiceInt = 3;
            break;
        default:
            cout <<"Invalid choice." << endl;
            choiceInt = 0;
            break;
        }//end switch
    }while( choiceInt == 0);

    return choiceInt;
}

/**********************************************
* function to display the Temp Choice menu
***********************************************/
int displayTempChoiceMenu()
{
    char choice;
    int choiceInt;

    do
    {

        cout << "What would you like to do?" << endl;
        cout << "1. View low and high temperatures" << endl;
        cout << "2. Find out what is the warmest month" << endl;
        cout << "3. Find out what is the coldest month" << endl;
        cout << "4. Exit this menu" << endl;
        cin >> choice;
        cin.sync();
        cin.clear();

        switch(choice)
        {
        case '1':
            choiceInt = 1;
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
        default:
            cout <<"Invalid choice." << endl;
            choiceInt = 0;
            break;
        }//end switch
    }while( choiceInt == 0);

    return choiceInt;
}

/**********************************************
* function to get convert f to c
***********************************************/
double fahrenheitToCelsius(double fahrenheit)
{
    double celsius;

    //c = 5/9*(f-32)
    celsius = 5.0/9*(fahrenheit-32);

    return celsius;
}

/**********************************************
* function to convert c to f
***********************************************/
double celsiusToFahrenheit(double celsius)
{
    double fahrenheit;

    //f = 9/5*C +32
    fahrenheit = 9.0/5*celsius + 32;

    return fahrenheit;
}
/**********************************************
* function to display the City temperatures
***********************************************/
void displayCityTempInfo(const CityTempInfo *city, int months, char scale )
{

    cout << city->cityName << endl;
    cout <<left <<setw(15) << "Month " << setw(9)<< "Low"<< setw(7)<< "High" << endl;
    for( int i = 0; i < months; i++)
    {
        if(scale == city->TempInfo[i].scale)
        {
            cout << left
            << setw(15)
            << city->TempInfo[i].monthName
            << setw(5)
            << fixed
            << setprecision(1)
            << city->TempInfo[i].low
            << setw(4)
            << city->TempInfo[i].scale
            << setw(5)
            << city->TempInfo[i].high
            << setw(4)
            << city->TempInfo[i].scale << endl;
        }
        else if (scale == 'C')
        {

            cout << left
            << setw(15)
            << city->TempInfo[i].monthName
            << setw(5)
            << fixed
            << setprecision(1)
            << fahrenheitToCelsius(city->TempInfo[i].low)
            << setw(4)
            << scale
            << setw(5)
            << fahrenheitToCelsius(city->TempInfo[i].high)
            << setw(4)
            << scale << endl;
        }
        else if (scale == 'F')
        {
            cout << left
            << setw(15)
            << city->TempInfo[i].monthName
            << setw(5)
            << fixed
            << setprecision(1)
            << celsiusToFahrenheit(city->TempInfo[i].low)
            << setw(4)
            << scale
            << setw(5)
            << celsiusToFahrenheit(city->TempInfo[i].high)
            << setw(4)
            << scale << endl;
        }

        }// end for loop
}// end function



/**********************************************
* function to display the coldest month
***********************************************/
void displayColdestMonth(const CityTempInfo *city, int months )
{
    double cold = 0;
    double sum = 0;
    int coldestMonth = 0;

    for (int i = 0; i < months; i++)
    {
        sum = city->TempInfo[i].low + city->TempInfo[i].high;

        if ( sum < cold)
        {
            cold = sum;
            coldestMonth = i;
        }
    }
   cout << "The coldest month is : " << city->TempInfo[coldestMonth].monthName << endl;
}
/**********************************************
* function to display the warmest month
***********************************************/
void displayWarmestMonth(const CityTempInfo *city, int months )
{
    double sum = 0;
    double warm = 0;  // holds warmest temp
    int warmestMonth = 0;

    for (int i = 0; i < months; i++)
    {
        sum = city->TempInfo[i].low + city->TempInfo[i].high;

        if ( sum > warm)
        {
            warm = sum;
            warmestMonth = i;
        }
    }
    cout << "The warmest month is : " << city->TempInfo[warmestMonth].monthName << endl;
}


/**********************************************
* function to open the file
***********************************************/
bool openFileIn(fstream &dataFile, string name)
{
    dataFile.open("citytemps.txt");
    if(dataFile.fail())
        return false;
    else
        return true;
}
