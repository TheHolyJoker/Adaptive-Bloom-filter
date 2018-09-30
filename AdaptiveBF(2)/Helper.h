//
// Created by tomer on 9/20/18.
//

#ifndef ADAPTIVEBF_HELPER_H
#define ADAPTIVEBF_HELPER_H


#include "BloomFilter.h"
#include "SetTable.h"


class Helper {
    vector<BloomFilter> bfVec;
    SetTable setTable = SetTable(1, 1);
    size_t HelpersDepth;

public:
    Helper(size_t n, double eps);

    /**
     * Adds s to the relevant level BF, starting for level depth
     * @param s
     * @param depth minimal level BF to who s is trying to be inserted in.
     */
    void add(string *s, size_t depth = 0, bool *reBuildCall = nullptr);

    /**
     *
     * @param s
     * @return
     * 0 tn
     * 1 fp
     * 2 tp
     */
    int lookup(string *s);

    /**
     * Like lookup, when there s is a FP, there is no call to adapt.
     * @param s
     * @return
     */
    int naiveLookup(string *s);

    /**
     * Moves all elements in the set in SetTable[depth][index] to the next level BF.
     * @param depth level in which there was a FP
     * @param index
     */
    void adapt(size_t depth, size_t index);

    /**
     * Choosing a random index from hashIndex. Currently deterministically choosing hashIndex[0].
     * @param hashIndex an array of indexes.
     * @param size hashIndex size.
     * @return random index from hashIndex.
     */
    size_t chooseIndex(size_t *hashIndex, size_t size);

    /**
     * When trying to add an element to the last level BF, and it maps to an index in the BF where the stale is on,
     * We rebuild the Helpers BFs vector and setTable.
     */
    void reBuild();

    const vector<BloomFilter> &getBfVec() const;

    string getName();


};

ostream &operator<<(ostream &os, const Helper &hp);


#endif //ADAPTIVEBF_HELPER_H

/*
void add(string *s);

void addTime(string *s, double *totalTime);

void add(string *s, size_t depth);

void add(string s);
void add(string s);



int getElementStatusTime(string s, double *totalTime);

int lookup(string s);

int onlyLookup(string *s);

int onlyLookup(string s);

void adapt(string *s, size_t depth, size_t index);

void adaptTime(string *s, size_t depth, size_t index);



void adaptTime(size_t depth, size_t index, double *totalTime);

int lookupTime(string *s, double *totalTime);     */
