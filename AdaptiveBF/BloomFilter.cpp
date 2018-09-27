//
// Created by tomer on 9/15/18.
//

#include "BloomFilter.h"




BloomFilter::BloomFilter(size_t n, double eps) {
    size_t m = calcM(n, eps);
    assert(m > 1);
    size_t k = calcK(n, m);
    if (k < 1) k = 1;
    this->size = m;
    this->filter = new bool[m]();
    this->stale = new bool[m]();
    kHashFuncs.resize(k);
    for (int i = 0; i < k; ++i) this->kHashFuncs[i] = Hash(size);
}

BloomFilter::BloomFilter(BloomFilter *bfp) {
    size_t mySize = bfp->getSize();
    size_t myK = bfp->getK();
    this->size = mySize;
    this->filter = new bool[mySize]();
    this->stale = new bool[mySize]();
    kHashFuncs.resize(myK);
    for (int i = 0; i < myK; ++i) this->kHashFuncs[i] = Hash(mySize);
}



BloomFilter::BloomFilter(size_t m, size_t k, bool secondConst) {
    this->size = m;
    this->filter = new bool[m]();
    this->stale = new bool[m]();
    kHashFuncs.resize(k);
    for (int i = 0; i < k; ++i) this->kHashFuncs[i] =  Hash(size);
}


BloomFilter::~BloomFilter() {
    delete[] filter;
    delete[] stale;
}


int BloomFilter::getElementStatus(string *cp, size_t *hashIndex) {
    bool areAllBitInFilterOn = true;
    for (int i = 0; i < this->kHashFuncs.size(); ++i)
    {
        hashIndex[i] = this->kHashFuncs[i].calc(cp, size);
        if (this->stale[hashIndex[i]]) return -1;
        areAllBitInFilterOn &= filter[hashIndex[i]];
    }
    return (int) areAllBitInFilterOn;
}

void BloomFilter::add(size_t *hashIndex) {
    for (int i = 0; i < this->kHashFuncs.size(); ++i) this->filter[hashIndex[i]] = true;
}

void BloomFilter::add(string *elementP, size_t *hashIndex) {
    size_t i = 0;
    for (auto h : this->kHashFuncs) {
        hashIndex[i] = h.calc(elementP, size);
        this->filter[hashIndex[i]] = true;
        ++i;
    }
}




size_t BloomFilter::getFilterOnBits() const {
    size_t sum = 0;
    for (int i = 0; i < this->size; ++i) if (this->filter[i]) ++sum;
    return sum;
}

size_t BloomFilter::getStaleOnBits() const {
    size_t sum = 0;
    for (int i = 0; i < this->size; ++i) if (this->stale[i]) ++sum;
    return sum;
}

size_t BloomFilter::getBloomFilterSize(size_t n, double eps) {
    return sizeof(BloomFilter(n, eps));
}


size_t BloomFilter::getSize() const {
    return this->size;
}

size_t BloomFilter::getK() const {
    this->kHashFuncs.size();
}



void getParam(size_t n, double eps) {
    cout << "Number of element is:" << n << endl;
    cout << "Error rate(eps):" << eps << endl;
    size_t m = calcM(n, eps);
    size_t k = calcK(n, m);
    cout << "Bloom filter size is(rounded):" << m << endl;
    cout << "Number of hash function(k) is:" << k << endl;
}

