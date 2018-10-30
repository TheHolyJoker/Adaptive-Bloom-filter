//
// Created by tomer on 10/25/18.
//

#include "VLTests.h"

bool VLtpLookup(size_t q, size_t r, size_t elNum, size_t vLength) {
    assert(elNum <= SL(q));
    set<string> memberSet;
    setInit(elNum, &memberSet);
    VLHelper vh(q, r, vLength + 1);

    size_t c = 0;
    for (auto s: memberSet) {
        vh.add(&s, 0, vLength);
        if (!vh.lookup(&s, vLength)) {
            vh.lookup(&s, vLength);
            assert(false);
        }
        ++c;
    }

    /*for (auto s: memberSet)
        vh.add(&s, 0, vLength);

//    h.statisticsPrint();
    for (auto s: memberSet) {
        if (!vh.lookup(&s, vLength)) {
            vh.lookup(&s, vLength);
            assert(false);
        }
    }*/
//    h.statisticsPrint();
    cout << "Pass tp_lookup" << endl;
}

void vlt1() {
    const int length = 4;
    const int elNum = 3;
    const uint q = 4;
    const uint r = 4;
    VLHelper h(q, r, length + 1);
//    RegularVLQF vq(q, r, 3, length + 1);
    cout << h << endl;
    string A[elNum] = {"a", "b", "c"};
    for (auto &i : A) {
        h.add(&i, 0, length);
        cout << h << endl;
    }
//    vq.convert()
}

void vlt2() {
    const int length = 3;
    const int elNum = 3;
    const uint q = 4;
    const uint r = 4;
    VLHelper h(q, r, length + 1);
    cout << h << endl;
    uint index[elNum];
    BLOCK_TYPE data[elNum][length];
    for (int i = 0; i < elNum; ++i) {
        for (int j = 0; j < length; ++j) {
            data[i][j] = i * elNum + j;
        }
    }
    for (int k = 0; k < elNum; ++k) {
        index[k] = k * elNum;
    }
    for (int k = 0; k < elNum; ++k) {
        h.testAdd(data[k], length, index[k]);
        cout << h << endl;
    }
//    BLOCK_TYPE res[7] = {2088, 37316, 19098, 14980, 0, 0, 0};
//    vq.convert()
}

void vlt3() {
    const int length = 5;
    const int elNum = 2;
    const uint q = 4;
    const uint r = 4;
    VLHelper h(q, r, length + 1);
    cout << h << endl;
    uint index[elNum] = {3, 5};
    BLOCK_TYPE data1[length] = {15, 14, 13, 12, 11};
    BLOCK_TYPE data2[length] = {2, 3, 4, 5, 6};
    /*BLOCK_TYPE data[elNum][length];
    for (int i = 0; i < elNum; ++i) {
        for (int j = 0; j < length; ++j) {
            data[i][j] = i * elNum + j;
        }
    }
    for (int k = 0; k < elNum; ++k) {
        index[k] = k * elNum;
    }*/
    h.testAdd(data1, length, index[0]);
    cout << h << endl;
    h.testAdd(data2, length, index[1]);
    cout << h << endl;
    /*
    for (int k = 0; k < elNum; ++k) {
        h.testAdd(data[k], length, index[k]);
        cout << h << endl;
    }
*/
//    BLOCK_TYPE res[7] = {2088, 37316, 19098, 14980, 0, 0, 0};
//    vq.convert()
}

void vlt4() {
    const int vLength = 5;
    const int elNum = 4;
    const uint q = 4;
    const uint r = 4;
    VLHelper h(q, r, vLength + 1);
    cout << h << endl;
    BLOCK_TYPE elements[elNum][vLength] = {{15, 10, 5,  10, 14},
                                           {16, 18, 14, 1,  22},
                                           {26, 29, 11, 22, 21},
                                           {14, 1,  27, 7,  9}};
    uint indexes[elNum] = {1, 14, 7, 1};
    uint badLookups = 0;
    for (int i = 0; i < elNum; ++i) {
        h.testAdd(elements[i], vLength, indexes[i]);
        if (!h.testLookup(elements[i], vLength, indexes[i])) {
            ++badLookups;
            h.testLookup(elements[i], vLength, indexes[i]);
        }
        cout << h << endl;
    }

    if (!badLookups) {
        cout << "Passed vlt4." << endl;
        return;
    }
    cout << endl << endl << badLookups << " bad Lookups." << endl;
}

