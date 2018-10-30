//
// Created by tomer on 10/22/18.
//

#include "PackedArray.h"

PackedArray::PackedArray(size_t q, size_t r, size_t mbSize) : capacity(1ULL << q), dataSize(r), MB(mbSize),
                                                              h(Hash(SL(q + r))) {
    if (BLOCK_SIZE != (8 * sizeof(BLOCK_TYPE)))
        assert(false);
    size_t temp = (capacity * (dataSize + MB));
    size = temp / BLOCK_SIZE;
    if (temp % BLOCK_SIZE) ++size;
    A = new BLOCK_TYPE[size]();
}

PackedArray::PackedArray(size_t q, size_t r, size_t mbSize, size_t maxRemainderLength) : capacity(1ULL << q),
                                                                                         dataSize(r), MB(mbSize),
                                                                                         h(Hash(SL(q + r),
                                                                                                maxRemainderLength)) {
    if (BLOCK_SIZE != (8 * sizeof(BLOCK_TYPE)))
        assert(false);
    size_t temp = (capacity * (dataSize + MB));
    size = temp / BLOCK_SIZE;
    if (temp % BLOCK_SIZE) ++size;
    A = new BLOCK_TYPE[size]();
}
/*
PackedArray::PackedArray(size_t n, size_t dataSize) : capacity(n), dataSize(dataSize) {
    if (BLOCK_SIZE != (8 * sizeof(BLOCK_TYPE)))
        assert(false);
    size_t temp = (n * (dataSize + MB));
    size = temp / BLOCK_SIZE;
    if (temp % BLOCK_SIZE) ++size;
    A = new BLOCK_TYPE[size]();

}*/
//
//PackedArray::PackedArray(BLOCK_TYPE n, size_t dataSize, size_t mbSize, BLOCK_TYPE *A) : capacity(n), dataSize(dataSize),
//                                                                                        MB(mbSize) {
//    if (BLOCK_SIZE != (8 * sizeof(BLOCK_TYPE)))
//        assert(false);
//    size_t temp = (n * (dataSize + MB));
//    size = temp / BLOCK_SIZE;
//    if (temp % BLOCK_SIZE) ++size;
//    this->A = new BLOCK_TYPE[size];
//    if (A == nullptr)
//        return;
//    for (int i = 0; i < size; ++i)
//        this->A[i] = A[i];
//}

PackedArray::~PackedArray() {
    delete this->A;
}

BLOCK_TYPE PackedArray::get_bits(size_t address, size_t length) {
    size_t aIndex = address / BLOCK_SIZE, bitIndex = address % BLOCK_SIZE;
    size_t bitsFromRight = MOD_INVERSE(bitIndex);
    BLOCK_TYPE res = A[aIndex];
    if (bitIndex + length < BLOCK_SIZE) {
        BLOCK_TYPE temp = ON((bitsFromRight + 1), (bitsFromRight + 1 - length));
        res &= temp;
        size_t shift_right = ++bitsFromRight - length;
        res >>= shift_right;
    } else if (bitIndex + length == BLOCK_SIZE) {
        res &= MASK(bitsFromRight + 1);
    } else {
        size_t temp_length = bitIndex + length - BLOCK_SIZE;
        res &= get_bits(address, length - temp_length);
        res <<= temp_length;
        res += get_bits((aIndex + 1) * BLOCK_SIZE, temp_length);
    }
    return res;
    /*
        cout << "temp is:" << temp << "\t" << decToBin(temp, BLOCK_SIZE) << "\t" << A[aIndex] << endl;
        cout << "bitIndex is: " << bitIndex;
        cout << "\tbitsFromRight: " << bitsFromRight << "\tres: ";
        cout << res << "\t" << decToBin(res, BLOCK_SIZE) << std::endl;
*/

}

