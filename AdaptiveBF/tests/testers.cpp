//
// Created by tomer on 9/20/18.
//

#include "testers.h"
//
//char* randChar(int shift, int uni_size, int multiRatio) {
//    char temp = rand() % multiRatio;
//    int len = ++temp << shift;
//    char *s = new char[len];
//    for (int i = 0; i < len; ++i) s[i] = 64 ^ (rand() % 64);
//    s[len] = 0;
//    return s;
////    string res(s);
//}

void charSetInit(size_t size, set<string> *mySet, int shift, int uni_size, int multiRatio) {
    for (int i = 0; i < size; ++i) {
        char temp = rand() % multiRatio;
        int len = ++temp << shift;
        char s[len];// = new char[len];
        for (int j = 0; j < len; ++j) s[j] = 64 ^ (rand() % 64);
        s[len] = 0;
        mySet->insert(s);
    }
}

string randString(int shift, int uni_size, int multiRatio) {
    assert(multiRatio == 4 && shift > 5);
    int temp = rand() % multiRatio;
    int len = ((++temp) << shift);
    char s[len];
    for (int i = 0; i < len; ++i) s[i] = 64 ^ (rand() % 64);
    s[len] = 0;
    string res(s);
    return res;
/*
        bool cond = (temp >= 0 && temp <= 4);
    if (!cond)
    {
        cout << temp;
        assert(false);
    }
    if(len <= 6)
    {
        cout << len << ", ";
        cout << len << ", ";
        cout << len << ", ";
        cout << len << ", ";
        cout << len << ", ";
        assert(false);
    }
*/
}

void sameString(size_t lim, int shift, int uni_size) {
    clock_t t0 = clock();
    set<string> mySet;
    size_t c = 0;
    string temp;
    while (c == mySet.size() && ++c < lim) mySet.insert(randString(shift, uni_size));

    cout << "setSize: " << mySet.size() << ".\t" << "ratio is:" << mySet.size() / (double(lim)) << "\t";
    if (c < lim) cout << "Stopped after" << c << " times, with:" << temp << endl;
    else cout << "No repetition." << endl;
    double runTime = (clock() - t0) / (double(CLOCKS_PER_SEC));
    cout << "runTime: " << runTime << endl;
}

void setInit(size_t size, set<string> *mySet, int shift, int uni_size) {
    for (int i = 0; i < size; ++i) mySet->insert(randString(shift, uni_size));
}

void HelperSpecificSetInit(size_t size, Helper *h, set<string> *mySet, int shift, int uni_size) {
//    size_t m = 0;
//    int counter[3] = {0, 0, 0};
    while (mySet->size() < size){
        string temp = randString(shift, uni_size);
        int index = h->naiveLookup(&temp);
//        ++counter[index];
        if (1 == index) mySet->insert(temp);
    }
//    if (m == MAX_LOOP) cout << "stopped because of m" << endl;
//    cout << "setSize: " << mySet->size() << ".\t" << "ratio is:" << mySet->size() / (double(size)) << "\t";
//    counterPrinter(counter);
    /*size_t c = 0;//, m = 0;
    int counter[3] = {0, 0, 0};
    while (c < size) {
        string temp = randString(shift, uni_size);
        int index = h->naiveLookup(&temp);
        ++counter[index];
        if (1 == index) {
            mySet->insert(temp);
            ++c;
        }
    }
    cout << "setSize: " << mySet->size() << ".\t" << "ratio is:" << mySet->size()/(double(size)) << "\t";
    counterPrinter(counter);
*/
}

void NonAdaptiveSpecificSetInit(size_t size, NonAdaptiveHelper *h, set<string> *mySet, int shift,
                                int uni_size) {
//    int counter[3] = {0, 0, 0};
    while (mySet->size() < size) {
        string temp = randString(shift, uni_size);
        int index = h->lookup(&temp);
        if (1 == index) mySet->insert(temp);
    }
//    cout << "setSize: " << mySet->size() << ".\t" << "ratio is:" << mySet->size() / (double(size)) << "\t";
//    counterPrinter(counter);
}

void testHelperNaiveCounter(size_t size, Helper *h, set<string> *mySet, int shift, int uni_size) {
    int counter[3] = {0, 0, 0};//, m = 0;
    for (int i = 0; i < size; ++i) {
        string temp = randString(shift, uni_size);
        ++(counter[h->naiveLookup(&temp)]);
    }
    counterPrinter(counter);
}

void testNonAdaptiveNaiveCounter(size_t size, NonAdaptiveHelper *h, set<string> *mySet, int shift,
                                 int uni_size) {
    int counter[3] = {0, 0, 0};//, m = 0;
    for (int i = 0; i < size; ++i) {
        string temp = randString(shift, uni_size);
        ++(counter[h->lookup(&temp)]);
    }
    counterPrinter(counter);
}