void vlt5() {
    /*[11, 18, 13]
    [6, 27, 20]
    [20, 17, 14]
    [2, 20, 1]

    Indexes:
    [1, 13, 12, 7]*/

    const int vLength = 3;
    const int elNum = 4;
    const uint q = 4;
    const uint r = 4;
    VLHelper h(q, r, vLength + 1);
    cout << h << endl;
    BLOCK_TYPE elements[elNum][vLength] = {{11, 2,  13},
                                           {6,  11, 4},
                                           {4,  1,  14},
                                           {2,  4,  1,}};
    uint indexes[elNum] = {1, 13, 12, 7};
    uint badLookups = 0;
    for (int i = 0; i < elNum; ++i) {
        h.testAdd(elements[i], vLength, indexes[i]);
        if (!h.testLookup(elements[i], vLength, indexes[i])) {
            ++badLookups;
            h.testLookup(elements[i], vLength, indexes[i]);
        }
        cout << h << endl;
    }

    if (!badLookups) {
        cout << "Passed vlt4." << endl;
        return;
    }
    cout << endl << endl << badLookups << " bad Lookups." << endl;
}

void vlt6() {
    /*[11, 18, 13]
    [6, 27, 20]
    [20, 17, 14]
    [2, 20, 1]

    Indexes:
    [1, 13, 12, 7]*/
    const int vLength = 3;
    const int elNum = 2;
    const uint q = 3;
    const uint r = 5;
    VLHelper h(q, r, vLength + 1);
//    cout << h << endl;
    BLOCK_TYPE elements[elNum][vLength] = {{3, 7, 15},
                                           {8, 4, 2}};
    uint indexes[elNum] = {1, 2};
    uint badLookups = 0;
    for (int i = 0; i < elNum; ++i) {
        h.testAdd(elements[i], vLength, indexes[i]);
        if (!h.testLookup(elements[i], vLength, indexes[i])) {
            ++badLookups;
            h.testLookup(elements[i], vLength, indexes[i]);
        }
        cout << h << endl;
    }

    if (!badLookups) {
        cout << "Passed vlt4." << endl;
        return;
    }
    cout << endl << endl << badLookups << " bad Lookups." << endl;
}

void vlt7() {
    /*[11, 18, 13]
    [6, 27, 20]
    [20, 17, 14]
    [2, 20, 1]

    Indexes:
    [1, 13, 12, 7]*/
    const int vLength = 3;
    const int elNum = 2;
    const uint q = 3;
    const uint r = 5;
    VLHelper h(q, r, vLength + 1);
//    cout << h << endl;
    BLOCK_TYPE elements[elNum][vLength] = {{3, 7, 15},
                                           {8, 4, 2}};
    uint indexes[elNum] = {2, 1};
    uint badLookups = 0;
    for (int i = 0; i < elNum; ++i) {
        h.testAdd(elements[i], vLength, indexes[i]);
        if (!h.testLookup(elements[i], vLength, indexes[i])) {
            ++badLookups;
            h.testLookup(elements[i], vLength, indexes[i]);
        }
        cout << h << endl;
    }
    
    if (!badLookups) {
        cout << "Passed vlt4." << endl;
        return;
    }
    cout << endl << endl << badLookups << " bad Lookups." << endl;
}
bool vlRandom(size_t q, size_t r, size_t vLength, BLOCK_TYPE reps) {
    VLHelper h(q, r, vLength + 1);
    BLOCK_TYPE elements[reps][vLength];
    for (int i = 0; i < reps; ++i) {
        for (int j = 0; j < vLength; ++j) {
            elements[i][j] = rand() % SL(r);
        }
    }
    size_t indexes[reps];
    for (int k = 0; k < reps; ++k)
        indexes[k] = rand() % SL(q);

//    cout << h << endl;
    uint badLookups = 0;
    for (int i = 0; i < reps; ++i) {
        h.testAdd(elements[i], vLength, indexes[i]);
        if (!h.testLookup(elements[i], vLength, indexes[i])) {
            ++badLookups;
            h.testLookup(elements[i], vLength, indexes[i]);
        }
    }
//    cout << h << endl;

    if (!badLookups) {
        cout << "Passed vlRandom." << endl;
        return true;
    }
    cout << "Elements: " << endl;
    for (int l = 0; l < reps; ++l) {
        arrayPrinter(elements[l], vLength);
    }
    cout << endl << "Indexes: " << endl;
    arrayPrinter(indexes, reps);
    cout << endl << endl << badLookups << " bad Lookups." << endl;
    return false;
    /*qf.add(3, 3);
    qf.add(4, 3);
    qf.add(5, 3);
    qf.add(15, 4);
    if (!qf.lookup(15, 4, nullptr))
        cout << "Error in tr1." << endl;
    assert(qf.lookup(15, 4, nullptr));
    cout << "Passed tr1." << endl;
//    cout << qf.lookup(15, 4, nullptr) << endl;*/
}

void elementInit(BLOCK_TYPE *elements[], size_t vLength, BLOCK_TYPE reps, size_t mod) {

}