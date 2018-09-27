//
// Created by tomer on 9/25/18.
//

#include "NonAdaptiveBloomFilter.h"

NonAdaptiveBloomFilter::NonAdaptiveBloomFilter(size_t n, double eps) {
    size_t m = calcM(n, eps);
    size_t k = calcK(n, m);
    this->size = m;
    this->filter = new bool[m]();
    kHashFuncs.resize(k);
    for (int i = 0; i < k; ++i) this->kHashFuncs[i] = Hash(size);
}

NonAdaptiveBloomFilter::~NonAdaptiveBloomFilter() {
    delete[] filter;
}
void NonAdaptiveBloomFilter::add(string *elementP) {
    for (auto h : this->kHashFuncs) this->filter[h.calc(elementP, size)] = true;
}

void NonAdaptiveBloomFilter::add(string *elementP, size_t *hashIndex) {
    size_t i = 0;
    for (auto h : this->kHashFuncs) {
        hashIndex[i] = h.calc(elementP, size);
        this->filter[hashIndex[i]] = true;
        ++i;
    }
}


bool NonAdaptiveBloomFilter::lookup(string *elementP) {
    for (auto h: kHashFuncs) if (!(filter[h.calc(elementP, size)])) return false;
    return true;
}

bool NonAdaptiveBloomFilter::lookup(string *elementP, size_t *hashIndex) {
    for (int i = 0; i < kHashFuncs.size() ; ++i)
    {
        size_t index = kHashFuncs[i].calc(elementP, size);
        if (!(filter[index])) return false;
        hashIndex[i] = index;
    }
    return true;
}

size_t NonAdaptiveBloomFilter::getFilterOnBits() const {
    size_t sum = 0;
    for (int i = 0; i < this->size; ++i) if (this->filter[i]) ++sum;
    return sum;
}



ostream &operator<<(ostream &os, const NonAdaptiveBloomFilter &bfr) {
    const size_t size = bfr.size;
    const size_t k = bfr.kHashFuncs.size();
    os << "b_filter size: " << size;
    os << "\tk is: " << k;
    printKHashFunctions(os, bfr);
    os << "Number of on bits in filter: " << bfr.getFilterOnBits() << "\tRatio is: "
       << ((double) bfr.getFilterOnBits()) / size << endl;
    os << endl;
    return os;
}

ostream &printKHashFunctions(ostream &os, const NonAdaptiveBloomFilter &bfr) {
    if (bfr.kHashFuncs.empty()) {
        os << "bfr.kHashFuncs is empty." << endl;
        return os;
    }
    Hash h0p = bfr.kHashFuncs[0];
    os << "[" << h0p.getMultiConst();
    for (auto h : bfr.kHashFuncs) os << ", " << h.getMultiConst();
    os << "]" << endl;
    return os;
}

