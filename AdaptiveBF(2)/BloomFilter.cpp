//
// Created by tomer on 9/15/18.
//

#include "BloomFilter.h"


BloomFilter::BloomFilter(size_t n, double eps) {
    size_t m = size_t(calcM(n, eps) + 1);
    size_t k = calcK(n, m);
    assert(m > 1 && k > 1);
    this->size = m;
    this->filterStaleVec.resize(m << 1, false);
    kHashFuncs.resize(k);
    for (int i = 0; i < k; ++i) this->kHashFuncs[i] = Hash(size);
}

BloomFilter::BloomFilter(BloomFilter *bfp) {
    this->size = bfp->getSize();
    this->filterStaleVec.resize(this->size << 1, false);
    kHashFuncs.resize(bfp->getK());
    for (int i = 0; i < bfp->getK(); ++i) this->kHashFuncs[i] = Hash(this->size);
}


BloomFilter::BloomFilter(size_t m, size_t k, bool secondConst) {
    assert(m > 2);
    this->size = m;
    this->filterStaleVec.resize(m << 1, false);
    kHashFuncs.resize(k);
    for (int i = 0; i < k; ++i) this->kHashFuncs[i] = Hash(size);
}


int BloomFilter::lookup(string *cp, size_t *hashIndex) {
    bool areAllBitInFilterOn = true;
    for (int i = 0; i < this->kHashFuncs.size(); ++i) {
        hashIndex[i] = this->kHashFuncs[i].calc(cp, size);
        size_t shiftedIndex = hashIndex[i] << 1;
        if (this->filterStaleVec[shiftedIndex ^ 1]) return -1;
        areAllBitInFilterOn &= filterStaleVec[shiftedIndex];
    }
    return (int) areAllBitInFilterOn;
}


int BloomFilter::lookupAdvance(string *cp, size_t *hashIndex) {
    int i = 0;
    for (; i < this->kHashFuncs.size(); ++i) {
        size_t shiftedIndex = kHashFuncs[i].calc(cp, size) << 1;
        if (filterStaleVec[shiftedIndex ^ 1]) return -1;
        if (!filterStaleVec[shiftedIndex]) break;
    }
    if (i != this->kHashFuncs.size()) return 0;
    for (int j = 0; j < this->kHashFuncs.size(); ++j) hashIndex[j] = kHashFuncs[i].calc(cp, size);
    return 1;
}
//
//size_t *BloomFilter::getHashIndex(string *cp){
//    bool areAllBitInFilterOn = true;
//    for (int i = 0; i < this->kHashFuncs.size(); ++i) {
//        size_t tempIndex = this->kHashFuncs[i].calc(cp, size);
//        size_t shiftedIndex = tempIndex << 1;
//        if ( filterStaleVec[shiftedIndex ^ 1]) return -1;
//        hashIndex[i] = this->kHashFuncs[i].calc(cp, size);
//        size_t shiftedIndex = hashIndex[i] << 1;
//        areAllBitInFilterOn &= filterStaleVec[shiftedIndex];
//    }
//    return (int) areAllBitInFilterOn;
//}



void BloomFilter::add(size_t *hashIndex) {
    for (int i = 0; i < this->kHashFuncs.size(); ++i) this->filterStaleVec[((hashIndex[i]) << 1)] = true;
}

void BloomFilter::add(string *elementP, size_t *hashIndex) {
    size_t i = 0;
    for (auto h : this->kHashFuncs) {
        hashIndex[i] = h.calc(elementP, size);
        size_t shiftedIndex = hashIndex[i] << 1;
        this->filterStaleVec[shiftedIndex] = true;
        ++i;
    }
}


size_t BloomFilter::getFilterOnBits() const {
    size_t sum = 0;
    for (int i = 0; i < this->size; ++i) if (this->filterStaleVec[(i << 1)]) ++sum;
    return sum;
}

size_t BloomFilter::getStaleOnBits() const {
    size_t sum = 0;
    for (int i = 0; i < this->size; ++i) if (this->filterStaleVec[1 ^ (i << 1)]) ++sum;
    return sum;
}


size_t BloomFilter::getSize() const {
    return this->size;
}

size_t BloomFilter::getK() const {
    this->kHashFuncs.size();
}


ostream &operator<<(ostream &os, const BloomFilter &bfr) {
    const size_t size = bfr.getSize();
    const size_t k = bfr.getK();
    os << "b_filter size: " << size;
    os << "\tk is: " << k;
    printKHashFunctions(os, bfr);
    os << "Number of on bits in filter: " << bfr.getFilterOnBits() << "\tRatio is: "
       << ((double) bfr.getFilterOnBits()) / size << endl;
    os << "Number of on bits in stale: " << bfr.getStaleOnBits() << "\tRatio is: "
       << ((double) bfr.getStaleOnBits()) / size << endl;
    /*for (auto h : bfr.kHashFuncs) {
        const size_t a = h->getMultiConst();
//        if(a >= bfr.size) os << "$$$\n$$$\n$$$\nnext hash function multiConst is too big:";
        os << a << "|";
    }*/
    os << endl;
    return os;
}

ostream &printKHashFunctions(ostream &os, const BloomFilter &bfr) {
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
