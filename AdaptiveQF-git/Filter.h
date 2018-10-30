/*
//
// Created by tomer on 10/22/18.
//

#ifndef INHERITANCE_FILTER_H
#define INHERITANCE_FILTER_H


//#include "PackedArray.h"
#include "RegularQF.h"
#include "AdaptQF.h"
#include "Hash/Hash.h"

class Filter {

    PackedArray A;
    size_t q, r;
    Hash h;

public:
    Filter(size_t q, size_t r);

    Filter(size_t q, size_t r, bool isAdaptive);

    Filter(const PackedArray &A);

    bool add(string *s);

    int lookup(string *s);

    int lookup(string *s, size_t *fpIndex);

    void setFP(size_t fpIndex);

    void convert(string *s, size_t *qIndex, BLOCK_TYPE *data);

protected:

};


#endif //INHERITANCE_FILTER_H
*/
