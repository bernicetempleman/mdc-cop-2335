#include "Asset.h"

Asset::Asset()
{
    SetID(0);
    for(int i=0; i<MAX_LENGTH; i++)
        location[i] = '\0';
    for(int j=0; j<MAX_LENGTH; j++)
        assetType[j] = '\0';
    for(int k=0; k<MAX_LENGTH; k++)
        status[k] = '\0';
    for(int x=0; x<MAX_LENGTH; x++)
        borrowDate[x] = '\0';
    for(int y=0; y<MAX_LENGTH; y++)
        returnDate[y] = '\0';
    for(int z=0; z<MAX_LENGTH; z++)
        reservationDate[z] = '\0';
}

Asset::~Asset()
{

}

void Asset::printInfo()
{
    for(int a=0; a<80; a++)
        cout << '-';
    cout << endl;
    cout << left;
    cout << setw(21) << "Asset ID Num" << setw(21) << "Asset Type" << setw(21) << "Asset Location" << setw(21) << "Asset Status" << endl;
    cout << setw(21) << ID;
    for(int i=0; i<MAX_LENGTH; i++)
        cout << assetType[i];
    cout << ' ';
    for(int j=0; j<MAX_LENGTH; j++)
        cout << location[j];
    cout << ' ';
    for(int k=0; k<MAX_LENGTH; k++)
        cout << status[k];
    cout << endl;
    if (borrowDate[0] != '\0')
    {
        cout << "\nAsset Borrow Date: ";
        for(int x=0; x<MAX_LENGTH; x++)
            cout << borrowDate[x];
        cout << ' ';
    }
    if (returnDate[0] != '\0' && status[0] == 'I')
    {
        cout << "\nAsset Due Date: ";
        for(int y=0; y<MAX_LENGTH; y++)
            cout << returnDate[y];
        cout << ' ';
    }
    else if (returnDate[0] != '\0')
    {
        cout << "\nAsset Returned On: ";
        for(int y=0; y<MAX_LENGTH; y++)
            cout << returnDate[y];
        cout << ' ';
    }
    if (reservationDate[0] != '\0')
    {
        cout << "\nAsset Reservation Date: ";
        for(int z=0; z<MAX_LENGTH; z++)
            cout << reservationDate[z];
    }
    cout << endl;
}