void PackedArray::set_bits(size_t address, size_t bitsToWriteCounter, size_t value) {
    value &= MASK(bitsToWriteCounter);
    size_t aIndex = address / BLOCK_SIZE, bitIndex = address % BLOCK_SIZE;
    size_t rBitsCounter = MOD_INVERSE(bitIndex) + 1;

    if (bitIndex + bitsToWriteCounter < BLOCK_SIZE) {
        value <<= (BLOCK_SIZE - (bitIndex + bitsToWriteCounter));
        setHelp(aIndex, value, rBitsCounter, rBitsCounter - bitsToWriteCounter);
    } else if (bitIndex + bitsToWriteCounter == BLOCK_SIZE) {
        setHelp(aIndex, value, rBitsCounter, 0);
    } else {
        size_t exceedingBits = bitIndex + bitsToWriteCounter - BLOCK_SIZE;
        uint64_t firstVal = value >> exceedingBits;
        uint64_t secondVal = value & MASK(exceedingBits);
        secondVal <<= (BLOCK_SIZE - exceedingBits);
        setHelp(aIndex, firstVal, rBitsCounter, 0);
        if (exceedingBits > BLOCK_SIZE)
            set_bits((++aIndex) * BLOCK_SIZE, exceedingBits, secondVal);
        else
            setHelp(++aIndex, secondVal, BLOCK_SIZE, BLOCK_SIZE - exceedingBits);
    }
}

void PackedArray::setHelp(size_t aIndex, size_t value, size_t borderStart, size_t borderEnd) {
    A[aIndex] &= OFF(borderStart, borderEnd);
    BLOCK_TYPE temp = ON(borderStart, borderEnd);
    value &= ON(borderStart, borderEnd);
    A[aIndex] |= value;
}

void PackedArray::set_bit(size_t address, bool setOn) {
    size_t aIndex, bitIndex, shift;
    bitIndex = address % BLOCK_SIZE;
    aIndex = address / BLOCK_SIZE;
    shift = MOD_INVERSE(bitIndex);
    size_t temp = (1ULL << shift);
    (setOn) ? A[aIndex] |= temp : A[aIndex] ^= temp;
}

BLOCK_TYPE PackedArray::get_data(size_t qIndex) {
    size_t address = qIndex * (this->dataSize + MB);
    return get_bits(address, dataSize);
}

/*void PackedArray::get_data(size_t qIndex, BLOCK_TYPE *resArr, size_t length) {
    for (int i = 0; i < length; ++i) {
        size_t address = qIndex * (this->dataSize + MB);
        resArr[i] = get_bits(address, dataSize);
        inc(&qIndex);
    }
}*/


BLOCK_TYPE PackedArray::get_mb(size_t qIndex) {
    size_t address = qIndex * (dataSize + MB) + dataSize;
    return get_bits(address, MB);
}

BLOCK_TYPE PackedArray::get_cell(size_t qIndex) {
    size_t address = qIndex * (this->dataSize + MB);
    return get_bits(address, dataSize + MB);
}

void PackedArray::set_data(size_t qIndex, size_t value) {
    size_t address = qIndex * (this->dataSize + MB);
    set_bits(address, dataSize, value);
}

void PackedArray::set_mb(size_t qIndex, size_t value) {
    size_t address = qIndex * (this->dataSize + MB) + dataSize;
    set_bits(address, MB, value);
}

void PackedArray::set_cell(size_t qIndex, size_t value) {
//    cout << "in set_cell, qIndex given is: " << qIndex << endl;
    size_t address = qIndex * (this->dataSize + MB);
    set_bits(address, dataSize + MB, value);
}

/*void PackedArray::set_cell(size_t qIndex, BLOCK_TYPE tempMB, BLOCK_TYPE *dataArr, size_t length) {
    BLOCK_TYPE val = (dataArr[0] << MB) | tempMB;
    for (int i = 0; i < length; ++i) {
        set_cell(qIndex, val);
        inc(&qIndex);
        tempMB = MB_BIT(2); // Set is_Continuation on.
        if (isOccupied(qIndex))
            tempMB |= MB_BIT(1);
        val = (dataArr[i] << MB) | tempMB;
    }
    *//*
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
    }*//*
}*/