void HelperTNsetInit(size_t size, Helper *h, set<string> *mySet, int shift, int uni_size) {
    size_t c = 0;//, m = 1000;
    //int counter[3] = {0, 0, 0};
    while (c < size) {
        string temp = randString(shift, uni_size);
        int index = h->naiveLookup(&temp);
        //  ++counter[index];
        if (index == 0) {
            mySet->insert(temp);
            ++c;
        }
//        if (m % 1000 == 0) counterPrinter(counter);
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

////Set Tests

double testDiffSetInit(size_t n, int shift, int uni_size) {
    clock_t t0 = clock();
    set<string> mySet;
    for (int i = 0; i < n; ++i) mySet.insert(randString(shift, uni_size));
    return (clock() - t0) / (double) CLOCKS_PER_SEC;
}


long double setInitRatio(size_t size, int shift, int uni_size) {
    set<string> mySet;
    clock_t t0 = clock();
    for (int i = 0; i < size; ++i) mySet.insert(randString(shift, uni_size));
    return ((long double) mySet.size() / (double) size);
}
//
//void setInit(size_t size, set<string> *mySet, int shift, int uni_size) {
//    for (int i = 0; i < size; ++i) mySet->insert(randString(shift, uni_size));
//}


////SetTable Tests

/*

//
//void testPrintSetMinimal(size_t depth, size_t *vectorSizesArray) {
//    SetTable table(depth, vectorSizesArray, 0);
//    cout << table;
//}
//
//void testPrintSetTable(size_t depth, size_t *vectorSizesArray, size_t wordsInSet) {
//    size_t wordsCounter = 0;//, depthCounter = 0;
//    size_t loadFactor = 3;//, depthCounter = 0;
//    SetTable table(depth, vectorSizesArray, 0);
//    for (int i = 0; i < vectorSizesArray[0]; ++i) {
//        int hashIndex[] = {i};
//        for (int j = 0; j < loadFactor; ++j) {
//            table.add(WORDS[j + i * loadFactor], hashIndex, 1, 0);
//        }
////        depthCounter
//    }
//    cout << table;
//}
*/


////Helper Tests

void testHelperInit(size_t n, double eps) {
    set<string> memberSet;

    clock_t t0 = clock();
    Helper h(n, eps);
    double HelperInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    cout << "printing h:" << endl;
//    cout << h;
    cout << "initTime: " << HelperInitTime << endl;
}

void testHelperInsertionTime(size_t n, double eps, int shift, int uni_size) {
    clock_t startRunTime = clock();
    set<string> memberSet;//, nomSet;

    clock_t t0 = clock();
    setInit(n, &memberSet, shift, uni_size);
    double memberSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);

    t0 = clock();
    Helper h(n, eps);
    double initTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);

    t0 = clock();
    for (auto iter: memberSet) h.add(&iter);
    double insertionTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);


    double setRatio = ((double) memberSet.size() / n);
    string name = h.getName();
    double totalRunTime = (clock() - startRunTime) / ((double) CLOCKS_PER_SEC);

    cout << "memberSetInitTime: " << memberSetInitTime << endl;
    if (setRatio < 1) cout << "Set to lim ratio : " << setRatio << endl << endl;
    cout << name << " initTime: " << initTime << endl;
    cout << name << " insertionTime: " << insertionTime << "\t" << n / insertionTime << " el/sec" << endl;
    cout << "totalRunTime: " << totalRunTime << endl;

    cout << h << endl;
}

double testHelperNaiveLookup(size_t n, double eps, size_t lim, size_t naiveLim, int shift, int uni_size) {
    {
        clock_t startRunTime = clock();
        set<string> memberSet, nomSet, naiveLookupSet;

        clock_t t0 = clock();
        setInit(n, &memberSet, shift, uni_size);
        double memberSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);

        t0 = clock();
        setInit(lim, &nomSet, shift, uni_size);
        double nomSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
        double nomSetRatio = nomSet.size() / (double) lim;

        t0 = clock();
        setInit(naiveLim, &naiveLookupSet, shift, uni_size);
        double naiveLookupSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
        double naiveLookupSetRatio = nomSet.size() / (double) lim;


        t0 = clock();
        Helper h(n, eps);
        double initTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);

        t0 = clock();
        for (auto iter : memberSet) h.add(&iter);
        double insertionTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);


        // [TN, FP, TP]
        int counter[3] = {0, 0, 0};
        t0 = clock();
        for (auto iter : nomSet) ++counter[h.lookup(&iter)];
        double lookupTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);


        int counterNaive[3] = {0, 0, 0};
        t0 = clock();
        for (auto iter : naiveLookupSet) ++counterNaive[h.naiveLookup(&iter)];
        double naiveLookupTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);


        double totalRunTime = (clock() - startRunTime) / ((double) CLOCKS_PER_SEC);


        speedPrinter(n, lim, naiveLim, nomSetRatio, naiveLookupSetRatio, insertionTime, lookupTime, naiveLookupTime,
                     totalRunTime, h.getName());
