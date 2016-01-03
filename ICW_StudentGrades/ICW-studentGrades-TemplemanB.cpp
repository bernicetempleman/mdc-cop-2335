/* Programmers : Bernice Templeman & Braden Harrington
 * ICW : Student Grades

 Description
 1) prompt the1) prompt the user for # of students

 2) For each Student

   prompt the user for student name

   prompt the user for # of quizzes (20%)

   collect quiz scores according to user input

   prompt the user for # of Assignemnts (50%)

   colelct assignment scores for # of quizzes

   prompt the user for the MTE (10%)

   prompt the user for the FE (%20)

 3) for each student calculate the average

 4) determine the letter grade

 5) display student name, score (avg), letter grade  user for # of students

 2) For each Student

   prompt the user for student name

   prompt the user for # of quizzes (20%)

   collect quiz scores according to user input

   prompt the user for # of Assignemnts (50%)

   colelct assignment scores for # of quizzes

   prompt the user for the MTE (10%)

   prompt the user for the FE (%20)

 3) for each student calculate the average

 4) determine the letter grade

 5) display student name, score (avg), letter grade


*/

#include <iostream>

using namespace std;


struct StudentInfo
{
    string name;
    int    id;
    int    quizzes[10];
    int    assignments[10];
    int    midtermExam;
    int    finalExam;
};

//prototypes
void displayStudent(const StudentInfo &, int, int, double, string);
double calculateAverage(const StudentInfo &, int, int);
string letterGrade(double);

int main()
{
    //variables
    int numstuds, quiz, ass;

    // prompt the user for # of students
    cout<<"How many students are in the class: ";
    cin>>numstuds;

    StudentInfo studs[numstuds];

    //loop for each student
    for(int i=0; i<numstuds; i++)
    {
        //prompt for name
        cout<<"What is the student's name: ";
        cin>>studs[i].name;

        //prompt for id
        cout<<"What is the student's ID #: ";
        cin>>studs[i].id;

        //prompt for quiz numbers
        cout<<"How many Quizzes: ";
        cin>>quiz;

        //check if less than max
        while(quiz>=10)
        {

            cout<<"please enter a number less than 10: ";

            cin>>quiz;
        }

        //prompt for quiz grades
        for (int j=0; j<quiz; j++)
        {
            cout << "Quiz # " << j+1 << " score: ";
            cin >> studs[i].quizzes[j];
        }

        //prompt for assignments
        cout<<"How many Assignments: ";
        cin>>ass;

        while(ass>=10)
        {
            cout<<"please enter a number less than 10: ";
            cin>>ass;
        }

        for (int j=0; j<ass; j++)
        {
            cout << "Assignment # " << j+1 << " score: ";
            cin >> studs[i].assignments[j];
        }

        cout<<"Midterm Exam Grade: ";

        cin>>studs[i].midtermExam;

        cout<<"Final Exam Grade: ";

        cin>>studs[i].finalExam;

    }

    for(int i=0; i<numstuds; i++)
    {

        double avg=calculateAverage(studs[i], quiz, ass);

        string grade=letterGrade(avg);

        displayStudent(studs[i], quiz, ass, avg, grade);

    }
    return 0;
}

string letterGrade(double grade)
{
    if(grade>=90) return "A";

    else if(grade<90 && grade>=80) return "B";

    else if(grade<80 && grade>=70) return "C";

    else if(grade<70 && grade>=60) return "D";

    else if(grade<60) return "F";
}

void displayStudent(const StudentInfo & myStudent, int quiz, int ass, double avg, string grade)
{

    cout << "Name : " << myStudent.name << endl;

    cout << "ID : " << myStudent.id << endl;

    // display quizzes
    for (int i=0; i<quiz; i++)
    {
        cout << "Quiz # " << i+1 << " " <<  myStudent.quizzes[i]

             << endl;
    }

    // display assignment

    for (int i=0; i<ass; i++)
    {
        cout << "Assignment # " << i+1 << " " <<   myStudent.assignments[i] << endl;
    }

    cout << "MTE: " << myStudent.midtermExam << endl;

    cout << "Final Exam: " << myStudent.finalExam << endl;

    cout << "Student Letter Grade: "<<grade<<endl;

    cout << "Student Average Grade: "<<avg<<endl;

}

double calculateAverage(const StudentInfo & myStudent, int numQuiz, int numAssignments)
{
    // quiz *.20
    // assignments * .50
    // MTE *.10
    // FE * .20

    int quizTotal = 0;

    int assignmentTotal =0 ;

    for (int i=0; i<numQuiz; i++)
    {
        quizTotal = quizTotal + myStudent.quizzes[i];
    }

    for (int i=0; i<numAssignments; i++)
    {

        assignmentTotal = assignmentTotal +  myStudent.assignments[i];
    }

    return ((quizTotal/numQuiz)*.20)+((assignmentTotal/numAssignments) *.50)+(myStudent.midtermExam*.10)+( myStudent.finalExam*.20);
}
