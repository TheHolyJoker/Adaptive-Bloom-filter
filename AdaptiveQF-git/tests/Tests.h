//
// Created by tomer on 10/22/18.
//

#ifndef INHERITANCE_TESTS_H
#define INHERITANCE_TESTS_H

#include "paTests.h"
#include "../Helper.h"

#define TIME_PASSED_FROM(t) (double(clock()-(t))/CLOCKS_PER_SEC)

string randString(int minWordLength = 8, int charsNum = 32, int numOfDiffLength = 8);

void setInit(size_t size, set<string> *mySet, int minWordLength = 8, int charsNum = 32);

bool tpLookup(size_t q, size_t r, size_t mbSize, size_t elNum);

bool sanity(size_t q, size_t r, size_t mbSize, size_t elNum);

bool hTPLookup(size_t q, size_t r, size_t mbSize, size_t elNum);

void hpAdaptiveTest(size_t q, size_t r, size_t elementNum, size_t lookupReps);

int statusCorrectness(size_t q, size_t r, size_t elementNum);

ostream &rates(size_t q, size_t r, double loadFactor, size_t lookupReps, ostream &os = cout);

ostream &
getStats(double qfInitTime, double memberSetInitTime, double lookupSetInitTime, double insertionTime, double lookupTime,
         size_t memberSetSize, size_t lookupReps, int *counter, ostream &os);

ostream &counterPrinter(int *counter, ostream &os);


void VLFingerPrint(size_t q, size_t r, size_t elNum);

#endif //INHERITANCE_TESTS_H
