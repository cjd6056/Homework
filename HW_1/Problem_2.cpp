// AERSP 424 HW 1, Problem 2
//Authors: Conor Dowdell, Gabrielle Dowdell, Chukwu Agbo, Shanon Hyde

/*
Prompt: Given a picture of a map around the University Park airport, design a C++ container that stores
information shown in the picture, specifically:
• There are 160-mile flights between “SCE” and “PHL”.
• There are 640-mile flights between “SCE” and “ORD”.
• There are 220-mile flights between “SCE” and “EWR”
*/

#include <iostream>
#include <map> // for using map containers
#include <string> // self explanatory
#include <utility> // for std::pair

// Defining using type alias was for easier use of map with pair of strings
using AirportPair = std::pair<std::string, std::string>;
using DistanceMap = std::map<AirportPair, int>; //map associated with integer distances

int main() 
{
    // Create a map to store distances between airport pairs
    // Maps are associative containers that store elements in a mapped fashion.
    // However, no two mapped values can have the same key values
    DistanceMap flightDistances;

    // Insert flight distances into the map
    flightDistances[{"SCE", "PHL"}] = 160; // 160-mile flight between SCE and PHL
    flightDistances[{"SCE", "ORD"}] = 640; // 640-mile flight between SCE and ORD
    flightDistances[{"SCE", "EWR"}] = 220; // 220-mile flight between SCE and EWR

    // Output the distances (Note: this is typically done in lexicographical order)
    std::cout << "Flight Distances:" << std::endl;
   // For Loop to output the pair elements and the values stored in them via map
    for (const auto& flight : flightDistances) 
    
    {
        std::cout << flight.first.first << " to " << flight.first.second << " is " 
          << flight.second << " miles." << std::endl; // Printing out flight map
    }

    return 0;
}
