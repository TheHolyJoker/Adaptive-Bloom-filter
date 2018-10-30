//
// Created by tomer on 10/22/18.
//

#include "paTests.h"

/*

void simple_tp_lookup(size_t cap, size_t dataSize, const size_t elementNum) {
    assert(elementNum <= cap);
    size_t indexList[elementNum];
    BLOCK_TYPE dataList[elementNum];
    for (int i = 0; i < elementNum; ++i) {
        indexList[i] = (rand() % cap);
        dataList[i] = (rand() % MASK(dataSize));
    }
    QF qf(cap, dataSize);
    for (int j = 0; j < elementNum; ++j)
        rqf.add(indexList[j], dataList[j]);
    for (int j = 0; j < elementNum; ++j) {
        if (!qf.lookup(indexList[j], dataList[j])) {
            elPrint(indexList, dataList, elementNum);
            cout << endl;
            cout << "Failed in simple_tp" << endl;
            return;
        }
    }
    cout << "Passed simple_tp" << endl;
}
*/
/*
void ta1() {
    RegularQF rqf(3, 6, nullptr);
    BLOCK_TYPE temp = (MASK(5) ^ 4);
    rqf.add(temp, 0);
    BLOCK_TYPE res[2] = {28160, 0};
//    BLOCK_TYPE *nom = qfArray.getA().getA();
    if (compareArray(rqf.getA(), res, 2)) {
        cout << "Pass ta1" << endl;
        return;
    }
    cout << "Failed ta1" << endl;
}

void ta2() {
    RegularQF rqf(5, 6, nullptr);
    const size_t elNum = 4;
    size_t indexList[elNum] = {0, 0, 0, 4};
    BLOCK_TYPE dataList[elNum] = {(MASK(5) ^ 4), 15, MASK(6), 9};
    for (int i = 0; i < elNum; ++i) {
        rqf.add(dataList[i], indexList[i]);
    }
    elPrint(indexList, dataList, elNum);
    rqf.elementOnlyPrint(cout);
//    string sRes = "[0:(001111,100),1:(011011,011),2:(111111,011),3:(000000,000),4:(001001,100),5:(000000,000),6:(000000,000),7:(000000,000),]";
//    cout << sRes << endl;
//    cout << rqf << endl;
//    BLOCK_TYPE res[elNum] = {15899, 28632, 38, 0};
//    if (compareArray(rqf.getA(), res, elNum)) {
//        cout << "Pass ta2" << endl;
//        return;
//    }
//    cout << "Failed ta2" << endl;
}

void ta3() {
    RegularQF rqf(5, 6, nullptr);
    const size_t elNum = 4;
    size_t indexList[elNum] = {2, 2, 2, 2};
    BLOCK_TYPE dataList[elNum] = {1, 2, 3, 4};
    elPrint(indexList, dataList, elNum);
    for (int i = 0; i < elNum; ++i) {
        rqf.add(dataList[i], indexList[i]);
        rqf.elementOnlyPrint();
    }
//        cout << qfArray << endl;
    BLOCK_TYPE res[elNum] = {4480, 96, 9741, 32768};
    if (compareArray(rqf.getA(), res, elNum)) {
        cout << "Pass ta3" << endl;
        return;
    }
    cout << "Failed ta3" << endl;
}

void ta4() {
    RegularQF rqf(8, 6, 3);
    const size_t elNum = 5;
    size_t indexList[elNum] = {1, 6, 6, 6, 6};
    BLOCK_TYPE dataList[elNum] = {1, 10, 11, 5, MASK(5)};
    for (int i = 0; i < elNum; ++i) {
        rqf.add(dataList[i], indexList[i]);
    }
//    cout << qfArray << endl;
    BLOCK_TYPE res[elNum] = {11679, 57416, 0, 1, 24742};
    if (compareArray(rqf.getA(), res, elNum)) {
        cout << "Pass ta4" << endl;
        return;
    }
    cout << "Failed ta4" << endl;
}

void ta5() {
    PackedArray rqf(5, 6, 3);
    const size_t elNum = 4;
    size_t indexList[elNum] = {1, 3, 3, 4};
    BLOCK_TYPE dataList[elNum] = {1, 3, 7, MASK(6)};
    for (int i = 0; i < elNum; ++i) {
        rqf.add(dataList[i], indexList[i]);
    }
//    cout << qfArray << endl;
    BLOCK_TYPE res[elNum] = {64641, 32768, 14367, 32768};
    if (compareArray(rqf.getA(), res, elNum)) {
        cout << "Pass ta5" << endl;
        return;
    }
    cout << "Failed ta5" << endl;
}

void ta6() {
    RegularQF rqf(5, 6, nullptr);
    const size_t elNum = 4;
    size_t indexList[elNum] = {0, 3, 3, 4};
    BLOCK_TYPE dataList[elNum] = {1, 3, 7, MASK(6)};
    for (int i = 0; i < elNum; ++i) {
        rqf.add(dataList[i], indexList[i]);
//        qf.elementOnlyPrint(cout);
    }
//    elPrint(indexList, dataList, elNum);
//    cout << qf << endl;
    BLOCK_TYPE res[elNum] = {65153, 8192, 14367, 32768};
    passCheck(rqf.getA(), res, elNum, "ta6");
}

void tan6() {
    RegularQF rqf(5, 6, nullptr);
    const size_t elNum = 4;
    size_t indexList[elNum] = {0, 3, 3, 4};
    BLOCK_TYPE dataList[elNum] = {1, 3, 7, MASK(6)};
//    cout << qf << endl;
    for (int i = 0; i < elNum; ++i) {
        rqf.add(dataList[i], indexList[i]);
//        cout << qf << endl;
//        qf.elementPrint(cout);
    }
//    elPrint(indexList, dataList, elNum);
//    cout << qf << endl;
    BLOCK_TYPE res[elNum] = {65154, 16385, 49656};
    passCheck(rqf.getA(), res, elNum, "ta6");
}


void tl1() {
    RegularQF rqf(8, 6, nullptr);
    const size_t elNum = 5;
//    [(2, 18), (6, 23), (3, 12), (1, 8), (1, 24)]
    size_t indexList[elNum] = {2, 6, 3, 1, 1};
    BLOCK_TYPE dataList[elNum] = {18, 23, 12, 8, 24};
    for (int i = 0; i < elNum; ++i) {
        rqf.add(dataList[i], indexList[i]);
    }
//    elPrint(indexList, dataList, elNum);
//    cout << qf << endl;
    cout << "FP list: ";
    for (int i = 0; i < elNum; ++i) {
        if (rqf.lookup(dataList[i], indexList[i])) {
            rqf.lookup(dataList[i], indexList[i]);
            cout << "(" << indexList[i] << "," << dataList[i] << " ), ";
        }
    }
    cout << endl;
//    BLOCK_TYPE res[elNum] = {65153, 8192, 14367, 32768};
//    passCheck(qfArray.getA().getA(), res, elNum, "ta5");

}

void tGet1() {
    size_t length = 4;
    const size_t n = 4;
    BLOCK_TYPE a = 0;
    for (int i = 1; i < n; ++i) {
        a += (1ULL << (n - i));
        a <<= length;
    }
    ++a;
    BLOCK_TYPE A[1];
    A[0] = a;
    PackedArray mp(n, length, 0, A);
    cout << mp << endl;
    BLOCK_TYPE r[n];
    for (int i = 0; i < n; ++i)
        r[i] = mp.get_bits(n * i, length);

    BLOCK_TYPE res[n] = {8, 4, 2, 1};
    for (int i = 0; i < n; ++i)
        assert(r[i] == res[i]);

    cout << "pass tGet1" << endl;
}

void tGet2() {
    size_t length = 10;
    size_t n = 4;
    BLOCK_TYPE A[3] = {64, 1048, 124};
//    A[0] = (1ULL << 6);
//    A[1] = (1ULL << 10) + (1ULL << 4) + (1ULL << 3);
//    A[2] = (1ULL << 7) + 6;
    PackedArray mp(n, length, 0, A);
    cout << mp << endl;
    BLOCK_TYPE r[4];
    for (int i = 0; i < n; ++i)
        r[i] = mp.get_bits(length * i, length);

    arrayPrinter(r, 4);
    BLOCK_TYPE res[4] = {1, 0, 262, 0};
    for (int i = 0; i < n; ++i)
        assert(r[i] == res[i]);

    cout << "pass tGet2" << endl;
}

void tGet3() {
    size_t length = 7;
    const size_t n = 8;
    size_t capacity = (n * length) / BLOCK_SIZE;
    if (n * length) ++capacity;
    BLOCK_TYPE A[capacity];
    for (int i = 0; i < capacity; ++i)
        A[i] = rand();
    PackedArray mp(n, length, 0, A);
    cout << mp << endl;
    BLOCK_TYPE resNoms[n];
    for (int i = 0; i < n; ++i)
        resNoms[i] = mp.get_bits(length * i, length);

    BLOCK_TYPE res[n] = {34, 89, 100, 60, 52, 97, 82, 72};
//    arrayPrinter(resNoms, n);
    for (int i = 0; i < n; ++i)
        assert(resNoms[i] == res[i]);

    cout << "pass tGet3" << endl;
}

void tGet4() {
    const size_t n = 30, dataSize = 11;
    BLOCK_TYPE A[21] = {37728, 40870, 51808, 61110, 4949, 37018, 51904, 9350, 29677, 18180, 61692, 5973, 60255, 933,
                        57031, 17042, 20006, 20956, 25768, 60265, 14159};
    BLOCK_TYPE res[n] = {1179, 39, 1869, 1190, 119, 728, 618, 1424, 1238, 688, 73, 103, 502, 1308, 158, 252, 186, 1402,
                         1726, 58, 751, 797, 82, 590, 306, 1143, 201, 654, 1460, 1245};
    PackedArray mp(n, dataSize, 0, A);
    BLOCK_TYPE resNoms[n];
    for (int i = 0; i < n; ++i)
        resNoms[i] = mp.get_bits(dataSize * i, dataSize);

    for (int i = 0; i < n; ++i)
        assert(resNoms[i] == res[i]);

    cout << "pass tGet4" << endl;
}

void tSet1() {
    const size_t n = 4, length = 4;
    BLOCK_TYPE res[n] = {8, 4, 2, 1};
    PackedArray mp(n, length, 0, nullptr);
    cout << mp << endl;
    for (int i = 0; i < n; ++i) {
        mp.set_bits(i * length, length, res[i]);
        cout << mp << endl;
    }

    for (int i = 0; i < n; ++i)
        cout << mp.get_bits(length * i, length) << endl;

}

void tSet2() {
    const size_t n = 4, length = 10;
    BLOCK_TYPE res[4] = {1, 0, 262, 0};
    PackedArray mp(n, length, 0, nullptr);
    cout << mp << endl;
    for (int i = 0; i < n; ++i) {
        mp.set_bits(i * length, length, res[i]);
        cout << mp << endl;
    }

    for (int i = 0; i < n; ++i)
        cout << mp.get_bits(length * i, length) << endl;

}

void tSet3() {
    const size_t n = 8, length = 7;
    BLOCK_TYPE res[n] = {34, 89, 100, 60, 52, 97, 82, 72};
    PackedArray mp(n, length, 0, nullptr);
    cout << mp << endl;
    for (int i = 0; i < n; ++i) {
        mp.set_bits(i * length, length, res[i]);
    }
    cout << mp << endl;

    for (int i = 0; i < n; ++i)
        assert(mp.get_bits(length * i, length) == res[i]);
//        cout << mp.get_bits(length * i, length) << endl;
}

void tSet4() {
    const size_t n = 30, length = 11;
    BLOCK_TYPE res[n] = {1179, 39, 1869, 1190, 119, 728, 618, 1424, 1238, 688, 73, 103, 502, 1308, 158, 252, 186, 1402,
                         1726, 58, 751, 797, 82, 590, 306, 1143, 201, 654, 1460, 1245};
    PackedArray mp(n, length, 0, nullptr);
    cout << mp << endl;
    for (int i = 0; i < n; ++i) {
        mp.set_bits(i * length, length, res[i]);
    }
    cout << mp << endl;

    for (int i = 0; i < n; ++i)
        assert(mp.get_bits(length * i, length) == res[i]);
//    cout << mp.get_bits(length * i, length) << endl;

}
*/

