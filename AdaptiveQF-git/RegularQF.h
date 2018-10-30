//
// Created by tomer on 10/22/18.
//

#ifndef INHERITANCE_REGULARQF_H
#define INHERITANCE_REGULARQF_H


#include "PackedArray.h"
#include "Hash/Hash.h"

#define RMB 3

class RegularQF : public PackedArray {
//    size_t q, r;
//    Hash h;
public:
    RegularQF(size_t q, size_t r, size_t mbSize = RMB);

//    RegularQF(BLOCK_TYPE n, size_t dataSize, BLOCK_TYPE *A);

    bool add(BLOCK_TYPE data, size_t qIndex) override;

//    bool add(BLOCK_TYPE *dataArr, size_t length, size_t qIndex) override;

    int lookup(BLOCK_TYPE data, size_t qIndex, size_t *fpIndex) override;

//    int lookup(BLOCK_TYPE *dataArr, size_t length, size_t qIndex, size_t *fpIndex) override;

protected:
    size_t runShift(size_t emptyQIndex, size_t qIndex) override;

    bool runAdd(uint64_t data, size_t runIndex);

//    size_t multiRunShift(size_t emptyQIndex, size_t qIndex, size_t steps) override;

//    bool runMultiAdd(BLOCK_TYPE *dataArr, size_t length, size_t runIndex);
/*

    */
/**
     * Is the element in qIndex smaller.
     * @param qIndex
     * @param tempLength
     * @param dataArr
     * @param length
     * @return
     *//*

    bool isSmaller(size_t qIndex, size_t *tempLength, BLOCK_TYPE *dataArr, size_t length);

    */
/**
     *
     * @param qIndex
     * @param tempLength
     * @param dataArr
     * @param length
     * @return
     * -1 if the element in qIndex is smaller,
     *  0 if equal,
     *  1 if the element in qIndex is bigger.
     *//*

    int compare(size_t qIndex, size_t *tempLength, BLOCK_TYPE *dataArr, size_t length);
*/

};


#endif //INHERITANCE_REGULARQF_H