//        testNaiveLookupPrinter(n, eps, lim, naiveLim, nomSetRatio, naiveLookupSetRatio, counter, counterNaive,
//                               memberSetInitTime, nomSetInitTime, naiveLookupSetInitTime,
//                               initTime, insertionTime, lookupTime, naiveLookupTime, totalRunTime, h.getName());
//
//        if (h.getName() == "Helper") cout << h;
//        return ((double) counter[1]) / lim;
    }
}

void testHelperRates(size_t n, double eps, size_t lim, int shift, int uni_size) {
    {
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
        setInit(lim, &nomSet, shift, uni_size);
        double nomSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
        double setRatio = nomSet.size() / (double) lim;

        // [TN, FP, TP]
        int counter[3] = {0, 0, 0};
        t0 = clock();
        for (auto iter : nomSet) ++counter[h.lookup(&iter)];

        double lookupTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
        double totalRunTime = (clock() - startRunTime) / ((double) CLOCKS_PER_SEC);


        testPrinter(n, eps, lim, setRatio, counter, memberSetInitTime, nomSetInitTime,
                    initTime, insertionTime, lookupTime, totalRunTime, h.getName());

        cout << h;
//        return ((double) counter[1]) / lim;
    }
}

void testHelperFP(size_t n, double eps, size_t lim, int shift, int uni_size) {
//    assert(shift > 5 && );
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
    while (TNSet.size() < lim) {
        string temp = randString(shift, uni_size);
        int index = h.naiveLookup(&temp);
        ++counter[index];
        if (1 == index) TNSet.insert(temp);
    }
    cout << "setSize: " << TNSet.size() << ".\t" << "ratio is:" << TNSet.size() / (double(lim)) << "\t";
    counterPrinter(counter);
*/
    t0 = clock();
    HelperSpecificSetInit(lim, &h, &TNSet, shift, uni_size);
    double TNSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double TNSetRatio = TNSet.size() / (double) lim;

    /*

    t0 = clock();
    setInit(naiveLim, &naiveLookupSet, shift, uni_size);
    double naiveLookupSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double naiveLookupSetRatio = nomSet.size() / (double) lim;

*/


    // [TN, FP, TP]
//    counter[2] = counter[1] = counter[0] = 0;
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

    testPrinter(n, eps, lim, TNSetRatio, counter, memberSetInitTime, TNSetInitTime,
                initTime, insertionTime, lookupTime, totalRunTime, h.getName());

    cout << h;
}

void testHelperTP(size_t n, double eps, int shift, int uni_size) {
    clock_t startRunTime = clock();
    set<string> memberSet;//, nomSet, naiveLookupSet;

    clock_t t0 = clock();
    setInit(n, &memberSet, shift, uni_size);
    double memberSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
/*

    t0 = clock();
    setInit(lim, &nomSet, shift, uni_size);
    double nomSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double nomSetRatio = nomSet.size() / (double) lim;

    t0 = clock();
    setInit(naiveLim, &naiveLookupSet, shift, uni_size);
    double naiveLookupSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double naiveLookupSetRatio = nomSet.size() / (double) lim;

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


    testPrinter(n, eps, n, 42, counter, memberSetInitTime, 0,
                initTime, insertionTime, lookupTime, totalRunTime, h.getName());


//    speedPrinter(n, lim, naiveLim, nomSetRatio, naiveLookupSetRatio, insertionTime, lookupTime, naiveLookupTime,
//                 totalRunTime, h.getName());
}

void testHelperTN(size_t n, double eps, size_t lim, int shift, int uni_size) {
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
    HelperTNsetInit(lim, &h, &TNSet, shift, uni_size);
    double TnSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
/*
    double nomSetRatio = nomSet.size() / (double) lim;

    t0 = clock();
    setInit(naiveLim, &naiveLookupSet, shift, uni_size);
    double naiveLookupSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double naiveLookupSetRatio = nomSet.size() / (double) lim;

*/


    // [TN, FP, TP]
    int counter[3] = {0, 0, 0};
    t0 = clock();
    for (auto iter : TNSet) ++counter[h.lookup(&iter)];
//    for (auto iter : TNSet) ++counter[h.naiveLookup(&iter)];
    double lookupTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);


