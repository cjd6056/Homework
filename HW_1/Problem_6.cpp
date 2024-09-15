// AERSP 424 HW 1, Problem 6
// Authors: Conor Dowdell, Gabrielle Dowdell, Chukwu Agbo

#include <iostream>
#include <string>

class Plane; // Forward declaration of the Plane class

class Pilot {
private:
    std::string name;

public:
    // Constructor
    Pilot(const std::string& pilotName) : name(pilotName), myPlane(nullptr) {
        std::cout << "Pilot " << name 
                  << " is at the gate, ready to board the plane." 
                  << " (Address: " << this << ")" << std::endl;
    }

    // Destructor
    ~Pilot() {
        std::cout << "Pilot " << name 
                  << " is out of the plane." << std::endl;
    }

    // Getter function for the name
    std::string getName() const {
        return name;
    }

    // Pointer to a Plane object
    Plane* myPlane;
};

// You would also need to define the Plane class, even if it is empty for now
class Plane {
    // Plane class implementation would go here
};

int main() {
    // Example usage
    Pilot pilot("Robin Olds");
    return 0;
}
