/*
AESP 424 HW 2, Question 4
Authors: Conor and Gabrielle Dowdell

Part 01:
Write a C++ program to plot a 2D graph (or 3D if feeling frisky) of the 
equation using any graphic library of your choice. You can pick any parameter for the 𝑥- and the 𝑦
axis and initiate other parameters with a realistic value.

Part 02: 
Read from a CSV file a table of data with headers “time,x,y”. Create a 2D graph of the resulting data.
*/

#include <matplot/matplot.h>
#include <vector>

int main2() 

{
    using namespace matplot;

    // Constants for Reynolds number calculation
    const double density = 1.225;  // kg/m³, air density at sea level
    const double length = 1.0;     // m, characteristic length
    const double viscosity = 1.81e-5; // Pa·s, dynamic viscosity of air at sea level

    // Velocity range (m/s) and Reynolds number calculations
    std::vector<double> velocities;
    std::vector<double> reynolds_numbers;

    for (double v = 0.1; v <= 100.0; v += 0.5) 
    {
        velocities.push_back(v);
        double reynolds_number = (density * v * length) / viscosity;
        reynolds_numbers.push_back(reynolds_number);
    }

    // Plot
    auto fig = figure();
    fig->size(800, 600);
    plot(velocities, reynolds_numbers);
    xlabel("Velocity (m/s)");
    ylabel("Reynolds Number");
    title("Reynolds Number vs. Fluid Velocity");

    show();
    return 0;
}
