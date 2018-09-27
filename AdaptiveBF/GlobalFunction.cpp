//
// Created by tomer on 9/20/18.
//

#include "GlobalFunction.h"


unsigned int udr(unsigned int a, unsigned int b) {
    const int range_from = a;
    const int range_to = b;
    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution<int> distr(range_from, range_to);
    return (unsigned int) distr(generator);
}

size_t udr(size_t a, size_t b) {
    const int range_from = a;
    const int range_to = b;
    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution<int> distr(range_from, range_to);
    return (size_t) distr(generator);
}


size_t getMi(size_t n0, double previousEps) {
    return (size_t) round(n0 * (previousEps * M_LOG2E) * (1 + 1.0/log2(n0)) * (log2(1.0 / previousEps)) + 1);
}

double getMi(size_t n0, double previousEps, bool overload) {
    return (n0 * (previousEps * M_LOG2E) * (1 + 1.0/log2(n0)) * (log2(1.0 / previousEps)));
}

size_t calcM(size_t n, double eps) {
    double a = (n * log(eps) / (M_LN2 * M_LN2)) * (-1);
    return (unsigned int) ++a;
}

double calcM(size_t n, double eps, bool overload) {
    return (n * log(eps) / (M_LN2 * M_LN2)) * (-1);
//    return (unsigned int) ++a;
}

size_t calcK(size_t n, size_t m) {
    auto temp = (size_t) (M_LN2 * ((double) m) / n);
    return (temp) ? temp : 1;
//    return (unsigned int) (M_LN2 * ((float) m) / n);
}

size_t getDepthByMinNM(size_t n, double eps) {
    size_t depth = 1;
    const double upperConst = 1 + 1 / log2(n);
    double tempN = (double) n, tempM = calcM(n, eps, true);
    while (tempM > 1 && tempN > 1) {
        ++depth;
        tempM = getMi(n, eps, true);
        tempN = upperConst * (tempN * eps);
        eps *= eps;
    }
    return depth;
}

void GetMList(size_t n, double eps, size_t *mList, size_t depth) {
    mList[0] = calcM(n, eps);
    for (int i = 1; i < depth; ++i) {
        mList[i] = getMi(n, eps);
        eps *= eps;
    }
//    mList[depth - 1] = mList[depth - 2];
}

void GetKList(size_t n, double eps, size_t *kList, size_t *mList, size_t depth) {
    kList[0] = calcK(n,mList[0]);
    size_t n_i = n;
    double upperConst = 1 + 1/ log2(n);
    for (int i = 1; i < depth; ++i) {
        double exp_i = n_i * eps;
        n_i = (size_t) (exp_i * upperConst + 1);
        kList[i] = calcK(n_i, mList[i]);
    }
//    kList[depth - 1] = kList[depth - 2];

}

void lastPrintMK(size_t n, double eps) {
    size_t depth = getDepthByMinNM(n, eps);
    size_t mList[depth];
    size_t kList[depth];
    GetMList(n, eps, mList, depth);
    GetKList(n, eps, kList, mList, depth);
    for (int i = 0; i < depth; ++i) {
        cout << i << ":\t" << mList[i] << ", " << kList[i] << endl;
    }
}


void mk_test() {
    size_t n = 1000;
    for (int i = 0; i < 5; ++i) {
        n *= 5;
        for (int j = 1; j < 8; ++j) {
            double eps = pow(0.5, j);
            cout << "n is: " << n;
            cout << " eps is: " << eps;
            cout << " depth is: " << getDepthByMinNM(n, eps) << endl;
            lastPrintMK(n, eps);
        }
    }
}



//bool isMSmall(size_t m) {
//    return log2(m) < MIN_M_LOG_VAL;
//}

//bool isNSmall(size_t m) {
//    return log2(m) < MIN_N_LOG_VAL;
//}



//size_t getNiExp(size_t previousN, double previousEps) {
//    return (size_t) round(previousN * previousEps + 1);
//}

