//
// Created by tomer on 9/16/18.
//

#ifndef ADAPTIVEBF_HASH_H
#define ADAPTIVEBF_HASH_H

#include "GlobalFunction.h"
#include "MurmurHash3.h"

using namespace std;

class Hash {
    size_t multiConst;

public:
    Hash() {this->multiConst = 0;}
    explicit Hash(size_t size);

    size_t calc(const char *elementP, size_t size) const;
    size_t calc(string *elementP, size_t size) const;

    size_t  getMultiConst() const;
//    unsigned int calc(string *elementP, size_t size);
//    unsigned int calc(string *elementP, size_t size) const;
//    unsigned int calc(char const *elementP, size_t size);

//    Hash[unsigned int k] {this->multiConst = 0;}
//    explicit Hash(unsigned int size, unsigned int k);
//    void hashArray(Hash *kHashFunc, unsigned int size, unsigned int k);
//    unsigned int multipliHash(uint32_t index);

} ;


//ostream& operator<<(ostream &os, Hash &h);


#endif //ADAPTIVEBF_HASH_H
