//
// Created by tomer on 11/7/18.
//

#ifndef INHERITANCE_FILTER_H
#define INHERITANCE_FILTER_H

#include "../Hash/Hash.h"
#include "BasicFilter.h"

#include <tuple>


typedef tuple<size_t, vector<BLOCK_TYPE>> KEY_TYPE;

class Filter {
    BasicFilter bf;
    size_t q, r;
    Hash indexHash;
    vector<Hash> hashVec;

public:
    Filter(size_t q, size_t r, size_t MBSize);

    KEY_TYPE add(string *s);

    int lookup(string *s, size_t *fpIndex);

    KEY_TYPE strToKey(string *s);

    void setFP(size_t qIndex);

private:
    void strToData(string *s, size_t *qIndex, BLOCK_TYPE * dataArray);

};


#endif //INHERITANCE_FILTER_H