void PackedArray::getNextEmpty(size_t qIndex, size_t *emptyIndex, size_t *runCounter) {
    while (!isEmpty(qIndex)) {
        *runCounter += isRunStart(qIndex);
        inc(&qIndex);
    }
    *emptyIndex = qIndex;
}

/*void PackedArray::getNextMultiEmpties(size_t qIndex, size_t steps, size_t *emptyIndex, size_t *runCounter) {
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
}*/

size_t PackedArray::getRunStart(size_t qIndex) {
    while (!isRunStart(qIndex)) {
        dec(&qIndex);
    }
    return qIndex;
}

size_t PackedArray::getNextRunStart(size_t qIndex) {
    if (isRunStart(qIndex))
        inc(&qIndex);
    while (isContinuation(qIndex))
        inc(&qIndex);
    return qIndex;
}

size_t PackedArray::getClusterStart(size_t qIndex, size_t *occupiedCounter) {
    if (isEmpty(qIndex))
        return qIndex;
    while (!isClusterStart(qIndex)) {
        dec(&qIndex);
        if (isOccupied(qIndex))
            ++*occupiedCounter;
    }
    return qIndex;
}

size_t PackedArray::getCompatibleRun(size_t qIndex) {
    size_t occupiedCounter = 0;
    size_t tempRunStart = getClusterStart(qIndex, &occupiedCounter);
    for (int i = 0; i < occupiedCounter; ++i)
        tempRunStart = getNextRunStart(tempRunStart);
    return tempRunStart;
}

/*
size_t PackedArray::runShift(size_t emptyQIndex, size_t qIndex) {
    while (emptyQIndex != qIndex) {
        size_t temp = dec(emptyQIndex);
        BLOCK_TYPE val = get_cell(temp);
        (isOccupied(emptyQIndex)) ? val |= MB_BIT(1) : val &= ~(MB_BIT(
                1)); // Setting val's occupied bit according to current cell.
        (isFP(emptyQIndex)) ? val |= 1 : val &= (~(1ULL)); // Setting val's fp bit according to current cell.
        set_cell(emptyQIndex, val);
        emptyQIndex = temp;
    }

    if (isRunStart(qIndex))
        setShifted(inc(qIndex), true);

    return emptyQIndex;
}
*/

void PackedArray::push(size_t qIndex, bool toPushAgain) {
    if (isEmpty(qIndex)) return;
    size_t emptyQIndex, runCounter = 0;
    getNextEmpty(qIndex, &emptyQIndex, &runCounter);
    for (int i = 0; i < runCounter; ++i) {
        size_t tempIndex = dec(emptyQIndex);
        size_t tempRunStart = getRunStart(tempIndex);
        emptyQIndex = runShift(emptyQIndex, tempRunStart);
    }
    if (toPushAgain)
        runShift(emptyQIndex, qIndex);
}

/*void PackedArray::multiPush(size_t qIndex, size_t steps, bool toPushAgain) {
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
}*/

size_t PackedArray::runShift(size_t emptyQIndex, size_t qIndex) {}

/*size_t PackedArray::multiRunShift(size_t emptyQIndex, size_t qIndex, size_t steps) {}*/

bool PackedArray::add(BLOCK_TYPE data, size_t qIndex) {}

bool PackedArray::add(BLOCK_TYPE *dataArr, size_t length, size_t qIndex) {}


//bool PackedArray::runAdd(uint64_t data, size_t qIndex) {}

int PackedArray::lookup(BLOCK_TYPE data, size_t qIndex, size_t *fpIndex) {}