//double niUpperConst(size_t n0) {
//    return (1 + 1.0 / log2(n0));
//}



//size_t *getMiList(size_t n0, double previousEps, size_t depth) {
//
//    return (size_t) round(n0 * (previousEps * M_LOG2E) * niUpperConst(n0) * (log2(1.0 / previousEps)) + 1);
//}


//size_t getNi(size_t n0, size_t previousN, double previousEps) {
//    return (size_t) round(niUpperConst(n0) * getNiExp(previousN, previousEps) + 1);
//}




//unsigned int myGetDepth(size_t n, double eps) {
//    double upperBound = (1 + 1.0 / log2(n));
//    unsigned int s = 0;
//    auto temp = (double) n;
//    while (temp >= 1) {
//        ++s;
//        temp *= eps * upperBound;
//        eps *= eps;
//    }
//    return s;
//}

//size_t softGetDepth(size_t n, double eps) {
//    return (size_t) round(log2(log2(n)) + 1);
//}

//unsigned int*[2] softMKList(){
//
//}

//
//size_t getNi(size_t currN, size_t previousN, double currEps) {
//    double NiExp = currN * currEps;
//    double upperConst = 1 + 1.0 / log2(currN);
//    return (unsigned int) (NiExp * upperConst + 1);
//}
//
//double myGetNextN(double currN, double currEps) {
//    double NiExp = currN * currEps;
//    double upperConst = 1 + 1.0 / log2(currN);
//    return NiExp * upperConst;
//}
//
//double myGetNextN(size_t currN, double currEps) {
//    return myGetNextN((double) currN, currEps);
//}

/*

//unsigned int getNi(unsigned int elementCounter, unsigned int depth) {
//    double tempEps = EPS;
//    for (int i = 1; i < depth; ++i) tempEps *= tempEps;
//    double par1 = elementCounter * (tempEps * M_LOG2E);
//    double par2 = 1 + 1 / log2(elementCounter);
//    double par3 = log2(1 / tempEps);
//
//    double tempRes = par1 * par2 * par3;
//    if (tempRes <= K_HASH_FUNCTION) return K_HASH_FUNCTION;
//    return (unsigned int) ++tempRes;
//}
*/

//size_t getNextM(size_t initN, double previousEps) {
//    return (size_t) (initN * (previousEps * M_LOG2E) * (1 + 1.0 / log2(initN)) * (log2(1.0 / previousEps)) + 1);
//}
//
//size_t getNextK(size_t previousNi, double previousEps) {
//    size_t ni = (size_t) myGetNextN(previousNi, previousEps) + 1;
//    return (size_t) (previousNi * (previousEps * M_LOG2E) * (1 + 1.0 / log2(previousNi)) * (log2(1.0 / previousEps)) +
//                     1);
//}


//unsigned int logStar(unsigned int n) {
//    unsigned int s = 0;
//    auto temp = (double) n;
//    while (temp > 1) {
//        ++s;
//        temp = log2(temp);
//    }
//    return s;
//}


//size_t getTotalSize(size_t n, double eps) {
//    size_t depth = myGetDepth(n, eps);
//}

//std::ostream &printN_M_K(std::ostream &os, size_t n, double eps) {
//    const size_t depth = softGetDepth(n, eps);
////    const size_t m = calcM(n, eps);
//    os << "[";
//    printN_M_K_single(os, n, calcM(n, eps));
//    os << ", ";
//    size_t n_i = n, m_i = 0;
//    const double upperConst = (1 + 1.0 / log2(n));
//    for (int i = 1; i < depth; ++i) {
//        auto exp_i = (size_t) round(n_i * eps + 1);
//        n_i = (size_t) round(exp_i * upperConst + 1);
//        m_i = getMi(n, eps);
//        printN_M_K_single(os, n_i, m_i);
//        eps *= eps;
//    }
//    os << "]" << std::endl;
//    return os;
//}

