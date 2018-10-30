//
// Created by tomer on 10/25/18.
//

#include "VLHelper.h"

VLHelper::VLHelper(size_t q, size_t r, size_t maxRemainderLength) : depth(1) {
    fVec.push_back(new RegularVLQF(q, r, 3, maxRemainderLength));
}

void VLHelper::add(string *s, size_t level, size_t vLength) {
    if (depth == 1)
        return singleAdd(s, vLength);
    else
        assert(false);
    /*for (size_t i = level; i < depth; ++i) {
        size_t qIndex;
        uint64_t data;
        fVec[i]->convert(s, &qIndex, &data);
        if (fVec[i]->add(s)) {
            memberMap[pair<size_t, size_t>(qIndex, data)] = *s;
            return;
        }
    }*/
}

int VLHelper::lookup(string *s, size_t vLength) {
    if (depth == 1)
        return singleLookup(s, vLength);
    else
        assert(false);
}

ostream &VLHelper::statisticsPrint(ostream &os) {
    for (int i = 0; i < depth; ++i) {
        os << i << ": " << endl;
        this->fVec[i]->statisticsPrint(os);
    }
    return os;
}

void VLHelper::singleAdd(string *s, size_t vLength) {
    size_t qIndex;
    BLOCK_TYPE dataArr[vLength];
    fVec[0]->convert(s, &qIndex, dataArr, vLength);
    cout << "qIndex is:" << qIndex << "\t";
    arrayPrinter(dataArr, vLength);
    fVec[0]->add(dataArr, vLength, qIndex);
    vector<BLOCK_TYPE> tempVec(dataArr, dataArr + vLength);
    memberMap[pair<size_t, vector<BLOCK_TYPE>>(qIndex, tempVec)] = *s;
}

int VLHelper::singleLookup(string *s, size_t vLength) {
    int res = fVec[0]->lookup(s, vLength);
    if (res == 1) {
        size_t qIndex;
        BLOCK_TYPE dataArr[vLength];
        fVec[0]->convert(s, &qIndex, dataArr, vLength);
        vector<BLOCK_TYPE> tempVec(dataArr, dataArr + vLength);
        if (memberMap[pair<size_t, vector<BLOCK_TYPE>>(qIndex, tempVec)] == *s)
            return 2;
        return 1;
    } else if (res == 0)
        return 0;
    else {
        cout << res << endl;
        assert(false);
    }
}

ostream &operator<<(ostream &os, const VLHelper &helper) {
    os << "fVec: " << endl;
    uint i = 0;
    for (auto vec : helper.fVec) {
        cout << "i: " << endl;
        vec->elementPrint(os);
        vec->elementPrintDec(os);
        arrayPrinter(vec->getA(), vec->getSize());
    }
    return os;
}

void VLHelper::testAdd(BLOCK_TYPE *dataArr, size_t length, size_t qIndex) {
//    cout << "qIndex is:" << qIndex << "\t";
//    arrayPrinter(dataArr, length);
    fVec[0]->add(dataArr, length, qIndex);
//    vector<BLOCK_TYPE> tempVec(dataArr, dataArr + length);
}

bool VLHelper::testLookup(BLOCK_TYPE *dataArr, size_t length, size_t qIndex) {
    return fVec[0]->lookup(dataArr, length, qIndex, nullptr) != 0;
 /*   if (res == 1) {
        size_t qIndex;
        BLOCK_TYPE dataArr[vLength];
        fVec[0]->convert(s, &qIndex, dataArr, vLength);
        vector<BLOCK_TYPE> tempVec(dataArr, dataArr + vLength);
        if (memberMap[pair<size_t, vector<BLOCK_TYPE>>(qIndex, tempVec)] == *s)
            return 2;
        return 1;
    } else if (res == 0)
        return 0;
    else {
        cout << res << endl;
        assert(false);
    }*/
}
