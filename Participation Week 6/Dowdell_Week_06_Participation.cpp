#include <iostream>
#include <cmath>
#include <vector>
#include <tuple>    // Include this header to define std::tuple
#include <iomanip>

const double PI = 3.141592653589793;
const double RAD2DEG = 180.0 / PI;

// Function to calculate p, q, r at a given time t
std::tuple<double, double, double> ffunc(double t) {
    double p = PI / 6 + 0 * t;
    double q = std::cos(t * 6 / PI);
    double r = 3 * std::sin(t * 30 / PI);
    return std::make_tuple(p, q, r);
}

// Function to calculate derivatives based on the input x, dcm, v_body, and t
std::tuple<std::vector<double>, std::vector<std::vector<double>>> dfunc(
    std::vector<double> x, std::vector<std::vector<double>> dcm, std::vector<double> v_body, double t) {

    // Extract Euler angles
    double phi = x[0];
    double theta = x[1];
    double psi = x[2];

    // Get p, q, r values from the function
    auto [p, q, r] = ffunc(t);

    // Gimbal equation (q_dot)
    std::vector<double> q_dot(3);
    q_dot[0] = 1 * std::tan(theta) * std::sin(phi) * p + std::tan(theta) * std::cos(phi) * r;
    q_dot[1] = std::cos(phi) * q - std::sin(phi) * r;
    q_dot[2] = std::sin(phi) / std::cos(theta) * q + std::cos(phi) / std::cos(theta) * r;

    // Simplified C_dot (assuming identity matrix for simplicity)
    std::vector<std::vector<double>> Cdot = dcm; // Here we will simulate small matrix calculations

    return {q_dot, Cdot};
}

int main() {
    // Time step and simulation parameters
    double dt = 0.01;
    double tmax = 60;
    int steps = static_cast<int>(tmax / dt);
    int func_calls = 0;

    // Initial conditions
    std::vector<double> x0 = {0, 0, 0}; // Euler angles
    std::vector<double> V_body = {60 * 6076 / 3600, 0, 0}; // Velocity in ft/sec

    // Define the DCM matrix (Identity for simplicity here)
    std::vector<std::vector<double>> DCM = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

    // Initialize vectors for storing results
    std::vector<double> time(steps + 1);
    std::vector<std::vector<double>> x(steps + 1, std::vector<double>(6, 0));
    x[0] = {x0[0], x0[1], x0[2], V_body[0], V_body[1], V_body[2]};
    
    // Time integration loop (Runge-Kutta method)
    for (int idx = 0; idx < steps; ++idx) {
        double time_val = idx * dt;
        time[idx] = time_val;

        // Call the derivative function dfunc for Runge-Kutta steps
        auto [xdot1, Cdot1] = dfunc(x[idx], DCM, V_body, time_val);
        auto [xdot2, Cdot2] = dfunc(x[idx], DCM, V_body, time_val + dt / 2);
        auto [xdot3, Cdot3] = dfunc(x[idx], DCM, V_body, time_val + dt / 2);
        auto [xdot4, Cdot4] = dfunc(x[idx], DCM, V_body, time_val + dt);

        // Update Euler angles using a simple Runge-Kutta average
        for (int i = 0; i < 3; ++i) {
            x[idx + 1][i] = x[idx][i] + (xdot1[i] + 2 * xdot2[i] + 2 * xdot3[i] + xdot4[i]) / 6 * dt;
        }

        func_calls += 4;
    }

    // Output some of the results for time and Euler angles (phi, theta, psi)
    std::cout << "Time(s)\tPhi(deg)\tTheta(deg)\tPsi(deg)" << std::endl;
    for (int idx = 0; idx < steps; idx += 100) {  // Output every 100th step for brevity
        double phi_deg = RAD2DEG * x[idx][0];
        double theta_deg = RAD2DEG * x[idx][1];
        double psi_deg = RAD2DEG * x[idx][2];
        std::cout << std::setw(10) << std::fixed << std::setprecision(2) << time[idx] << "\t" 
                  << phi_deg << "\t" << theta_deg << "\t" << psi_deg << std::endl;
    }

    // Calculate the final values after the last time step
    double final_time = steps * dt; // Calculate the final time
    double final_phi = RAD2DEG * x[steps][0]; // Final phi value
    double final_theta = RAD2DEG * x[steps][1]; // Final theta value
    double final_psi = RAD2DEG * x[steps][2]; // Final psi value

    // Print the final time step values
    std::cout << std::setw(10) << std::fixed << std::setprecision(2) << final_time << "\t"
              << final_phi << "\t" 
              << final_theta << "\t" 
              << final_psi << std::endl;

    std::cout << "Function calls: " << func_calls << std::endl;
    return 0;
}