//int PackedArray::lookup(BLOCK_TYPE *dataArr, size_t length, size_t qIndex, size_t *fpIndex) {}
//bool PackedArray::add(uint64_t data, size_t qIndex) {
//    size_t runIndex = getCompatibleRun(qIndex);
//
//    /*Inserting element to an empty slot, could be shifted*/
//    if (isEmpty(runIndex)) {
//        BLOCK_TYPE tempMB = (qIndex != runIndex) ? uint16_t(MB_BIT(3)) : uint16_t(MB_BIT(1)); // is shifted condition.
//        uint64_t val = (data << MB) | tempMB;
//        set_cell(runIndex, val);
//        setOccupied(qIndex, true);
//        return true;
//    }
//
//    /*Inserting element to a new run, must be shifted. (require push)*/
//    if (!isOccupied(qIndex)) {
//        setOccupied(qIndex, true);
//
//        push(runIndex);
//
//        BLOCK_TYPE tempMB = MB_BIT(3); // Set is_shifted on.
//        if (isOccupied(runIndex))
//            tempMB |= MB_BIT(1);
//        uint64_t val = (data << MB) | tempMB;
//
//        set_cell(runIndex, val);
//        return true;
//    }
//
//    /*If element shouldn't be first in it's run. (isn't smallest in its run). */
//    if (get_data(runIndex) < data) {
////        inc(&runIndex);
//        BLOCK_TYPE cell = 0;<assert.h>
//        bool isContinuationCond = true;
//        while (isContinuationCond & ((cell >> MB) < data)) {
//            inc(&runIndex);
//            cell = get_cell(runIndex);
//            isContinuationCond = cell & MB_BIT(2);
//        }
//
//        if ((cell & (MB_BIT(2) | MB_BIT(4))) & ((cell >> MB) == data))
//            return false;
//
//        if (!(cell & MASK(MB))) { // Cell is empty.
//            uint64_t val = MB_BIT(2) | MB_BIT(3); // Continuation and Shifted.
//            val |= (data << MB);
//            set_cell(runIndex, val);
//        } else {
//            push(runIndex, true);
//            uint64_t val = MB_BIT(2) | MB_BIT(3); // Continuation and Shifted.
//            if (isOccupied(runIndex)) val |= MB_BIT(1);
//            val |= (data << MB);
//            set_cell(runIndex, val);
//        }
//    } else {
//        BLOCK_TYPE tempMB = get_mb(runIndex);
//        if ((get_data(runIndex) == data) & (tempMB & 1))
//            return false;
//        push(runIndex);
//        uint64_t val = (data << MB) | tempMB;
//        set_cell(runIndex, val);
//        inc(&runIndex);
//        setShifted(runIndex);
//        setContinuation(runIndex);
///*
//        cout << "in Add:" << endl;
//        cout << *this << endl;
//        cout << *this << endl;
//        cout << *this << endl;
//        cout << "End." << endl;
//*/
//    }
//    return true;
//
//}
/*

int PackedArray::lookup(uint64_t data, size_t qIndex, size_t *fpIndex) {

    if (!isOccupied(qIndex))
        return 0;
    size_t runIndex = getCompatibleRun(qIndex);
    if (data == get_data(runIndex))
        return (isFP(runIndex)) ? -1 : 1;

    inc(&runIndex);
    while (true) {
        BLOCK_TYPE cell = get_cell(runIndex);
        bool continuationCond = bool(cell & MB_BIT(2));
        bool compareCond = (cell >> MB) <= data;

        if (!(continuationCond and compareCond))
            return 0;

        if ((cell >> MB) == data)
            return (isFP(runIndex)) ? -1 : 1;
        inc(&runIndex);
    }
}
*/

