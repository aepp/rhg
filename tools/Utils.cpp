//
// Created by Aleksandr Epp on 18.07.18.
//

#include "Utils.h"
#include <iostream>
#include <limits>
#include <tuple>
#include <vector>

bool Utils::sortPairsBySecond(const std::tuple<double, double, int> &a, const std::tuple<double, double, int> &b) {
    return (std::get<1>(a) < std::get<1>(b));
}
