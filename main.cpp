#include <iostream>
#include "tools/geometry.h"
#include <vector>
#include <random>

using namespace std;

int main() {
    int avgDegree = 4; // desired degree
    double n = pow(2, 10); // desired amount of vertices
    double m = n * avgDegree / 2; // expected amount of edges
    double alpha = 1; // desired parameter alpha

    double R = PGGeometry::getTargetRadius(n, m, alpha); // target radius

//    cout << "target radius: " << R << endl;

    double p = 0.9; // radialBoundaryRatio
    double c_0 = 0;
    double c_max = R;
    double c_1 = ((1 - p) * R) / (1 - pow(p, log2(n)));
    double c_i, c_i_prev, c_i_next;

    vector<double> C;
    C.push_back(c_0);
    C.push_back(c_1);

    vector<vector<pair<double, double> > > B;
//    cout << C[0] << endl;

    // generate annuli
    for (int i = 1; i < log2(n); i++) {
        c_i = C[i];
//        cout << c_i << endl;
        c_i_prev = C[i - 1];
        c_i_next = p * (c_i - c_i_prev) + c_i;

        C.push_back(c_i_next);
        B.emplace_back();
    }
    C.push_back(c_max);


    // generate vertices
    double phi, r;

    random_device rd_r;  //Will be used to obtain a seed for the random number engine
    mt19937 gen_r(rd_r()); //Standard mersenne_twister_engine seeded with rd()
    uniform_int_distribution<> dis_r(0, 360);

    // todo: implement random distro from density
    // for now it's just uniform distro
    random_device rd_phi;  //Will be used to obtain a seed for the random number engine
    mt19937 gen_phi(rd_phi()); //Standard mersenne_twister_engine seeded with rd()
    uniform_real_distribution<> dis_phi(0, R);

    for (int v = 0; v < n; v++) {
        r = 2 * M_PI * (double) dis_r(gen_r) / 360.0;
        phi = dis_phi(gen_phi);

        for (int i = 0; i < C.size() - 1; i++) {
            if (r > C[i] && r <= C[i + 1]) {
                B[i].push_back(make_pair(r, phi));
            }
        }
    }

    vector<pair<double, double> > b_i;
    for (int i = 0; i < B.size(); i++) {
        b_i = B[i];
        for (int v = 0; v < b_i.size(); v++) {
            cout << "(" << b_i[v].first << ", " << b_i[v].second << "); ";
        }
        cout << endl;
    }

    // integral of density function is the cdf
    // integrate f(r)=a*sinh(a*r)/(cosh(a*R)-1) = cosh(alpha * r)/(cosh(alpha * R) - 1) + constant


    return 0;
}