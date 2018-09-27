//
// Created by tomer on 9/20/18.
//

#ifndef ADAPTIVEBF_HELPER_H
#define ADAPTIVEBF_HELPER_H


#include "BloomFilter.h"
#include "SetTable.h"
#include "GlobalFunction.h"


class Helper {
//    vector<BloomFilter> bfVec;
    BloomFilter **BF2DArray;
    SetTable *setTable;
    size_t Helpersdepth, nForReBuild;
    double epsForReBuild;
public:
    Helper(size_t n, double eps);

    ~Helper();
//    void add(const char *s);
    void add(string *s, size_t depth = 0);
//    void add(string s, size_t depth = 0);

    /**
     *
     * @param s
     * @return
     * 0 tn
     * 1 fp
     * 2 tp
     */
    int lookup(string *s);

    int naiveLookup(string *s);

    void adapt(size_t depth, size_t index);

    void reBuilt();

    void lastLevelFalse();

    size_t getVecSize() const;

    const BloomFilter &getBloomI(int i) const;

    string getName();

    size_t chooseIndex(size_t *hashIndex, size_t size);

    /*
    void add(string *s);

    void addTime(string *s, double *totalTime);

    void add(string *s, size_t depth);

    void add(string s);
    void add(string s);



    int getElementStatusTime(string s, double *totalTime);

    int getElementStatus(string s);

    int onlyLookup(string *s);

    int onlyLookup(string s);

    void adapt(string *s, size_t depth, size_t index);

    void adaptTime(string *s, size_t depth, size_t index);

    void adaptTime(string *s, size_t depth, size_t index, double *totalTime);

*/

};

ostream &operator<<(ostream &os, const Helper &hp);


//helper *helperInit(unsigned int size);


#endif //ADAPTIVEBF_HELPER_H
