// AERSP 424 HW 1, Problem 3
//Authors: Conor Dowdell, Gabrielle Dowdell, Chukwu Agbo, Shanon Hyde
// NOTE: This “Question” is just to setup the class, no “real” functionality to test (yet).
/* Prompt 3
Create a class named “Plane” with the following class members.
Private members:
• double variables named “pos”, “vel”, and “distance”.
• boolean variable named “at_SCE”.
• string variables named “origin” and “destination”.
• The container from Question 2 (see Q2)

Public members:
• A constructor that takes in two strings “from” and “to” as input.
• A deconstructor.
• A function named “operate” with a double variables “dt” as an input, and return nothing.
get functions for “pos”, “origin”, “destination”, and “at_SCE” variables and get/set functions for “vel”
variable.
*/

#include <iostream>
#include <map>
#include <string>
#include <utility> // for std::pair

// Define a type alias for easier use of map with pair of strings
using AirportPair = std::pair<std::string, std::string>;
using DistanceMap = std::map<AirportPair, int>;

class Plane 
{
private: //creating private members of class Plane
    double pos;            // Position of the plane
    double vel;            // Velocity of the plane
    double distance;       // Distance traveled or remaining
    bool at_SCE;           // Whether the plane is at SCE (Specific Checkpoint or Condition)
    std::string origin;    // Origin of the flight
    std::string destination; // Destination of the flight
    DistanceMap distances; // Container (from Q2) that stores distances between airports

public:
    // Constructor that takes in two strings ("from" and "to")
    Plane(const std::string& from, const std::string& to)
        : pos(0.0), vel(0.0), distance(0.0), at_SCE(false), origin(from), destination(to) 
        
    {
        // Initialize distances map with some example values
        distances[{"SCE", "PHL"}] = 160; // 160-mile flight between SCE and PHL
        distances[{"SCE", "ORD"}] = 640; // 640-mile flight between SCE and ORD
        distances[{"SCE", "EWR"}] = 220; // 220-mile flight between SCE and EWR
    }

    // Destructor
    ~Plane() 
    
    {
        //Insert Destructor code here
    }

    // Function to operate the plane
    void operate(double /*dt*/)  //dt is input
    {
        // Code to Operate
    }

    // Get Func. for position
    double getPos() const 
    {
        return pos;
    }

    // Get Func. for origin
    std::string getOrigin() const 
    {
        return origin;
    }

    // Get Func. for destination
    std::string getDestination() const 
    {
        return destination;
    }

    // Getter for at_SCE
    bool getAtSCE() const 
    {
        return at_SCE;
    }

    // Get Func. for velocity
    double getVel() const 
    {
        return vel;
    }

    // Set Func. for vel
    void setVel(double newVel) 
    {
        vel = newVel;
    }
};

// Main function for testing
int main() 
{
    // Create an instance of Plane
    Plane myPlane("SCE", "EWR");
    
    return 0;
}