/*


    int counterNaive[3] = {0, 0, 0};
    t0 = clock();
    for (auto iter : naiveLookupSet) ++counterNaive[h.naiveLookup(&iter)];
    double naiveLookupTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);


*/
    double totalRunTime = (clock() - startRunTime) / ((double) CLOCKS_PER_SEC);

    testPrinter(n, eps, n, 42, counter, memberSetInitTime, 0,
                initTime, insertionTime, lookupTime, totalRunTime, h.getName());

    cout << h;
}


/*//double testHelperFPTime(unsigned int n, double eps, unsigned int lim, int shift, int uni_size) {
//    {
//        clock_t startRunTime = clock();
//        set<string> memberSet, nomSet;
//
//        clock_t t0 = clock();
//        setInit(n, &memberSet, shift, uni_size);
//        double memberSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
//
//        t0 = clock();
//        setInit(lim, &nomSet, shift, uni_size);
//        double nomSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
//        double setRatio = nomSet.size() / (double) lim;
//
//        t0 = clock();
//        Helper h(n, eps);
//        double initTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
//
////        double insertTime = 0;
//        t0 = clock();
//        for (auto iter = memberSet.begin(); iter != memberSet.end(); ++iter) h.add(*iter);
//        double insertionTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
//
//
//        double lookupAdaptTime = 0;
//
//
//        // [TN, FP, TP]
//        int counter[3] = {0, 0, 0};
//        t0 = clock();
//        for (const auto &iter : nomSet) ++counter[h.getElementStatusTime(iter, &lookupAdaptTime)];
//
//        double lookupTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
//        double totalRunTime = (clock() - startRunTime) / ((double) CLOCKS_PER_SEC);
//
//        cout << "total time to adapt: " << lookupAdaptTime << endl;
//
//        testPrinter(n, eps, lim, setRatio, counter[0], counter[1], counter[2], memberSetInitTime, nomSetInitTime,
//                    initTime, insertionTime, lookupTime, totalRunTime, h.getName());
//
//        cout << h;
//        return ((double) counter[1]) / lim;
//    }
//}*/


////NonAdaptiveHelper Tests

void testNAHelperInit(size_t n, double eps) {
    NonAdaptiveHelper nh(n, eps);
    cout << "NA init over" << endl;
}

void testNonAdaptiveHelperInsert(size_t n, double eps, int lim, int shift, int uni_size) {
    clock_t startRunTime = clock();
    set<string> memberSet, nomSet;

    clock_t t0 = clock();
    setInit(n, &memberSet, shift, uni_size);
    double memberSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);

    t0 = clock();
    setInit(lim, &nomSet, shift, uni_size);
    double nomSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double setRatio = nomSet.size() / (double) lim;

    t0 = clock();
    NonAdaptiveHelper nh(n, eps);
    double NonAdaptiveHelperInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);

    t0 = clock();
    for (auto iter : memberSet) nh.add(&iter);
    double NonAdaptiveHelperInsertionTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    cout << "NA insert over" << endl;
}

//void testNonAdaptiveHelperInsertionTime(unsigned int n, double eps, int shift, int uni_size) {
//    clock_t startRunTime = clock();
//    set<string> memberSet, nomSet;
//
//    clock_t t0 = clock();
//    setInit(n, &memberSet, shift, uni_size);
//    double memberSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
//
//
//    t0 = clock();
//    NonAdaptiveHelper h(n, eps);
//    double initTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
//
//    t0 = clock();
//    for (auto iter = memberSet.begin(); iter != memberSet.end(); ++iter) h.add(*iter);
//    double insertionTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
//
//
//    double setRatio = ((double) memberSet.size() / n);
//    string name = h.getName();
//    double totalRunTime = (clock() - startRunTime) / ((double) CLOCKS_PER_SEC);
//
//    cout << "memberSetInitTime: " << memberSetInitTime << endl;
//    if (setRatio < 1) cout << "Set to lim ratio : " << setRatio << endl << endl;
//    cout << name << " initTime: " << initTime << endl;
//    cout << name << " insertionTime: " << insertionTime << "\t" << n / insertionTime << " el/sec" << endl;
//    cout << "totalRunTime: " << totalRunTime << endl;
//
//}


