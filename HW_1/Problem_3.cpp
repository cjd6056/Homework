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
    double distance;       // Distance traveled or remaining
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
    }

    // Destructor
    ~Plane() {}

    // Function to operate the plane
    void operate(double /*dt*/) {
        // No operation for now
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
};

// Main function for testing
int main() {
    // Create an instance of Plane
    Plane myPlane("SCE", "EWR");

    // Print some information
    std::cout << "Origin: " << myPlane.getOrigin() << std::endl;
    std::cout << "Destination: " << myPlane.getDestination() << std::endl;
    std::cout << "Position: " << myPlane.getPos() << std::endl;
    std::cout << "Velocity: " << myPlane.getVel() << std::endl;
    std::cout << "At SCE: " << (myPlane.getAtSCE() ? "Yes" : "No") << std::endl;

    // Set a new velocity and print it
    myPlane.setVel(550.0);
    std::cout << "Updated Velocity: " << myPlane.getVel() << std::endl;

    // Test distance retrieval
    std::cout << "Distance from SCE to EWR: " << myPlane.getDistance("SCE", "EWR") << " miles" << std::endl;
    std::cout << "Distance from SCE to ORD: " << myPlane.getDistance("SCE", "ORD") << " miles" << std::endl;
    std::cout << "Distance from SCE to PHL: " << myPlane.getDistance("SCE", "PHL") << " miles" << std::endl;

    return 0;
}
