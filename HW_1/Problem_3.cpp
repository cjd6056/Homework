// AERSP 424 HW 1, Problem 3
// Authors: Conor Dowdell, Gabrielle Dowdell, Chukwu Agbo

#include <iostream>
#include <string>

class Plane {
private:
    double pos;
    double vel;
    double distance;
    bool at_SCE;
    std::string origin;
    std::string destination;

public:
    // Constructor
    Plane(const std::string& from, const std::string& to)
        : pos(0.0), vel(0.0), distance(0.0), at_SCE(false), origin(from), destination(to) {}

    // Destructor
    ~Plane() {}

    // Function to operate the plane
    void operate(double dt) {
        // For now, this function doesn't do anything meaningful.
        // You can implement functionality later.
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

    // Getter and Setter for vel
    double getVel() const {
        return vel;
    }

    void setVel(double newVel) {
        vel = newVel;
    }
};
