// AERSP 424 HW 1, Problem 3
// Authors: Conor Dowdell, Gabrielle Dowdell, Chukwu Agbo

#include <iostream>
#include <map>
#include <string>
#include <utility> // for std::pair

// Define a type alias for easier use of map with pair of strings
using AirportPair = std::pair<std::string, std::string>;
using DistanceMap = std::map<AirportPair, int>;

class Plane {
private:
    double pos;            // Position of the plane
    double vel;            // Velocity of the plane
    double distance;       // Distance to be traveled between origin and destination
    bool at_SCE;           // Whether the plane is at SCE (Specific Checkpoint or Condition)
    std::string origin;    // Origin of the flight
    std::string destination; // Destination of the flight
    DistanceMap distances; // Container to store distances between airports

public:
    // Constructor
    Plane(const std::string& from, const std::string& to)
        : pos(0.0), vel(0.0), distance(0.0), at_SCE(false), origin(from), destination(to) {

        // Initialize distances map with some example values
        distances[{"SCE", "PHL"}] = 160; // 160-mile flight between SCE and PHL
        distances[{"SCE", "ORD"}] = 640; // 640-mile flight between SCE and ORD
        distances[{"SCE", "EWR"}] = 220; // 220-mile flight between SCE and EWR

        // Set distance based on the origin and destination
        distance = getDistance(origin, destination);

        // Print the memory address of the object
        std::cout << "Plane Created at " << this << std::endl;
    }

    // Destructor
    ~Plane() {
        std::cout << "Plane Destroyed" << std::endl;
    }

    // Getter for pos
    double getPos() const {
        return pos;
    }

    // Getter for origin
    std::string getOrigin() const {
        return origin;
    }

    // Getter for destination
    std::string getDestination() const {
        return destination;
    }

    // Getter for at_SCE
    bool getAtSCE() const {
        return at_SCE;
    }

    // Getter for vel
    double getVel() const {
        return vel;
    }

    // Setter for vel
    void setVel(double newVel) {
        vel = newVel;
    }

    // Function to get the distance between two airports
    int getDistance(const std::string& from, const std::string& to) const {
        AirportPair pair = {from, to};
        auto it = distances.find(pair);
        if (it != distances.end()) {
            return it->second;
        }
        return -1; // Return -1 if the distance is not found
    }

    // Function to operate the plane (simulate movement)
    void operate(double dt) {
        if (dt < 0) dt = 0; // Make sure dt is non-negative

        double traveledDistance = vel * dt;

        // Update position and ensure it doesn't go negative
        pos += traveledDistance;
        if (pos > distance) {
            pos = distance; // Plane has reached the destination
        }

        // If plane reaches the destination (at SCE or not), update `at_SCE`
        if (pos == distance) {
            at_SCE = true;
        } else {
            at_SCE = false;
        }

        // Output plane status
        std::cout << "Operating plane for " << dt << " seconds.\n";
        std::cout << "Current position: " << pos << " miles out of " << distance << std::endl;
        std::cout << "At SCE: " << (at_SCE ? "Yes" : "No") << std::endl;
    }
};

// Main function for testing
int main() {
    // Create an instance of Plane
    Plane myPlane("SCE", "EWR");

    // Set velocity and operate the plane
    myPlane.setVel(500.0); // Assume velocity is 500 miles/hour
    myPlane.operate(1.0);  // Operate the plane for 1 second
    myPlane.operate(0.5);  // Operate the plane for another 0.5 seconds

    // Plane object will be destroyed at the end of the scope
    return 0;
}
