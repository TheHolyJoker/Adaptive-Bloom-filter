//
// Created by tomer on 9/24/18.
//

#include "NonAdaptiveHelper.h"

//
//NonAdaptiveHelper::~NonAdaptiveHelper() {
//    for (int i = 0; i < setsVec.size(); ++i) delete setsVec[i];
//}

void NonAdaptiveHelper::add(string *s) {
    size_t hashIndex[nBFVec[0].kHashFuncs.size()];
    nBFVec[0].add(s, hashIndex);
    for (int i = 0; i < nBFVec[0].kHashFuncs.size(); ++i) setsVec[hashIndex[i]].insert(*s);

//        if (setsVec[hashIndex[i]] == nullptr) setsVec[hashIndex[i]] = new set<string>;
//    }
}

int NonAdaptiveHelper::lookup(string *s) {
    size_t hashIndex[nBFVec[0].kHashFuncs.size()];
    if (nBFVec[0].lookup(s, hashIndex)) {
        auto iter = setsVec[hashIndex[0]].find(*s);
        return (iter == setsVec[hashIndex[0]].end()) ? 1 : 2;
    }
    return 0;
}

int NonAdaptiveHelper::naiveLookup(string *s) {
    for (size_t i = 0; i < 1; ++i) {
        NonAdaptiveBloomFilter *bfp = &nBFVec[0];
        size_t k = nBFVec[0].kHashFuncs.size();
        size_t hashIndex[k];
        int status = nBFVec[0].lookup(s, hashIndex);
        if (!status) return 0;
        if (status == 1) return (setsVec[hashIndex[0]].find(*s) == setsVec[hashIndex[0]].end()) ? 1 : 2;
    }
    assert(false);
}

string NonAdaptiveHelper::getName() {
    return "NonAdapt";
}
//
//NonAdaptiveBloomFilter *NonAdaptiveHelper::getNABFPointer() const {
//    auto nBFp = &nBFVec[0];
//    return nBFp;
//}
NonAdaptiveBloomFilter NonAdaptiveHelper::getNABF() const {
    return nBFVec[0];
}



ostream &operator<<(ostream &os, const NonAdaptiveHelper &hp) {
    const NonAdaptiveBloomFilter &nbfp = hp.getNABF();
    os << 0 << " : " << endl << nbfp;
    return os;
}