double testNonAdaptiveNaiveLookup(size_t n, double eps, size_t lim, size_t naiveLim, int shift, int uni_size) {
    {
        clock_t startRunTime = clock();
        set<string> memberSet, nomSet, naiveLookupSet;

        clock_t t0 = clock();
        setInit(n, &memberSet, shift, uni_size);
        double memberSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);

        t0 = clock();
        setInit(lim, &nomSet, shift, uni_size);
        double nomSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
        double nomSetRatio = nomSet.size() / (double) lim;

        t0 = clock();
        setInit(naiveLim, &naiveLookupSet, shift, uni_size);
        double naiveLookupSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
        double naiveLookupSetRatio = nomSet.size() / (double) lim;


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


        int counterNaive[3] = {0, 0, 0};
        t0 = clock();
        for (auto iter : naiveLookupSet) ++counterNaive[h.naiveLookup(&iter)];
        double naiveLookupTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);


        double totalRunTime = (clock() - startRunTime) / ((double) CLOCKS_PER_SEC);

        speedPrinter(n, lim, naiveLim, nomSetRatio, naiveLookupSetRatio, insertionTime, lookupTime, naiveLookupTime,
                     totalRunTime, h.getName());
//        testNaiveLookupPrinter(n, eps, lim, naiveLim, nomSetRatio, naiveLookupSetRatio, counter, counterNaive,
//                               memberSetInitTime, nomSetInitTime, naiveLookupSetInitTime,
//                               initTime, insertionTime, lookupTime, naiveLookupTime, totalRunTime, h.getName());

    }
}

void testNonAdaptiveRates(size_t n, double eps, size_t lim, int shift, int uni_size) {
    {
        clock_t startRunTime = clock();
        set<string> memberSet, nomSet;

        clock_t t0 = clock();
        setInit(n, &memberSet, shift, uni_size);
        double memberSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);

        t0 = clock();
        setInit(lim, &nomSet, shift, uni_size);
        double nomSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
        double setRatio = nomSet.size() / (double) lim;

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

        testPrinter(n, eps, lim, setRatio, counter, memberSetInitTime, nomSetInitTime,
                    initTime, insertionTime, lookupTime, totalRunTime, h.getName());

//        return ((double) counter[1]) / lim;
    }
}

