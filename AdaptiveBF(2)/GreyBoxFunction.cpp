//
// Created by tomer on 9/20/18.
//

#include "GreyBoxFunction.h"



size_t rangedUniformDistribution(size_t a, size_t b) {
    const int range_from = a;
    const int range_to = b;
    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution<int> distr(range_from, range_to);
    return (size_t) distr(generator);
}

double getNextM(size_t n, double previousEps) {
    return (n * (previousEps * M_LOG2E) * (1 + 1.0 / log2(n)) * (log2(1.0 / previousEps)));
}

double calcM(size_t n, double eps) {
    return (n * log(eps) / (M_LN2 * M_LN2)) * (-1);
}

size_t calcK(size_t n, size_t m) {
    auto temp = size_t(round(M_LN2 * ((double) m) / n));
    return (temp) ? temp : 1;
//    return (unsigned int) (M_LN2 * ((float) m) / n);
}

size_t getDepth(size_t n, double eps) {
    size_t depth = 0;
    const double upperConst = 1 + 1 / log2(n);
    double tempN = (double) n, tempM = calcM(n, eps);
    while (tempM > 1 && tempN > 1) {
        ++depth;
        tempM = getNextM(n, eps);
        tempN = upperConst * (tempN * eps);
        eps *= eps;
    }
    return depth;
}

void GetMList(size_t n, double eps, size_t *mList, size_t depth) {
    mList[0] = calcM(n, eps);
    for (int i = 1; i < depth; ++i) {
        mList[i] = getNextM(n, eps);
        eps *= eps;
    }
//    mList[depth - 1] = mList[depth - 2];
}

void GetKList(size_t n, double eps, size_t *kList, size_t *mList, size_t depth) {
    kList[0] = calcK(n, mList[0]);
    size_t n_i = n;
    double upperConst = 1 + 1 / log2(n);
    for (int i = 1; i < depth; ++i) {
        double exp_i = n_i * eps;
        n_i = (size_t) (exp_i * upperConst + 1);
        kList[i] = calcK(n_i, mList[i]);
    }
//    kList[depth - 1] = kList[depth - 2];

}