/*
void arrayPrinter(BLOCK_TYPE *a, size_t length) {
    cout << "[" << a[0];
    for (int i = 1; i < length; ++i) {
        cout << ", " << a[i];
    }
    cout << "]" << endl;
}
*/

void tr1() {
    const uint q = 4, r = 5, elNum = 4;
    RegularQF qf(q, r);
    qf.add(3, 3);
    qf.add(4, 3);
    qf.add(5, 3);
    qf.add(15, 4);
    if (!qf.lookup(15, 4, nullptr))
        cout << "Error in tr1." << endl;
        assert(qf.lookup(15, 4, nullptr));
    cout << "Passed tr1." << endl;
//    cout << qf.lookup(15, 4, nullptr) << endl;
}


void Printer(int *a, size_t length) {
    cout << "[" << a[0];
    for (int i = 1; i < length; ++i) {
        cout << ", " << a[i];
    }
    cout << "]" << endl;
}

void decTest() {
    const size_t n = 10;
    int a[n] = {0};
    Printer(a, n);

    for (int i = 0; i < n; ++i)
        a[i] = i;
    Printer(a, n);

    for (int i = 0; i < n; ++i) {
        int temp = (n - 1) - i;
//        a[temp] = a[dec(&temp, n)];
    }
    Printer(a, n);

}

void passCheck(BLOCK_TYPE *nom, BLOCK_TYPE *res, size_t elNum, string name) {
    if (compareArray(nom, res, elNum)) {
        cout << "Passed " << name << endl;
        return;
    }
    cout << "Failed " << name << endl;
}


void elPrint(size_t *indexList, BLOCK_TYPE *dataList, size_t size) {
    cout << "[" << "(" << indexList[0] << "," << dataList[0] << ")";
    for (int i = 1; i < size; ++i)
        cout << " ,(" << indexList[i] << "," << dataList[i] << ")";
    cout << "]" << endl;
}

//void callAll() {
//    ta1();
//    ta2();
//    ta3();
//    ta4();
////    ta5();
//    ta6();
//    tl1();
//    tSet1();
//    tSet2();
//    tSet3();
//    tSet4();
//}


