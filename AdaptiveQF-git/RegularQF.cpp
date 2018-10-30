//
// Created by tomer on 10/22/18.
//

#include "RegularQF.h"

RegularQF::RegularQF(size_t q, size_t r, size_t mbSize) : PackedArray(q, r, mbSize) {
};

//RegularQF::RegularQF(uint16_t n, size_t dataSize, BLOCK_TYPE *A) : PackedArray(n, dataSize, 3, A) {}

int RegularQF::lookup(BLOCK_TYPE data, size_t qIndex, size_t *fpIndex) {
    if (!isOccupied(qIndex))
        return 0;
    size_t runIndex = getCompatibleRun(qIndex);
    if (data == get_data(runIndex))
        return 1;

    inc(&runIndex);
    while (true) {
        BLOCK_TYPE cell = get_cell(runIndex);
        bool continuationCond = bool(cell & MB_BIT(2));
        bool compareCond = (cell >> MB) <= data;

        if (!(continuationCond and compareCond))
            return 0;

        if ((cell >> MB) == data)
            return 1;
        inc(&runIndex);
    }
}

/*int RegularQF::lookup(BLOCK_TYPE *dataArr, size_t length, size_t qIndex, size_t *fpIndex) {
    if (!isOccupied(qIndex))
        return 0;
    size_t runIndex = getCompatibleRun(qIndex);
    size_t tempLength = 1;
    if (compare(runIndex, &tempLength, dataArr, length) == 0)
        return 1;

    runIndex = (runIndex + tempLength) % capacity;
    while (isContinuation(runIndex)) {
        int res = compare(runIndex, &tempLength, dataArr, length);
        switch (res) {
            case -1:
                runIndex = (runIndex + tempLength) % capacity;
                break;
            case 0:
                return 1;
            case 1:
                return 0;
            default:
                assert(false);
        }
    }
    return 0;
    *//*if (tempLength < length)
            runIndex = (runIndex + tempLength) % capacity;
        else if (tempLength == length) {
            if (compare(runIndex, &tempLength, dataArr, length))
        }
        BLOCK_TYPE cell = get_cell(runIndex);
        bool continuationCond = bool(cell & MB_BIT(2));
        bool compareCond = (cell >> MB) <= data;

        if (!(continuationCond and compareCond))
            return 0;

        if ((cell >> MB) == data)
            return 1;
        inc(&runIndex);
    }*//*
}*/

bool RegularQF::add(BLOCK_TYPE data, size_t qIndex) {
    size_t runIndex = getCompatibleRun(qIndex);

    /*Inserting element to an empty slot, could be shifted*/
    if (isEmpty(runIndex)) {
        BLOCK_TYPE tempMB = (qIndex != runIndex) ? BLOCK_TYPE(MB_BIT(3)) : BLOCK_TYPE(
                MB_BIT(1)); // is shifted condition.
        uint64_t val = (data << MB) | tempMB;
        set_cell(runIndex, val);
        setOccupied(qIndex, true);
        return true;
    }

    /*Inserting element to a new run, must be shifted. (require push)*/
    if (!isOccupied(qIndex)) {
        setOccupied(qIndex, true);

        push(runIndex);

        BLOCK_TYPE tempMB = MB_BIT(3); // Set is_shifted on.
        if (isOccupied(runIndex))
            tempMB |= MB_BIT(1);
        uint64_t val = (data << MB) | tempMB;

        set_cell(runIndex, val);
        return true;
    }

    /*If element shouldn't be first in it's run. (isn't smallest in its run). */
    runAdd(data, runIndex);
    /*if (get_data(runIndex) < data) {
        BLOCK_TYPE cell = 0;
        bool isContinuationCond = true;
        while (isContinuationCond & ((cell >> MB) < data)) {
            inc(&runIndex);
            cell = get_cell(runIndex);
            isContinuationCond = cell & MB_BIT(2);
        }

        if (!(cell & MASK(MB))) { // Cell is empty.
            uint64_t val = MB_BIT(2) | MB_BIT(3); // Continuation and Shifted.
            val |= (data << MB);
            set_cell(runIndex, val);
        } else {
            push(runIndex, true);
            uint64_t val = MB_BIT(2) | MB_BIT(3); // Continuation and Shifted.
            if (isOccupied(runIndex)) val |= MB_BIT(1);
            val |= (data << MB);
            set_cell(runIndex, val);
        }
    } else {
        BLOCK_TYPE tempMB = get_mb(runIndex);
        push(runIndex);
        uint64_t val = (data << MB) | tempMB;
        set_cell(runIndex, val);
        inc(&runIndex);
        setShifted(runIndex);
        setContinuation(runIndex);
    }*/
    return true;
}

