#ifndef ASSET_H
#define ASSET_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include <iomanip>

const int MAX_LENGTH = 20;

using namespace std;

class Asset
{
    public:
        Asset();
        ~Asset();

        long GetID() { return ID; }
        void SetID(long val) { ID = val; }
        char* Getlocation() { return location; }
        void Setlocation(char* val) { strncpy(location, val, MAX_LENGTH); }
        char* GetassetType() { return assetType; }
        void SetassetType(char* val) { strncpy(assetType, val, MAX_LENGTH); }
        char* Getstatus() { return status; }
        void Setstatus(char* val) { strncpy(status, val, MAX_LENGTH); }
        char* GetborrowDate() { return borrowDate; }
        void SetborrowDate(char* val) { strncpy(borrowDate, val, MAX_LENGTH); }
        char* GetreturnDate() { return returnDate; }
        void SetreturnDate(char* val) { strncpy(returnDate, val, MAX_LENGTH); }
        char* GetreservationDate() { return reservationDate; }
        void SetreservationDate(char* val) { strncpy(reservationDate, val, MAX_LENGTH); }

        void printInfo();

    private:
        long ID;
        char location[MAX_LENGTH];
        char assetType[MAX_LENGTH];
        char status[MAX_LENGTH];
        char borrowDate[MAX_LENGTH];
        char returnDate[MAX_LENGTH];
        char reservationDate[MAX_LENGTH];
};

#endif // ASSET_H