void testNonAdaptiveFP(size_t n, double eps, size_t lim, int shift, int uni_size) {
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
    NonAdaptiveSpecificSetInit(lim, &h, &TNSet, shift, uni_size);
    double TNSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double TNSetRatio = TNSet.size() / (double) lim;

    /*

    t0 = clock();
    setInit(naiveLim, &naiveLookupSet, shift, uni_size);
    double naiveLookupSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double naiveLookupSetRatio = nomSet.size() / (double) lim;

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

    testPrinter(n, eps, lim, TNSetRatio, counter, memberSetInitTime, TNSetInitTime,
                initTime, insertionTime, lookupTime, totalRunTime, h.getName());

    cout << h;
}

void testNonAdaptiveTP(size_t n, double eps, int shift, int uni_size) {
    clock_t startRunTime = clock();
    set<string> memberSet;//, nomSet, naiveLookupSet;

    clock_t t0 = clock();
    setInit(n, &memberSet, shift, uni_size);
    double memberSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
/*

    t0 = clock();
    setInit(lim, &nomSet, shift, uni_size);
    double nomSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double nomSetRatio = nomSet.size() / (double) lim;

    t0 = clock();
    setInit(naiveLim, &naiveLookupSet, shift, uni_size);
    double naiveLookupSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double naiveLookupSetRatio = nomSet.size() / (double) lim;

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


    testPrinter(n, eps, n, 42, counter, memberSetInitTime, 0,
                initTime, insertionTime, lookupTime, totalRunTime, h.getName());

//    speedPrinter(n, lim, naiveLim, nomSetRatio, naiveLookupSetRatio, insertionTime, lookupTime, naiveLookupTime,
//                 totalRunTime, h.getName());
}

void testNonAdaptiveTN(size_t n, double eps, size_t lim, int shift, int uni_size) {
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
    NonAdaptiveTNsetInit(lim, &h, &TNSet, shift, uni_size);
    double TnSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
/*
    double nomSetRatio = nomSet.size() / (double) lim;

    t0 = clock();
    setInit(naiveLim, &naiveLookupSet, shift, uni_size);
    double naiveLookupSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    double naiveLookupSetRatio = nomSet.size() / (double) lim;

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


    testPrinter(n, eps, lim, 42, counter, memberSetInitTime, 0,
                initTime, insertionTime, lookupTime, totalRunTime, h.getName());

    cout << h;
}


////HelperS tests

//{
//    clock_t startRunTime = clock();
//    set<string> memberSet, nomSet;
//
//    clock_t t0 = clock();
//    setInit(n, &memberSet, shift, uni_size);
//    double memberSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
//
//
//    t0 = clock();
//    NonAdaptiveHelper h(n, eps);
//    double initTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
//
//    t0 = clock();
//    for (auto iter = memberSet.begin(); iter != memberSet.end(); ++iter) h.add(*iter);
//    double insertionTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
//
//
//    double setRatio = ((double) memberSet->size() / n);
//    string name = h.getName();
//    double totalRunTime = clock() - startRunTime;
//
//    cout << "memberSetInitTime: " << memberSetInitTime << endl;
//    if (setRatio < 1) cout << "Set to lim ratio : " << setRatio << endl << endl;
//    cout << name << " initTime: " << initTime << endl;
//    cout << name << " insertionTime: " << insertionTime << "\t" << n / insertionTime << " el/sec" << endl;
//    cout << "totalRunTime: " << totalRunTime << endl;
//


//}

////Printers

void counterPrinter(int *counter) {
    cout << "[trueNegative, falsePositive, truePositive]" << "\t[" << counter[0] << ", " << counter[1] << " ,"
         << counter[2] << "]" << endl;
}

void testPrinter(size_t n, double eps, size_t lim, double setRatio, int *counter, double memberSetInitTime,
                 double nomSetInitTime, double initTime, double insertionTime, double lookupTime, double totalRunTime,
                 const string name) {
    counterPrinter(counter);
    double ans = ((double) counter[1]) / lim;
    cout << "memberSetInitTime: " << memberSetInitTime << endl;
    cout << "nomSetInitTime: " << nomSetInitTime << endl;
    cout << "nomSet to lim ratio : " << setRatio << endl << endl;
    cout << "False positive rate:" << ans;
    cout << "\tExpected: " << eps << ". Error div(in % as eps): " << 100 * (ans - eps) / eps << "%" << endl;
    cout << name << " initTime: " << initTime << endl;
    cout << name << " insertionTime: " << insertionTime << "\t" << n / insertionTime << " el/sec" << endl;
    cout << name << " lookupTime: " << lookupTime << "\t" << lim / lookupTime << " el/sec" << endl << endl;
    cout << "totalRunTime: " << totalRunTime << endl;

//    ((double) n) / HelperInitTime << "el per sec" << endl;
}


void
testNaiveLookupPrinter(size_t n, double eps, size_t lim, size_t naiveLim, double nomSetRatio,
                       double naiveLookupSetRatio, int *counter,
                       int *naiveLookupCounter, double memberSetInitTime, double nomSetInitTime,
                       double naiveLookupSetInitTime, double initTime, double insertionTime, double lookupTime,
                       double naiveLookupTime, double totalRunTime, string name) {
    counterPrinter(counter);
    counterPrinter(naiveLookupCounter);
    double ans1 = ((double) counter[1]) / lim;
    double ans2 = ((double) naiveLookupCounter[1]) / naiveLim;
    cout << "memberSetInitTime: " << memberSetInitTime << endl;
    cout << "nomSetInitTime: " << nomSetInitTime << "\t";
    cout << "nomSet to lim ratio : " << nomSetRatio << endl;
    cout << "naiveLookupSetInitTime: " << naiveLookupSetInitTime << "\t";
    cout << "onlyLookupSet to lim ratio : " << naiveLookupSetRatio << endl << endl;
    cout << "False positive rate:" << ans1;
    cout << "\tExpected: " << eps << ". Error div(in % as eps): " << 100 * (ans1 - eps) / eps << "%" << endl;
    cout << "False positive rate:" << ans2;
    cout << "\tExpected: " << eps << ". Error div(in % as eps): " << 100 * (ans2 - eps) / eps << "%" << endl;
    cout << name << " initTime: " << initTime << endl;
    cout << name << " insertionTime: " << insertionTime << "\t" << n / insertionTime << " el/sec" << endl;
    cout << name << " lookupTime: " << lookupTime << "\t" << lim / lookupTime << " el/sec" << endl;
    cout << name << " naiveLookupTime: " << naiveLookupTime << "\t" << naiveLim / naiveLookupTime << " el/sec" << endl
         << endl;
    cout << "totalRunTime: " << totalRunTime << endl;

//    ((double) n) / HelperInitTime << "el per sec" << endl;
}

void speedPrinter(size_t n, size_t lim, size_t naiveLim, double nomSetRatio, double naiveLookupSetRatio,
                  double insertionTime, double lookupTime, double naiveLookupTime, double totalRunTime, string name) {
    if (nomSetRatio < 1) cout << "nomSet to lim ratio : " << nomSetRatio << endl;
    if (naiveLookupSetRatio < 1) cout << "onlyLookupSet to lim ratio : " << naiveLookupSetRatio << endl;
//    cout << name << " initTime: " << initTime << endl;
    cout << name << " insertionTime: " << insertionTime << "\t" << n / insertionTime << " el/sec" << endl;
    cout << name << " lookupTime: " << lookupTime << "\t" << lim / lookupTime << " el/sec" << endl;
    cout << name << " naiveLookupTime: " << naiveLookupTime << "\t" << naiveLim / naiveLookupTime << " el/sec" << endl
         << endl;
    cout << "totalRunTime: " << totalRunTime << endl;

}

void TPPrinter(size_t n, double initTime, double insertionTime, double totalRunTime, string name) {
    /*counterPrinter(counter);
    counterPrinter(naiveLookupCounter);
    double ans1 = ((double) counter[1]) / lim;
    double ans2 = ((double) naiveLookupCounter[1]) / naiveLim;
    cout << "memberSetInitTime: " << memberSetInitTime << endl;
    cout << "nomSetInitTime: " << nomSetInitTime << "\t";
    cout << "nomSet to lim ratio : " << nomSetRatio << endl;
    cout << "naiveLookupSetInitTime: " << naiveLookupSetInitTime << "\t";
    cout << "onlyLookupSet to lim ratio : " << naiveLookupSetRatio << endl << endl;
    cout << "False positive rate:" << ans1;
    cout << "\tExpected: " << eps << ". Error div(in % as eps): " << 100 * (ans1 - eps) / eps << "%" << endl;
    cout << "False positive rate:" << ans2;
    cout << "\tExpected: " << eps << ". Error div(in % as eps): " << 100 * (ans2 - eps) / eps << "%" << endl;
    */
    cout << name << " initTime: " << initTime << endl;
    cout << name << " insertionTime: " << insertionTime << "\t" << n / insertionTime << " el/sec" << endl;
    /*cout << name << " lookupTime: " << lookupTime << "\t" << lim / lookupTime << " el/sec" << endl;
    cout << name << " naiveLookupTime: " << naiveLookupTime << "\t" << naiveLim / naiveLookupTime << " el/sec" << endl
         << endl;
    */
    cout << "totalRunTime: " << totalRunTime << endl;

}



