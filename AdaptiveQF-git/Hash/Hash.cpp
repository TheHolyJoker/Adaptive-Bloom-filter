//
// Created by tomer on 9/16/18.
//

#include "Hash.h"

Hash::Hash(size_t size) : size(size), multiConst(1,rangedUniformDistribution(1, 1000)) {};

Hash::Hash(size_t size, size_t maxRemainderLength)  : size(size){
    multiConst.resize(maxRemainderLength);
    for (int i = 0; i < maxRemainderLength; ++i) {
        multiConst[i] = rangedUniformDistribution(1, 1000);
    }
}

uint32_t Hash::calc(const char *elementP) const {
    uint32_t a, b;
    MurmurHash3_x86_32(elementP, (int) (strlen(elementP)), DEFAULT_SEED, &a);
    MurmurHash3_x86_32(elementP, (int) (strlen(elementP)), SECOND_SEED, &b);
    return (a % size + this->multiConst[0] * (b % this->size)) % this->size;
}

uint32_t Hash::calc(string *elementP) const {
    char const *cp = elementP->c_str();
    return calc(cp);
}

size_t Hash::calc(string *elementP, HASH_BLOCK_TYPE *dataArr, size_t length) const {
    assert(length + 1 <= multiConst.size());
    char const *cp = elementP->c_str();
    uint32_t a, b;
    for (int i = 0; i < length; ++i) {
        MurmurHash3_x86_32(cp, (int) (strlen(cp)), DEFAULT_SEED, &a);
        MurmurHash3_x86_32(cp, (int) (strlen(cp)), SECOND_SEED, &b);
        dataArr[i] = (a % size + this->multiConst[(i+1)] * (b % this->size)) % this->size;
    }
    MurmurHash3_x86_32(cp, (int) (strlen(cp)), DEFAULT_SEED, &a);
    MurmurHash3_x86_32(cp, (int) (strlen(cp)), SECOND_SEED, &b);
    return (a % size + this->multiConst[0] * (b % this->size)) % this->size;
}

/*

size_t Hash::getMultiConst() const {
    return multiConst;
}
*/



size_t rangedUniformDistribution(size_t a, size_t b) {
    const int range_from = a;
    const int range_to = b;
    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution<int> distr(range_from, range_to);
    return (size_t) distr(generator);
}


