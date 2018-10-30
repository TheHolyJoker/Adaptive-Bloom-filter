//
// Created by tomer on 10/22/18.
//

#include "Tests.h"


string randString(int minWordLength, int charsNum, int numOfDiffLength) {
    int len = minWordLength bitor (rand() % numOfDiffLength);
    assert(4 < len);
    char s[len];
    for (int i = 0; i < len; ++i) s[i] = 64 bitor (rand() % charsNum);
    s[len] = 0;
    string res(s);
    return res;
}

void setInit(size_t size, set<string> *mySet, int minWordLength, int charsNum) {
    for (int i = 0; i < size; ++i) mySet->insert(randString(minWordLength, charsNum));
    if (mySet->size() / double(size) < 1)
        cout << "setInit ratio is: " << (mySet->size() / double(size) < 1) << endl;

}

/*

bool tpLookup(size_t q, size_t r, size_t mbSize, size_t elNum)
{
    assert(elNum <= SL(q));
    set<string> memberSet;
    setInit(elNum, &memberSet);
    RegularQF rqf(q, r);
    for (auto s: memberSet)
        rqf.add(&s);
    for (auto s: memberSet)
    {
        if (!rqf.lookup(&s))
        {
            rqf.lookup(&s);
            assert(false);
        }
    }
    cout << "Pass tp_lookup" << endl;
}
*/


bool hTPLookup(size_t q, size_t r, size_t mbSize, size_t elNum) {
    assert(elNum <= SL(q));
    set<string> memberSet;
    setInit(elNum, &memberSet);
    Helper h(q, r);

/*
    size_t counter = 0;
    for (auto s: memberSet) {
        h.add(&s);
        if(!h.lookup(&s))
        {
            h.lookup(&s);
            assert(false);
        }
        ++counter;
    }
*/
    for (auto s: memberSet)
        h.add(&s);

    h.statisticsPrint();
    for (auto s: memberSet) {
        if (!h.lookup(&s)) {
            h.lookup(&s);
            assert(false);
        }
    }
//    h.statisticsPrint();
    cout << "Pass tp_lookup" << endl;
}

bool sanity(size_t q, size_t r, size_t mbSize, size_t elNum) {
    assert(elNum <= SL(q));
    set<string> mySet;
    setInit(elNum, &mySet);
    Helper h(q, r);
    for (auto s: mySet) {
        if (h.lookup(&s)) {
            h.lookup(&s);
            assert(false);
        }
    }
    cout << "Pass sanity_lookup" << endl;
}

int statusCorrectness(size_t q, size_t r, size_t elementNum) {
    assert(elementNum <= SL(q));
    set<string> memberSet;
    setInit(elementNum, &memberSet);
    Helper h(q, r, true);
    for (auto s: memberSet)
        h.add(&s);
    h.statusCorrectness();
}

ostream &rates(size_t q, size_t r, double loadFactor, size_t lookupReps, ostream &os) {
    clock_t t0 = clock(), temp;
    Helper h(q, r);
    double qfInitTime = TIME_PASSED_FROM(t0);

    size_t setSize = size_t(ceil(SL(q) * loadFactor));
    set<string> memberSet, lookupSet;
    temp = clock();
    setInit(setSize, &memberSet);
    double memberSetInitTime = TIME_PASSED_FROM((temp));

    if (memberSet.size() / double(setSize) < 1)
        cout << "memberSet Ratio to setSize is :" << memberSet.size() / double(setSize) << endl;
    temp = clock();
    setInit(lookupReps, &lookupSet);
    double lookupSetInitTime = TIME_PASSED_FROM((temp));

    if (lookupSet.size() / double(setSize) < 1)
        cout << "lookupSet Ratio to lookupReps is :" << lookupSet.size() / double(lookupReps) << endl;
    temp = clock();
    for (auto s: memberSet)
        h.add(&s);
    double insertionTime = TIME_PASSED_FROM((temp));

    temp = clock();
    for (auto s: lookupSet)
        h.lookup(&s);
    cout << "First lookup time is: " << TIME_PASSED_FROM((temp)) << endl;


    // [TN, FP, TP]
    int counter[3] = {0};
    temp = clock();
    for (auto s: lookupSet)
        ++counter[h.lookup(&s)];
    double lookupTime = TIME_PASSED_FROM((temp));


    getStats(qfInitTime, memberSetInitTime, lookupSetInitTime, insertionTime, lookupTime,
             setSize, lookupReps, counter, os);
    os << 1.0 / (1ULL << r) << endl;
    os << "Total run time: " << TIME_PASSED_FROM(t0) << endl;
    return os;
}

void hpAdaptiveTest(size_t q, size_t r, size_t elementNum, size_t lookupReps) {
    Helper hp(q, r, true);
    set<string> memberSet, lookupSet;
    setInit(elementNum, &memberSet);
    setInit(lookupReps, &lookupSet);

    for (auto s: memberSet)
        hp.add(&s);

    hp.statisticsPrint();

    int counter[3] = {0};
    for (auto s: lookupSet)
        ++counter[hp.lookup(&s)];
    counterPrinter(counter, cout);
    cout << 1.0 / (1ULL << r) << endl;
    hp.statisticsPrint();


    counter[0] = counter[1] = counter[2] = 0;
    for (auto s: lookupSet)
        ++counter[hp.lookup(&s)];
    counterPrinter(counter, cout);
    cout << 0 << endl;

}


ostream &
getStats(double qfInitTime, double memberSetInitTime, double lookupSetInitTime, double insertionTime, double lookupTime,
         size_t memberSetSize, size_t lookupReps, int *counter, ostream &os) {
    os << "qfInitTime: " << qfInitTime << endl;
    os << "memberSetInitTime: " << memberSetInitTime << endl;
    os << "lookupSetInitTime: " << lookupSetInitTime << endl;
    double insertionRatio = memberSetSize / insertionTime;
    os << "insertionTime: " << insertionTime << "\tSpeed: " << insertionRatio << " el/s" << endl;
    double lookupRatio = lookupReps / lookupTime;
    os << "lookupTime: " << lookupTime << "\tSpeed: " << lookupRatio << " el/s" << endl;
    counterPrinter(counter, os);
    return os;
}

ostream &counterPrinter(int *counter, ostream &os) {
    os << "[TN, FP, TP]" << "\t";
    os << "[" << counter[0] << ", " << counter[1] << ", " << counter[2] << "]";
    double sum = counter[0] + counter[1] + counter[2];
    os << "\t FP ratio:" << (counter[1] / sum) << "\t expected: ";

}


void VLFingerPrint(size_t q, size_t r, size_t elNum) {
    assert(elNum <= SL(q));
    set<string> memberSet;
    setInit(elNum, &memberSet);
    Helper h(q, r);

/*
    size_t counter = 0;
    for (auto s: memberSet) {
        h.add(&s);
        if(!h.lookup(&s))
        {
            h.lookup(&s);
            assert(false);
        }
        ++counter;
    }
*/
    for (auto s: memberSet)
//        h.add(&s, 0, 2);

    h.statisticsPrint();
//    for (auto s: memberSet) {
//        if (!h.lookup(&s)) {
//            h.lookup(&s);
//            assert(false);
//        }
//    }
//    h.statisticsPrint();
//    cout << "Pass tp_lookup" << endl;
}