/*bool RegularQF::add(BLOCK_TYPE *dataArr, size_t length, size_t qIndex) {
    {
        size_t runIndex = getCompatibleRun(qIndex);

        *//*Inserting element to an empty slot, could be shifted*//*
//        if (areConsecutiveEmpties(runIndex, qIndex)) {
        if (isEmpty(runIndex)) {
            // is shifted condition.
            BLOCK_TYPE tempMB = (qIndex != runIndex) ? BLOCK_TYPE(MB_BIT(3)) : BLOCK_TYPE(MB_BIT(1));
            BLOCK_TYPE val = (dataArr[0] << MB) | tempMB;
            set_cell(runIndex, val, dataArr, length);
            setOccupied(qIndex, true);
            return true;
            *//*size_t cellCounter = 1;
            while (cellCounter < length) {
                if (!isEmpty(runIndex))
                    break;
                val = (dataArr[cellCounter] << MB) | MB_BIT(2);
                set_cell(runIndex, val);
                ++cellCounter;
                inc(&runIndex);
            }
            if (cellCounter == length)
                return true;
            else {
                //todo
            }*//*
        }

        *//*Inserting element to a new run, must be shifted. (require push)*//*
        if (!isOccupied(qIndex)) {
            setOccupied(qIndex, true);

            multiPush(runIndex, length);

            BLOCK_TYPE tempMB = MB_BIT(3); // Set is_shifted on.
            if (isOccupied(runIndex))
                tempMB |= MB_BIT(1);
            BLOCK_TYPE val = (dataArr[0] << MB) | tempMB;
            set_cell(runIndex, val, dataArr, length);
            *//*inc(&runIndex);
            for (int i = 1; i < length; ++i) {
                tempMB = MB_BIT(2); // Set is_Continuation on.
                if (isOccupied(runIndex))
                    tempMB |= MB_BIT(1);
                val = (dataArr[i] << MB) | tempMB;
                set_cell(runIndex, val);
                inc(&runIndex);
            }*//*
            return true;
        }
        runMultiAdd(dataArr, length, runIndex);

        *//*If element shouldn't be first in it's run. (isn't smallest in its run). *//*
        *//*
        size_t tempLength = getRemainderLength(runIndex);
        if (tempLength < length) {
//            bool compareLengthCond = true;
//            bool isContinuationCond = true;
            runIndex = (runIndex + tempLength) % capacity;
            assert(isPartOfRemainder(runIndex));
            while (isContinuation(runIndex)) {
                tempLength = getRemainderLength(runIndex);
                if (tempLength < length)
                    runIndex = (runIndex + tempLength) % capacity;
                else {
                    bool pushCond = true;
                    if (tempLength == length) {
                        BLOCK_TYPE tempData[length];
                        get_data(runIndex, tempData, length);
                        //compareLengthCond = dataArr > tempData.
                        if (compareArray(dataArr, tempData, length) == 1)
                            pushCond = false;
                    }
                    if (pushCond)
                        multiPush(runIndex, length);
                }
                if (tempLength > length)

                    compareLengthCond = false;
                else if (tempLength == length) {
                    BLOCK_TYPE tempData[length];
                    get_data(runIndex, tempData, length);
                    //compareLengthCond = dataArr > tempData.
                    compareLengthCond = (compareArray(dataArr, tempData, length) == 1);
                }

                BLOCK_TYPE cell = get_cell(runIndex);
                isContinuationCond = cell & MB_BIT(2);
            }

            if (!(cell & MASK(MB))) { // Cell is empty.
                uint64_t val = MB_BIT(2) | MB_BIT(3); // Continuation and Shifted.
                val |= (data << MB);
                set_cell(runIndex, val);
            } else {
                push(runIndex, true);
                uint64_t val = MB_BIT(2) | MB_BIT(3); // Continuation and Shifted.
                if (isOccupied(runIndex)) val |= MB_BIT(1);
                val |= (data << MB);
                set_cell(runIndex, val);
            }
        } else {
            BLOCK_TYPE tempMB = get_mb(runIndex);
            push(runIndex);
            uint64_t val = (data << MB) | tempMB;
            set_cell(runIndex, val);
            inc(&runIndex);
            setShifted(runIndex);
            setContinuation(runIndex);
        }
    *//*}
    return true;
}*/

