

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


    int M_PI = 3.1415926535897932384626;

       // Define the range and step for angle of attack (alpha)
    std::vector<double> alpha; // Angle of attack in degrees
    std::vector<double> C_L;   // Coefficient of lift

    // Generate alpha values from -10 to 20 degrees and corresponding C_L values
    for (double i = -10; i <= 20; i += 1) 
    {
        alpha.push_back(i);

        // Nonlinear relationship for C_L vs alpha (more curvy with stall)
        if (i <= 15) 
        {
            // Use a sinusoidal function to simulate curviness before stall
            C_L.push_back(1.2 * std::sin(i * M_PI / 30));
        } else 
        
        {
            // After stall angle, C_L decreases to simulate the stall effect
            C_L.push_back(1.2 * std::sin(15 * M_PI / 30) - 0.05 * (i - 15));
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
    matplot::save("CL_vs_AoA", "jpeg");

    return 0;
}