//
//void testBFOnBits(BloomFilter *bfp) {
//    for (auto word: WORDS) bfp->add(&word);
//    cout << *bfp << endl;
//}


//void addElementsFromSet(BloomFilter *bfp, set<string> *mySet, unsigned int *resCounter) {
//    for (auto iter = mySet->begin(); iter != mySet->end(); ++iter) {
//        string s = *iter;
//        if (bfp->lookup(&s)) (mySet->find(s) == mySet->end()) ? ++(resCounter[2]) : ++(resCounter[1]);
//        else ++(resCounter[0]);
//    }
//}

//double NABFPCount(unsigned int n, float eps, unsigned int lim, unsigned int universe_power) {
//    clock_t t0 = clock();
//    set<string> mySet;
//    NonAdaptiveBloomFilter nabf(n, eps);
//
//    for (int i = 0; i < n; ++i) {
//        string s = randomString(universe_power);
//        nabf.add(&s);
//        mySet.insert(s);
//    }
//    clock_t t1 = clock();
//
//    cout << nabf;
//
//    clock_t t2 = clock();
//
//    unsigned int tnc = 0, tpc = 0, fpc = 0;
//    for (int j = 0; j < lim; ++j) {
//        string s = randomString(universe_power);
//        if (nabf.lookup(&s)) (mySet.find(s) == mySet.end()) ? ++fpc : ++tpc;
//        else ++tnc;
//    }
//
//    clock_t t3 = clock();
//    cout << "[trueNegative, truePositive, falsePositive]" << "\t[" << tnc << ", " << tpc << " ," << fpc << "]" << endl;
//    double ans = ((double) fpc) / lim;
//    cout << "False positive rate:" << ans << endl;
//    cout << "Expected: " << eps << ". Error div(in % as eps): " << 100 * (ans - eps) / eps << "%" << endl;
//    cout << "Insertion time:" << (t1 - t0) / ((double) CLOCKS_PER_SEC) << endl << "Run time:"
//         << (t3 - t2) / ((double) CLOCKS_PER_SEC)
//         << endl << "Total time:" << (clock() - t0) / ((double) CLOCKS_PER_SEC) << endl;
//    return ans;
//}

//string randomString(int len) {
//    static const char alphanum[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E',
//                                      'F'};
//
//    char s[len];
//    for (int i = 0; i < len; ++i) s[i] = alphanum[udr(0, 15)];
//    s[len] = 0;
//    string res(s);
//    return res;
//}

//string randomString(int minLength, int maxLength) {
//    int len = udr(minLength, maxLength);
//    return randomString(len);
//}

