//
// Created by tomer on 10/25/18.
//

#ifndef INHERITANCE_VLQF_H
#define INHERITANCE_VLQF_H


#include "../PackedArray.h"

class VLQF : public PackedArray {

    size_t maxRemainderLength;
public:
    VLQF(size_t q, size_t r, size_t mbSize, size_t maxRemainderLength);

    virtual bool add(BLOCK_TYPE *dataArr, size_t length, size_t qIndex);

    virtual int lookup(BLOCK_TYPE *dataArr, size_t length, size_t qIndex, size_t *fpIndex);

    bool add(string *s, size_t length);

    int lookup(string *s, size_t length);

    void set_cell(size_t qIndex, BLOCK_TYPE tempMB, BLOCK_TYPE *dataArr, size_t length);

    void get_data(size_t qIndex, BLOCK_TYPE *resArr, size_t length);

    void getNextMultiEmpties(size_t qIndex, size_t steps, size_t *emptyIndex, size_t *runCounter);

    virtual size_t multiRunShift(size_t emptyQIndex, size_t qIndex, size_t steps);

    void multiPush(size_t qIndex, size_t steps, bool toPushAgain = false);

    bool isPartOfRemainder(size_t qIndex);

    size_t getRemainderLength(size_t qIndex);

    bool areConsecutiveEmpties(size_t qIndex, size_t steps);

    size_t enoughConsecutiveEmpties(size_t qIndex, size_t steps);

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
     */
    int compare(size_t qIndex, size_t *tempLength, BLOCK_TYPE *dataArr, size_t length);

    void convert(string *s, size_t *qIndex, BLOCK_TYPE *dataArr, size_t length = 0);

};


#endif //INHERITANCE_VLQF_H
