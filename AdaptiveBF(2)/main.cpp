#include <iostream>
#include <fstream>
#include <cstring>
#include <set>
#include <unordered_set>
#include "MurmurHash3.h"
#include "Hash.h"
#include "BloomFilter.h"
#include "SetTable.h"
#include "tests/testers.h"
#include "GreyBoxFunction.h"

using namespace std;

void allTests(size_t n, double eps, size_t lookupsNum, int shift, int uni_size, ostream &os);

void allTestsArray(size_t *nArray, size_t nArraySize, double *epsArray, size_t epsArraySize, int shift,
                   int uni_size, ostream &os);


int main() {
    cout << "Hello!" << endl;

    int uni_size = 64;
    int shift = 6;

    size_t factor = 1000 * 5;
    size_t n = factor << 1;
    size_t lookupsNum = factor << 1;
    double eps = 0.01;


    filebuf fb;
    fb.open("test.txt", ios::out);
    ostream os(&fb);

    int a = 9, b = 4;
    size_t nArray[a];
    nArray[0] = factor << 1;
    for (int i = 1; i < a; ++i) nArray[i] = nArray[i - 1] << 1;

    double epsArray[b];
    epsArray[0] = eps;
    for (int i = 1; i < b; ++i) epsArray[i] = epsArray[i - 1] * 0.5;

    testHelperRates(n,eps,lookupsNum,shift,uni_size);
//    allTestsArray(nArray, a, epsArray, b, shift, uni_size, os);


    fb.close();
    cout << "End!" << endl;
    return 0;
}

void allTests(size_t n, double eps, size_t lookupsNum, int shift, int uni_size, ostream &os) {
    os << "Number of elements: " << n << "\teps: " << eps << "\tNumber of Lookups: " << lookupsNum << endl;
    cout << "Number of elements: " << n << "\teps: " << eps << "\tNumber of Lookups: " << lookupsNum << endl;

    os << "TN tests:" << endl;
    cout << "TN tests:" << endl;
    testHelperTN(n, eps, lookupsNum, shift, uni_size,os);
    testNonAdaptiveTN(n, eps, lookupsNum, shift, uni_size,os);

    os << "TP tests:" << endl;
    cout << "TP tests:" << endl;
    testHelperTP(n, eps, shift, uni_size, os);
    testNonAdaptiveTP(n, eps, shift, uni_size, os);

    os << "Random tests:" << endl;
    cout << "Random tests:" << endl;
    testHelperRates(n, eps, lookupsNum, shift, uni_size, os);
    testNonAdaptiveRates(n, eps, lookupsNum, shift, uni_size, os);

    cout << "Number of lookups reduced by eps" << endl;
    os << "Number of lookups reduced by eps" << endl;
    lookupsNum = size_t(eps * lookupsNum);

    os << "FP tests:" << endl;
    cout << "FP tests:" << endl;
    testHelperFP(n, eps, lookupsNum, shift, uni_size, os);
    testNonAdaptiveFP(n, eps, lookupsNum, shift, uni_size, os);
}

void allTestsArray(size_t *nArray, size_t nArraySize, double *epsArray, size_t epsArraySize, int shift,
                   int uni_size, ostream &os) {
    for (int i = 0; i < nArraySize; ++i)
        for (int j = 0; j < epsArraySize; ++j)
            allTests(nArray[i], epsArray[j], nArray[i], shift, uni_size, os);
}