size_t RegularQF::runShift(size_t emptyQIndex, size_t qIndex) {
    while (emptyQIndex != qIndex) {
        size_t temp = dec(emptyQIndex);
        BLOCK_TYPE val = get_cell(temp);
        (isOccupied(emptyQIndex)) ? val |= MB_BIT(1) : val &= ~(MB_BIT(
                1)); // Setting val's occupied bit according to current cell.
        set_cell(emptyQIndex, val);
        emptyQIndex = temp;
    }

    if (isRunStart(qIndex))
        setShifted(inc(qIndex), true);

    return emptyQIndex;
}

/*size_t RegularQF::multiRunShift(size_t emptyQIndex, size_t qIndex, size_t steps) {
    while (emptyQIndex != (qIndex + steps - 1)) {
        size_t temp = (emptyQIndex - steps) % capacity;
        BLOCK_TYPE val = get_cell(temp);
        // Setting val's occupied bit according to current cell.
        (isOccupied(emptyQIndex)) ? val |= MB_BIT(1) : val &= ~(MB_BIT(1));
        set_cell(emptyQIndex, val);
        dec(&emptyQIndex);
    }

    if (isRunStart(qIndex))
        setShifted(inc(qIndex), true);

    return qIndex;
}*/

bool RegularQF::runAdd(uint64_t data, size_t runIndex) {
    if (get_data(runIndex) < data) {
        BLOCK_TYPE cell = 0;
        bool isContinuationCond = true;
        while (isContinuationCond & ((cell >> MB) < data)) {
            inc(&runIndex);
            cell = get_cell(runIndex);
            isContinuationCond = cell & MB_BIT(2);
        }

        push(runIndex, true);
        BLOCK_TYPE val = MB_BIT(2) | MB_BIT(3); // Continuation and Shifted.
        if (isOccupied(runIndex)) val |= MB_BIT(1);
        val |= (data << MB);
        set_cell(runIndex, val);

/*
        if (!(cell & MASK(MB))) { // Cell is empty.
            uint64_t val = MB_BIT(2) | MB_BIT(3); // Continuation and Shifted.
            val |= (data << MB);
            set_cell(runIndex, val);
        } else {
            push(runIndex, true);
            uint64_t val = MB_BIT(2) | MB_BIT(3); // Continuation and Shifted.
            if (isOccupied(runIndex)) val |= MB_BIT(1);
            val |= (data << MB);
            set_cell(runIndex, val);
        }
*/
    } else {
        BLOCK_TYPE tempMB = get_mb(runIndex);
        push(runIndex);
        uint64_t val = (data << MB) | tempMB;
        set_cell(runIndex, val);
        inc(&runIndex);
        setShifted(runIndex);
        setContinuation(runIndex);
    }
    return true;
}

