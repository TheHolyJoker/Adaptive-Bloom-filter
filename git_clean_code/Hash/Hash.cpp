//
// Created by tomer on 9/16/18.
//

#include "Hash.h"

Hash::Hash() : size(0), multiConst(rangedUniformDistribution(1, 1000)) {};


Hash::Hash(size_t size) : size(size), multiConst(rangedUniformDistribution(1, 1000)) {};


uint32_t Hash::hash(const char *elementP) const {
    uint32_t a, b;
    MurmurHash3_x86_32(elementP, (int) (strlen(elementP)), DEFAULT_SEED, &a);
    MurmurHash3_x86_32(elementP, (int) (strlen(elementP)), SECOND_SEED, &b);
    return uint32_t(a + multiConst * b);
/*//    size_t mod = size;
//    uint64_t ans0 = a % mod;
//    uint64_t ans1 = a % this->size;
//    auto ans2 = multiConst * (b % this->size);

//    uint32_t temp = (a % size + this->multiConst * (b % this->size)) % this->size;
//    return uint32_t((a % size + this->multiConst * (b % this->size)) % this->size);*/
}

uint32_t Hash::hash(string *elementP) const {
    char const *cp = elementP->c_str();
    return hash(cp);
}

uint32_t Hash::dataHash(string *elementP) const {
    char const *cp = elementP->c_str();
    uint32_t a, b;
    MurmurHash3_x86_32(elementP, (int) (strlen(cp)), DEFAULT_SEED, &a);
    MurmurHash3_x86_32(elementP, (int) (strlen(cp)), SECOND_SEED, &b);
    return uint32_t(a % size + this->multiConst * (b % this->size));
}

/*
Hash::Hash(size_t size, size_t maxRemainderLength)  : size(size){
    multiConst.resize(maxRemainderLength + 1);
    for (int i = 0; i < maxRemainderLength; ++i) {
        multiConst[i] = rangedUniformDistribution(1, 1000);
    }
}*/




uint32_t Hash::calc(const char *elementP) const {
    uint32_t a, b;
    MurmurHash3_x86_32(elementP, (int) (strlen(elementP)), DEFAULT_SEED, &a);
    MurmurHash3_x86_32(elementP, (int) (strlen(elementP)), SECOND_SEED, &b);
    return (a % size + this->multiConst * (b % this->size)) % this->size;
}

uint32_t Hash::calc(string *elementP) const {
    char const *cp = elementP->c_str();
    return calc(cp);
}


size_t rangedUniformDistribution(size_t a, size_t b) {
    const int range_from = a;
    const int range_to = b;
    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution<int> distr(range_from, range_to);
    return (size_t) distr(generator);
}



/*

size_t Hash::calc(string *elementP, HASH_BLOCK_TYPE *dataArr, size_t length) const {
    assert(length < multiConst.size());
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

size_t Hash::calc(string *elementP, uint16_t *dataArr, size_t length) const {
    assert(length < multiConst.size());
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

size_t Hash::lengthHash(string *elementP, uint32_t *dataArr, size_t arraySize) const {
    assert(arraySize < multiConst.size());
    char const *cp = elementP->c_str();
    uint32_t a, b;
    for (int i = 0; i < arraySize; ++i) {
        MurmurHash3_x86_32(cp, (int) (strlen(cp)), DEFAULT_SEED, &a);
        MurmurHash3_x86_32(cp, (int) (strlen(cp)), SECOND_SEED, &b);
        dataArr[i] = uint32_t(a % size + this->multiConst[(i+1)] * (b % size));
    }
    MurmurHash3_x86_32(cp, (int) (strlen(cp)), DEFAULT_SEED, &a);
    MurmurHash3_x86_32(cp, (int) (strlen(cp)), SECOND_SEED, &b);
    return (a % size + this->multiConst[0] * (b % this->size)) % this->size;
}
*/
