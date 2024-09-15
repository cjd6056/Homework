// AERSP 424 HW 1, Problem 5
// Authors: Conor Dowdell, Gabrielle Dowdell, Chukwu Agbo

#include <iostream>
#include <map>
#include <string>
#include <utility> // for std::pair
#include <cstdlib> // for rand()
#include <ctime>   // for time()

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
    if (pos < distance) {
        pos += vel * dt;
    } else {
        // If we've reached the destination
        if (destination == "SCE") {
            if (at_SCE) {
                // Reset position and swap origin/destination
                std::swap(origin, destination);
                pos = 0.0;
                std::cout << "Plane has reached " << destination << ". Swapping for the next leg!" << std::endl;
            }
        } else {
            at_SCE = false;
        }
    }

    // Print the current state of the plane
    std::cout << "Operating: Position = " << pos << " miles, Velocity = " << vel
              << " miles/sec, at_SCE = " << (at_SCE ? "true" : "false") << std::endl;
}

};

// Main function for testing
int main() 
{
    // Create a plane from SCE to ORD
    Plane myPlane("SCE", "ORD");

    // Set velocity to something between 400-500 mph, converting it to miles per second
    myPlane.setVel(450.0 / 3600.0); // 450 miles per hour = 0.125 miles per second

    // Pick a timestep between 10 and 100 seconds
    double timestep = 15.0; // 15 seconds

    // Choose a maximum number of iterations between 1000 and 2000
    int maxIterations = 1000;
    
    int currentTime = 0;
    for (int i = 0; i < maxIterations; ++i) {
        myPlane.operate(timestep);
        currentTime += timestep;

        // Print the current position at each timestep
        std::cout << "Time: " << currentTime << " seconds, Position: " 
                  << myPlane.getPos() << " miles." << std::endl;

        // Check if the plane has reached its destination
        if (!myPlane.isAtSCE()) {
            std::cout << "Plane from " << myPlane.getOrigin() << " to " 
                      << myPlane.getDestination() << " has been completed. On to the next leg!" << std::endl;
            break;
        }
    }

    // Destructor will be called automatically when the object goes out of scope
    return 0;
}