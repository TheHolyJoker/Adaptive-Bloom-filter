//
// Created by tomer on 9/16/18.
//

#ifndef ADAPTIVEBF_HASH_H
#define ADAPTIVEBF_HASH_H

#include "MurmurHash3.h"
#include <iostream>
#include <cstring>
#include <random>
#include <assert.h>


#define DEFAULT_SEED 2
#define SECOND_SEED 42
#define HASH_BLOCK_TYPE uint16_t

using namespace std;

class Hash {

    size_t size;
    vector<size_t> multiConst;

public:
//    Hash() { multiConst = 0; }

    explicit Hash(size_t size);

    Hash(size_t size, size_t maxRemainderLength);

    /**
     * Calculate the fingerprint on an element (elementP) using double hashing.
     * @param elementP
     * @param size
     * @return
     */
    uint32_t calc(const char *elementP) const;

    uint32_t calc(string *elementP) const;

    size_t calc(string *elementP, HASH_BLOCK_TYPE *dataArr, size_t length) const;

//    size_t getMultiConst() const;

};

/**
 *
 * @param a
 * @param b
 * @return natural random number in the range [a,b]
 */
size_t rangedUniformDistribution(size_t a, size_t b);


#endif //ADAPTIVEBF_HASH_H
