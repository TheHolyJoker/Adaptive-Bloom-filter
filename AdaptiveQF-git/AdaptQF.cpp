//
// Created by tomer on 10/22/18.
//

#include "AdaptQF.h"

//AdaptQF::AdaptQF(size_t q, size_t r) {}

bool AdaptQF::add(BLOCK_TYPE  data, size_t qIndex) {
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

    /*Inserting to a run*/
    return runAdd(data, runIndex);

}

int AdaptQF::lookup(BLOCK_TYPE  data, size_t qIndex, size_t *fpIndex) {
    assert(fpIndex != nullptr);
    if (!isOccupied(qIndex))
        return 0;
    size_t runIndex = getCompatibleRun(qIndex);
    if (data == get_data(runIndex)) {
        if (isFP(runIndex))
            return -1;
        *fpIndex = runIndex;
        return 1;
    }

    size_t startIndex = runIndex;
    inc(&runIndex);
    while (true) {
        BLOCK_TYPE cell = get_cell(runIndex);
        bool continuationCond = bool(cell & MB_BIT(2));
        bool compareCond = (cell >> MB) <= data;

        if (!(continuationCond and compareCond))
            return 0;

        if ((cell >> MB) == data) {
            if (isFP(runIndex))
                return -1;
            *fpIndex = runIndex;
            return 1;
        }
        if (runIndex == capacity - 1)
            cout << "loop" << endl;
        inc(&runIndex);
    }
    assert(false);
}

size_t AdaptQF::runShift(size_t emptyQIndex, size_t qIndex) {
    while (emptyQIndex != qIndex) {
        size_t temp = dec(emptyQIndex);
        BLOCK_TYPE val = get_cell(temp);
        (isOccupied(emptyQIndex)) ? val |= MB_BIT(1) : val &= ~(MB_BIT(
                1)); // Setting val's occupied bit according to current cell.
        (isFP(emptyQIndex)) ? val |= MB_BIT(4) : val &= (~(MB_BIT(
                4))); // Setting val's fp bit according to current cell.
        set_cell(emptyQIndex, val);
        emptyQIndex = temp;
    }

    if (isRunStart(qIndex))
        setShifted(inc(qIndex), true);

    return emptyQIndex;
}

bool AdaptQF::runAdd(BLOCK_TYPE  data, size_t runIndex) {
    if (get_data(runIndex) < data) {
//        inc(&runIndex);
        BLOCK_TYPE cell = 0;
        bool isContinuationCond = true;
        while (isContinuationCond & ((cell >> MB) < data)) {
            inc(&runIndex);
            cell = get_cell(runIndex);
            isContinuationCond = cell & MB_BIT(2);
        }

        if ((cell & (MB_BIT(2) | MB_BIT(4))) & ((cell >> MB) == data))
            return false;

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
        if ((get_data(runIndex) == data) & (tempMB & 1))
            return false;
        push(runIndex);
        uint64_t val = (data << MB) | tempMB;
        set_cell(runIndex, val);
        inc(&runIndex);
        setShifted(runIndex);
        setContinuation(runIndex);
/*
        cout << "in Add:" << endl;
        cout << *this << endl;
        cout << *this << endl;
        cout << *this << endl;
        cout << "End." << endl;
*/
    }
    return true;
}
//
//bool AdaptQF::add(BLOCK_TYPE *dataArr, size_t length, size_t qIndex) {
//    return true;
//}
/*
size_t AdaptQF::multiRunShift(size_t emptyQIndex, size_t qIndex, size_t steps) {
    assert(false);
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
