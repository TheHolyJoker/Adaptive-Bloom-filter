//
// Created by tomer on 9/25/18.
//



#ifndef ADAPTIVEBF_NONADAPTIVEBLOOMFILTER_H
#define ADAPTIVEBF_NONADAPTIVEBLOOMFILTER_H

#include "../Hash.h"

using namespace std;


class NonAdaptiveBloomFilter {
public:
    vector<bool> filter;
    vector<Hash> kHashFuncs;
    size_t size;

    explicit NonAdaptiveBloomFilter(size_t n, double eps);

    void add(string *elementP);
    void add(string *elementP, size_t *hashIndex);

    bool lookup(string *elementP);
    bool lookup(string *elementP, size_t *hashIndex);

    size_t getFilterOnBits() const;
};


ostream &operator<<(ostream &os, const NonAdaptiveBloomFilter &bfr);
ostream &printKHashFunctions(ostream &os, const NonAdaptiveBloomFilter &bfr);

#endif //ADAPTIVEBF_NONADAPTIVEBLOOMFILTER_H
