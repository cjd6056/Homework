/*
AERSP 424 HW 2: Questions 1 - 3
Authors: Conor & Gabrielle Dowdell, Shanon Hyde

*/

#include <matplot/matplot.h>
#include <vector>
#include "question123.h"
#include <iostream>
using  std::cin, std::cout, std::endl;


int main() 
{
    
    q123::question123(); //function that runs questions 1 thru 3

std::cout << "------ Question 4, Part 01 ------ \n" << std::endl;

       // Define constants
 //   const double M_PI = 3.1415926535;       // Pi constant
    const double stall_angle = 15.0;        // Stall angle in degrees
    const double max_CL = 1.2;              // Maximum coefficient of lift
    const double curviness_factor = M_PI / 30; // Factor for adjusting lift curve shape
    const double stall_dropoff_rate = 0.08; // Rate at which CL decreases after stall

    // Define the range and step for angle of attack (alpha)
    std::vector<double> alpha; // Angle of attack in degrees
    std::vector<double> C_L;   // Coefficient of lift

    // Generate alpha values from -10 to 20 degrees and corresponding C_L values
    for (double i = -10; i <= 20; i += 1) 
    {
        alpha.push_back(i);

        // Nonlinear relationship for C_L vs alpha (robust and realistic)
        if (i <= stall_angle) 
        {
            // Smooth, curvy increase in C_L up to stall using a sine function
            C_L.push_back(max_CL * std::sin(i * curviness_factor));
        } else 
        {
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
    std::cout << "Check for figure in output folder\n" << std::endl;



std::cout << "------ Question 4, Part 02 ------ \n" << std::endl;


// CSV file path
    std::string csv_path = "C:\\Users\\conor.CONORS-XPS-15\\OneDrive\\Desktop\\Repos\\Homework\\HW_2\\include\\AERP_424_HW_2_Q4_Data.csv";

    // Read data from CSV file (time,x,y)
    std::ifstream file(csv_path);
    std::string line;
    std::vector<double> time, x, y;

    if (file.is_open()) 
    {
        // Skip the header line
        std::getline(file, line);

        // Read each line of the CSV
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string value;
            std::vector<double> row;

            // Read comma-separated values in each line
            while (std::getline(ss, value, ',')) {
                row.push_back(std::stod(value));
            }

            if (row.size() == 3) {
                time.push_back(row[0]);
                x.push_back(row[1]);
                y.push_back(row[2]);
            }
        }
        file.close();
        std::cerr << "CSV File was accessed!\n" << std::endl;
    } 
    
    else 
    {
        std::cerr << "Unable to open .csv" << std::endl;
        return 1;
    }

    // Plot x vs y from CSV data
    auto fig2 = matplot::figure();
    matplot::plot(x, y);
    matplot::title("2D Plot of x vs y from CSV Data");
    matplot::xlabel("x");
    matplot::ylabel("y");
    matplot::grid(true);
    matplot::save("xy_from_csv", "jpeg");
    
    std::cout << "------ End of Homework 2 :) ------ \n" << std::endl;


    return 0;
}
