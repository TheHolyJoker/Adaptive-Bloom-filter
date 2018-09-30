//
// Created by tomer on 9/16/18.
//

#ifndef ADAPTIVEBF_HASH_H
#define ADAPTIVEBF_HASH_H

#include "GreyBoxFunction.h"
#include "MurmurHash3.h"

using namespace std;

class Hash {

    size_t multiConst;

public:
    Hash() {this->multiConst = 0;}
    explicit Hash(size_t size);

    /**
     * Calculate the fingerprint on an element (elementP) using double hashing.
     * @param elementP
     * @param size
     * @return
     */
    size_t calc(const char *elementP, size_t size) const;

    size_t calc(string *elementP, size_t size) const;

    size_t  getMultiConst() const;

} ;




#endif //ADAPTIVEBF_HASH_H
