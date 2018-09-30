//
// Created by tomer on 9/20/18.
//

#include "testers.h"

string randString(int minLength, int numOfDiffElements, int numOfDiffLength) {
    int len = minLength ^(rand() % numOfDiffLength);
    char s[len];
    for (int i = 0; i < len; ++i) s[i] = numOfDiffElements ^ (rand() % 32);
    s[len] = 0;
    string res(s);
    return res;
}

void setInit(size_t size, set<string> *mySet, int shift, int uni_size) {
    for (int i = 0; i < size; ++i) mySet->insert(randString(shift, uni_size));
}

void HelperTPSetInit(size_t size, Helper *h, set<string> *mySet, int shift, int uni_size) {
    while (mySet->size() < size) {
        string temp = randString(shift, uni_size);
        int index = h->naiveLookup(&temp);
        if (1 == index) mySet->insert(temp);
    }
}

void NonAdaptiveTPSetInit(size_t size, NonAdaptiveHelper *h, set<string> *mySet, int shift, int uni_size) {
    while (mySet->size() < size) {
        string temp = randString(shift, uni_size);
        int index = h->lookup(&temp);
        if (1 == index) mySet->insert(temp);
    }
}

void HelperTNsetInit(size_t size, Helper *h, set<string> *mySet, int shift, int uni_size) {
    size_t c = 0;
    while (c < size) {
        string temp = randString(shift, uni_size);
        if (h->naiveLookup(&temp) == 0) {
            mySet->insert(temp);
            ++c;
        }
    }
}

void NonAdaptiveTNsetInit(size_t size, NonAdaptiveHelper *h, set<string> *mySet, int shift, int uni_size) {
    size_t c = 0;
    while (c < size) {
        string temp = randString(shift, uni_size);
        if (h->lookup(&temp) == 0) {
            mySet->insert(temp);
            ++c;
        }
    }
}

////Helper Tests

ostream &testHelperRates(size_t n, double eps, size_t lookupsNum, int shift, int uni_size, ostream &os) {
    clock_t startRunTime = clock();
    set<string> memberSet, nomSet;

    clock_t t0 = clock();
    setInit(n, &memberSet, shift, uni_size);
    double memberSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);

    t0 = clock();
    Helper h(n, eps);
    double initTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);

    t0 = clock();
    for (auto iter : memberSet) h.add(&iter);
    double insertionTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);

    t0 = clock();
    setInit(lookupsNum, &nomSet, shift, uni_size);
    double nomSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double setRatio = nomSet.size() / (double) lookupsNum;

    // [TN, FP, TP]
    int counter[3] = {0, 0, 0};
    t0 = clock();
    for (auto iter : nomSet) ++counter[h.lookup(&iter)];

    double lookupTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double totalRunTime = (clock() - startRunTime) / ((double) CLOCKS_PER_SEC);


    testPrinter(n, eps, lookupsNum, setRatio, counter, memberSetInitTime, nomSetInitTime,
                initTime, insertionTime, lookupTime, totalRunTime, h.getName(), os);

    os << h;
}

ostream &testHelperFP(size_t n, double eps, size_t lookupsNum, int shift, int uni_size, ostream &os) {
    clock_t startRunTime = clock();

    set<string> memberSet, TNSet;//, naiveLookupSet;

    clock_t t0 = clock();
    setInit(n, &memberSet, shift, uni_size);
    double memberSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);

    t0 = clock();
    Helper h(n, eps);
    double initTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);

    t0 = clock();
    for (string iter : memberSet) h.add(&iter);
    double insertionTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    /*cout << "MY insertion time: " << insertionTime;
    cout << "\t" << (n / insertionTime);
    cout << " el/s" << endl;
*/
/*

    int counter[3] = {0, 0, 0};
    while (TNSet.size() < lookupsNum) {
        string temp = randString(shift, uni_size);
        int index = h.naiveLookup(&temp);
        ++counter[index];
        if (1 == index) TNSet.insert(temp);
    }
    cout << "setSize: " << TNSet.size() << ".\t" << "ratio is:" << TNSet.size() / (double(lookupsNum)) << "\t";
    counterPrinter(counter);
*/
    t0 = clock();
    HelperTPSetInit(lookupsNum, &h, &TNSet, shift, uni_size);
    double TNSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double TNSetRatio = TNSet.size() / (double) lookupsNum;

    /*

    t0 = clock();
    setInit(naiveLim, &naiveLookupSet, shift, uni_size);
    double naiveLookupSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double naiveLookupSetRatio = nomSet.size() / (double) lookupsNum;

*/


    // [TN, FP, TP]
    int counter[3] = {0, 0, 0};
    t0 = clock();
    for (auto iter : TNSet) ++counter[h.lookup(&iter)];
    double lookupTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);


