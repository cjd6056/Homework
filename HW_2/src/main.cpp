

#include <matplot/matplot.h>
// #include <math.h>
// #include <cmath>
// #include <corecrt.h>
#include <vector>

#include "question1.h"

#include <iostream>
using  std::cin, std::cout, std::endl;


int main() 
{
    cout << "***** QUESTION 01 *****" << endl;
    q1::question1();


    
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
    matplot::show();
    matplot::save("figure", "jpeg");

    return 0;
}
