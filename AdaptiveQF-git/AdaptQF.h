//
// Created by tomer on 10/22/18.
//

#ifndef INHERITANCE_ADAPTQF_H
#define INHERITANCE_ADAPTQF_H

#define AMB 4
//#define AMB_BIT(n) (1ULL << (AMB - (n)))

#include "PackedArray.h"

class AdaptQF : public PackedArray {
//    AdaptQF() : PackedArray(0, 0, 0, nullptr) {}

    size_t MB;
public:
    AdaptQF(size_t q, size_t r) : MB(AMB), PackedArray(q, r, AMB) {}

    bool add(BLOCK_TYPE data, size_t qIndex) override;

//    bool add(BLOCK_TYPE *dataArr, size_t length, size_t qIndex) override;

    int lookup(BLOCK_TYPE  data, size_t qIndex, size_t *fpIndex) override;

protected:
    size_t runShift(size_t emptyQIndex, size_t qIndex) override;

    bool runAdd(BLOCK_TYPE data, size_t runIndex);

//    size_t multiRunShift(size_t emptyQIndex, size_t qIndex, size_t steps) override;


};


#endif //INHERITANCE_ADAPTQF_H
