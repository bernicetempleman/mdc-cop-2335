/**********************************************
 * Programmer : Bernice Templeman
 * Class      : COP 2335
 * ICW        : Linked Lists

/**********************************************/

#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

const int SIZE = 35;

struct Entry
{
    char name[SIZE];
    int  age;
    Entry *next;
};

/**********************************************/

// Getting Started

/**********************************************/
void displayEntry(Entry* e)
{
    cout << e->name << "   " << e->age << endl;
}

Entry* getNewEntry()
{
    char name[SIZE];
    cout << "Enter a new name (ENTER to quit):";
    cin.getline(name,SIZE);     if (strlen(name) == 0)
    {
        cout << "You pressed ENTER" << endl;
        return NULL;
    }

    Entry *newOne = new Entry;
    strcpy(newOne->name, name);
    cout << "Age: ";
    cin >> newOne->age;
    cin.ignore(1024,'\n');
    newOne->next = NULL;
    return newOne; }

    //The function allocates a new Entry structure on the heap, and populates its members with user supplied data.
    //The function returns a NULL pointer if the user presses the ENTER key when entering person’s name.
    //The test case for this function follows:
/*
    int main(int argc, char *argv[])
    {
        Entry* newOne = getNewEntry();
        if (newOne)
            displayEntry(newOne);

        system("PAUSE");
        return EXIT_SUCCESS;
    }
*/


/**********************************************/

// Adding Nodes at beginning of list

/**********************************************/
/*
bool addFirst(Entry* newEntry, Entry* &head)
{
    if (newEntry == NULL)
        return false;
    newEntry->next = head;
    head = newEntry;
    return true;
}
/*
Entry* buildList()
{
    Entry *listHead = NULL;
    // start of the list
    while(true)
        {
            Entry *newOne = getNewEntry();
            // add to the beginning
            if(!addFirst(newOne, listHead))
                break;
        }
        return listHead;
}
*/
//We also introduce the displayList function at this point:
void displayList(Entry *list)
{
    for (Entry *current = list; current!=NULL; current = current->next)
        displayEntry(current);
}

    // And the main function is basically calling the buildList function,
    // and the displayList function:
/*
int main(int argc, char *argv[])
{
    Entry* listHead = buildList();
    displayList(listHead);

    system("PAUSE");
    return EXIT_SUCCESS;
}
*/
/**********************************************/

// Adding Nodes at end of list

/**********************************************/
/*
//The following function called addLast demonstrates that:
bool addLast(Entry* newEntry, Entry* &head)
{
    if (newEntry == NULL)
        return false;
    Entry* current;
    current = head;
    do
    {
        current= current->next;
    }while(current==NULL);

    // Set the current's next to the newEntry
    current->next = newEntry;
    return true;
    }
 //And here are the changes to the main function:
 int main(int argc, char *argv[])
 {
    Entry* listHead = buildList();
    displayList(listHead);
    Entry* lastEntry = getNewEntry();
    if (!addLast(lastEntry, listHead))
    {
            return EXIT_FAILURE;;
    }     cout << "Will display the list now: " << endl;
    displayList(listHead);

    system("PAUSE");
    return EXIT_SUCCESS;
}
*/
/*********************************************/
// Check if empty
/*********************************************/
//All we need to do is check whether the list is empty:

bool addLast(Entry* newEntry, Entry* &head)
{
    if (newEntry == NULL)
        return false;
    else
    {
        Entry* current;
        current = head;
        if (head == NULL)
        {
            head = newEntry;
        }
        else
        {
            // traverse the list to get to the end
            while(current->next != NULL)
            {
                current = current->next;
            }

            // Set the current's next to the newEntry
            current->next = newEntry;
        }

    }
    return true;
}
/*
//We also make a minimal change to the buildList function:
Entry* buildList()
{
    Entry *listHead = NULL;
    // start of the list
    while(true)
    {
        Entry *newOne = getNewEntry();
    // add to the beginning
    if(!addLast(newOne, listHead))
        break;
    }
    return listHead;
}

/*
//And to int main:
int main(int argc, char *argv[])
{
    Entry* listHead = buildList();
    displayList(listHead);

    system("PAUSE");
    return EXIT_SUCCESS;
}
*/
/********************************************/

//Using pointers

/*********************************************/

//Using Pointers to Keep Track of Positions in the List
//So far, we only dealt with the head (of the list) pointer,
//but what if we need to keep track of the end (“tail”) of the list as well?
//What are the benefits of implementing a list with both head and tail pointers?
//for a few extra lines of code,
//we can get additional flexibility and speed to be able to add the new node to the list immediately
//rather than traversing through the list.
//This can be accomplished by keeping track of the head and tail position,
//and also, the current, and the previous positions in the list.
//We will rewrite our functions to demonstrate that:
//addFirst with “tail”

