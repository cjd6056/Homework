#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <cmath>
#include <memory>
#include <utility>
#include <string>

// Gross Weight function
double gross_weight(double W_, double FS_total_W_, double RS_total_W_, double W_fuel_total_, double W_bags_) {
    return W_ + FS_total_W_ + RS_total_W_ + W_fuel_total_ + W_bags_;
}

// CG calculation function
double CG_(double W_m_, double FS_m_, double RS_m_, double FT_m_, double bags_m_, double W_gross_) {
    return (W_m_ + FS_m_ + RS_m_ + FT_m_ + bags_m_) / W_gross_;
}

// Questions 2 - 5 "Plane" class
class Plane {
private:
    double pos;
    double vel;
    double distance;
    bool at_SCE;
    std::string origin;
    std::string destination;
    std::map<std::pair<std::string, std::string>, int> flights_cont; // Map type container from Question 2
public:
    Plane(const std::string& from, const std::string& to); // Constructor
    ~Plane(); // Destructor
    void operate(double dt);
    double get_pos() const;
    std::string get_origin() const;
    std::string get_destination() const;
    bool get_at_SCE() const;
    double get_vel() const;
    void set_vel(double new_vel);
};

// Plane class constructor definition
Plane::Plane(const std::string& from, const std::string& to) 
    : pos(0), vel(0), distance(0), at_SCE(false), origin(from), destination(to) 
{
    // Container from Question 2 incorporated into the Plane class
    flights_cont[std::make_pair("SCE", "PHL")] = 160;
    flights_cont[std::make_pair("SCE", "ORD")] = 640;
    flights_cont[std::make_pair("SCE", "EWR")] = 220;
    distance = flights_cont[std::make_pair(from, to)];
    std::cout << "Plane Created at " << this << std::endl;
}

// Destructor definition
Plane::~Plane() {
    std::cout << "Plane Destroyed" << std::endl;
}

// Operate function according to flowchart
void Plane::operate(double dt) {
    if (dt < 0) dt = 0; // Sets time-related variables to 0
    if (pos < distance) {
        pos += vel * dt / 3600;
        at_SCE = false;
    } else {
        if (destination == "SCE") {
            at_SCE = true;
            std::swap(origin, destination);
            pos = 0.0;
        } else {
            std::swap(origin, destination);
            pos = 0.0;
            at_SCE = false;
        }
    }
}

// Get and Set functions
double Plane::get_pos() const {
    return pos;
}

std::string Plane::get_origin() const {
    return origin;
}

std::string Plane::get_destination() const {
    return destination;
}

bool Plane::get_at_SCE() const {
    return at_SCE;
}

double Plane::get_vel() const {
    return vel;
}

void Plane::set_vel(double new_vel) {
    vel = new_vel;
}

// Questions 6 - 8 "Pilot" class
class Pilot {
private:
    std::string name;
public:
    std::shared_ptr<Plane> myPlane; // Modern CPP style pointer
    Pilot(const std::string& pilotName, std::shared_ptr<Plane> planePtr);
    Plane* myPlane_old; // Old CPP style pointer
    Pilot(const std::string & pilotName, Plane * planePtr_old);
    ~Pilot(); // Destructor
    std::string get_name() const;
};

// Pilot class constructor definition
Pilot::Pilot(const std::string& pilotName, std::shared_ptr<Plane> planePtr) 
    : name(pilotName), myPlane(planePtr) // Modern style
{
    std::cout << "Pilot " << name << " with certificate number " << this << " is at the gate, ready to board the plane." << std::endl;
}

Pilot::Pilot(const std::string& pilotName, Plane* planePtr_old) 
    : name(pilotName), myPlane_old(planePtr_old) // Old style
{
    std::cout << "Pilot " << name << " with certificate number " << this << " is at the gate, ready to board the plane." << std::endl;
}

// Destructor definition
Pilot::~Pilot() {
    std::cout << "Pilot " << name << " is out of the plane." << std::endl;
}

