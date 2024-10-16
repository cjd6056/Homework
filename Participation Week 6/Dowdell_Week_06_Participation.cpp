/*
Class: AERSP 424
Title: Week 06 Participation Credit
Authors: Conor and Gabrielle Dowdell
Date: 16 Oct. 2024
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <fstream>
#include <iomanip>

const double PI = 3.141592653589793;
const double RAD2DEG = 180.0 / PI;
const double KNOTS_TO_FT_PER_SEC = 1.68781;  // Conversion for velocity from knots to ft/sec

// Function for angular velocities p, q, r
std::tuple<double, double, double> ffunc(double t) 
{
    double p = (30 * PI) / 6;  // Constant roll rate [deg/sec]
    double q = std::cos((6.0 / PI) * t);  // Angular velocity q
    double r = 3 * std::sin((30.0 / PI) * t);  // Angular velocity r
    return std::make_tuple(p, q, r);
}

// Function for the gimbal equation (rate of change of Euler angles)
std::vector<double> gimbalEq(double phi, double theta, double p, double q, double r) 
{
    std::vector<double> q_dot(3);
    q_dot[0] = tan(theta) * sin(phi) * p + tan(theta) * cos(phi) * r;  // phi_dot
    q_dot[1] = cos(phi) * q - sin(phi) * r;                            // theta_dot
    q_dot[2] = sin(phi) / cos(theta) * q + cos(phi) / cos(theta) * r;  // psi_dot
    return q_dot;
}

// Skew-symmetric matrix for angular velocities [p, q, r]
std::vector<std::vector<double>> skewSymmetricMatrix(double p, double q, double r) 
{
    return 
    {
        {0, -r, q},
        {r, 0, -p},
        {-q, p, 0}
    };
}

// Matrix multiplication (3x3 * 3x3)
std::vector<std::vector<double>> matrixMultiply(const std::vector<std::vector<double>>& A, const std::vector<std::vector<double>>& B) 
{
    std::vector<std::vector<double>> result(3, std::vector<double>(3, 0.0));
    for (int i = 0; i < 3; ++i) 
    {
        for (int j = 0; j < 3; ++j) 
        {
            for (int k = 0; k < 3; ++k) 
            {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

// DCM update using strapdown equation
std::vector<std::vector<double>> updateDCM(const std::vector<std::vector<double>>& dcm, double p, double q, double r, double dt) 
{
    auto S = skewSymmetricMatrix(p, q, r);
    auto C_dot = matrixMultiply(dcm, S);  // C_dot = DCM * S
    // Simple Euler integration: C_new = C_old + C_dot * dt
    std::vector<std::vector<double>> dcm_new(3, std::vector<double>(3, 0.0));
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            dcm_new[i][j] = dcm[i][j] + C_dot[i][j] * dt;
        }
    }
    return dcm_new;
}

// RK4 step for Euler angles
std::vector<double> RK4Step(double phi, double theta, double psi, double p, double q, double r, double dt) 
{
    auto k1 = gimbalEq(phi, theta, p, q, r);

    auto k2_phi = phi + 0.5 * k1[0] * dt;
    auto k2_theta = theta + 0.5 * k1[1] * dt;
    auto k2_psi = psi + 0.5 * k1[2] * dt;
    auto k2 = gimbalEq(k2_phi, k2_theta, p, q, r);

    auto k3_phi = phi + 0.5 * k2[0] * dt;
    auto k3_theta = theta + 0.5 * k2[1] * dt;
    auto k3_psi = psi + 0.5 * k2[2] * dt;
    auto k3 = gimbalEq(k3_phi, k3_theta, p, q, r);

    auto k4_phi = phi + k3[0] * dt;
    auto k4_theta = theta + k3[1] * dt;
    auto k4_psi = psi + k3[2] * dt;
    auto k4 = gimbalEq(k4_phi, k4_theta, p, q, r);

    std::vector<double> phi_theta_psi_dot(3);
    phi_theta_psi_dot[0] = (k1[0] + 2 * k2[0] + 2 * k3[0] + k4[0]) / 6.0;  // phi_dot
    phi_theta_psi_dot[1] = (k1[1] + 2 * k2[1] + 2 * k3[1] + k4[1]) / 6.0;  // theta_dot
    phi_theta_psi_dot[2] = (k1[2] + 2 * k2[2] + 2 * k3[2] + k4[2]) / 6.0;  // psi_dot

    return phi_theta_psi_dot;
}

// Main simulation function
void simulateAndSave(double dt, const std::string& filename) 
{
    // Time and initial conditions
    double tmax = 60;
    int steps = static_cast<int>(tmax / dt);

    // Initial conditions
    std::vector<double> x0 = {0, 0, 0};  // Euler angles [phi, theta, psi]
    std::vector<double> V_body = {60 * KNOTS_TO_FT_PER_SEC, 0, 0};  // Velocity in body frame (ft/sec)
    std::vector<double> pos_NED = {0, 0, 0};  // Position in NED
    std::vector<std::vector<double>> DCM = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};  // Initial DCM (identity)

    // Open output file
    std::ofstream file(filename);
    file << "Time,phi,theta,psi,p,q,r,phi_dot,theta_dot,psi_dot,V_NED_x,V_NED_y,V_NED_z,Pos_NED_x,Pos_NED_y,Pos_NED_z\n";

    for (int idx = 0; idx < steps; ++idx) 
    {
        double t = idx * dt;

        // Get angular velocities [p, q, r]
        auto [p, q, r] = ffunc(t);

        // Update DCM
        DCM = updateDCM(DCM, p, q, r, dt);

        // Calculate velocity in NED frame
        std::vector<double> V_NED(3, 0.0);
        for (int i = 0; i < 3; ++i) 
        {
            V_NED[i] = DCM[i][0] * V_body[0] + DCM[i][1] * V_body[1] + DCM[i][2] * V_body[2];
        }

        // Update position in NED frame
        for (int i = 0; i < 3; ++i) 
        {
            pos_NED[i] += V_NED[i] * dt;
        }

        // Get current Euler angles
        auto phi = x0[0], theta = x0[1], psi = x0[2];

        // Perform RK4 integration step to update Euler angles
        auto euler_dot = RK4Step(phi, theta, psi, p, q, r, dt);

        // Update Euler angles
        x0[0] += euler_dot[0] * dt;  // Update phi
        x0[1] += euler_dot[1] * dt;  // Update theta
        x0[2] += euler_dot[2] * dt;  // Update psi

        // Write data to CSV
        file << t << "," << RAD2DEG * x0[0] << "," << RAD2DEG * x0[1] << "," << RAD2DEG * x0[2] << ","
             << p << "," << q << "," << r << ","
             << euler_dot[0] << "," << euler_dot[1] << "," << euler_dot[2] << ","
             << V_NED[0] << "," << V_NED[1] << "," << V_NED[2] << ","
             << pos_NED[0] << "," << pos_NED[1] << "," << pos_NED[2] << "\n";
    }

    file.close();
}

int main() 
{
    // Simulate for different time steps and save results to CSV files
    simulateAndSave(0.2, "0.2_Data.csv");
    simulateAndSave(0.1, "0.1_Data.csv");
    simulateAndSave(0.025, "0.025_Data.csv");
    simulateAndSave(0.0125, "0.0125_Data.csv");

    std::cout << "Files Saved Successfully!\n" << std::endl;

    return 0;
}