bool addFirst(Entry* newEntry, Entry* &head, Entry* &tail)
{
    if (newEntry == NULL)
        return false;
    else
    {
        if (head == NULL)
        {
            head = newEntry;
            tail = newEntry;
        }
        else
        {
            newEntry->next = head;
            head = newEntry;
        }
    }
    return true;
}
/*
//We also make a change in the buildList:
Entry* buildList()
{
    Entry *listHead = NULL;
    // start of the list
    Entry* listTail = NULL;
    while(true)
    {
        Entry *newOne = getNewEntry();

        // add to the beginning
        if(!addFirst(newOne, listHead, listTail))
            break;
    }
    return listHead;
}
*/
//Next, we compile, and execute our program with the familiar input:
//addLast with “tail”:
bool addLast(Entry* newEntry, Entry* &head, Entry* &tail)
{
    if (newEntry == NULL)
        return false;
    else
    {
        Entry* current;
        current = head;
        if (head == NULL)
        {
            head = newEntry;
            tail = newEntry;
        }
        else
        {
            tail->next = newEntry;
            tail = newEntry;
        }
    }
    return true;
}
/*
//Changes in the buildList:
Entry* buildList()
{
    Entry *listHead = NULL;
    // start of the list
    Entry* listTail = NULL;
    while(true)
    {
        Entry *newOne = getNewEntry();
        // add to the beginning
        if(!addLast(newOne, listHead, listTail))
            break;
    }
    return listHead;
}


int main(int argc, char *argv[])
{
    Entry* listHead = buildList();
    displayList(listHead);

    system("PAUSE");
    return EXIT_SUCCESS;
}
*/
 /*******************************************/

 // Adding in the middle of the list

 /*******************************************/
bool addAnywhere(Entry* &previous, Entry* newEntry, Entry* &head, Entry* &tail)
{
    if (newEntry == NULL)
        return false;
    else
    {
        if (previous == NULL)
        {
            addFirst(newEntry, head, tail);
        }
        else if (previous == tail)
        {
            addLast(newEntry, head, tail);
        }
        else
        {
            Entry* next = previous->next;
            previous->next = newEntry;
            newEntry->next = next;
        }
        return true;
    }
}
/*
void traverseList(Entry* &head, Entry* &tail, Entry* newEntry)
 {
     Entry* current;
     Entry* previous;
     bool found = false;
     current = head;
     previous = NULL;
    while ((current != NULL) && !found)
    {
        if (newEntry->age >= current->age)
        {
            found = true;
        }
        else
        {
            previous = current;
            current = current->next;
        }
     }
    if (!addAnywhere(previous, newEntry, head, tail))
    {
        cout << "Failed to addAnywhere!" << endl;
        found = false;
    }
}
*/

Entry* buildList(Entry* &tail)
{
    Entry *listHead = NULL;
    // start of the list

    while(true)
    {
        Entry *newOne = getNewEntry();

        // add to the end
        if(!addLast(newOne, listHead, tail))
            break;
    }
    return listHead; }
/*
int main(int argc, char *argv[])
{
    Entry* listTail = NULL;
    Entry* listHead = buildList(listTail);
    displayList(listHead);

    // get an entry and add it
    Entry* newOne = getNewEntry();
    if (newOne)
        traverseList(listHead, listTail, newOne);
    displayList(listHead);

    system("PAUSE");
    return EXIT_SUCCESS;
}
*/
/**********************************************/

//Deleting a node from the list

/**********************************************/

bool removeFirst(Entry* &head, Entry* &tail)
{
    if (head == NULL)
        return false;
    else
    {
        Entry* toBeDeleted;
        toBeDeleted = head;
        if (head == tail)
        {
            head = NULL;
            tail = NULL;
        }
        else
        {
            head = head->next;
        }
        delete toBeDeleted;
    }
    return true;
}
/*
int main(int argc, char *argv[])
{
    Entry* listTail = NULL;
    Entry* listHead = buildList(listTail);
    displayList(listHead);
    removeFirst(listHead, listTail);
    cout << "The list after the first node was removed:" << endl;
    displayList(listHead);
    system("PAUSE");
    return EXIT_SUCCESS;
}
*/
/**********************************************/

// Removing the last node

/**********************************************/

bool removeLast(Entry* &head, Entry* &tail)
{
    if (tail == NULL)
        return false;
    else
    {
        Entry* toBeDeleted;

        toBeDeleted = tail;

        if (head == tail)
        {
            head = NULL;
            tail = NULL;
        }
        else
        {
            Entry* previous;
            previous = head;
            while (previous->next != tail)
                previous = previous->next;
                tail = previous;
                tail->next = NULL;
        }
        delete toBeDeleted;
    }
}

int main(int argc, char *argv[])
{
    Entry* listTail = NULL;
    Entry* listHead = buildList(listTail);

    displayList(listHead);

    removeLast(listHead, listTail);
    cout << "The list after the last node was removed:" << endl;
    displayList(listHead);

    system("PAUSE");
    return EXIT_SUCCESS;
}

/**********************************************/

// Deleting a node in the middle of the list

/**********************************************/

bool removeAnywhere(Entry* &previous, int age, Entry* &head, Entry* &tail)
{
    if (previous == NULL)
        removeFirst(head, tail);
    else if (previous->next == tail)
    {
        Entry* toBeRemoved;
        toBeRemoved = previous->next;
        tail = previous;
        tail->next = NULL;
        delete toBeRemoved;
    }
    else if (previous == tail)
    {
        Entry* toBeRemoved;
        toBeRemoved = previous->next;
        previous->next = toBeRemoved->next;
        delete toBeRemoved;
    }
}

// Since the  removeAnywhere function removes a node when a match between members called”age” is found,
// we need to make a small change in traverseList function:
void traverseList(Entry* &head, Entry* &tail, Entry* newEntry)
{
    Entry* current;
    Entry* previous;
    bool found = false;
    current = head;
    previous = NULL;
    while ((current != NULL) && !found)
        {
            if (newEntry->age >= current->age)
            {
                found = true;
            }
            else
            {
                previous = current;
                current = current->next;
            }

        }
        if (!removeAnywhere(previous, newEntry->age, head, tail))
        {
            cout << "Failed to addAnywhere!" << endl;
            found = false;
        }
}

