//
// Created by tomer on 9/24/18.
//


#ifndef ADAPTIVEBF_NONADAPTIVEHELPER_H
#define ADAPTIVEBF_NONADAPTIVEHELPER_H


#include <set>
#include "NonAdaptiveBloomFilter.h"
//#include "../SetTable.h"


class NonAdaptiveHelper {
    NonAdaptiveBloomFilter *nbfp;
    vector<set<string> *> setsVec;

public:
    NonAdaptiveHelper(size_t n, double eps) : nbfp(new NonAdaptiveBloomFilter(n, eps))
    {
        setsVec.resize(nbfp->size);
    }

    ~NonAdaptiveHelper();
    void add(string *s);

    int lookup(string *s);

    int naiveLookup(string *s);

    string getName();

    NonAdaptiveBloomFilter *getNABFPointer() const;
    NonAdaptiveBloomFilter getNABF() const;
};

ostream &operator<<(ostream &os, const NonAdaptiveHelper &hp);
//
//    void adapt(string *s, size_t depth, size_t index);
//
//    size_t getVecSize() const;
//
//    const BloomFilter &getBloomI(int i) const;
//
//ostream &operator<<(ostream &os, const Helper &hp);
//
//};
//
//
#endif //ADAPTIVEBF_NONADAPTIVEHELPER_H
