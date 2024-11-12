

#include <matplot/matplot.h>
// #include <math.h>
// #include <cmath>
// #include <corecrt.h>
#include <vector>
#include "question123.h"
#include <iostream>
using  std::cin, std::cout, std::endl;


int main() 
{
    
    q123::question123();


    
    // Define the range and step
    std::vector<double> x;
    std::vector<double> y;

    // Generate x values from -2π to 2π
    for (double i = -2 * 3.14; i <= 2 * 3.14; i += 0.1) {
        x.push_back(i);
        y.push_back(std::sin(i));
    }

    // Create the plot
    // Initial Setup
	auto fig = matplot::figure();
	// fig->size(900, 600);
	// fig->position(450, -300);


    matplot::plot(x, y);
    matplot::title("Plot of y = sin(x)");
    matplot::xlabel("x");
    matplot::ylabel("y");
    matplot::grid(true);

    // Show the plot
    matplot::save("Sine Plot", "jpeg");

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
    auto fig2 = figure();
    fig2->size(800, 600);
    plot(velocities, reynolds_numbers);
    xlabel("Velocity (m/s)");
    ylabel("Reynolds Number");
    title("Reynolds Number vs. Fluid Velocity");

    show();
    matplot::save("Reynolds Plot", "jpeg");


    return 0;
}
