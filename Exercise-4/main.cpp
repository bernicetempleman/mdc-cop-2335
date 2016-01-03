/*
Programmer : Bernice Templeman
COP 2335 Spring 2015 Prof. Zejnilovic
Exercise 4: Palindrome
Date due: April 27th, 2015

Write a program that uses a dynamic stack data structure (implemented with linked list)
to determine if a string is a palindrome.

A simple palindrome is a character string that spells identically backward and forward,
for example
   “rotor”.
If you look up palindrome in Wikipedia (http://en.wikipedia.org/wiki/Palindrome),
you will find examples such as
   Madam, I’m Adam.
Such an example is not a simple palindrome as we would need to ignore spaces and punctuation marks.

For this assignment,
a palindrome is defined to be a character string in which all characters other than alphabetic characters are ignored,
upper-case and lower-case versions of the same letter are counted as equal,
and this character string is the same as its reverse.

An alphabetic character is a character between ‘A’ and ‘Z” (inclusive)
or between ‘a’ and ‘z’ inclusive.

Thus punctuation marks, digits, space, tab, carriage return, hyphens, underscores, and other characters
are not alphabetic characters.

The following is a list of some examples that you could use to test your program
(Hint: use input file):
racecar
RACEcar // uppercase equals lowercase
rotator
rotor
civic
Red rum, sir, is murder! // punctuation and spaces are neglected
Rats live on no evil star.
Neil, a trap! Sid is part alien!
Step on no pets.
Dammit, I’m mad!
Madam, I’m Adam.
Madam, in Eden, I’m Adam.
Rise to vote, sir.
Never odd or even
If I had a hi-fi
Yo, banana boy!
Do geese see God?
No devil lived on."
Ah, Satan sees Natasha."
A dog, a panic in a pagoda
Was it a cat I saw?",
Was it a car or a cat I saw?
No lemons, no melon",
“A dog, a plan, a canal, pagoda,
A man,a plan, a canal-- Panama!"


Note the punctuation marks are there on purpose!
Please make sure that your program evaluates all these examples as palindromes.

Your program should prompt the user to either
enter a phrase or
read input from a file.
In either case the program should output the following to the screen:

String                                  isPalindrome
A man, a plan, a canal, Panama!!!         Y
Hello World!                              N
Radar
                                     Y
The 1st column should contain the string (unformatted),
followed by either a “Y” or “N” (upper-case) to indicate if a string is a palindrome.


This program reads from input file: palindrome.txt or user input.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "DynCharStack.h"
#include "DynCharQueue.h"
#include <iomanip>

using namespace std;

//function prototypes
char displayMenu();
char displayMenu2();
void readFileContents(fstream &);
bool openFileIn(fstream &, string);
void getUserPalindrome(string &);
bool isPalindrome(string );
void printResult(string , bool);
void clearInputBuffer();
void rewindFile(fstream &file);
void displayHeader();

int main()
{

    fstream inputFile;  // input file
    char choice;        // holds user's choic
    string line;        // holds line from file or input
    bool isPal;         // holds true or false if line is a palindrome

    //if file exists:
    if(openFileIn(inputFile,"palindrome.txt"))
    {
        do
        {
            //display menu
            choice = displayMenu();

            switch(choice)
            {
                case '1': //enter a phrase

                    //get user phrase
                    getUserPalindrome(line);

                    //check if it is a palindrome
                    isPal = isPalindrome(line);

                    //display header & result
                    displayHeader();
                    printResult(line, isPal);
                    break;

                case '2': //read from file

                    displayHeader();

                    //readFileContents(inputFile);
                    // rewind to beginning
                    rewindFile(inputFile);

                    //get first line
                    getline(inputFile, line);

                    while (inputFile)
                    {
                        //process line]
                        isPal = isPalindrome(line);
                        printResult(line, isPal);

                        //get next line
                        getline(inputFile, line);
                    }
                    break;

                case '3': //exit
                    cout << "Thank You." << endl;
                    break;

                default:
                    cout << "Invalid choice. Please choose 1, 2, or 3."<<endl;
                    break;
            }
        }while (choice != '3');

        //close file
        inputFile.close();
    }

    else //if file does not exist ask for palindrome
    {
        cout << "file does not exist"<<endl;

        do
        {
            //display menu
            choice = displayMenu2();

            switch(choice)
            {
            case '1':
                //get user phrase
                getUserPalindrome(line);

                //check if it is a palindrome
                isPal = isPalindrome(line);

                //display header & result
                displayHeader();
                printResult(line, isPal);

                break;

            case '2':
                    cout << "Thank You." << endl;
                    break;

            default:
                    cout << "Invalid choice. Please choose 1 or 2."<<endl;
                    break;
            }
        }while (choice != '2');

    }
    return 0;
}
//****************************************************
char displayMenu()
{
    char choice;

    //prompt the user to either enter a phrase or read input from a file.
    cout << endl<<"Palindrome Tester" << endl<<endl;
    cout << "1. Enter a phrase" <<endl;
    cout << "2. Read input from a file"<< endl;
    cout << "3. Exit"<< endl;
    cout << "Your Choice: ";
    cin >> choice;
    clearInputBuffer();

    return choice;

}
//****************************************************
char displayMenu2()
{
    char choice;

    //prompt the user to either enter a phrase or read input from a file.
    cout << endl<<"Palindrome Tester" << endl<<endl;
    cout << "1. Enter a phrase" <<endl;
    cout << "2. Exit"<< endl;
    cout << "Your Choice: ";
    cin >> choice;
    clearInputBuffer();

    return choice;

}
//****************************************************
bool openFileIn(fstream &file, string name)
{
    file.open(name.c_str(), ios::in);
    if (file.fail())
        return false;
    else
        return true;
}
//****************************************************
void readFileContents(fstream &file)
{
    string line;

    while (file)
    {
        getline(file, line);
    }
}
//****************************************************
void getUserPalindrome(string &line)
{
    cout << endl<< "Enter a word or a phrase to test: "<<endl;
    getline(cin, line);
}
//****************************************************
bool isPalindrome(string line)
{
    DynCharStack stack;
    DynCharQueue queue;
    int lineSize;
    char catchVar;
    char value, stackValue, queueValue;
    bool isPal;

    lineSize = line.length();
    for (int i = 0 ; i < lineSize; i++)
    {
        if ((line[i]>= 'A')&&(line[i]<= 'z'))
        {
            stack.push(toupper(line[i]));
            queue.enqueue(toupper(line[i]));
        }
    }

    isPal = true;
    while (!queue.isEmpty() && (!stack.isEmpty()) && (isPal == true) )
    {
        stack.pop(stackValue);
        queue.dequeue(queueValue);
        //cout << stackValue<< " "<< queueValue<<endl;
        if (stackValue != queueValue)
        {
            isPal = false;
        }
    }

    return isPal;
}
//****************************************************
void printResult(string line , bool isPal)
{
    if (isPal)
        cout << left<<setw(42)<<line <<setw(13)<<"Y"<<endl;
    else
        cout << left << setw(42)<<line <<setw(13) <<"N"<<endl;
}

//****************************************************
void clearInputBuffer()
{
    cin.ignore();
    cin.sync();
}
//****************************************************
void rewindFile(fstream &file)
{
    file.clear();
    file.seekg(0L, ios::beg);
}
//****************************************************
void displayHeader()
{
    cout << endl << "String                                  isPalindrome"<< endl;
}
//****************************************************