/*


    int counterNaive[3] = {0, 0, 0};
    t0 = clock();
    for (auto iter : naiveLookupSet) ++counterNaive[h.naiveLookup(&iter)];
    double naiveLookupTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);


*/
    double totalRunTime = (clock() - startRunTime) / ((double) CLOCKS_PER_SEC);

    testPrinter(n, eps, lookupsNum, TNSetRatio, counter, memberSetInitTime, TNSetInitTime,
                initTime, insertionTime, lookupTime, totalRunTime, h.getName(), os);

    os << h;
}

ostream &testHelperTP(size_t n, double eps, int shift, int uni_size, ostream &os) {
    clock_t startRunTime = clock();
    set<string> memberSet;//, nomSet, naiveLookupSet;

    clock_t t0 = clock();
    setInit(n, &memberSet, shift, uni_size);
    double memberSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double memberSetRatio = memberSet.size() / (double) n;

/*

    t0 = clock();
    setInit(lookupsNum, &nomSet, shift, uni_size);
    double nomSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double nomSetRatio = nomSet.size() / (double) lookupsNum;

    t0 = clock();
    setInit(naiveLim, &naiveLookupSet, shift, uni_size);
    double naiveLookupSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double naiveLookupSetRatio = nomSet.size() / (double) lookupsNum;

*/

    t0 = clock();
    Helper h(n, eps);
    double initTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);

    t0 = clock();
    for (auto iter : memberSet) h.add(&iter);
    double insertionTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);


    // [TN, FP, TP]
    int counter[3] = {0, 0, 0};
    t0 = clock();
    for (auto iter : memberSet) ++counter[h.lookup(&iter)];
    double lookupTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
/*


    int counterNaive[3] = {0, 0, 0};
    t0 = clock();
    for (auto iter : naiveLookupSet) ++counterNaive[h.naiveLookup(&iter)];
    double naiveLookupTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);


*/
    double totalRunTime = (clock() - startRunTime) / ((double) CLOCKS_PER_SEC);


    testPrinter(n, eps, n, memberSetRatio, counter, memberSetInitTime, 42,
                initTime, insertionTime, lookupTime, totalRunTime, h.getName(), os);

    os << h;
    return os;

}

ostream &testHelperTN(size_t n, double eps, size_t lookupsNum, int shift, int uni_size, ostream &os) {
    clock_t startRunTime = clock();
    set<string> memberSet, TNSet;//, naiveLookupSet;

    clock_t t0 = clock();
    setInit(n, &memberSet, shift, uni_size);
    double memberSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);

    t0 = clock();
    Helper h(n, eps);
    double initTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);

    t0 = clock();
    for (auto iter : memberSet) h.add(&iter);
    double insertionTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);


    t0 = clock();
    HelperTNsetInit(lookupsNum, &h, &TNSet, shift, uni_size);
    double TNSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double TNSetRatio = TNSet.size() / double(lookupsNum);
