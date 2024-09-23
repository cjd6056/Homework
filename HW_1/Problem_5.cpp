// AERSP 424 HW 1, Problem 5
// Authors: Conor Dowdell, Gabrielle Dowdell, Chukwu Agbo

// Note: Really this is problems 2 thru 5. Works good CAO 23 Sep
/*
Pick a flight speed between 400-500 mph. In your main function, instantiate an object from the
“Plane” class written in Question 3 & 4.
• This object represents an airplane of the chosen pair of arrival & departure flights.
• Use the set function for “vel” to set the speed of the airplane.
• Then ...
o pick a timestep between [10, 100],
o choose the maximum number of iterations between [1000, 2000], and
o create an iterative statement that call the “operate” function member for each
airplane object with timestep being an input
o Print out the airplane position at each timestep until the maximum number of
iterations is reached

*/

#include <iostream>
#include <iomanip> // for std::setprecision
#include <map>
#include <string>
#include <utility> // for std::pair

using AirportPair = std::pair<std::string, std::string>;
using DistanceMap = std::map<AirportPair, int>;

DistanceMap flightDistances = 
{
    {{"SCE", "PHL"}, 160},
    {{"SCE", "ORD"}, 640},
    {{"SCE", "EWR"}, 220}
};

class Plane {
private:
    double pos;
    double vel;
    double distance;
    std::string origin;
    std::string destination;

    // Helper function to calculate the distance between origin and destination
    double getDistanceBetweenAirports(const std::string& from, const std::string& to) 
    
    {
        auto it = flightDistances.find({from, to});
        if (it != flightDistances.end()) {
            return it->second;
        }
        it = flightDistances.find({to, from});
        if (it != flightDistances.end()) {
            return it->second;
        }
        return 0.0; // default distance if no match found
    }

public:
    Plane(const std::string& from, const std::string& to)
        : origin(from), destination(to), pos(0), vel(0) 
    {
        distance = getDistanceBetweenAirports(from, to);
        
        std::cout << "-----Question 5-----\n";  
        std::cout << "Plane Created at " << this << std::endl;
    }

    ~Plane() 
    {
        std::cout << "Plane Destroyed." << std::endl;
            std::cout << "-----Question 5-----\n\n";  
    }

    double getPos() const 
    {
        return pos;
    }

    void setVel(double newVel) 
    {
        vel = newVel;
    }

    void operate(double dt) 
    {
        if (pos < distance) {
            pos += vel * dt / 3600.0; // Convert velocity from mph to miles per second
            if (pos > distance) {
                pos = distance; // Cap the position at the destination
            }
        }
    }

    bool hasArrived() const 
    {
        return pos >= distance;
    }

    std::string getOrigin() const 
    {
        return origin;
    }

    std::string getDestination() const 
    {
        return destination;
    }

    void swapLeg() 
    {
        std::swap(origin, destination);
        pos = 0;
        distance = getDistanceBetweenAirports(origin, destination); // Update distance for the new leg
    }
};

// Main function for simulation
int main() 
{
    // Create a plane from SCE to PHL
    Plane myPlane("SCE", "PHL");

    // Set velocity to 450 mph
    myPlane.setVel(450.0);

    // Set timestep to 15 seconds
    int timestep = 60; // seconds (60 for timesteps in mins)

    // Max iterations for the loop (between 1000 to 2000)
    int maxIterations = 1500;

    int currentTime = 0;

    // Fixed-point output formatting
    std::cout << std::fixed << std::setprecision(3);

    for (int i = 0; i < maxIterations; ++i) 
    {
        // Operate the plane for the timestep
        myPlane.operate(timestep);
        currentTime += timestep;

        // Print the current time and position
        std::cout << "Time: " << currentTime << " seconds, Position: " 
        << myPlane.getPos() << " miles." << std::endl;

        // Check if the plane has arrived at the destination
         if (myPlane.hasArrived()) 
         {
                std::cout << "Navigation from " << myPlane.getOrigin() << " to " 
            << myPlane.getDestination() << " has been completed. On to the next leg!" << std::endl;
            // Swap the legs for the next trip
            myPlane.swapLeg();
         }
    }

    // Plane destruction message
    std::cout << "Plane should get destroyed now!" << std::endl;


    return 0;
}
