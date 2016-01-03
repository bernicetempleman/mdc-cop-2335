#include <iostream>
#include "DynCharStack.h"

using namespace std;

//**************************************************
// Destructor                                      *
// This function deletes every node in the list.   *
//**************************************************
DynCharStack::~DynCharStack()
{
    StackNode *nodePtr = NULL, *nextNode = NULL;

    //position nodePtr at top of the stack.
    nodePtr = top;

    //Traverse the list deleting each node.
    while(nodePtr != NULL)
    {
        nextNode = nodePtr ->next;
        delete nodePtr;
        nodePtr = nextNode;
    }
}

//**************************************************
// Member Function push                            *
// pushes the argument onto the stack.             *
//**************************************************

void DynCharStack::push (char let)
{
    StackNode *newNode = NULL; //Ptr to a new node

    //Allocate a new node and store a letter there.
    newNode = new StackNode;
    newNode->letter = let;

    // If there are no nodes in the list
    // make newNode the first node.
    if (isEmpty())
    {
        top = newNode;
        newNode->next = NULL;
    }
    else // Otherwise, insert NewNode before top.
    {
        newNode->next = top;
        top = newNode;
    }
}
//**************************************************
// Member Function pop                             *
// pops the value at the top of the stack off and  *
// copies it into the variable passed as argument  *            *
//**************************************************
void DynCharStack::pop(char &let)
{
    StackNode *temp = NULL; //temporary pointer

    //First make sure the stack isn't empty.
    if(isEmpty())
    {
        //cout << "the stack is empty.\n";
    }
    else // pop value off top of stack
    {
        let = top->letter;
        temp = top->next;
        delete top;
        top = temp;
    }
}

//**************************************************
// Member Function isEmpty                         *
// returns true if the stack is empty              *
// or false otherwise                              *
//**************************************************
bool DynCharStack::isEmpty()
{
    bool status;

    if (!top)
        status = true;
    else
        status = false;
    return status;
}
/*
DynCharStack::DynCharStack()
{
    //ctor
}

DynCharStack::~DynCharStack()
{
    //dtor
}
*/

