/*AERSP 424 HW 1, Problem 8
   Authors: Conor Dowdell, Gabrielle Dowdell, Chukwu Agbo, Shanon Hyde
   Prompt 8: If you write a code in Question 7 using an old C/CPP-style pointer, rewrite it using modern CPP-style
pointer. If you write a code in Question 7 using a modern CPP-style pointer, rewrite it using an old
C/CPP-style pointer.
NOTE: In the modern CPP-style, there will NOT be any ‘*’, ‘new’, ‘delete’, ‘malloc’, or ‘free’ keywords
in the code.
*/
#include <iostream>
#include <map>
#include <memory>   // for std::unique_ptr
#include <string>
#include <utility>  // for std::pair
#include <vector>   // for std::vector

using AirportPair = std::pair<std::string, std::string>;
using DistanceMap = std::map<AirportPair, int>;

// Define distances between airport pairs
DistanceMap flightDistances = 
{
    {{"SCE", "PHL"}, 160},  // 160-mile flight between SCE and PHL
    {{"PHL", "SCE"}, 160}   // 160-mile flight between PHL and SCE (round-trip)
};

// Pilot class definition
class Pilot 
{
private:
    std::string name;

public:
    Pilot(const std::string& pilotName) 
        : name(pilotName) 
    {
        std::cout << "Pilot " << name
                  << " with certificate number " << this
                  << " is at the gate, ready to board the plane." << std::endl;
    }

    ~Pilot() 
    {
        std::cout << "\nPilot " << name << " is out of the plane.\n" << std::endl;
    }

    std::string getName() const 
    { 
        return name; 
    }

    // Use a smart pointer for myPlane
    std::shared_ptr<class Plane> myPlane; // Shared pointer to the plane controlled by the pilot
};

// Plane class definition
class Plane 
{
private:
    double pos;
    double vel;
    double distance;
    bool at_SCE;
    std::string origin;
    std::string destination;

    // Retrieve distance between two airports
    double getDistanceBetweenAirports(const std::string& from, const std::string& to) 
    {
        auto it = flightDistances.find({from, to});
        if (it != flightDistances.end()) 
        {
            return it->second;
        }
        it = flightDistances.find({to, from});
        if (it != flightDistances.end()) 
        {
            return it->second;
        }
        return 0.0;
    }

public:
    // Constructor
    Plane(const std::string& from, const std::string& to) 
        : origin(from), destination(to), pos(0), vel(0), at_SCE(true) 
    {
        distance = getDistanceBetweenAirports(from, to);
        std::cout << "Plane created with tail number " << this << std::endl;
    }

    double getPos() const 
    { 
        return pos; 
    }

    std::string getOrigin() const 
    { 
        return origin; 
    }

    std::string getDestination() const 
    { 
        return destination; 
    }

    bool isAtSCE() const 
    { 
        return at_SCE; 
    }

    double getVel() const 
    { 
        return vel; 
    }

    void setVel(double newVel) 
    {
        vel = (newVel < 0) ? 0 : newVel; // Prevent negative velocity
    }

    void setOrigin(const std::string& newOrigin) 
    {
        origin = newOrigin;
    }

    void setDestination(const std::string& newDestination) 
    {
        destination = newDestination;
    }

    // Function to simulate the plane's operation
    void operate(double dt) 
    {
        if (dt < 0) 
        {
            dt = 0; // Prevent negative time
        }

        if (pos < distance) 
        {
            pos += vel * dt;
        } 
        else 
        {
            if (destination == "SCE") 
            {
                at_SCE = true;  // Mark the plane is at SCE
                pos = 0.0;      // Reset position for the next leg
            } 
            else 
            {
                at_SCE = false;  // Mark that the plane is not at SCE anymore
            }
        }
    }

    // Indicate completion of a leg
    void completeLeg() 
    {
        if (destination == "SCE") 
        {
            std::cout << "The plane " << this << " is at SCE." << std::endl;
        }
    }
};

int main() 
{
    // Create two pilots using smart pointers
    auto pilot1 = std::make_shared<Pilot>("Robin Olds");
    auto pilot2 = std::make_shared<Pilot>("Amelia Earhart");

    // Create the initial plane alternating between SCE and PHL
    auto myPlane = std::make_shared<Plane>("SCE", "PHL");
    myPlane->setVel(450.0 / 3600.0); // Set the plane's velocity
    double timestep = 15.0;
    int maxIterations = 1000;

    // Assign plane to the first pilot
    pilot1->myPlane = myPlane;
    pilot2->myPlane = nullptr;

    std::shared_ptr<Pilot> currentPilot = pilot1;
    std::shared_ptr<Pilot> nextPilot = pilot2;

    std::cout << "Pilot " << currentPilot->getName()
              << " with certificate number " << currentPilot.get()
              << " is in control of a plane: " << currentPilot->myPlane.get()
              << std::endl;

    std::string lastLeg = "SCE"; // Track the last completed leg

    for (int i = 0; i < maxIterations; ++i) 
    {
        myPlane->operate(timestep);

        if (myPlane->isAtSCE()) 
        {
            if (lastLeg == "SCE") 
            {
                std::cout << "\nNavigation from SCE to PHL has been completed. On to the next leg!" << std::endl;
                lastLeg = "PHL"; // Update the last leg to PHL
            } 
            else 
            {
                std::cout << "Navigation from PHL to SCE has been completed. On to the next leg!" << std::endl;
                lastLeg = "SCE"; // Update the last leg to SCE
            }

            // Mark the plane as at SCE
            myPlane->completeLeg();

            // Swap the pilots after arrival at SCE
            std::swap(currentPilot, nextPilot);

            // Print the next pilot's details after navigation
            std::cout << "Pilot " << currentPilot->getName()
                      << " with certificate number " << currentPilot.get()
                      << " is in control of a plane: " << currentPilot->myPlane.get()
                      << std::endl;

            // Switch for the next leg from SCE to PHL
            myPlane->setVel(450.0 / 3600.0); // Reset velocity
            myPlane->setOrigin(myPlane->getDestination());
            myPlane->setDestination(myPlane->getOrigin());
        }
    }

    return 0;
}
