//
// Created by tomer on 9/24/18.
//


#ifndef ADAPTIVEBF_NONADAPTIVEHELPER_H
#define ADAPTIVEBF_NONADAPTIVEHELPER_H


#include <set>
#include "NonAdaptiveBloomFilter.h"


class NonAdaptiveHelper {
    vector<NonAdaptiveBloomFilter> nBFVec;
    vector<set<string> > setsVec;

public:
    NonAdaptiveHelper(size_t n, double eps) {
        nBFVec.emplace_back(n, eps);
        setsVec.resize(nBFVec[0].size);
    }

    void add(string *s);

    int lookup(string *s);

    int naiveLookup(string *s);

    string getName();

    NonAdaptiveBloomFilter getNABF() const;
};

ostream &operator<<(ostream &os, const NonAdaptiveHelper &hp);

#endif //ADAPTIVEBF_NONADAPTIVEHELPER_H
