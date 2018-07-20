//
// Created by Aleksandr Epp on 18.07.18.
//

#include "Utils.h"
#include <iostream>
#include <limits>
#include <tuple>
#include <vector>
#include <cmath>

bool Utils::sortTuplesBySecond(const std::tuple<double, double, int> &a, const std::tuple<double, double, int> &b) {
    return (std::get<1>(a) < std::get<1>(b));
}

bool Utils::sortG(const std::tuple<int, int> &v, const std::tuple<int, int> &u) {
    if (std::get<0>(u) == std::get<0>(v)) {
        return (std::get<1>(u) > std::get<1>(v));
    }
    return (std::get<0>(u) > std::get<0>(v));
}

double Utils::drawRWithInverseTransformSampling(double prob, double alpha, double R) {
//    return acosh(prob * (cosh(alpha * R) - 1) + 1) / alpha;
    return acosh(R * (cosh(alpha * prob) - 1)) / alpha;
//    return alpha * sinh(alpha * prob) / (cosh(alpha * R) - 1); // pdf
//    return cosh(alpha * prob)/(cosh(alpha * R) - 1); // cdf
}