/*
    double nomSetRatio = nomSet.size() / (double) lookupsNum;

    t0 = clock();
    setInit(naiveLim, &naiveLookupSet, shift, uni_size);
    double naiveLookupSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double naiveLookupSetRatio = nomSet.size() / (double) lookupsNum;

*/


    // [TN, FP, TP]
    int counter[3] = {0, 0, 0};
    t0 = clock();
    for (auto iter : TNSet) ++counter[h.lookup(&iter)];
    double lookupTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);


/*


    int counterNaive[3] = {0, 0, 0};
    t0 = clock();
    for (auto iter : naiveLookupSet) ++counterNaive[h.naiveLookup(&iter)];
    double naiveLookupTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);


*/
    double totalRunTime = (clock() - startRunTime) / ((double) CLOCKS_PER_SEC);

    testPrinter(n, eps, lookupsNum, TNSetRatio, counter, memberSetInitTime, TNSetInitTime,
                initTime, insertionTime, lookupTime, totalRunTime, h.getName(), os);
    os << h;
    return os;
}


////NonAdaptiveHelper Tests

ostream &testNonAdaptiveRates(size_t n, double eps, size_t lookupsNum, int shift, int uni_size, ostream &os) {
    clock_t startRunTime = clock();
    set<string> memberSet, nomSet;

    clock_t t0 = clock();
    setInit(n, &memberSet, shift, uni_size);
    double memberSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);

    t0 = clock();
    setInit(lookupsNum, &nomSet, shift, uni_size);
    double nomSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double setRatio = nomSet.size() / (double) lookupsNum;

    t0 = clock();
    NonAdaptiveHelper h(n, eps);
    double initTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);

    t0 = clock();
    for (auto iter : memberSet) h.add(&iter);
    double insertionTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);



    // [TN, FP, TP]
    int counter[3] = {0, 0, 0};
    t0 = clock();
    for (auto iter : nomSet) ++counter[h.lookup(&iter)];

    double lookupTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double totalRunTime = (clock() - startRunTime) / ((double) CLOCKS_PER_SEC);

    testPrinter(n, eps, lookupsNum, setRatio, counter, memberSetInitTime, nomSetInitTime,
                initTime, insertionTime, lookupTime, totalRunTime, h.getName(), os);

    os << h;
    return os;
}

ostream &testNonAdaptiveFP(size_t n, double eps, size_t lookupsNum, int shift, int uni_size, ostream &os) {
    clock_t startRunTime = clock();
    set<string> memberSet, TNSet;//, naiveLookupSet;

    clock_t t0 = clock();
    setInit(n, &memberSet, shift, uni_size);
    double memberSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);

    t0 = clock();
    NonAdaptiveHelper h(n, eps);
    double initTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);

    t0 = clock();
    for (auto iter : memberSet) h.add(&iter);
    double insertionTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);


    t0 = clock();
    NonAdaptiveTPSetInit(lookupsNum, &h, &TNSet, shift, uni_size);
    double TNSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double TNSetRatio = TNSet.size() / (double) lookupsNum;

    /*

    t0 = clock();
    setInit(naiveLim, &naiveLookupSet, shift, uni_size);
    double naiveLookupSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double naiveLookupSetRatio = nomSet.size() / (double) lookupsNum;

*/


    // [TN, FP, TP]
    int counter[3] = {0, 0, 0};
    t0 = clock();
    for (auto iter : TNSet) ++counter[h.lookup(&iter)];
    double lookupTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);


/*


    int counterNaive[3] = {0, 0, 0};
    t0 = clock();
    for (auto iter : naiveLookupSet) ++counterNaive[h.naiveLookup(&iter)];
    double naiveLookupTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);


*/
    double totalRunTime = (clock() - startRunTime) / ((double) CLOCKS_PER_SEC);

    testPrinter(n, eps, lookupsNum, TNSetRatio, counter, memberSetInitTime, TNSetInitTime,
                initTime, insertionTime, lookupTime, totalRunTime, h.getName(), os);

    os << h;
    return os;
}

