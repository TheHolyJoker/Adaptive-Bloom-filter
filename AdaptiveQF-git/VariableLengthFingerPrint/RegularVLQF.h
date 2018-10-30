//
// Created by tomer on 10/25/18.
//

#ifndef INHERITANCE_REGULARVLQF_H
#define INHERITANCE_REGULARVLQF_H

#include "VLQF.h"

class RegularVLQF : public VLQF {

public:
    RegularVLQF(size_t q, size_t r, size_t mbSize, size_t maxRemainderLength);

    bool add(BLOCK_TYPE *dataArr, size_t length, size_t qIndex) override;

    int lookup(BLOCK_TYPE *dataArr, size_t length, size_t qIndex, size_t *fpIndex) override;

private:
    size_t multiRunShift(size_t emptyQIndex, size_t qIndex, size_t steps) override;

    bool runMultiAdd(BLOCK_TYPE *dataArr, size_t length, size_t runIndex);

};


#endif //INHERITANCE_REGULARVLQF_H
