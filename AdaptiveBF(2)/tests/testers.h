//
// Created by tomer on 9/20/18.
//

#ifndef ADAPTIVEBF_TESTERS_H
#define ADAPTIVEBF_TESTERS_H

#include <iostream>
#include <cstring>
#include <set>
#include <unordered_set>
#include "../MurmurHash3.h"
#include "../Hash.h"
#include "../BloomFilter.h"
#include "../SetTable.h"
#include "../Helper.h"
#include "../Non_Adaptive/NonAdaptiveHelper.h"

using namespace std;


string randString(int minLength, int numOfDiffElements, int numOfDiffLength = 8);

void setInit(size_t size, set<string> *mySet, int shift, int uni_size);

void HelperTPSetInit(size_t size, Helper *h, set<string> *mySet, int shift, int uni_size);

void HelperTNsetInit(size_t size, Helper *h, set<string> *mySet, int shift, int uni_size);

void NonAdaptiveTNsetInit(size_t size, NonAdaptiveHelper *h, set<string> *mySet, int shift, int uni_size);

void NonAdaptiveTPSetInit(size_t size, NonAdaptiveHelper *h, set<string> *mySet, int shift,
                          int uni_size);

////Helper Tests


ostream &testHelperRates(size_t n, double eps, size_t lookupsNum, int shift, int uni_size, ostream &os = cout);

ostream &testHelperFP(size_t n, double eps, size_t lookupsNum, int shift, int uni_size, ostream &os = cout);

ostream &testHelperTP(size_t n, double eps, int shift, int uni_size, ostream &os = cout);

ostream &testHelperTN(size_t n, double eps, size_t lookupsNum, int shift, int uni_size, ostream &os = cout);


////NonAdaptiveHelper Tests


ostream &testNonAdaptiveRates(size_t n, double eps, size_t lookupsNum, int shift, int uni_size, ostream &os = cout);

ostream &testNonAdaptiveFP(size_t n, double eps, size_t lookupsNum, int shift, int uni_size, ostream &os = cout);

ostream &testNonAdaptiveTP(size_t n, double eps, int shift, int uni_size, ostream &os = cout);

ostream &testNonAdaptiveTN(size_t n, double eps, size_t lookupsNum, int shift, int uni_size, ostream &os = cout);


//// Function for printing.

ostream &
testPrinter(size_t n, double eps, size_t lookupsNum, double setRatio, int *counter, double memberSetInitTime,
            double nomSetInitTime, double initTime, double insertionTime, double lookupTime, double totalRunTime,
            const string name, ostream &os = cout);


void
testNaiveLookupPrinter(size_t n, double eps, size_t lookupsNum, size_t naiveLim, double nomSetRatio,
                       double naiveLookupSetRatio, int *counter, int *naiveLookupCounter, double memberSetInitTime,
                       double nomSetInitTime, double naiveLookupSetInitTime, double initTime, double insertionTime,
                       double lookupTime, double naiveLookupTime, double totalRunTime, string name);

void counterPrinter(int *counter);

ostream &counterPrinter(ostream &os, int *counter);


void speedPrinter(size_t n, size_t lookupsNum, size_t naiveLim, double nomSetRatio, double naiveLookupSetRatio,
                  double insertionTime, double lookupTime, double naiveLookupTime, double totalRunTime, string name);

void TPPrinter(size_t n, double initTime, double insertionTime, double totalRunTime, string name);

#endif //ADAPTIVEBF_TESTERS_H
