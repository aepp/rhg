#include <iostream>
#include "tools/geometry.h"
#include <vector>
#include <random>

int main() {
    int avgDegree = 4; // desired degree
    double n = pow(2, 10); // desired amount of vertices
    double m = n * avgDegree / 2; // expected amount of edges
    double alpha = 1; // desired parameter alpha

    double R = PGGeometry::getTargetRadius(n, m, alpha); // target radius

//    std::cout << "target radius: " << R << std::endl;

    double p = 0.9; // radialBoundaryRatio
    double c_0 = 0;
    double c_max = R;
    double c_1 = ((1 - p) * R) / (1 - pow(p, log2(n)));
    double c_i, c_i_prev, c_i_next;

    std::vector<double> C;
    C.push_back(c_0);
    C.push_back(c_1);

    std::vector<double> B;
//    std::cout << C[0] << std::endl;

    // generate annuli
    for (int i = 1; i < log2(n); i++) {
        c_i = C[i];
//        std::cout << c_i << std::endl;
        c_i_prev = C[i - 1];
        c_i_next = p * (c_i - c_i_prev) + c_i;

        C.push_back(c_i_next);
//        B.push_back(set)
    }
    C.push_back(c_max);


    // generate vertices
    double phi, r;

    std::random_device rd_r;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen_r(rd_r()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis_r(0, 360);

    // todo: implement random distro from density
    // for now it's just uniform distro
    std::random_device rd_phi;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen_phi(rd_phi()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis_phi(0, R);

    for (int i = 0; i < n; i++) {
        r = 2 * M_PI * (double) dis_r(gen_r) / 360.0;
        phi = dis_phi(gen_phi);
        std::cout << phi << std::endl;
    }

    // integral of density function is the cdf
    // integrate f(r)=a*sinh(a*r)/(cosh(a*R)-1) = cosh(alpha * r)/(cosh(alpha * R) - 1) + constant


    return 0;
}