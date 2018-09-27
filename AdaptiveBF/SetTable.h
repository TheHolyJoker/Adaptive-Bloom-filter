//
// Created by tomer on 9/17/18.
//

#ifndef ADAPTIVEBF_SetTable_H
#define ADAPTIVEBF_SetTable_H

#include <set>
#include "GlobalFunction.h"
#include "BloomFilter.h"

#define MIN_SIZE 10
using namespace std;

class SetTable {

    vector<vector<set<string> * > > set2DVec;

public:
    SetTable(size_t n, double eps);

    SetTable(size_t depth, size_t *sizeArray);

    ~SetTable();

    void lastLevelFalse();

    void add(const string& s, size_t *hashIndex, size_t hashIndexSize, size_t depth);

//    void add(string &s, size_t *hashIndex, size_t hashIndexSize, size_t depth);

    bool find(string *s, size_t depth, size_t index);

    set<string>::iterator getElements(size_t depth, size_t index);

    set<string>::iterator getEnd(size_t depth, size_t index);

    void addVecToTable(BloomFilter *bf);

    void deleteIndex(size_t depth, size_t index);

    const vector<vector<set<string> *>> &getSet2DVec() const;

    size_t getSize();

    size_t getILength(int i);

    set<string> getAllElements();

    void clear();
/*
        SetTable(size_t depth, size_t *sizeArray, size_t lim);
        bool find(string s, int index, size_t depth);
    void addAid(vector<set<string> *> vec, string s, int index);
    vector<vector<set<string>>>& getTable();
    void add(const char* s, size_t *hashIndex, size_t hashIndexSize, size_t depth);
    bool find(const char* s, size_t index, size_t depth);
*/

};

ostream &operator<<(ostream &os, const SetTable &setTable);

void printSet(ostream &os, const set<string> *mySet);

void printSet(ostream &os, set<string> *mySet);


//void printSet(ostream &os, const set<string> &mySet);
/*
os << "b_filter size: " << bfr.size << ". On bits: " << bfr.getOnBits() << ". Ratio is: "
   << ((float) bfr.getFilterOnBits()) / bfr.size << endl;
for (auto h : bfr.kHashFuncs) {
    const size_t a = h->getMultiConst();
//        if(a >= bfr.size) os << "$$$\n$$$\n$$$\nnext hash function multiConst is too big:";
    os << a << "|";
}
os << endl;
return os;
 */
//}
//unsigned int getNi(unsigned int currentSize, double currentEps);

//unsigned int * getTotalSize(unsigned int initSize, double initEps);

//void changeSizeParam(unsigned int *currentSize, double *currentEps);


//unsigned int getMaxDepth(unsigned int initSize);


#endif //ADAPTIVEBF_SetTable_H
