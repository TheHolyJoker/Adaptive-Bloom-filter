//
// Created by tomer on 10/25/18.
//

#ifndef INHERITANCE_VLHELPER_H
#define INHERITANCE_VLHELPER_H

#include <ostream>
#include "../Helper.h"
#include "RegularVLQF.h"

typedef tuple<size_t, vector<BLOCK_TYPE>> VLkey;


class VLHelper {
    vector<VLQF *> fVec;
    size_t depth;
    map<VLkey, string> memberMap;

public:
    VLHelper(size_t q, size_t r, size_t maxRemainderLength);

    void add(string *s, size_t level, size_t vLength);

    void testAdd(BLOCK_TYPE *dataArr, size_t length, size_t qIndex);

    bool testLookup(BLOCK_TYPE *dataArr, size_t length, size_t qIndex);

    int lookup(string *s, size_t vLength);

    ostream &statisticsPrint(ostream &os = cout);

    friend ostream &operator<<(ostream &os, const VLHelper &helper);

private:

    int singleLookup(string *s, size_t vLength);

    void singleAdd(string *s, size_t vLength);

//    int singleLookup(string *s);

//    void singleAdd(string *s);

//    void adapt(size_t qIndex, uint64_t data, size_t fpIndex, size_t level);

};

//size_t calcDepthByQ(size_t q, size_t r);

//void getArraysSizes(size_t *qArr, size_t *rArr, size_t length);




#endif //INHERITANCE_VLHELPER_H
