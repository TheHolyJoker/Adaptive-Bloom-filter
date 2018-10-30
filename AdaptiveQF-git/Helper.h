//
// Created by tomer on 10/22/18.
//

#ifndef INHERITANCE_HELPER_H
#define INHERITANCE_HELPER_H

//#include "Filter.h"
#include "RegularQF.h"
#include "AdaptQF.h"
#include "Hash/Hash.h"
#include <map>

typedef tuple<size_t, uint64_t> tup;

class Helper {
    vector<PackedArray *> fVec;
    size_t depth;
    map<tup, string> memberMap;

public:
    Helper(size_t q, size_t r);

    Helper(size_t q, size_t r, bool isAdaptive);

    ~Helper();

    void add(string *s, size_t level = 0);

//    void add(string *s, size_t level, size_t vLength);

    int lookup(string *s);

//    int lookup(string *s, size_t vLength);


    void statusCorrectness();

    ostream &statisticsPrint(ostream &os = cout);

private:
    void singleAdd(string *s);

//    void singleAdd(string *s, size_t vLength);

    int singleLookup(string *s);

//    int singleLookup(string *s, size_t vLength);

    void adapt(size_t qIndex, BLOCK_TYPE data, size_t fpIndex, size_t level);

};

size_t calcDepthByQ(size_t q, size_t r);

void getArraysSizes(size_t *qArr, size_t *rArr, size_t length);

//void arrayPrinter(size_t *a, size_t length);

#endif //INHERITANCE_HELPER_H
