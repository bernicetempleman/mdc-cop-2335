#include <iostream>
#include "DynCharQueue.h"

using namespace std;

//********************************************
// The constructor creates an empty queue.   *
//********************************************
DynCharQueue::DynCharQueue()
{
    front = NULL;
    rear = NULL;
    numItems = 0;
}
//********************************************
// Destructor
//********************************************

DynCharQueue::~DynCharQueue()
{
    clear();
}
//********************************************
// Function enqueue inserts node at the rear of the queue
//********************************************
void DynCharQueue::enqueue(char let)
{
    QueueNode *newNode = NULL;

    // create a new node and store a char there
    newNode = new QueueNode;
    newNode->letter = let;
    newNode->next = NULL;

    //adjust front and rear as necessary
    if (isEmpty())
    {
        front = newNode;
        rear = newNode;
    }
    else{
        rear->next = newNode;
        rear = newNode;

    }

    //update numitems
    numItems++;
}
//********************************************
// Function dequeue remove a node from beginning of queue
//********************************************
void DynCharQueue::dequeue(char &let)
{

    QueueNode *temp = NULL;

    if (isEmpty())
    {
        //cout << "empty"<<endl;
    }
    else
    {
        //save the front node value
        let = front->letter;

        //remove the front node and delete it
        temp = front;
        front = front->next;
        delete temp;

        //update numitems
        numItems--;

    }
}
//********************************************
// Fuction isEmpty returns true if empty
//********************************************
bool DynCharQueue::isEmpty() const
{
    bool status;

    if(numItems > 0)
        status = false;
    else
        status = true;
    return status;
}
//********************************************
// Function clear dequeues all elements in the queue
//********************************************
void DynCharQueue::clear()
{
    char value;

    while(!isEmpty())
        dequeue(value);
}
