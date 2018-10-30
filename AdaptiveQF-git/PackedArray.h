//
// Created by tomer on 10/22/18.
//

#ifndef INHERITANCE_PACKEDARRAY_H
#define INHERITANCE_PACKEDARRAY_H


#include <cstdint>
#include <cstddef>
#include <ostream>
#include <iostream>
#include <assert.h>
#include "Hash/Hash.h"
#include "globalFunction.h"

#define BLOCK_SIZE (16)
#define BLOCK_TYPE uint16_t

#define MOD_INVERSE(n) (BLOCK_SIZE - (n) - 1)
#define SL(p) (1ULL <<(p))
#define MASK(p)  ( (1ULL <<(p))  - 1ULL)
#define ON(a, b) (MASK(a) ^ MASK(b))
#define OFF(a, b) (~(MASK(a) ^ MASK(b)))
#define MB_BIT(n) (1ULL << (MB - (n)))


using namespace std;

class PackedArray {
protected:
    size_t size;
    size_t capacity;
    size_t dataSize;
    size_t MB;
    BLOCK_TYPE *A;
    Hash h;

public:
    PackedArray(size_t q, size_t r, size_t mbSize);

    PackedArray(size_t q, size_t r, size_t mbSize, size_t maxRemainderLength);

//    PackedArray(BLOCK_TYPE n, size_t dataSize, size_t mbSize, BLOCK_TYPE *A);

    ~PackedArray();

    virtual bool add(BLOCK_TYPE data, size_t qIndex);

    virtual bool add(BLOCK_TYPE *dataArr, size_t length, size_t qIndex);

    virtual int lookup(BLOCK_TYPE data, size_t qIndex, size_t *fpIndex);

//    virtual int lookup(BLOCK_TYPE *dataArr, size_t length, size_t qIndex, size_t *fpIndex);

    void setFP(size_t qIndex);

    bool add(string *s);

//    bool add(string *s, size_t length);

    int lookup(string *s);

//    int lookup(string *s, size_t length);

    int lookup(string *s, size_t *fpIndex);

    void convert(string *s, size_t *qIndex, BLOCK_TYPE *data);

//    void convert(string *s, size_t *qIndex, BLOCK_TYPE *dataArr, size_t length = 0);

    void statusCorrectness(ostream &os = cout);

    void emptyData(ostream &os = cout);

    void dataCounter(BLOCK_TYPE data, ostream &os = cout);

    void neighborhoodPrint(size_t qIndex, ostream &os = cout);

protected:

    BLOCK_TYPE get_cell(size_t qIndex);

    void set_cell(size_t qIndex, size_t value);

//    void set_cell(size_t qIndex, BLOCK_TYPE tempMB, BLOCK_TYPE *dataArr, size_t length);

    BLOCK_TYPE get_bits(size_t address, size_t length);

    void set_bits(size_t address, size_t bitsToWriteCounter, size_t value);

    void set_bit(size_t address, bool setOn);

    BLOCK_TYPE get_data(size_t qIndex);

//    void get_data(size_t qIndex, BLOCK_TYPE *resArr, size_t length);

    BLOCK_TYPE get_mb(size_t qIndex);

    size_t countElement(size_t qIndex);

    void set_data(size_t qIndex, size_t value);

    void set_mb(size_t qIndex, size_t value);

//    int lookupAdapt(uint64_t data, size_t qIndex, size_t *fpIndex);

public:
    BLOCK_TYPE *getA() const;

    size_t getSize() const;

    size_t getCapacity() const;

    size_t getDataSize() const;

    size_t getMBSize() const;

    friend ostream &operator<<(std::ostream &os, const PackedArray &pa);

    ostream &statisticsPrint(ostream &os);

    ostream &elementPrint(ostream &os = cout);

    ostream &elementPrintDec(ostream &os = cout);
//    ostream &elementPrintDec(size_t start, size_t end, ostream &os = cout);

    ostream &elementPrint(size_t start, size_t end, ostream &os = cout);

protected:

    void setHelp(size_t aIndex, size_t value, size_t borderStart, size_t borderEnd);

//    void getNextMultiEmpties(size_t qIndex, size_t steps, size_t *emptyIndex, size_t *runCounter);

    void getNextEmpty(size_t qIndex, size_t *emptyIndex, size_t *runCounter);

    size_t getRunStart(size_t qIndex);

    size_t getNextRunStart(size_t qIndex);

    size_t getClusterStart(size_t qIndex, size_t *occupiedCounter);

    size_t getCompatibleRun(size_t qIndex);

    virtual size_t runShift(size_t emptyQIndex, size_t qIndex);

//    virtual size_t multiRunShift(size_t emptyQIndex, size_t qIndex, size_t steps);

    void push(size_t qIndex, bool toPushAgain = false);

//    void multiPush(size_t qIndex, size_t steps, bool toPushAgain = false);

    bool isEmpty(size_t qIndex);

    bool isOccupied(size_t qIndex);

    bool isContinuation(size_t qIndex);

    bool isShifted(size_t qIndex);

    bool isFP(size_t qIndex);

//    bool isPartOfRemainder(size_t qIndex);

    bool isRunStart(size_t qIndex);

    bool isClusterStart(size_t qIndex);

    void setOccupied(size_t qIndex, bool setOn = true);

    void setContinuation(size_t qIndex, bool setOn = true);

    void setShifted(size_t qIndex, bool setOn = true);

//    size_t getRemainderLength(size_t qIndex);

    void inc(size_t *index);

    size_t inc(size_t index);

    void dec(size_t *index);

    size_t dec(size_t index);

    ostream &runStatistic(ostream &os = cout);

    ostream &clusterStatistic(ostream &os = cout);

    size_t fpCounter();

    size_t calcRunLength(size_t runIndex);

    size_t calcClusterLength(size_t clusterStart);

//    bool areConsecutiveEmpties(size_t qIndex, size_t steps);
};

ostream &operator<<(std::ostream &os, const PackedArray &pa);

string listToStr(const PackedArray &pa);

string decToBin(BLOCK_TYPE n, size_t length);

ostream &splitStr(ostream &os, string *s, size_t dataSize, size_t elNum, size_t mbSize, size_t startIndex);

ostream &splitStrDec(ostream &os, string *s, size_t dataSize, size_t elNum, size_t mbSize, size_t startIndex);

int compareArray(BLOCK_TYPE *A1, BLOCK_TYPE *A2, size_t length);


#endif //INHERITANCE_PACKEDARRAY_H
