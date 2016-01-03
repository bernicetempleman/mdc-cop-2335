/*
   Programmer : Bernice Templeman
   Quiz 4

   Given the following program,
    write the main function
   to demonstrate polymorphimsm
*/

#include <iostream>

using namespace std;

int const NUM_ANIMALS = 9;

class Animal
{
    private:
        string vocabulary;
    public:
        Animal() {vocabulary = "I DO NOT SPEAK ANY ANIMAL";}
        virtual string speak() {return vocabulary;}
};

class Horse : public Animal
{
    private:
        string vocabulary;
    public:
        Horse() {vocabulary = "Neighs";}
        string speak() {return vocabulary;}
};

class Cow : public Animal
{
    private:
        string vocabulary;
    public:
        Cow() {vocabulary = "Moos";}
        string speak() {return vocabulary;}
};

class Chicken : public Animal
{
    private:
        string vocabulary;
    public:
        Chicken() {vocabulary = "Clucks";}
        string speak() {return vocabulary;}
};

class Pig : public Animal
{
    private:
        string vocabulary;
    public:
        Pig() {vocabulary = "Squeals";}
        string speak() {return vocabulary;}
};

class Dog : public Animal
{
    private:
        string vocabulary;
    public:
        Dog() {vocabulary = "Barks";}
        string speak() {return vocabulary;}
};

class Cat : public Animal
{
    private:
        string vocabulary;
    public:
        Cat() {vocabulary = "Meows";}
        string speak() {return vocabulary;}
};

void doSpeak(Animal *);

int main(int argc, char *argv[])
{
    // Dynammically allocate an array called
    // farm of NUM_ANIMALS
    //
    // populate the array
    //
    // use a for loop to invoke the speak method
    // thereby demonstrating polymorphic behavior



    Animal *farm;
    farm = new Animal[NUM_ANIMALS];

    Animal *dog = new Dog();
    Animal *cat = new Cat();
    Animal *pig = new Pig();
    Animal *cow = new Cow();
    Animal *chicken = new Chicken();
    Animal *horse = new Horse();

    doSpeak(dog);
    doSpeak(cat);
    doSpeak(pig);
    doSpeak(cow);
    doSpeak(chicken);
    doSpeak(horse);


    for(int i = 0; i < NUM_ANIMALS; i++)
    {
        doSpeak(farm[i]);
    }

    delete farm;

    delete dog;
    delete cat;
    delete pig;
    delete cow;
    delete chicken;
    delete horse;

}

void doSpeak(Animal *animal)

{

    cout << animal->speak() << endl;

}
===================

#include <cstdlib>

#include <iostream>




using namespace std;




int const NUM_ANIMALS = 9;




class Animal

{

    private:

        string vocabulary;

    public:

        Animal() {vocabulary = "I DO NOT SPEAK ANY ANIMAL";}

        virtual string speak() {return vocabulary;}

};




class Horse : public Animal

{

    private:

        string vocabulary;

    public:

        Horse() {vocabulary = "Neighs";}

        string speak() {return vocabulary;}

};




class Cow : public Animal

{

    private:

        string vocabulary;

    public:

        Cow() {vocabulary = "Moos";}

        string speak() {return vocabulary;}

};




class Chicken : public Animal

{

    private:

        string vocabulary;

    public:

        Chicken() {vocabulary = "Clucks";}

        string speak() {return vocabulary;}

};




class Pig : public Animal

{

    private:

        string vocabulary;

    public:

        Pig() {vocabulary = "Squeals";}

        string speak() {return vocabulary;}

};




class Dog : public Animal

{

    private:

        string vocabulary;

    public:

        Dog() {vocabulary = "Barks";}

        string speak() {return vocabulary;}

};




class Cat : public Animal

{

    private:

        string vocabulary;

    public:

        Cat() {vocabulary = "Meows";}

        string speak() {return vocabulary;}

};







int main(int argc, char *argv[])

{

    Animal *farm[NUM_ANIMALS];

    farm[0] = new Horse();

    farm[1] = new Chicken();

    farm[2] = new Pig();

    farm[3] = new Cow();

    farm[4] = new Cat();

    farm[5] = new Dog();

    farm[6] = new Chicken();

    farm[7] = new Dog();

    farm[8] = new Chicken();




    for (int i=0; i<NUM_ANIMALS; i++)

       cout << farm[i]->speak() << endl;




    // delete missing






    system("PAUSE");

    return EXIT_SUCCESS;

}
