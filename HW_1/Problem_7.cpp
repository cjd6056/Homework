// AERSP 424 HW 1, Problem 7
// Authors: Conor Dowdell, Gabrielle Dowdell, Chukwu Agbo
/* Prompt 7...
Now, imagine that there are two pilots flying a plane, e.g., the Pilot-in-Command and the Co-Pilot.
Each of them takes turns to control the plane whenever the plane is landed at SCE. For example, at
the beginning, the first pilot takes off from SCE, flies to the destination, files back, and lands at SCE.
After that, the second pilot takes control of the plane, then takes off from SCE, flies to the
destination, files back, and lands at SCE. After that, the first pilot takes over, and this process keeps
repeating. Write a code to simulate this scenario – i.e., each time we arrive at SCE, you will swap the
the myPlane between the two and change who is in each role.
Use the same velocity, timestep, and the maximum number of iterations as Question 5.
• Before starting an iteration prints out the pilots’ name, pilots’ memory address, and the
memory address of the plane that they are controlling.
• When the plane lands at SCE, print out the memory address of the plane and say that it is at
SCE.
• After switching who’s in control of the plane, print out the pilots’ name and the memory
address of the plane that they are controlling.
• Pilot objects are instantiated from the “Pilot” class in Question 6.
• The plane object is from Question 3 & 4.
*/
#include <iostream>
#include <map>
#include <string>
#include <utility> // for std::pair
#include <vector>  // for std::vector

using AirportPair = std::pair<std::string, std::string>;
using DistanceMap = std::map<AirportPair, int>;

// Define distances between airport pairs
DistanceMap flightDistances = {
    {{"SCE", "PHL"}, 160},  // 160-mile flight between SCE and PHL
    {{"PHL", "SCE"}, 160}}; // 160-mile flight between PHL and SCE (round-trip)

class Plane;

// Pilot class definition
class Pilot {
private:
    std::string name;

public:
    Pilot(const std::string& pilotName) : name(pilotName), myPlane(nullptr) {
        std::cout << "Pilot " << name
                  << " with certificate number " << this
                  << " is at the gate, ready to board the plane." << std::endl;
    }

    ~Pilot() {
        std::cout << "Pilot " << name << " is out of the plane." << std::endl;
    }

    std::string getName() const { return name; }

    Plane* myPlane; // Pointer to the plane controlled by the pilot
};

// Plane class definition
class Plane {
private:
    double pos;
    double vel;
    double distance;
    bool at_SCE;
    std::string origin;
    std::string destination;

    // Retrieve distance between two airports
    double getDistanceBetweenAirports(const std::string& from,
                                      const std::string& to) {
        auto it = flightDistances.find({from, to});
        if (it != flightDistances.end()) {
            return it->second;
        }
        it = flightDistances.find({to, from});
        if (it != flightDistances.end()) {
            return it->second;
        }
        return 0.0;
    }

public:
    // Constructor
    Plane(const std::string& from, const std::string& to)
        : origin(from), destination(to), pos(0), vel(0), at_SCE(true) {
        distance = getDistanceBetweenAirports(from, to);
        std::cout << "Plane created with tail number " << this << std::endl;
    }

    double getPos() const { return pos; }

    std::string getOrigin() const { return origin; }

    std::string getDestination() const { return destination; }

    bool isAtSCE() const { return at_SCE; }

    double getVel() const { return vel; }

    void setVel(double newVel) {
        vel = (newVel < 0) ? 0 : newVel; // Prevent negative velocity
    }

    // Function to simulate the plane's operation
    void operate(double dt) {
        if (dt < 0) {
            dt = 0; // Prevent negative time
        }

        if (pos < distance) {
            pos += vel * dt;
        } else {
            if (destination == "SCE") {
                at_SCE = true;  // Mark the plane is at SCE
                pos = 0.0;      // Reset position for the next leg
                std::swap(origin, destination);  // Swap origin and destination
            } else {
                at_SCE = false;  // Mark that the plane is not at SCE anymore
            }
        }
    }

    // Indicate completion of a leg and reset the plane to SCE
    void completeLeg() {
        at_SCE = true;
        std::cout << "The plane " << this << " is at SCE" << std::endl;
    }
};

int main() {
    // Create two pilots
    Pilot pilot1("Robin Olds");
    Pilot pilot2("Amelia Earhart");

    // Create the initial plane alternating between SCE and PHL
    Plane* myPlane = new Plane("SCE", "PHL");
    myPlane->setVel(450.0 / 3600.0); // Set the plane's velocity
    double timestep = 15.0;
    int maxIterations = 1000;

    // Assign plane to the first pilot
    pilot1.myPlane = myPlane;
    pilot2.myPlane = nullptr;

    Pilot* currentPilot = &pilot1;
    Pilot* nextPilot = &pilot2;

    std::cout << "Pilot " << currentPilot->getName()
              << " with certificate number " << currentPilot
              << " is in control of a plane: " << currentPilot->myPlane
              << std::endl;

    for (int i = 0; i < maxIterations; ++i) {
        myPlane->operate(timestep);

        if (myPlane->isAtSCE()) {
            std::cout << "\nNavigation from " << myPlane->getOrigin() << " to "
                      << myPlane->getDestination()
                      << " has been completed. On to the next leg!" << std::endl;

            myPlane->completeLeg();

            // Swap the pilots
            std::swap(currentPilot, nextPilot);

            std::cout << "Pilot " << currentPilot->getName()
                      << " with certificate number " << currentPilot
                      << " is in control of a plane: " << currentPilot->myPlane
                      << std::endl;

            // Switch to the next leg by swapping origin and destination
            myPlane->setVel(450.0 / 3600.0); // Reset velocity
        }
    }

    return 0;
}