//int PackedArray::lookupAdapt(uint64_t data, size_t qIndex, size_t *fpIndex) {
//    if (!isOccupied(qIndex))
//        return 0;
//    size_t runIndex = getCompatibleRun(qIndex);
//    if (data == get_data(runIndex)) {
//        if (isFP(runIndex))
//            return -1;
//        *fpIndex = runIndex;
//        return 1;
//    }
//
//    size_t startIndex = runIndex;
//    inc(&runIndex);
//    while (true) {
//        BLOCK_TYPE cell = get_cell(runIndex);
//        bool continuationCond = bool(cell & MB_BIT(2));
//        bool compareCond = (cell >> MB) <= data;
//
//        if (!(continuationCond and compareCond))
//            return 0;
//
//        if ((cell >> MB) == data) {
//            if (isFP(runIndex))
//                return -1;
//            *fpIndex = runIndex;
//            return 1;
//        }
//        if (runIndex == capacity - 1)
//            cout << "loop" << endl;
//        inc(&runIndex);
//    }
//    assert(false);
//}

ostream &operator<<(ostream &os, const PackedArray &pa) {
    BLOCK_TYPE *tempA = pa.getA();
    os << "[" << tempA[0];
    for (int i = 1; i < pa.getSize(); ++i)
        os << ", " << tempA[i];
    os << "]" << endl;

    os << "[" << decToBin(tempA[0], BLOCK_SIZE);
    for (int i = 1; i < pa.getSize(); ++i)
        os << ", " << decToBin(tempA[i], BLOCK_SIZE);
    os << "]" << std::endl;
    string s = listToStr(pa);
    splitStr(os, &s, pa.getDataSize(), pa.getCapacity(), pa.getMBSize(), 0);
    return os;
}

BLOCK_TYPE *PackedArray::getA() const {
    return A;
}

size_t PackedArray::getSize() const {
    return size;
}

size_t PackedArray::getCapacity() const {
    return capacity;
}

size_t PackedArray::getDataSize() const {
    return dataSize;
}

size_t PackedArray::getMBSize() const {
    return MB;
}

bool PackedArray::isEmpty(size_t qIndex) {
    return (get_mb(qIndex) == 0);
}

bool PackedArray::isOccupied(size_t qIndex) {
    return bool(get_mb(qIndex) & MB_BIT(1)); // 8 = "1000".
}

bool PackedArray::isContinuation(size_t qIndex) {
    return bool(get_mb(qIndex) & MB_BIT(2)); // 4 = "0100".
}

bool PackedArray::isShifted(size_t qIndex) {
    return bool(get_mb(qIndex) & MB_BIT(3));
}

bool PackedArray::isFP(size_t qIndex) {
    return bool(get_mb(qIndex) & MB_BIT(4));
}

/*
bool PackedArray::isPartOfRemainder(size_t qIndex) {
    BLOCK_TYPE tempMB = get_mb(qIndex);
    return ((tempMB & MB_BIT(2)) and !(tempMB & MB_BIT(3)));
    //Continuation and not shifted.
}
*/

bool PackedArray::isRunStart(size_t qIndex) {
    BLOCK_TYPE tempMB = get_mb(qIndex);
    return bool((tempMB & MASK(MB)) and (!(tempMB & MB_BIT(2))));
//    return bool(get_mb(qIndex) & 11); // 11 = "1011".
}

bool PackedArray::isClusterStart(size_t qIndex) {
    /*BLOCK_TYPE cell = get_mb(qIndex);
    bool notEmptyCond = bool(cell & MASK(MB));
    bool notShiftedOrCont = !(cell & (MB_BIT(2) | MB_BIT(3)));
    return notEmptyCond & notShiftedOrCont;*/
    return !((MB_BIT(3) | MB_BIT(2)) & get_mb(qIndex));
}

void PackedArray::setOccupied(size_t qIndex, bool setOn) {
    size_t address = qIndex * (this->dataSize + MB) + dataSize;
    set_bit(address, setOn);
}

void PackedArray::setContinuation(size_t qIndex, bool setOn) {
    size_t address = qIndex * (this->dataSize + MB) + dataSize + 1;
    set_bit(address, setOn);
}

void PackedArray::setShifted(size_t qIndex, bool setOn) {
    size_t address = qIndex * (this->dataSize + MB) + dataSize + 2;
    set_bit(address, setOn);
}

