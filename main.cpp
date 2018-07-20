#include <iostream>
#include <vector>
#include <random>
#include <tuple>
#include <fstream>

#include "tools/Geometry.h"
#include "tools/Utils.h"

using namespace std;

int main() {
    int avgDegree = 4; // desired degree
    double n = pow(2, 10); // desired amount of vertices
    double m = n * avgDegree / 2; // expected amount of edges
    double alpha = 1; // desired parameter alpha

    double R = Geometry::getTargetRadius(n, m, alpha); // target radius

    double p = 0.9; // radialBoundaryRatio
    double c_0 = 0;
    double c_max = R;
    double c_1 = ((1 - p) * R) / (1 - pow(p, log2(n)));
    double c_i, c_i_prev, c_i_next;

    vector<double> C;
    C.push_back(c_0);
    C.push_back(c_1);

//    vector<tuple<double, double, double, double> > annuli;
//    double mincdf = std::cosh(alpha * c_0);
//    double mass = std::cosh(alpha * c_1) - mincdf;
//    annuli.emplace_back(make_tuple(c_0, c_1, mincdf, mass));

    vector<vector<tuple<double, double, int> > > B;
    B.emplace_back();
    B.emplace_back();

    cout << "\nannuli boundaries (c_i):\n" << endl;
    cout << "c_0: " << c_0 << endl;
    cout << "c_1: " << c_1 << endl;

    /**
     * generate annuli
     */
    for (int i = 1; i < log2(n) - 3; i++) {
        c_i = C[i];
        c_i_prev = C[i - 1];
        c_i_next = p * (c_i - c_i_prev) + c_i;

        C.push_back(c_i_next);
        B.emplace_back();
//        mincdf = std::cosh(alpha * c_i);
//        mass = std::cosh(alpha * c_i_next) - mincdf;
//        annuli.emplace_back(make_tuple(c_i, c_i_next, mincdf, mass));

        cout << "c_" << i + 1 << ": " << c_i_next << endl;
    }
    cout << "c_" << C.size() << " (R): " << c_max << endl << "-------------" << endl << endl;
    C.push_back(c_max);

    // no need to push another empty set into B, because B holds intervals and intervals are 1 less than limits
    // B.emplace_back();

    /**
     * generate vertices
     */
    double phi, r;

    random_device rd_phi;  //Will be used to obtain a seed for the random number engine
    mt19937 gen_phi(rd_phi()); //Standard mersenne_twister_engine seeded with rd()
    uniform_real_distribution<> dis_phi(0, 2 * M_PI);

    random_device rd_r;  //Will be used to obtain a seed for the random number engine
    mt19937 gen_r(rd_r()); //Standard mersenne_twister_engine seeded with rd()
    uniform_real_distribution<> dis_r(0.1, 1);

    for (int v = 0; v < n; v++) {
        // draw phi
        r = Utils::drawRWithInverseTransformSampling(dis_r(gen_r), alpha, R);
        cout << r << endl;
        phi = dis_phi(gen_phi);

        // check in which slab drawn r belongs
        for (int i = 0; i < C.size() - 1; i++) {
            if (r >= C[i] && r <= C[i + 1]) {
                // insert vertex v in annulus b_i if r between c_i and c_i+1
                B[i].push_back(make_tuple(r, phi, v));
                break;
            }
        }
    }

    /**
     * sort vertices in each b_i
     */
    for (int i = 0; i < B.size(); i++) {
        sort(B[i].begin(), B[i].end(), Utils::sortTuplesBySecond);
    }

    /**
     * generate edges
     */
    double r_v, phi_v, phi_u, maxAbsDeviation;
    vector<tuple<int, int> > G;

    for (int i = 0; i < B.size(); i++) {
        for (int v = 0; v < B[i].size(); v++) {
            r_v = get<0>(B[i][v]);
            phi_v = get<1>(B[i][v]);
            maxAbsDeviation = Geometry::getMaxPhiDeviation(r_v, C[i], R);

            for (int u = 0; u < B[i].size(); u++) {
                phi_u = get<1>(B[i][u]);
                if (abs(phi_v - phi_u) <= maxAbsDeviation && v != u) {
                    G.emplace_back(get<2>(B[i][v]), get<2>(B[i][u]));
                }
            }
        }
    }

    /**
     * sort resulting graph G
     */
    sort(G.begin(), G.end(), Utils::sortG);

    /**
     * log
     */
    cout << "# of elements per b_i: " << endl << endl;

    for (int i = 0; i < B.size(); i++) {
        cout << "B_" << i << ": " << B[i].size() << endl;
    }
    cout << "-------------" << endl << endl;

    /**
     * write resulting graph G to file
     */
    std::ofstream result("/Users/aleksandr/Masterarbeit/hgg_epp/result.txt");

    for (int v = 0; v < G.size(); v++) {
        result << get<0>(G[v]) << " " << get<1>(G[v]) << "\n";
    }

    result.close();

    // integral of density function is the cdf
    // integrate f(r)=a*sinh(a*r)/(cosh(a*R)-1) = cosh(alpha * r)/(cosh(alpha * R) - 1)


    return 0;
}