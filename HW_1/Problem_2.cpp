// AERSP 424 HW 1, Problem 2
// Authors: Conor Dowdell, Gabrielle Dowdell, Chukwu Agbo

#include <iostream>
#include <map>
#include <string>
#include <utility> // for std::pair

// Define a type alias for easier use of map with pair of strings
using AirportPair = std::pair<std::string, std::string>;
using DistanceMap = std::map<AirportPair, int>;

int main() {
    // Create a map to store distances between airport pairs
    DistanceMap flightDistances;

    // Insert flight distances into the map
    flightDistances[{"SCE", "PHL"}] = 160; // 160-mile flight between SCE and PHL
    flightDistances[{"SCE", "ORD"}] = 640; // 640-mile flight between SCE and ORD
    flightDistances[{"SCE", "EWR"}] = 220; // 220-mile flight between SCE and EWR

    // Output the distances
    std::cout << "Flight Distances:" << std::endl;
    for (const auto& flight : flightDistances) {
        std::cout << flight.first.first << " to " << flight.first.second << " is " 
          << flight.second << " miles." << std::endl;
    }

    return 0;
}
