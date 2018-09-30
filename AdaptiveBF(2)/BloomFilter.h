//
// Created by tomer on 9/15/18.
//

#ifndef ADAPTIVEBF_BLOOMFILTER_H
#define ADAPTIVEBF_BLOOMFILTER_H

#include "Hash.h"

using namespace std;


class BloomFilter {
public:
    vector<bool> filterStaleVec;
    vector<Hash> kHashFuncs;
    size_t size;

    explicit BloomFilter(size_t n, double eps);

    explicit BloomFilter(size_t m, size_t k, bool secondConst);

    explicit BloomFilter(BloomFilter *bfp);


    /**
     * adding elementP to the Bloom filter, and inserting the indexes to whom it was mapped, into the
     * hashIndex array
     * @param elementP
     * @param hashIndex array if indexes to whom the hash functions of Bloom filter mapped the element.
     */
    void add(string *elementP, size_t *hashIndex);

    /**
     *
     * @param hashIndex array of indexes to whom some element was mapped to.
     */
    void add(size_t *hashIndex);


    /**
     *
     * @param s The string we are hashing
     * @param hashIndex To which indexes s was hashed to.
     * @return :
     *  1 - all stale bits are off and all filter bits are on.
     *  0 - all stale bits are off and at least one filter bit is off.
     * -1 - at least one stale bit is on.
     */
    int lookup(string *cp, size_t *hashIndex);

    int lookupAdvance(string *cp, size_t *hashIndex);

//    size_t * getHashIndex(string *cp);

    size_t getK() const;

    size_t getSize() const;

    size_t getFilterOnBits() const;

    size_t getStaleOnBits() const;


};

/**
 * Prints the BF
 * @param os
 * @param bfr
 * @return
 */
ostream &operator<<(ostream &os, const BloomFilter &bfr);

//Todo prints the first hash function twice.
/**
 * Print the BF's hash functions as in array.
 * @param os
 * @param bfr
 * @return
 */
ostream &printKHashFunctions(ostream &os, const BloomFilter &bfr);

#endif //ADAPTIVEBF_BLOOMFILTER_H