ostream &testNonAdaptiveTP(size_t n, double eps, int shift, int uni_size, ostream &os) {
    clock_t startRunTime = clock();
    set<string> memberSet;//, nomSet, naiveLookupSet;

    clock_t t0 = clock();
    setInit(n, &memberSet, shift, uni_size);
    double memberSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double memberSetRatio = memberSet.size() / (double) n;

/*

    t0 = clock();
    setInit(lookupsNum, &nomSet, shift, uni_size);
    double nomSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double nomSetRatio = nomSet.size() / (double) lookupsNum;

    t0 = clock();
    setInit(naiveLim, &naiveLookupSet, shift, uni_size);
    double naiveLookupSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double naiveLookupSetRatio = nomSet.size() / (double) lookupsNum;

*/

    t0 = clock();
    NonAdaptiveHelper h(n, eps);
    double initTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);

    t0 = clock();
    for (auto iter : memberSet) h.add(&iter);
    double insertionTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);


    // [TN, FP, TP]
    int counter[3] = {0, 0, 0};
    t0 = clock();
    for (auto iter : memberSet) ++counter[h.lookup(&iter)];
    double lookupTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
/*


    int counterNaive[3] = {0, 0, 0};
    t0 = clock();
    for (auto iter : naiveLookupSet) ++counterNaive[h.naiveLookup(&iter)];
    double naiveLookupTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);


*/
    double totalRunTime = (clock() - startRunTime) / ((double) CLOCKS_PER_SEC);


    testPrinter(n, eps, n, memberSetRatio, counter, memberSetInitTime, 42,
                initTime, insertionTime, lookupTime, totalRunTime, h.getName(), os);

    os << h;
    return os;
}

ostream &testNonAdaptiveTN(size_t n, double eps, size_t lookupsNum, int shift, int uni_size, ostream &os) {
    clock_t startRunTime = clock();
    set<string> memberSet, TNSet;//, naiveLookupSet;

    clock_t t0 = clock();
    setInit(n, &memberSet, shift, uni_size);
    double memberSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);

    t0 = clock();
    NonAdaptiveHelper h(n, eps);
    double initTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);

    t0 = clock();
    for (auto iter : memberSet) h.add(&iter);
    double insertionTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);


    t0 = clock();
    NonAdaptiveTNsetInit(lookupsNum, &h, &TNSet, shift, uni_size);
    double TNSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double TNSetRatio = TNSet.size() / double(lookupsNum);
/*
    double nomSetRatio = nomSet.size() / (double) lookupsNum;

    t0 = clock();
    setInit(naiveLim, &naiveLookupSet, shift, uni_size);
    double naiveLookupSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double naiveLookupSetRatio = nomSet.size() / (double) lookupsNum;

*/


    // [TN, FP, TP]
    int counter[3] = {0, 0, 0};
    t0 = clock();
    for (auto iter : TNSet) ++counter[h.lookup(&iter)];
    double lookupTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);


/*


    int counterNaive[3] = {0, 0, 0};
    t0 = clock();
    for (auto iter : naiveLookupSet) ++counterNaive[h.naiveLookup(&iter)];
    double naiveLookupTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);


*/
    double totalRunTime = (clock() - startRunTime) / ((double) CLOCKS_PER_SEC);

    testPrinter(n, eps, lookupsNum, TNSetRatio, counter, memberSetInitTime, TNSetInitTime,
                initTime, insertionTime, lookupTime, totalRunTime, h.getName(), os);
    os << h;
    return os;
}



//// Function for printing.
ostream &counterPrinter(ostream &os, int *counter) {
    os << "[trueNegative, falsePositive, truePositive]" << "\t[" << counter[0] << ", " << counter[1] << " ,"
       << counter[2] << "]" << endl;
    return os;
}


