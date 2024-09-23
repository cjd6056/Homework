// AERSP 424 HW 1, Problem 6
// Authors: Conor Dowdell, Gabrielle Dowdell, Chukwu Agbo
//NOTE: This “Question” is just to setup the class, no “real” functionality to test (yet).

/*
Create a class “Pilot” with the following members and implementation.
• Private members:
o string variable named “name”
• Public members:
o constructor that prints out the pilot’s name, memory address, and say that the pilot is
at the gate, ready to board the plane
o deconstructor that prints out the pilot’s name and say that the pilot is out of the
plane
o getter function of the variable “name”
o pointer, named “myPlane”, to an object of the “Plane” class
*/

#include <iostream>
#include <string>

class Plane; // Forward declaration of the Plane class

class Pilot 
{
private:
    std::string name;

public:
    // Constructor
    Pilot(const std::string& pilotName) : name(pilotName), myPlane(nullptr) 
    {
        std::cout << "Pilot " << name 
                  << " is at the gate, ready to board the plane." 
                  << " (Address: " << this << ")" << std::endl;
    }

    // Destructor
    ~Pilot() 
    {
        std::cout << "Pilot " << name 
                  << " is out of the plane." << std::endl;
    }

    // Getter function for the name
    std::string getName() const 
    {
        return name;
    }

    // Pointer to a Plane object
    Plane* myPlane;
};

// You would also need to define the Plane class, even if it is empty for now
class Plane 
{
    // Plane class implementation would go here
};

int main() 
{
    // Example usage
    Pilot pilot("Robin Olds");
    return 0;
}
