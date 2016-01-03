/* Programmer   : Bernice Templeman
 * MidTerm Exam : Number Array Class
 * Date         : 03/05/2015
 *
 */


#include <iostream>
#include "NumberArray.h"

using namespace std;

NumberArray::NumberArray(int size)
{
    //ctor
    //cout << "in constructor"<<endl;
    ptr = new float [size];
}

NumberArray::~NumberArray()
{
    //dtor
    //cout << "in destructor"<< endl;
    delete [] ptr;
}

void NumberArray::StoreNumber( float number, int index)
{
    ptr[index] = number;
}

float NumberArray::RetrieveNumber(int index)
{
    return ptr[index];
}

float NumberArray::HighestNumber(int index)
{
    float highest = ptr[0];

    for (int i = 0; i < index; i++)
    {
        if ( highest < ptr[i])
            highest = ptr[i];
    }
    return highest;
}

float NumberArray::LowestNumber(int index)
{
    float lowest = ptr[0];

    for (int i = 0; i < index; i++)
    {
        if(lowest > ptr[i])
            lowest = ptr[i];
    }
    return lowest;

}

float NumberArray::AverageNumber(int index)
{
    double average =0.0;
    float sum = 0;

    for (int i= 0; i < index; i++)
    {
        sum = sum + ptr[i];
    }

    average = sum / index;
    return average;

}