void getParam(size_t n, double eps, bool minimal) {
    if (minimal) {
        size_t m = calcM(n, eps);
        size_t k = calcK(n, m);
        cout << n << " ," << eps << " ," << m << ", " << k << endl;
    } else getParam(n, eps);
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


/*BloomFilter::~BloomFilter() {
    BloomFilter *tempBFp = this, *tempNext = this->nextBloomFilter;
    while(tempBFp != nullptr)
    {
        delete tempBFp->filter;
        delete tempBFp->stale;
        free()
        tempBFp = tempNext;
        tempNext = tempNext->nextBloomFilter;
    }

}*/

//void BloomFilter::add(char *elementP) {
//    for (int i = 0; i < this->kHashFuncs.size(); ++i)
//    {
//        size_t index;
//        MurmurHash3_x86_32(elementP, (int) strlen(elementP), 1, &index );
//        this->filter[index] = true;
//    }
//}


//
//int BloomFilter::getElementStatus(string *s, int *hashIndex) {
//    char const *cp = s->c_str();
//    return getElementStatus(cp, hashIndex);
//    /*
////    size_t i = 0;
////    for (auto h : this->kHashFuncs) {
////        hashIndex[i] = h->calc(s, size);
////        ++i;
////    }
//////        hashIndex[i] = h->calc(s, size);
////
////    size_t filterSize = sizeof(filter);
////    bool areAllBitInFilterOn = true;
////    for (int j = 0; j < this->kHashFuncs.size(); ++j) {
////        int index = hashIndex[j];
////        if (this->stale[index]) return -1;
////        areAllBitInFilterOn &= filter[index];
////    }
////    return (areAllBitInFilterOn) ? 1 : 0;*/
//}



//size_t calcM(size_t n, float eps) {
//    double a = (n * log(eps) / (M_LN2 * M_LN2)) * (-1);
//    return (size_t) ++a;
//}
//
//size_t calcK(size_t n, size_t m) {
//    return (size_t) (M_LN2 * ((float) m) / n);
//}


//
//void BloomFilter::add(string *elementP, int *hashIndex) {
//    char const *cp = elementP->c_str();
//    this->add(cp, hashIndex);
//}

//
//void BloomFilter::add(string *elementP) {
//    int hashIndex[kHashFuncs.size()];
//    int state = getElementStatus(elementP, hashIndex);
//    switch (state) {
//        case 1:
//            break;
//        case 0:
//            add(hashIndex);
//            break;
//        case -1:
//            cout << "In BloomFilter::add(string *elementP), trying to add when stale." << endl;
//            break;
//        default:
//            cout << MISTAKE << "In BloomFilter::add(string *elementP) default case in switch." << endl;
//    }
//}
//
//void BloomFilter::add(string elementP) {
//    for (Hash *h : this->kHashFuncs) {
//        this->filter[h->calc(&elementP, size)] = true;
//    }
//}

/*bool BloomFilter::getElementStatus(char *elementP) {
//    bool inBloom = true;
    for (int i = 0; i < this->kHashFuncs; ++i)
    {
        size_t index;
        MurmurHash3_x86_32(elementP, (int) strlen(elementP), this->seedsList[i], &index );
        if(!this->filter[index]) return false;
    }
    return true;
}*/

//bool BloomFilter::lookup(string *elementP, int *hashIndex) {
//    char const *cp = elementP->c_str();
//    return this->lookup(cp, hashIndex);
//}
//
//
//bool BloomFilter::lookup(string *elementP) {
//    int hashIndex[kHashFuncs.size()];
//    int state = getElementStatus(elementP, hashIndex);
//    switch (state) {
//        case 1:
//            return true;
//        case 0:
//            return false;
//        case -1:
//            cout << "In BloomFilter::getElementStatus(string *elementP), checking for member when stale." << endl;
//            break;
//        default:
//            cout << MISTAKE << "In BloomFilter::getElementStatus(string *elementP) default case in switch." << endl;
//    }
//    return true;
//}
//
//bool BloomFilter::lookup(char const *elementP, int *hashIndex) {
//    size_t i = 0;
//    for (auto &kHashFunc : this->kHashFuncs) {
//        hashIndex[i] = kHashFunc->calc(elementP, size);
//        //Works I checked. The i val increases after the ENTIRE line.
//        if (!this->filter[hashIndex[i++]]) return false;
//    }
//    return true;
//}

//}

//
//bool BloomFilter::getIndex(string *s, int *hashIndex) {
//    char const *cp = s->c_str();
//    size_t i = 0;
//    for (auto &kHashFunc : this->kHashFuncs) {
//        size_t index = kHashFunc->calc(cp, size);
//        if (!this->filter[index]) return false;
//        hashIndex[i] = index;
//        ++i;
//    }
//    return true;
//}



//void BloomFilter::printFilter(size_t start, size_t end) {
//    bool **filterArray = &filter + start;
//    size_t size = end - start;
//    printArray<>(*filterArray, size);
//}
