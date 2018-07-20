//
// Created by Aleksandr Epp on 18.07.18.
//

#ifndef HGG_EPP_UTILS_H
#define HGG_EPP_UTILS_H

#include <vector>
#include <tuple>

class Utils {
public:
    static bool sortTuplesBySecond(const std::tuple<double, double, int> &a, const std::tuple<double, double, int> &b);

    static bool sortG(const std::tuple<int, int> &v, const std::tuple<int, int> &u);

    static double drawRWithInverseTransformSampling(double prob, double alpha, double R);
};


#endif //HGG_EPP_UTILS_H
