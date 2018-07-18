//
// Created by Aleksandr Epp on 18.07.18.
//

#ifndef HGG_EPP_UTILS_H
#define HGG_EPP_UTILS_H

#include <vector>
#include <tuple>

class Utils {
public:
    static bool sortPairsBySecond(const std::tuple<double, double, int> &a, const std::tuple<double, double, int> &b);
};


#endif //HGG_EPP_UTILS_H