// Name get function
std::string Pilot::get_name() const {
    return name;
}

// Main function (Questions 2-8)
int main() 
{
    // Questions 2 - 5
    {
        std::cout << "\n------ Questions 2 - 5 ------" << std::endl;
        // Instance for Plane class object
        Plane plane("SCE", "PHL");

        // Setting the speed of the airplane
        double speed = 450; // mph
        plane.set_vel(speed);

        // Timestep and number of iterations
        int timestep = 15; // seconds
        int max_iterations = 1500;

        // Perform iterations until deconstructor deletes "Plane" object
        for (int i = 0; i < max_iterations; ++i) {
            if (i == 0) {
                std::cout << "Time: " << (i) * timestep << " seconds, Position: " << plane.get_pos() << " miles." << std::endl;
                max_iterations = max_iterations - 1;
            }
            plane.operate(timestep);
            std::cout << "Time: " << (i+1) * timestep << " seconds, Position: " << plane.get_pos() << " miles." << std::endl;
        }
    }
    std::cout << "------ End of Questions 2 - 5 ------" << std::endl;

    // Questions 6 - 7
    {
        std::cout << "\n------ Questions 6 and 7 ------" << std::endl;
        // Instance for Plane and Pilot objects
        std::shared_ptr<Plane> planePtr = std::make_shared<Plane>("SCE", "PHL");
        std::shared_ptr<Pilot> pilot1 = std::make_shared<Pilot>("Alpha", planePtr);
        std::shared_ptr<Pilot> pilot2 = std::make_shared<Pilot>("Bravo", planePtr);

        // Set speed of the airplane
        double speed = 450; // mph
        planePtr->set_vel(speed);

        // Set timestep and maximum number of iterations
        int timestep = 15; // seconds
        int max_iterations = 1500;

        // Start simulation
        std::shared_ptr<Pilot> currentPilot = pilot1;
        std::shared_ptr<Pilot> currentCoPilot = pilot2;

        std::cout << "Plane Created at " << planePtr.get() << std::endl;

        // Print initial pilot information
        std::cout << "Pilot " << currentPilot->get_name() << " with certificate number " << currentPilot.get() << " is in control of a plane: " << currentPilot->myPlane.get() << std::endl;
        std::cout << "Pilot " << currentCoPilot->get_name() << " with certificate number " << currentCoPilot.get() << " is in control of a plane: " << "0000000000000000" << std::endl;

        for (int i = 0; i < max_iterations; ++i) {
            // Take off, fly, and land
            currentPilot->myPlane->operate(timestep);

            if (currentPilot->myPlane->get_at_SCE()) {
                std::cout << "\nThe plane " << currentPilot->myPlane.get() << " is at SCE" << std::endl;
                // Switch pilot
                if (currentPilot->get_name() == "Alpha") {
                    currentPilot = pilot2;
                    currentCoPilot = pilot1;
                } else if (currentPilot->get_name() == "Bravo") {
                    currentPilot = pilot1;
                    currentCoPilot = pilot2;
                }
                std::cout << "Pilot " << currentPilot->get_name() << " with certificate number " << currentPilot.get() << " is in control of a plane: " << currentPilot->myPlane.get() << std::endl;
                std::cout << "Pilot " << currentCoPilot->get_name() << " with certificate number " << currentCoPilot.get() << " is in control of a plane: " << "0000000000000000" << std::endl;
            }
        }
    }
    std::cout << "------ End of Questions 6 - 7 ------" << std::endl;

    // Question 8 - Using an old CPP style pointer
    {
        std::cout << "\n------ Question 8 ------" << std::endl;
        // Instantiate Plane and Pilot objects
        Plane* planePtr_old = new Plane("SCE", "PHL");
        Pilot* pilot1 = new Pilot("Alpha", planePtr_old);
        Pilot* pilot2 = new Pilot("Bravo", planePtr_old);

        // Set speed of the airplane
	}
	}