ostream &
testPrinter(size_t n, double eps, size_t lookupsNum, double setRatio, int *counter, double memberSetInitTime,
            double nomSetInitTime, double initTime, double insertionTime, double lookupTime, double totalRunTime,
            const string name, ostream &os) {
    counterPrinter(os, counter);
    double ans = ((double) counter[1]) / lookupsNum;
    os << "memberSetInitTime: " << memberSetInitTime << endl;
    os << "nomSetInitTime: " << nomSetInitTime << endl;
    os << "nomSet to lookupsNum ratio : " << setRatio << endl << endl;
    os << "False positive rate:" << ans;
    os << "\tExpected: " << eps << ". Error div(in % as eps): " << 100 * (ans - eps) / eps << "%" << endl;
    os << name << " initTime: " << initTime << endl;
    cout << name << " insertionTime: " << insertionTime << "\t" << n / insertionTime << " el/sec" << endl;
    os << name << " insertionTime: " << insertionTime << "\t" << n / insertionTime << " el/sec" << endl;
    cout << name << " lookupTime: " << lookupTime << "\t" << lookupsNum / lookupTime << " el/sec" << endl << endl;
    os << name << " lookupTime: " << lookupTime << "\t" << lookupsNum / lookupTime << " el/sec" << endl << endl;
    os << "totalRunTime: " << totalRunTime << endl;
    return os;
//    ((double) n) / HelperInitTime << "el per sec" << endl;
}


void speedPrinter(size_t n, size_t lookupsNum, size_t naiveLim, double nomSetRatio, double naiveLookupSetRatio,
                  double insertionTime, double lookupTime, double naiveLookupTime, double totalRunTime, string name) {
    if (nomSetRatio < 1) cout << "nomSet to lookupsNum ratio : " << nomSetRatio << endl;
    if (naiveLookupSetRatio < 1) cout << "onlyLookupSet to lookupsNum ratio : " << naiveLookupSetRatio << endl;
//    cout << name << " initTime: " << initTime << endl;
    cout << name << " insertionTime: " << insertionTime << "\t" << n / insertionTime << " el/sec" << endl;
    cout << name << " lookupTime: " << lookupTime << "\t" << lookupsNum / lookupTime << " el/sec" << endl;
    cout << name << " naiveLookupTime: " << naiveLookupTime << "\t" << naiveLim / naiveLookupTime << " el/sec" << endl
         << endl;
    cout << "totalRunTime: " << totalRunTime << endl;

}

void TPPrinter(size_t n, double initTime, double insertionTime, double totalRunTime, string name) {
    /*counterPrinter(counter);
    counterPrinter(naiveLookupCounter);
    double ans1 = ((double) counter[1]) / lookupsNum;
    double ans2 = ((double) naiveLookupCounter[1]) / naiveLim;
    cout << "memberSetInitTime: " << memberSetInitTime << endl;
    cout << "nomSetInitTime: " << nomSetInitTime << "\t";
    cout << "nomSet to lookupsNum ratio : " << nomSetRatio << endl;
    cout << "naiveLookupSetInitTime: " << naiveLookupSetInitTime << "\t";
    cout << "onlyLookupSet to lookupsNum ratio : " << naiveLookupSetRatio << endl << endl;
    cout << "False positive rate:" << ans1;
    cout << "\tExpected: " << eps << ". Error div(in % as eps): " << 100 * (ans1 - eps) / eps << "%" << endl;
    cout << "False positive rate:" << ans2;
    cout << "\tExpected: " << eps << ". Error div(in % as eps): " << 100 * (ans2 - eps) / eps << "%" << endl;
    */
    cout << name << " initTime: " << initTime << endl;
    cout << name << " insertionTime: " << insertionTime << "\t" << n / insertionTime << " el/sec" << endl;
    /*cout << name << " lookupTime: " << lookupTime << "\t" << lookupsNum / lookupTime << " el/sec" << endl;
    cout << name << " naiveLookupTime: " << naiveLookupTime << "\t" << naiveLim / naiveLookupTime << " el/sec" << endl
         << endl;
    */
    cout << "totalRunTime: " << totalRunTime << endl;

}




