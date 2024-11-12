

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


       // Define constants
    const double M_PI = 3.1415926535;       // Pi constant
    const double stall_angle = 15.0;        // Stall angle in degrees
    const double max_CL = 1.2;              // Maximum coefficient of lift
    const double curviness_factor = M_PI / 30; // Factor for adjusting lift curve shape
    const double stall_dropoff_rate = 0.08; // Rate at which CL decreases after stall

    // Define the range and step for angle of attack (alpha)
    std::vector<double> alpha; // Angle of attack in degrees
    std::vector<double> C_L;   // Coefficient of lift

    // Generate alpha values from -10 to 20 degrees and corresponding C_L values
    for (double i = -10; i <= 20; i += 1) {
        alpha.push_back(i);

        // Nonlinear relationship for C_L vs alpha (robust and realistic)
        if (i <= stall_angle) {
            // Smooth, curvy increase in C_L up to stall using a sine function
            C_L.push_back(max_CL * std::sin(i * curviness_factor));
        } else {
            // Smooth stall effect using an exponential decay to represent the drop in lift
            double stall_effect = max_CL * std::exp(-stall_dropoff_rate * (i - stall_angle));
            C_L.push_back(stall_effect);
        }
    }

    // Create the plot
    auto fig = matplot::figure();
    matplot::plot(alpha, C_L);
    matplot::title("Coefficient of Lift vs Angle of Attack");
    matplot::xlabel("Angle of Attack (degrees)");
    matplot::ylabel("Coefficient of Lift (C_L)");
    matplot::grid(true);

    // Save the plot as a JPEG image
    matplot::save("CL_vs_AoA_new", "jpeg");

    return 0;
}
