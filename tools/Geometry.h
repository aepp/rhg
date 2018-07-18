//
// Created by Aleksandr Epp on 18.07.18.
//

#ifndef HGG_EPP_GEOMETRY_H
#define HGG_EPP_GEOMETRY_H

#include <vector>

class Geometry {
public:
    /**
     * from NetworKit by von Lootz
     *
     * @param n
     * @param m
     * @param alpha
     * @param epsilon
     * @return
     */
    static double getTargetRadius(double n, double m, double alpha = 1, double epsilon = 0.01);

    /**
     *
     * @param n
     * @param alpha
     * @param R
     * @return
     */
    static double getExpectedDegree(double n, double alpha, double R);

//    /**
//     * calculates deviation boundaries for p
//     * @param r_v
//     * @param c_i
//     * @param phi_v
//     * @param phi_u
//     * @return
//     */
//    static std::pair<double, double> getMinMaxPhi(double r_v, double c_i, double phi_v, double phi_u);

    /**
     * Get maximum angle (phi) deviation of a potential neighbour of vertex v with
     * a given radius r_v. If the difference between angle of vertex v and a potential
     * neighbour u is at most this deviation, then u is considered to be neighbour of v.
     *
     * @param r_v
     * @param c_i
     * @param R
     * @return
     */
    static double getMaxPhiDeviation(double r_v, double c_i, double R);
};


#endif //HGG_EPP_GEOMETRY_H
