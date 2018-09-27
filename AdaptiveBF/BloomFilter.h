//
// Created by tomer on 9/15/18.
//

#ifndef ADAPTIVEBF_BLOOMFILTER_H
#define ADAPTIVEBF_BLOOMFILTER_H

#include "Hash.h"

using namespace std;


class BloomFilter {
public:
    bool *filter, *stale;
    vector<Hash > kHashFuncs;
    size_t size;

    explicit BloomFilter(size_t n, double eps);
    explicit BloomFilter(size_t m, size_t k, bool secondConst);
    explicit BloomFilter(BloomFilter *bfp);

    ~BloomFilter();
    void add(size_t *hashIndex);

    void add(string *elementP, size_t *hashIndex);

    size_t getK() const;
    size_t getSize() const;
    size_t getFilterOnBits() const;
    size_t getStaleOnBits() const;

    size_t getBloomFilterSize(size_t n, double eps);

    /**
     *
    * @param s The string we are hashing
     * @param hashIndex To which indexes s was hashed to.
     * @return :
     *  1 - all the stale bits are off and the filter bits are on.
     *  0 - all the stale bits are off and at least on bit in the filter is off.
     * -1 - at least on bit in the stale is on.
     */
    int getElementStatus(string *cp, size_t *hashIndex);


    //    void add(string *elementP, int *hashIndex);
//    void add(string *elementP);
//    void add(string elementP);
//    bool lookup(char const *elementP, int *hashIndex);
//    bool lookup(string *elementP, int *hashIndex);
//    bool lookup(string *elementP);

//    bool getIndex(string *s, int *hashIndex);
//    int getElementStatus(string *s, int *hashIndex);


};

void getParam(size_t n, double eps);

void getParam(size_t n, double eps, bool minimal);


ostream &operator<<(ostream &os, const BloomFilter &bfr);
ostream &printKHashFunctions(ostream &os, const BloomFilter &bfr);

#endif //ADAPTIVEBF_BLOOMFILTER_H
