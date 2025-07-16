#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <algorithm>
#include <iomanip>
#include <Eigen/Dense>
#include <matplotlibcpp.h>

namespace plt = matplotlibcpp;

using namespace std;
using namespace Eigen;

void three_body_solution(const VectorXd& y, const VectorXd& masses, double G, VectorXd& dydt) {
    // Initialize the masses
    double m1 = masses(0);
    double m2 = masses(1);
    double m3 = masses(2);
    
    // Initialize state vector
    Vector3d r1 = y.segment<3>(0);
    Vector3d v1 = y.segment<3>(3);
    Vector3d r2 = y.segment<3>(6);
    Vector3d v2 = y.segment<3>(9);
    Vector3d r3 = y.segment<3>(12);
    Vector3d v3 = y.segment<3>(15);
    
    // Compute distances
    Vector3d r21 = r2 - r1;
    Vector3d r31 = r3 - r1;
    Vector3d r32 = r3 - r2;
    Vector3d r12 = -r21;
    Vector3d r13 = -r31;
    Vector3d r23 = -r32;

    // Normalized distances
    double r21n = r21.norm();
    double r31n = r31.norm();
    double r32n = r32.norm();
    
    // Acceleration portion
    Vector3d a1 = G * (m2 * r21 / pow(r21n, 3) + m3 * r31 / pow(r31n, 3));
    Vector3d a2 = G * (m1 * r12 / pow(r21n, 3) + m3 * r32 / pow(r32n, 3));
    Vector3d a3 = G * (m1 * r13 / pow(r31n, 3) + m2 * r23 / pow(r32n, 3));

    // Combine
    dydt << v1, a1, v2, a2, v3, a3;
}

void three_body_solver() {
    cout << "PROBLEM 1" << endl;

    // VARIABLES
    double G = 1;
    double m1 = 1;
    double m2 = 2;
    double m3 = 3;
    VectorXd masses(3);
    masses << m1, m2, m3;

    // INITIAL CONDITIONS (t0)
    Vector3d r1(0, 0, 0);
    Vector3d r2(1, 0, 0);
    Vector3d r3(0.5, sqrt(3) / 2, 0);

    Vector3d v1(0, 0, 0);
    Vector3d v2(0, sqrt(6), 0);
    Vector3d v3(-3 * sqrt(2) / 2, sqrt(6) / 2, 0);

    // State Vector
    VectorXd y0(18);
    y0 << r1, v1, r2, v2, r3, v3;

    // SOLVE ODE
    // time integral
    double tspan[2] = {0, M_PI};
    int num_steps = 100; // Number of steps for integration
    VectorXd T(num_steps);
    MatrixXd Y(num_steps, 18);

    // Simple Euler integration for demonstration
    double dt = (tspan[1] - tspan[0]) / (num_steps - 1);
    for (int i = 0; i < num_steps; ++i) {
        T(i) = tspan[0] + i * dt;
        VectorXd dydt(18);
        three_body_solution(y0, masses, G, dydt);
        y0 += dydt * dt;
        Y.row(i) = y0.transpose();
    }

    // PLOT
    // time step to plot
    double time_step[4] = {0, M_PI / 4, M_PI / 2, 3 * M_PI / 4};

    plt::figure();
    plt::grid(true);
    vector<string> colors = {"r", "b", "c"};

    for (int i = 0; i < 4; ++i) {
        double t_target = time_step[i];
        int index = static_cast<int>(t_target / dt);
        VectorXd y_interp = Y.row(index);

        // Extract positions
        Vector3d r1 = y_interp.segment<3>(0);
        Vector3d r2 = y_interp.segment<3>(6);
        Vector3d r3 = y_interp.segment<3>(12);

        // Compute Center of Mass
        Vector3d rcm = (m1 * r1 + m2 * r2 + m3 * r3) / (m1 + m2 + m3);

        Vector3d r1_rel = r1 - rcm;
        Vector3d r2_rel = r2 - rcm;
        Vector3d r3_rel = r3 - rcm;

        // Plot Triangle
        plt::plot({r1_rel(0), r2_rel(0), r3_rel(0), r1_rel(0)},
                  {r1_rel(1), r2_rel(1), r3_rel(1), r1_rel(1)},
                  "-o", {{"label", "t = " + to_string(t_target)}});
    
        // Draw 3 concentric circles through each particle, centered at rcm
        vector<double> radii = {r1_rel.head<2>().norm(), r2_rel.head<2>().norm(), r3_rel.head<2>().norm()};
        for (int j = 0; j < 3; ++j) {
            vector<double> theta(300);
            for (int k = 0; k < 300; ++k) {
                theta[k] = 2 * M_PI * k / 300;
            }
            vector<double> x_circ(300), y_circ(300);
            for (int k = 0; k < 300; ++k) {
                x_circ[k] = radii[j] * cos(theta[k]);
                y_circ[k] = radii[j] * sin(theta[k]);
            }
            plt::plot(x_circ, y_circ, {{"color", colors[j]}, {"label", "Circle through r" + to_string(j + 1) + " at t=" + to_string(t_target)}});
        }
    }

    plt::legend();
    plt::xlabel("x");
    plt::ylabel("y");
    plt::title("Three-Body Positions in X-Y Plane Relative to Rcm");
    plt::axis("equal");
    plt::show();
}

int main() {
    three_body_solver();
    return 0;
}