//
// Created by Aleksandr Epp on 18.07.18.
//

#include "Geometry.h"
#include <cmath>

double Geometry::getTargetRadius(double n, double m, double alpha, double epsilon) {
    double pl_exp = 2 * alpha + 1;
    double target_avg_degree = (m / n) * 2;
    double xi_inv = ((pl_exp - 2) / (pl_exp - 1));
    double v = target_avg_degree * (M_PI / 2) * xi_inv * xi_inv;
    double current_r = 2 * log(n / v);
    double lower_bound = current_r / 2;
    double upper_bound = current_r * 2;
    do {
        current_r = (lower_bound + upper_bound) / 2;
        double current_k = Geometry::getExpectedDegree(n, alpha, current_r);
        if (current_k < target_avg_degree) {
            upper_bound = current_r;
        } else {
            lower_bound = current_r;
        }
    } while (std::abs(Geometry::getExpectedDegree(n, alpha, current_r) -
                      target_avg_degree) > epsilon);
    return current_r;
}

double Geometry::getExpectedDegree(double n, double alpha, double R) {
    double gamma = 2 * alpha + 1;
    double xi = (gamma - 1) / (gamma - 2);
    double first_sum_term = exp(-R / 2);
    double second_sum_term =
            exp(-alpha * R) * (alpha * (R / 2) *
                               ((M_PI / 4) * pow((1 / alpha), 2) -
                                (M_PI - 1) * (1 / alpha) + (M_PI - 2)) -
                               1);
    double exp_degree = (2 / M_PI) * xi * xi * n * (first_sum_term + second_sum_term);
    return exp_degree;
}

double Geometry::getMaxPhiDeviation(double r_v, double c_i, double R) {
    return acos((cosh(r_v) * cosh(c_i) - cosh(R)) / sinh(r_v) * sinh(c_i));
}
