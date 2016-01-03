/* Programmer : Bernice Templeman
 * Class      : COP2335
 * Exercise 3 : Hospital Bill
*/

#include <iostream>
#include <string>

#include "Doctor.h"
#include "Patient.h"
#include "HospitalCharges.h"
#include "Hospital.h"
#include "HospitalBill.h"

using namespace std;

int main()
{

    //Inheritance (Doctor & patient inherit from Person

    //create doctor
    cout << "Create Doctor 1:"<< endl;
    Doctor *myDoctor =  new Doctor("CS","Bernice", "Templeman");
    cout << "Doctor: " << myDoctor->GetfirstName()<<" " << myDoctor->GetlastName()<< endl;
    cout << "Specialty: " << myDoctor->GetSpecialty() <<endl;
    cout << endl <<endl;

    cout << "Print: " << endl;
    myDoctor->print();

    cout << "Create Doctor 2:"<< endl;
    Doctor *myDoctor2 =  new Doctor("NM","Randy", "Gage");
    cout << "Doctor: " << myDoctor2->GetfirstName()<<" " << myDoctor2->GetlastName()<< endl;
    cout << "Specialty: " << myDoctor2->GetSpecialty() <<endl;
    cout << endl <<endl;

    cout << "Print: " << endl;
    myDoctor2->print();

    cout << "Create Patient 1: " << endl;
    Patient  *myPatient = new Patient("01", "MMDDYYY", "Dr. Name", "0101YYYY", "B", "T");
    cout << "Patient: " << myPatient->GetfirstName()<<" "  << myPatient->GetlastName()<<endl;
    cout << "Patient ID: "<< myPatient->GetpatientID() << endl;
    cout << "Date of Birth: "<< myPatient ->GetdateOfBirth()<<endl;
    cout << "Attending Physician: "<< myPatient->GetattendingPhysician()<<endl;
    cout << "Date Admitted to Hospital: "<< myPatient->GetdateAdmittedToHospital()<<endl;
    cout << endl <<endl;

    cout << "Print"<<endl;
    myPatient->print();

    cout << "Create Patient 2: " << endl;
    Patient  *myPatient2 = new Patient("02", "MMDDYYY", "Dr2. Name2", "0201YYYY", "2First", "2Last");
    cout << "Patient: " << myPatient2->GetfirstName()<<" "  << myPatient2->GetlastName()<<endl;
    cout << "Patient ID: "<< myPatient2->GetpatientID() << endl;
    cout << "Date of Birth: "<< myPatient2 ->GetdateOfBirth()<<endl;
    cout << "Attending Physician: "<< myPatient2->GetattendingPhysician()<<endl;
    cout << "Date Admitted to Hospital: "<< myPatient2->GetdateAdmittedToHospital()<<endl;
    cout << endl <<endl;

    cout << "Print"<<endl;
    myPatient2->print();

    //Aggregation : Class contains an instance of another class

    cout << "Create Hospital Bill: " << endl;
    HospitalBill *myHospitalBill = new HospitalBill("hosName","pid", 0.01,0.02,0.03,0.04);
    cout << "Hospital Name: " << myHospitalBill->GethospitalName()<< endl;
    cout << "Patient ID: " << myHospitalBill->GetpatientID() <<endl;
 /*   cout << "Hospital Charges:" << endl;
    cout << "   pharmacy: " << myHospitalBill->hospitalCharges.GetpharmacyCharges() <<endl;
    cout << "   doctor: " << myHospitalBill->hospitalCharges.GetdoctorFees()<< endl;
    cout << "   room: " << myHospitalBill->hospitalCharges.GetroomCharges() <<endl;
    cout << "   X-Ray Charges: " << myHospitalBill->hospitalCharges.GetxRayCharges() <<endl;
  */  cout << endl <<endl;

    cout << "Print:"<< endl;
    myHospitalBill->print();


    cout << "Create Hospital:"<< endl;
    Hospital *myHospital = new Hospital("Hospital", "000111222", "123-456-7890");
    cout << "Hospital: "<< myHospital->GetHospitalName()<< endl;
    cout << "URL: " << myHospital->GethospitalURL()<<endl;
    cout << "Telephone: "<< myHospital->GethospitalTelephoneNumber()<<endl<<endl;

    cout << "Print:"<<endl;
    myHospital->print();

    cout << "Deallocate memory:" << endl;
    delete myDoctor;
    delete myDoctor2;
    delete myPatient;
    delete myPatient2;
    delete myHospitalBill;
    delete myHospital;

    return 0;
}
