//
// Created by tomer on 10/25/18.
//

#include "VLQF.h"

VLQF::VLQF(size_t q, size_t r, size_t mbSize, size_t maxRemainderLength) : maxRemainderLength(maxRemainderLength),
                                                                           PackedArray(q, r, mbSize,
                                                                                       maxRemainderLength) {}

bool VLQF::add(BLOCK_TYPE *dataArr, size_t length, size_t qIndex) {}

int VLQF::lookup(BLOCK_TYPE *dataArr, size_t length, size_t qIndex, size_t *fpIndex) {}

bool VLQF::add(string *s, size_t length) {
    size_t qIndex;
    BLOCK_TYPE dataArr[length];
    convert(s, &qIndex, dataArr, length);
    cout << "qIndex is:" << qIndex << "\t";
    arrayPrinter(dataArr, length);
    return add(dataArr, length, qIndex);
}

int VLQF::lookup(string *s, size_t length) {
    size_t qIndex;
    BLOCK_TYPE dataArr[length];
    convert(s, &qIndex, dataArr, length);
    cout << "qIndex is:" << qIndex << "\t";
    arrayPrinter(dataArr, length);
    return lookup(dataArr, length, qIndex, nullptr);
}

void VLQF::set_cell(size_t qIndex, BLOCK_TYPE tempMB, BLOCK_TYPE *dataArr, size_t length) {
//    BLOCK_TYPE val = (dataArr[0] << MB) | tempMB;
    BLOCK_TYPE val;// = (dataArr[0] << MB) | tempMB;
//    cout << "When add in set_cell: " << "\t";
//    arrayPrinter(dataArr, length);
//    cout << "Vals send to PA::set_cell: ";
    for (int i = 0; i < length; ++i) {
        val = (dataArr[i] << MB) | tempMB;
//        cout << val << ", ";
        PackedArray::set_cell(qIndex, val);
        inc(&qIndex);
        tempMB = MB_BIT(2); // Set is_Continuation on.
        if (isOccupied(qIndex))
            tempMB |= MB_BIT(1);
    }
//    qIndex = (qIndex - length) % capacity;
//    BLOCK_TYPE tempArr[length];
//    cout << "in set_cell, get_data result: " << "\t";
//    get_data(qIndex, tempArr, length);
    /*
    set_cell(qIndex, tempMB);
    inc(&qIndex);
//    BLOCK_TYPE tempMB;
    for (int i = 1; i < length; ++i) {
        tempMB = MB_BIT(2); // Set is_Continuation on.
        if (isOccupied(qIndex))
            tempMB |= MB_BIT(1);
        val = (dataArr[i] << MB) | tempMB;
        set_cell(qIndex, val);
        inc(&qIndex);
    }*/
}

void VLQF::get_data(size_t qIndex, BLOCK_TYPE *resArr, size_t length) {
    for (int i = 0; i < length; ++i) {
        size_t address = qIndex * (this->dataSize + MB);
        resArr[i] = get_bits(address, dataSize);
        inc(&qIndex);
    }
//    cout << "resArr is:" << "\t";
//    arrayPrinter(resArr, length);
}

void VLQF::getNextMultiEmpties(size_t qIndex, size_t steps, size_t *emptyIndex, size_t *runCounter) {
    while (!isEmpty(qIndex)) {
        *runCounter += isRunStart(qIndex);
        inc(&qIndex);
    }
    *emptyIndex = qIndex;

    size_t emptyCounter = 0;
    while (isEmpty(qIndex) and emptyCounter < steps) {
        ++emptyCounter;
        inc(&qIndex);
    }
    if (steps > emptyCounter) {
        multiPush(qIndex, steps - emptyCounter);
    }
}

size_t VLQF::multiRunShift(size_t emptyQIndex, size_t qIndex, size_t steps) {}

void VLQF::multiPush(size_t qIndex, size_t steps, bool toPushAgain) {
    if (areConsecutiveEmpties(qIndex, steps)) return;

    size_t emptyQIndex, runCounter = 0;
    getNextMultiEmpties(qIndex, steps, &emptyQIndex, &runCounter);
    for (int i = 0; i < runCounter; ++i) {
        size_t tempIndex = dec(emptyQIndex);
        size_t tempRunStart = getRunStart(tempIndex);
        emptyQIndex = multiRunShift(emptyQIndex, tempRunStart, steps);
    }
    if (toPushAgain)
        multiRunShift(emptyQIndex, qIndex, steps);
}

bool VLQF::isPartOfRemainder(size_t qIndex) {
    BLOCK_TYPE tempMB = get_mb(qIndex);
    return ((tempMB & MB_BIT(2)) and !(tempMB & MB_BIT(3)));
}

size_t VLQF::getRemainderLength(size_t qIndex) {
    if (isEmpty(qIndex))
        return 0;
    assert(!isPartOfRemainder(qIndex));
    size_t start = qIndex;
    inc(&qIndex);
    while (isPartOfRemainder(qIndex))
        inc(&qIndex);
    return (start <= qIndex) ? qIndex - start : (capacity - start) + qIndex;
    return qIndex - start;
}

bool VLQF::areConsecutiveEmpties(size_t qIndex, size_t steps) {
    for (size_t i = 0; i < steps; ++i) {
        if (!isEmpty(qIndex))
            return false;
        inc(&qIndex);
    }
    return true;
}

size_t VLQF::enoughConsecutiveEmpties(size_t qIndex, size_t steps) {
    for (size_t i = 0; i < steps; ++i) {
        if (!isEmpty(qIndex))
            return i;
        inc(&qIndex);
    }
    return steps;
}

void VLQF::convert(string *s, size_t *qIndex, BLOCK_TYPE *dataArr, size_t length) {
    *qIndex = (h.calc(s, dataArr, length) >> dataSize);
    if (dataSize < BLOCK_SIZE) {
        for (int i = 0; i < length; ++i)
            dataArr[i] = dataArr[i] % SL(dataSize);
    }
}

int VLQF::compare(size_t qIndex, size_t *tempLength, BLOCK_TYPE *dataArr, size_t length) {
    *tempLength = getRemainderLength(qIndex);
    if (*tempLength != 3)
//        elementPrint();
    if (*tempLength != length)
        return (*tempLength < length) ? -1 : 1;
    BLOCK_TYPE tempArr[*tempLength];
    get_data(qIndex, tempArr, length);
    for (int i = 0; i < length; ++i) {
        if (tempArr[i] != dataArr[i])
            return (tempArr[i] < dataArr[i]) ? -1 : 1;
    }
    return 0;
}
