#ifndef PERSON_H
#define PERSON_H

#include "Asset.h"

const int MAX_LIMIT_ASSET = 30, MAX_LIMIT_DATE = 180;

class Person
{
    public:
        Person();
        virtual ~Person();
        char* GetfirstName() { return firstName; }
        void SetfirstName(char* val) { strncpy(firstName, val, MAX_LENGTH); }
        char* GetlastName() { return lastName; }
        void SetlastName(char* val) { strncpy(lastName, val, MAX_LENGTH); }
        char* GetcollegeID() { return collegeID; }
        void SetcollegeID(char* val) { strncpy(collegeID, val, MAX_LENGTH); }
        char* GetphoneNum() { return phoneNum; }
        void SetphoneNum(char* val) { strncpy(phoneNum, val, MAX_LENGTH); }
        char* Getemail() { return email; }
        void Setemail(char* val) { strncpy(email, val, MAX_LENGTH); }
        char* Getdepartment() { return department; }
        void Setdepartment(char* val) { strncpy(department, val, MAX_LENGTH); }
        Asset GetassetListMember(int num) { return assetList[num]; }
        void SetassetList(long ID, char* location, char* type, char* status, char* borrowDate, char* returnDate, char* reservationDate, int listNum);
        int Getamount() {return amount;}
        void Setamount(int val) {amount = val;}

        void printInfo();
        int findAssetListNum(long id);
        void removeAnAssetFromList(int listNum);
        void removeAllAssetsFromList();

    private:
        char firstName[MAX_LENGTH];
        char lastName[MAX_LENGTH];
        char collegeID[MAX_LENGTH];
        char phoneNum[MAX_LENGTH];
        char email[MAX_LENGTH];
        char department[MAX_LENGTH];
        Asset assetList[MAX_LIMIT_ASSET];
        int amount;
};

#endif // PERSON_H