void PackedArray::setFP(size_t qIndex) {
//    cout << qIndex << " set as FP." << endl;
    size_t address = qIndex * (this->dataSize + MB) + dataSize + 3;
    set_bit(address, true);
}
/*
bool PackedArray::areConsecutiveEmpties(size_t qIndex, size_t steps) {
    for (size_t i = 0; i < steps; ++i) {
        if (!isEmpty(qIndex))
            return false;
        inc(&qIndex);
    }
    return true;
}*/
/*
size_t PackedArray::getRemainderLength(size_t qIndex) {
    if (isEmpty(qIndex))
        return 0;
    assert(!isPartOfRemainder(qIndex));
    size_t start = qIndex;
    inc(&qIndex);
    while (isPartOfRemainder(qIndex))
        inc(&qIndex);
    return qIndex - start;
}*/

void PackedArray::inc(size_t *index) {
    ++(*index);
    *index = (*index) % capacity;
//    *index %= capacity;
}

size_t PackedArray::inc(size_t index) {
    return (++index % capacity);
}

void PackedArray::dec(size_t *index) {
    (*index) ? --*index : *index = capacity - 1;
    //If index > 0 (!= 0) decrease by one, otherwise..
}

size_t PackedArray::dec(size_t index) {
    return (index) ? --index : capacity - 1;
}

ostream &PackedArray::statisticsPrint(ostream &os) {
    os << "Capacity is: " << capacity << ", " << "dataSize is: " << dataSize << ", MB: " << MB << endl;
    statusCorrectness(os);
    emptyData(os);
    dataCounter(MASK(dataSize) ^ 12);

    runStatistic(os);
    clusterStatistic(os);
    os << "Number of FP: " << fpCounter() << endl;
    return os;
}

size_t PackedArray::countElement(size_t qIndex) {
    BLOCK_TYPE data = get_data(qIndex);
    inc(&qIndex);
    size_t counter = 1;
    while (isContinuation(qIndex)) {
        if (data != get_data(qIndex))
            break;
        ++counter;
        inc(qIndex);
    }
    return counter;
}

string listToStr(const PackedArray &pa) {
    const size_t size = pa.getSize();
    BLOCK_TYPE *arr = pa.getA();
    string s;
    for (int i = 0; i < size; ++i)
        s += decToBin(arr[i], BLOCK_SIZE);
//    cout << "listToStr: " << s << endl;
    return s;
}

ostream &PackedArray::runStatistic(ostream &os) {
    size_t runsCounter = 0, maxLen = 0, sum = 0, index = 0, lim = capacity, tempRes;
    if (!isEmpty(index) and !isRunStart(index)) {
        lim = getRunStart(index);
        index = getNextRunStart(index);
        maxLen = (capacity - lim) + index;
        sum += maxLen;
        ++runsCounter;
    }
    while (index < lim) {
        if (isEmpty(index)) {
            while (isEmpty(index))
                ++index;
        } else {
            tempRes = calcRunLength(index);
            index += tempRes;
            sum += tempRes;
            if (maxLen < tempRes)
                maxLen = tempRes;
            ++runsCounter;
        }
    }
    os << "Capacity ratio: " << double(runsCounter) / capacity << endl;
    os << "Number of runs: " << runsCounter << "\t" << "longest run: " << maxLen << "\t" << "average: "
       << double(sum) / runsCounter << endl;
    return os;
}

ostream &PackedArray::clusterStatistic(ostream &os) {
    size_t clustersCounter = 0, maxLen = 0, sum = 0, index = 0, lim = capacity, tempRes;
    if (!isEmpty(index) and !isClusterStart(index)) {
        lim = getClusterStart(index, &tempRes);
        tempRes = calcClusterLength(lim);
        index = tempRes - (capacity - lim);
        maxLen = tempRes;
        sum += maxLen;
        ++clustersCounter;
    }
    while (index < lim) {
        if (isEmpty(index)) {
            while (isEmpty(index))
                ++index;
            /*if(!isClusterStart(index))
            {
                elementPrint(os);
                auto cell = get_cell(index);
                auto mb = get_mb(index);
                assert(isClusterStart(index));
            }*/
        } else {
            tempRes = calcClusterLength(index);
            index += tempRes;
            sum += tempRes;
            if (maxLen < tempRes)
                maxLen = tempRes;
            ++clustersCounter;
        }
    }
    os << "Number of clusters: " << clustersCounter << "\t" << "longest cluster: " << maxLen << "\t" << "average: "
       << double(sum) / clustersCounter << endl;
    return os;
}