/*bool RegularQF::runMultiAdd(BLOCK_TYPE *dataArr, size_t length, size_t runIndex) {
    size_t tempLength = 1;
    bool res = isSmaller(runIndex, &tempLength, dataArr, length);
    if (res) {
        runIndex = (runIndex + tempLength) % capacity;
        assert(!isPartOfRemainder(runIndex));
        while (isContinuation(runIndex)) {
            res = isSmaller(runIndex, &tempLength, dataArr, length);
            if (!res)
                break;
            runIndex = (runIndex + tempLength) % capacity;
            *//*else {
            multiPush(runIndex, length, true);
            BLOCK_TYPE val = MB_BIT(2) | MB_BIT(3); // Continuation and Shifted.
            if (isOccupied(runIndex)) val |= MB_BIT(1);
            val |= (dataArr[0] << MB);
            set_cell(runIndex, val, dataArr, length);
            return true;
        }*//*
        }
        *//*BLOCK_TYPE val = MB_BIT(2) | MB_BIT(3); // Continuation and Shifted.
        if (isOccupied(runIndex)) val |= MB_BIT(1);
        val |= (dataArr[0] << MB);*//*
        BLOCK_TYPE tempMB = MB_BIT(2) | MB_BIT(3); // Continuation and Shifted.
        if (isOccupied(runIndex)) tempMB |= MB_BIT(1);
        multiPush(runIndex, length, true);
        set_cell(runIndex, tempMB, dataArr, length);
    } else {
        BLOCK_TYPE tempMB = get_mb(runIndex);
        multiPush(runIndex, length);
        set_cell(runIndex, tempMB, dataArr, length);
        runIndex = (runIndex + length) % capacity;
        setShifted(runIndex);
        setContinuation(runIndex);
    }
    return true;
*//*tempLength = getRemainderLength(runIndex);
if (tempLength < length)
    runIndex = (runIndex + tempLength) % capacity;
else {
    bool pushCond = true;
    if (tempLength == length) {
        BLOCK_TYPE tempData[length];
        get_data(runIndex, tempData, length);
        //compareLengthCond = dataArr > tempData.
        if (compareArray(dataArr, tempData, length) == 1)
            pushCond = false;
    }
    if (pushCond)
        multiPush(runIndex, length);
}
if (tempLength > length)
    1;
//                compareLengthCond = false;
else if (tempLength == length) {
    BLOCK_TYPE tempData[length];
    get_data(runIndex, tempData, length);
    //compareLengthCond = dataArr > tempData.
//                compareLengthCond = (compareArray(dataArr, tempData, length) == 1);
}

}
} else {
BLOCK_TYPE tempMB = get_mb(runIndex);
push(runIndex);
uint64_t val = (data << MB) | tempMB;
set_cell(runIndex, val
);
inc(&runIndex);
setShifted(runIndex);
setContinuation(runIndex);
}*//*
}*/

/*bool RegularQF::isSmaller(size_t qIndex, size_t *tempLength, BLOCK_TYPE *dataArr, size_t length) {
//    const size_t tempLength = getRemainderLength(qIndex);
    *tempLength = getRemainderLength(qIndex);
    if (*tempLength != length)
        return (*tempLength < length);
    BLOCK_TYPE tempArr[*tempLength];
    get_data(qIndex, tempArr, length);
    for (int i = 0; i < length; ++i) {
        if (tempArr[i] != dataArr[i])
            return (tempArr[i] < dataArr[i]);
    }
    //If equal return true. (le)
    return true;
}*/

/*int RegularQF::compare(size_t qIndex, size_t *tempLength, BLOCK_TYPE *dataArr, size_t length) {
    *tempLength = getRemainderLength(qIndex);
    if (*tempLength != length)
        return (*tempLength < length) ? -1 : 1;
    BLOCK_TYPE tempArr[*tempLength];
    get_data(qIndex, tempArr, length);
    for (int i = 0; i < length; ++i) {
        if (tempArr[i] != dataArr[i])
            return (tempArr[i] < dataArr[i]) ? -1 : 1;
    }
    return 0;
}*/

/*

void RegularQF::add(string *s) {
    uint32_t hashVal = h.calc(s);
    size_t qIndex = hashVal >> r;
    uint64_t data = hashVal % SL(r);
    add(data, qIndex);
}

bool RegularQF::lookup(string *s) {
    uint32_t hashVal = h.calc(s);
    size_t qIndex = hashVal >> r;
    uint64_t data = hashVal % SL(r);
    return bool(lookup(data, qIndex));
}
*/


//
//int RegularQF::lookup(uint64_t data, size_t qIndex, size_t *fpIndex) {
//    return PackedArray::lookup(data, qIndex, fpIndex);
//}


