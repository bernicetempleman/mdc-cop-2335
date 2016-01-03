#ifndef RECORD_H
#define RECORD_H

#include "Asset.h"

const int MAX_NOTE_LENGTH = 500, MAX_STRING_LENGTH = 50;

class Record
{
    public:
        Record();
        ~Record();

        long GetID() { return ID; }
        void SetID(long val) { ID = val; }
        char* GetassetType() { return assetType; }
        void SetassetType(char* val) { strncpy(assetType, val, MAX_LENGTH); }
        void addRecordNote(char* recNote);
        void printInfo();
        void checkIfRecIsFull();
        void clearRecNotes(int delAmount);
    protected:
    private:
        long ID;
        char assetType[MAX_LENGTH];
        int recordNoteNum;
        char recordNote[MAX_NOTE_LENGTH];
};

#endif // RECORD_H