size_t PackedArray::calcRunLength(size_t runIndex) {
    if (!isRunStart(runIndex)) {
        cout << "runStart index " << runIndex << endl;
        auto cell = get_cell(runIndex);
        auto mb = get_mb(runIndex);
        statusCorrectness();
        elementPrint(0, 0, cout);
        runStatistic();
        if (!isRunStart(runIndex))
            assert(isRunStart(runIndex));
    }
    size_t end = getNextRunStart(runIndex);
    if (end < runIndex)
        return (capacity - runIndex) + end;
    return end - runIndex;
}

size_t PackedArray::calcClusterLength(size_t clusterStart) {
    if (!isClusterStart(clusterStart)) {
        cout << "clusterStart index " << clusterStart << endl;
        auto cell = get_cell(clusterStart);
        auto mb = get_mb(clusterStart);
        statusCorrectness();
        neighborhoodPrint(clusterStart);
//        elementPrint(0, 0, cout);
        clusterStatistic();
        assert(isClusterStart(clusterStart));
    }
    size_t counter = 1;
    inc(&clusterStart);
    while (isShifted(clusterStart) or isContinuation(clusterStart)) {
        inc(&clusterStart);
        ++counter;
    }
    return counter;
}

ostream &PackedArray::elementPrint(ostream &os) {
    return elementPrint(0, capacity, os);
}

ostream &PackedArray::elementPrint(size_t start, size_t end, ostream &os) {
    string s;
    for (size_t i = start; i < end; ++i)
        s += decToBin(A[i], BLOCK_SIZE);
    size_t elNum = (start < end) ? end - start : capacity - start + end;
    splitStr(os, &s, dataSize, elNum, MB, start);
    return os;
}

ostream &PackedArray::elementPrintDec(ostream &os) {
    size_t start = 0, end = capacity;
    string s;
    for (size_t i = start; i < end; ++i)
        s += decToBin(A[i], BLOCK_SIZE);
    size_t elNum = (start < end) ? end - start : capacity - start + end;
    splitStrDec(os, &s, dataSize, elNum, MB, start);
    return os;
}

string decToBin(BLOCK_TYPE n, size_t length) {
    string s = "";
    BLOCK_TYPE onBit = 1ULL << (length - 1);
    for (int i = 0; i < length; ++i) {
        (n & onBit) ? s.append(1, 49) : s.append(1, 48);
        onBit >>= 1;
    }

    return s;
}

ostream &splitStr(ostream &os, string *s, size_t dataSize, size_t elNum, size_t mbSize, size_t startIndex) {
    size_t index = 0, jump = dataSize + mbSize;
    os << "[";
    for (int i = 0; i < elNum; ++i) {
        os << (i + startIndex) << ":(" << s->substr(index, dataSize) << "," << s->substr(index + dataSize, mbSize)
           << "),";
        index += jump;
    }
    os << "]" << endl;
    return os;
}

ostream &splitStrDec(ostream &os, string *s, size_t dataSize, size_t elNum, size_t mbSize, size_t startIndex) {
    size_t index = 0, jump = dataSize + mbSize;
    os << "[";
    for (int i = 0; i < elNum; ++i) {
        os << (i + startIndex) << ":(" << stoi(s->substr(index, dataSize), nullptr, 2) << ","
           << s->substr(index + dataSize, mbSize)
           << "),";
        index += jump;
    }
    os << "]" << endl;
    return os;
}

