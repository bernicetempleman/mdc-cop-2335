#include "Record.h"

Record::Record()
{
    ID = 0;
    for (int j=0; j<MAX_LENGTH; j++)
        assetType[j] = '\0';
    recordNoteNum = 0;
    for (int i=0; i<MAX_NOTE_LENGTH; i++)
        recordNote[i] = '\0';
}

Record::~Record()
{
    //dtor
}

void Record::addRecordNote(char* recNote)
{
    char temp[MAX_STRING_LENGTH];
    strcpy(temp, recNote);
    strcat(recordNote, temp);
}

void Record::printInfo()
{
    for(int a=0; a<80; a++)
        cout << '-';
    cout << endl;
    cout << left;
    cout << setw(21) << "Asset ID" << setw(21) << "Asset Type" << endl;
    cout << setw(21) << ID;
    for(int b=0; b<MAX_LENGTH; b++)
        cout << assetType[b];
    cout << endl << "Record History:" << endl;

    for(int c=0; c<MAX_NOTE_LENGTH; c++)
    {
        if ( recordNote[c] != '\0')
            cout << recordNote[c];
    }

}

void Record::checkIfRecIsFull()
{
    int counter = 0, delCounter = 0;

    for (int i=0; i<MAX_NOTE_LENGTH; i++)
    {
        if (recordNote[i] != '\0')
            counter++;
        else if (recordNote[i] == '\n')
            delCounter++;

        if (delCounter == 5)
            break;
    }

    if (counter >= 420)
        clearRecNotes(delCounter);
}

void Record::clearRecNotes(int delAmount)
{
    char read[MAX_NOTE_LENGTH - delAmount];
    for (int i=0; i<(MAX_NOTE_LENGTH - delAmount); i++)
        read[i] = recordNote[delAmount+i];
    for (int j=0; j<MAX_NOTE_LENGTH; j++)
        recordNote[j] = '\0';
    for (int k=0; k<(MAX_NOTE_LENGTH - delAmount); k++)
        recordNote[k] = read[k];
}