//double testBloomFilterFP(unsigned int n, float eps, unsigned int lim, unsigned int universe_power) {
//    clock_t t0 = clock();
//    set<string> mySet;
//    BloomFilter bf(n, eps);
//    for (int i = 0; i < n; ++i) {
//        string s = randomString(universe_power);
//        bf.add(&s);
//        mySet.insert(s);
//    }
//    clock_t t1 = clock();
//
//    cout << bf;
//
//    clock_t t2 = clock();
//
//    unsigned int tnc = 0, tpc = 0, fpc = 0;
//    for (int j = 0; j < lim; ++j) {
//        string s = randomString(universe_power);
//        if (bf.lookup(&s)) (mySet.find(s) == mySet.end()) ? ++fpc : ++tpc;
//        else ++tnc;
//    }
//
//
//    clock_t t3 = clock();
//    cout << "[trueNegative, truePositive, falsePositive]" << "\t[" << tnc << ", " << tpc << " ," << fpc << "]" << endl;
//    double ans = ((double) fpc) / lim;
//    cout << "False positive rate:" << ans << endl;
//    cout << "Expected: " << eps << ". Error div(in % as eps): " << 100 * (ans - eps) / eps << "%" << endl;
//    cout << "Insertion time:" << (t1 - t0) / ((double) CLOCKS_PER_SEC) << endl << "Run time:"
//         << (t3 - t2) / ((double) CLOCKS_PER_SEC)
//         << endl << "Total time:" << (clock() - t0) / ((double) CLOCKS_PER_SEC) << endl;
//    return ans;
//}

//double testHelperRates(unsigned int n, float eps, unsigned int lim, unsigned int universe_power) {
//    clock_t startRunTime = clock();
//    set<string> memberSet, nomSet;
//
//    clock_t t0 = clock();
//    for (int i = 0; i < n; ++i) memberSet.insert(randString());
//    double memberSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
//
//    t0 = clock();
//    for (int i = 0; i < lim; ++i) nomSet.insert(randomString());
//    double nomSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
//    double setRatio = nomSet.size() / (double) lim;
//
//    t0 = clock();
//    Helper h(n, eps);
//    double HelperInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
//
//    t0 = clock();
//    for (auto iter = memberSet.begin(); iter != memberSet.end(); ++iter) h.add(*iter);
//    double HelperInsertionTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
//
//
////    cout << h;
//
//
////    unsigned int tnc = 0, tpc = 0, fpc = 0;
//    // [TN, FP, TP]
//    int counter[3] = {0, 0, 0};
//    t0 = clock();
//    for (const auto &iter : nomSet) ++counter[h.getElementStatus(iter)];
///*    {
///        int status = h.getElementStatus(iter);
////        counter[status] += 1;
////    }
//
//    cout << "[";
//    cout << counter[0];
//    cout << ", " << counter[1];
//    cout << ", " << counter[2];
//    cout << "]" << endl;
//
/// //    for (int j = 0; j < lim; ++j) {
////        string s = randomString(universe_power);
////        int status = h.getElementStatus(&s);
////        switch (status) {
////            case 2:
////                ++tnc;
////                break;
////            case 3:
////                ++fpc;
////                break;
////            case 4:
////                ++tpc;
////                break;
////            default:
////                assert(true);
////        }*/
//    double HelperLookupTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
//    double totalRunTime = (clock() - startRunTime) / ((double) CLOCKS_PER_SEC);
//
//    testPrinter(n, eps, lim, setRatio, counter[0], counter[1], counter[2], memberSetInitTime, nomSetInitTime,
//                HelperInitTime,
//                HelperInsertionTime,
//                HelperLookupTime, totalRunTime);
//    /*
//    cout << "[trueNegative, falsePositive, truePositive]" << "\t[" << counter[2] << ", " << counter[3] << " ,"
//         << counter[4] << "]" << endl;
//    double ans = ((double) counter[3]) / lim;
//    cout << "False positive rate:" << ans << endl;
//    cout << "Expected: " << eps << ". Error div(in % as eps): " << 100 * (ans - eps) / eps << "%" << endl;
//    cout << "memberSetInitTime: " << memberSetInitTime << endl;
//    cout << "nomSetInitTime: " << nomSetInitTime << endl;
//    cout << "HelperInitTime: " << HelperInitTime << endl;
//    cout << "HelperInsertionTime: " << HelperInsertionTime << endl;
//
//    cout << "Insertion time:" << HelperInsertionTime << endl << "Run time:"
//         << (t3 - t2) / ((double) CLOCKS_PER_SEC)
//         << endl << "Total time:" << (clock() - t0) / ((double) CLOCKS_PER_SEC) << endl;*/
//    return ((double) counter[1]) / lim;
//}