bool PackedArray::add(string *s) {
    size_t qIndex;
    BLOCK_TYPE data;
    convert(s, &qIndex, &data);
    return add(data, qIndex);
}

/*
bool PackedArray::add(string *s, size_t length) {
    size_t qIndex;
    BLOCK_TYPE dataArr[length];
    convert(s, &qIndex, dataArr, length);
    return add(dataArr, length, qIndex);
}
*/

int PackedArray::lookup(string *s) {
    size_t qIndex;
    BLOCK_TYPE data;
    convert(s, &qIndex, &data);
    return lookup(data, qIndex, nullptr);
}

/*
int PackedArray::lookup(string *s, size_t length) {
    size_t qIndex;
    BLOCK_TYPE dataArr[length];
    convert(s, &qIndex, dataArr, length);
    return lookup(dataArr, length, qIndex, nullptr);
}
*/

int PackedArray::lookup(string *s, size_t *fpIndex) {
    size_t qIndex;
    BLOCK_TYPE data;
    convert(s, &qIndex, &data);
    return lookup(data, qIndex, fpIndex);
}

void PackedArray::convert(string *s, size_t *qIndex, BLOCK_TYPE *data) {
    uint64_t hashVal = h.calc(s);
    *qIndex = (hashVal >> dataSize);
    *data = (hashVal % SL(dataSize)); // Todo
}

/*
void PackedArray::convert(string *s, size_t *qIndex, BLOCK_TYPE *dataArr, size_t length) {
    *qIndex = (h.calc(s, dataArr, length) >> dataSize);
    if (dataSize < BLOCK_SIZE) {
        for (int i = 0; i < length; ++i)
            dataArr[i] = dataArr[i] % SL(dataSize);
    }
//    size_t tempLength = myLength;
//    if (!myLength) tempLength = dataSize * myLength;
//    *qIndex = (hashVal >> dataSize);
//    *data = (hashVal % SL(dataSize)); // Todo
}
*/

void PackedArray::statusCorrectness(ostream &os) {
    int counter = 0;
    for (size_t i = 0; i < capacity; ++i) {
        auto mb = get_mb(i);
        if ((mb & (MB_BIT(2))) and !(mb & (MB_BIT(3))))
            ++counter;
    }
    if (counter)
        os << counter << " cells were corrupted." << endl;
//    return counter;
}

void PackedArray::emptyData(ostream &os) {
    int counter = 0;
    for (size_t i = 0; i < capacity; ++i) {
        auto cell = get_cell(i);
        if (((cell >> MB) == 0) and (cell & (MASK(MB))))
            ++counter;
    }
    if (counter)
        os << counter << " cells have empty data." << endl;
}

void PackedArray::dataCounter(BLOCK_TYPE data, ostream &os) {
    int counter = 0;
    for (size_t i = 0; i < capacity; ++i) {
        auto cell = get_cell(i);
        if (((cell >> MB) == data) and (cell & (MASK(MB))))
            ++counter;
    }
    if (counter)
        os << counter << " cells have the same data." << endl;
}

size_t PackedArray::fpCounter() {
    size_t counter = 0;
    for (size_t i = 0; i < capacity; ++i) {
        auto mb = get_mb(i);
        if (mb & (MB_BIT(4)))
            ++counter;
    }
    return counter;
}

void PackedArray::neighborhoodPrint(size_t qIndex, ostream &os) {
    size_t start = dec(qIndex), end = inc(qIndex);
    for (int i = 0; i < 1; ++i) {
        while (!isEmpty(start))
            dec(&start);
        while (!isEmpty(end))
            inc(&end);
    }
    elementPrint(start, end, os);
}


int compareArray(BLOCK_TYPE *A1, BLOCK_TYPE *A2, size_t length) {
    for (int i = 0; i < length; ++i) {
        if (A1[i] != A2[i])
            return (A1[i] > A2[i]) ? 1 : -1;
    }
    return 0;
}
