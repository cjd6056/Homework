#include <iostream>
#include <cmath>
#include <vector>
#include <tuple>
#include <iomanip>
#include <fstream>  // Include this header for file operations

const double PI = 3.141592653589793;
const double RAD2DEG = 180.0 / PI;

std::tuple<double, double, double> ffunc(double t) {
    double p = PI / 6 + 0 * t;
    double q = std::cos(t * 6 / PI);
    double r = 3 * std::sin(t * 30 / PI);
    return std::make_tuple(p, q, r);
}

std::tuple<std::vector<double>, std::vector<std::vector<double>>> dfunc(
    std::vector<double> x, std::vector<std::vector<double>> dcm, std::vector<double> v_body, double t) {
    double phi = x[0];
    double theta = x[1];
    double psi = x[2];

    auto [p, q, r] = ffunc(t);

    std::vector<double> q_dot(3);
    q_dot[0] = 1 * std::tan(theta) * std::sin(phi) * p + std::tan(theta) * std::cos(phi) * r;
    q_dot[1] = std::cos(phi) * q - std::sin(phi) * r;
    q_dot[2] = std::sin(phi) / std::cos(theta) * q + std::cos(phi) / std::cos(theta) * r;

    std::vector<std::vector<double>> Cdot = dcm;

    return {q_dot, Cdot};
}

int main() {
    double dt = 0.01;
    double tmax = 60;
    int steps = static_cast<int>(tmax / dt);
    int func_calls = 0;

    std::vector<double> x0 = {0, 0, 0};
    std::vector<double> V_body = {60 * 6076 / 3600, 0, 0};

    std::vector<std::vector<double>> DCM = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

    std::vector<double> time(steps + 1);
    std::vector<std::vector<double>> x(steps + 1, std::vector<double>(6, 0));
    x[0] = {x0[0], x0[1], x0[2], V_body[0], V_body[1], V_body[2]};

    // Open a file to write the output
    std::ofstream outfile("Data.csv");
    
    // Write the CSV header
    outfile << "Time(s),Phi(deg),Theta(deg),Psi(deg)" << std::endl;

    for (int idx = 0; idx < steps; ++idx) {
        double time_val = idx * dt;
        time[idx] = time_val;

        auto [xdot1, Cdot1] = dfunc(x[idx], DCM, V_body, time_val);
        auto [xdot2, Cdot2] = dfunc(x[idx], DCM, V_body, time_val + dt / 2);
        auto [xdot3, Cdot3] = dfunc(x[idx], DCM, V_body, time_val + dt / 2);
        auto [xdot4, Cdot4] = dfunc(x[idx], DCM, V_body, time_val + dt);

        for (int i = 0; i < 3; ++i) {
            x[idx + 1][i] = x[idx][i] + (xdot1[i] + 2 * xdot2[i] + 2 * xdot3[i] + xdot4[i]) / 6 * dt;
        }

        if (idx % 100 == 0) {  // Output every 100th step for brevity
            double phi_deg = RAD2DEG * x[idx][0];
            double theta_deg = RAD2DEG * x[idx][1];
            double psi_deg = RAD2DEG * x[idx][2];

            // Write data to file
            outfile << std::fixed << std::setprecision(2)
                    << time[idx] << "," 
                    << phi_deg << "," 
                    << theta_deg << "," 
                    << psi_deg << std::endl;
        }

        func_calls += 4;
    }

    // Write final time step data to the file
    double final_time = steps * dt;
    double final_phi = RAD2DEG * x[steps][0];
    double final_theta = RAD2DEG * x[steps][1];
    double final_psi = RAD2DEG * x[steps][2];
    outfile << final_time << "," 
            << final_phi << "," 
            << final_theta << "," 
            << final_psi << std::endl;

    // Close the file
    outfile.close();

    return 0;
}
