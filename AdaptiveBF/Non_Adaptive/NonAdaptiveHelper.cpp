//
// Created by tomer on 9/24/18.
//

#include "NonAdaptiveHelper.h"


NonAdaptiveHelper::~NonAdaptiveHelper() {
    delete nbfp;
    for (int i = 0; i < setsVec.size(); ++i) delete setsVec[i];
}

void NonAdaptiveHelper::add(string *s) {
    size_t hashIndex[nbfp->kHashFuncs.size()];
    nbfp->add(s, hashIndex);
    for (int i = 0; i < nbfp->kHashFuncs.size(); ++i) {
        if (setsVec[hashIndex[i]] == nullptr) setsVec[hashIndex[i]] = new set<string>;
        setsVec[hashIndex[i]]->insert(*s);
    }
}

int NonAdaptiveHelper::lookup(string *s) {
    size_t hashIndex[nbfp->kHashFuncs.size()];
    if (nbfp->lookup(s, hashIndex)) {
        auto iter = setsVec[hashIndex[0]]->find(*s);
        return (iter == setsVec[hashIndex[0]]->end()) ? 1 : 2;
    }
    return 0;
}

int NonAdaptiveHelper::naiveLookup(string *s) {
    for (size_t i = 0; i < 1; ++i) {
        NonAdaptiveBloomFilter *bfp = nbfp;
        size_t k = nbfp->kHashFuncs.size();
        size_t hashIndex[k];
        int status = nbfp->lookup(s, hashIndex);
        if (!status) return 0;
        if (status == 1) return (setsVec[hashIndex[0]]->find(*s) == setsVec[hashIndex[0]]->end()) ? 1 : 2;
    }
    assert(false);
}

string NonAdaptiveHelper::getName() {
    return "NonAdapt";
}

NonAdaptiveBloomFilter *NonAdaptiveHelper::getNABFPointer() const {
    return nbfp;
}
NonAdaptiveBloomFilter NonAdaptiveHelper::getNABF() const {
    return *nbfp;
}



ostream &operator<<(ostream &os, const NonAdaptiveHelper &hp) {
    const NonAdaptiveBloomFilter &nbfp = hp.getNABF();
    os << 0 << " : " << endl << nbfp;
    return os;
}