//std::ostream &printN_M_K_single(std::ostream &os, size_t n, size_t m) {
//    const size_t k = calcK(n, m);
//    os << "(" << n << ", " << m << ", " << k << ")";
//    return os;
//}

//void softMList(size_t n, double eps, size_t mList[], size_t depth) {
//    mList[0] = calcM(n, eps);
//    size_t n_i = n;
//    const double upperConst = (1 + 1.0 / log2(n));
//    for (int i = 1; i < depth; ++i) {
//        auto exp_i = (size_t) (n_i * eps + 1);
//        n_i = (size_t) (exp_i * upperConst + 1);
//        mList[i] = getMi(n, eps);
//        eps *= eps;
//    }
//}


//void myPrintArray(size_t *arr, size_t size) {
//    if (size == 0) {
//        cout << "[Empty]" << endl;
//        return;
//    }
//    cout << "[" << arr[0];
//    for (int i = 1; i < size; ++i) cout << ", " << arr[i];
//    cout << "]" << endl;
//
//}


//
//void softKList(size_t n, double eps, size_t *kList, size_t depth) {
//    kList[0] = calcK(n, calcM(n, eps));
//    size_t n_i = n;
//    const double upperConst = (1 + 1.0 / log2(n));
//    for (int i = 1; i < depth; ++i) {
//        auto exp_i = (size_t) (n_i * eps + 1);
//        n_i = (size_t) (exp_i * upperConst + 1);
//        kList[i] = calcK(getMi(n, eps), kList[i][0]);
//        eps *= eps;
//    }
//}
//
//size_t myMList(size_t n, double eps, size_t *mList, size_t depth) {
//    mList[0] = calcM(n, eps);
////    size_t n_i = n;
////    const double upperConst = (1 + 1.0 / log2(n));
//    for (int i = 1; i < depth; ++i) {
//        size_t m_i = getMi(n, eps);
//        mList[i] = getMi(n, eps);
//        if (round(log2(m_i)) < 10 && i < depth - 1)
//        {
//
//        }
////        auto exp_i = (size_t) (n_i * eps + 1);
////        n_i = (size_t) (exp_i * upperConst + 1);
//        eps *= eps;
//    }
//}

//size_t myNList(size_t n, double eps, size_t *nList, size_t depth) {
//    return 0;
//
//}

//void softMKList(size_t n, double eps, size_t *mkList[], size_t depth) {
////    size_t m = calcM(n, eps);
//    mkList[0][0] = calcM(n, eps);
//    mkList[0][1] = calcK(n, mkList[0][0]);
//    size_t n_i = n, m_i = 0;
//    const double upperConst = (1 + 1.0 / log2(n));
//    for (int i = 1; i < depth; ++i) {
//        auto exp_i = (size_t) (n_i * eps + 1);
//        n_i = (size_t) (exp_i * upperConst + 1);
//        mkList[i][0] = getMi(n, eps);
//        mkList[i][1] = calcK(n_i, mkList[i][0]);
//        eps *= eps;
//    }
//}

//void softMKList(size_t n, double eps, size_t *mkList[2], size_t depth) {
////    size_t m = calcM(n, eps);
//    mkList[0][0] = calcM(n, eps);
//    mkList[0][1] = calcK(n, mkList[0][0]);
//    size_t n_i = n, m_i = 0;
//    const double upperConst = (1 + 1.0 / log2(n));
//    for (int i = 1; i < depth; ++i) {
//        auto exp_i = (size_t) (n_i * eps + 1);
//        n_i = (size_t) (exp_i * upperConst + 1);
//        mkList[i][0] = getMi(n, eps);
//        mkList[i][1] = calcK(n_i, mkList[i][0]);
//        eps *= eps;
//    }
//}


//size_t getBloomFilterSize(size_t, double eps)


//template <typename T>
//void printArray(T array, size_t size)
//{
//    std::cout << "[" << array[0];
//    for(size_t i = 1; i < size ; ++i){
//        std::cout << ", " << array[i];
//    }
//    std::cout << "]" <<std::endl;
//
//}