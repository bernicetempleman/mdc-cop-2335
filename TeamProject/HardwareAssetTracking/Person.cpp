#include "Person.h"

Person::Person()
{
    for(int i=0; i<MAX_LENGTH; i++)
        firstName[i] = '\0';
    for(int j=0; j<MAX_LENGTH; j++)
        lastName[j] = '\0';
    for(int k=0; k<MAX_LENGTH; k++)
        phoneNum[k] = '\0';
    for(int x=0; x<MAX_LENGTH; x++)
        email[x] = '\0';
    for(int z=0; z<MAX_LENGTH; z++)
        department[z] = '\0';
    for(int a=0; a<MAX_LENGTH; a++)
        collegeID[a] = '\0';
    for(int y = 0; y < MAX_LIMIT_ASSET; y++)
        Asset assetList[y];
    amount = 0;
}

Person::~Person()
{
    //dtor
}

void Person::SetassetList(long ID, char* location, char* type, char* status, char* borrowDate, char* returnDate, char* reservationDate, int listNum)
{
    assetList[listNum].SetID(ID);
    assetList[listNum].Setlocation(location);
    assetList[listNum].SetassetType(type);
    assetList[listNum].Setstatus(status);
    assetList[listNum].SetborrowDate(borrowDate);
    assetList[listNum].SetreturnDate(returnDate);
    assetList[listNum].SetreservationDate(reservationDate);

}

void Person::printInfo()
{
    for(int a=0; a<80; a++)
        cout << '-';
    cout << endl;
    for(int b=0; b<80; b++)
        cout << '-';
    cout << endl;
    cout << left;
    cout << setw(21) << "First Name" << setw(21) << "Last Name" << setw(21) << "College ID" << setw(21) << "Department" << endl;
    for(int k=0; k<MAX_LENGTH; k++)
        cout << firstName[k];
    cout << ' ';
    for(int l=0; l<MAX_LENGTH; l++)
        cout << lastName[l];
    cout << ' ';
    for(int j=0; j<MAX_LENGTH; j++)
        cout << collegeID[j];
    cout << ' ';
    for(int i=0; i<MAX_LENGTH; i++)
        cout << department[i];
    cout << endl;
    cout << setw(21) << "Phone Number" << setw(21) << "E-mail Address" << endl;
    for(int m=0; m<MAX_LENGTH; m++)
        cout << phoneNum[m];
    cout << ' ';
    for(int n=0; n<MAX_LENGTH; n++)
        cout << email[n];
    cout << endl;

    for (int i=0; i<amount; i++)
        assetList[i].printInfo();
}

int Person::findAssetListNum(long id)
{
    int num = -1;
    for (int i=0; i<amount; i++)
    {
        if (assetList[i].GetID() == id)
            num = i;
    }

    return num;
}

void Person::removeAnAssetFromList(int listNum)
{
    int counter = 0;
    int oldAmountNum = amount;

    Asset newAssetList[amount];

    for (int i=0; i<amount; i++)
    {
        if (listNum != i)
        {
           newAssetList[counter] = assetList[i];
           counter++;
        }
    }

    removeAllAssetsFromList();

    amount = oldAmountNum-1;
    for(int j=0; j<amount; j++)
        assetList[j] = newAssetList[j];

}

void Person::removeAllAssetsFromList()
{
    char temp[MAX_LENGTH];
    for (int x=0; x<MAX_LENGTH; x++)
        temp[x] = '\0';

    for (int i=0; i<amount; i++)
        SetassetList(0, temp, temp, temp, temp, temp, temp, i);

   Setamount(0);
}
