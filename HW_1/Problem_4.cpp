// AERSP 424 HW 1, Problem 4
// Authors: Conor Dowdell, Gabrielle Dowdell, Chukwu Agbo

#include <iostream>
#include <map>
#include <string>
#include <utility> // for std::pair

// Define a type alias for easier use of map with pair of strings
using AirportPair = std::pair<std::string, std::string>;
using DistanceMap = std::map<AirportPair, int>;

// Create a global DistanceMap to be used by the Plane class
DistanceMap flightDistances = {
    {{"SCE", "PHL"}, 160},  // 160-mile flight between SCE and PHL
    {{"SCE", "ORD"}, 640},  // 640-mile flight between SCE and ORD
    {{"SCE", "EWR"}, 220}   // 220-mile flight between SCE and EWR
};

// Plane class definition
class Plane {
private:
    double pos;             // position of the plane
    double vel;             // velocity of the plane
    double distance;        // distance between origin and destination
    bool at_SCE;            // boolean indicating if the plane is at SCE
    std::string origin;     // origin airport code
    std::string destination;// destination airport code

    // Helper function to calculate the distance between origin and destination
    double getDistanceBetweenAirports(const std::string& from, const std::string& to) {
        auto it = flightDistances.find({from, to});
        if (it != flightDistances.end()) {
            return it->second;
        }
        // If not found in the order from->to, check to->from (assuming round-trip distance)
        it = flightDistances.find({to, from});
        if (it != flightDistances.end()) {
            return it->second;
        }
        return 0.0; // default distance if no match found
    }

public:
    // Constructor
    Plane(const std::string& from, const std::string& to)
        : origin(from), destination(to), pos(0), vel(0), at_SCE(true) 
    {
        distance = getDistanceBetweenAirports(from, to);
        std::cout << "Plane Created at " << this << std::endl;
    }

    // Destructor
    ~Plane() 
    {
        std::cout << "Plane Destroyed" << std::endl;
    }

    // Getter for position
    double getPos() const 
    {
        return pos;
    }

    // Getter for origin
    std::string getOrigin() const 
    {
        return origin;
    }

    // Getter for destination
    std::string getDestination() const 
    {
        return destination;
    }

    // Getter for at_SCE
    bool isAtSCE() const 
    {
        return at_SCE;
    }

    // Getter and Setter for velocity
    double getVel() const 
    {
        return vel;
    }

    void setVel(double newVel) 
    {
        if (newVel < 0) {
            vel = 0; // Prevent negative velocity
        } else {
            vel = newVel;
        }
    }

    // Function to simulate the operation of the plane
    void operate(double dt) 
    {
        if (dt < 0) {
            dt = 0;  // Prevent negative time
        }
        
        // Update the position based on velocity and time delta (dt)
        pos += vel * dt;

        // If position exceeds the total distance, set pos to the distance and at_SCE to false
        if (pos >= distance) {
            pos = distance;
            at_SCE = false;  // Plane has reached the destination
        }

        // Print current state
        std::cout << "Operating: Position = " << pos << " miles, Velocity = " << vel
                  << " miles/sec, at_SCE = " << (at_SCE ? "true" : "false") << std::endl;
    }
};

// Main function for testing
int main() 
{
    // Create a plane from SCE to ORD
    Plane myPlane("SCE", "ORD");

    // Set velocity
    myPlane.setVel(200); // 200 miles per second (example)

    // Operate the plane for 2 seconds
    myPlane.operate(2.0);

    // Operate the plane for another 3 seconds
    myPlane.operate(3.0);

    // Print out the current state of the plane
    std::cout << "Plane is at " << myPlane.getPos() << " miles." << std::endl;

    // Destructor will be called automatically when the object goes out of scope
    return 0;
}
