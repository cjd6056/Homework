// Question #4

#include <matplot/matplot.h>
#include <cmath>
#include <vector>

int main() 
{
    // Define the range and step
    std::vector<double> x;
    std::vector<double> y;

    // Generate x values from -2π to 2π
    for (double i = -2 * 3.1415963; i <= 2 * 3.1415963; i += 0.1) {
        x.push_back(i);
        y.push_back(std::sin(i));
    }

    // Create the plot
    matplot::plot(x, y);
    matplot::title("Plot of y = sin(x)");
    matplot::xlabel("x");
    matplot::ylabel("y");
    matplot::grid(true);

    // Show the plot
    matplot::show();

    return 0;
}
