//
// Created by tomer on 9/17/18.
//

#ifndef ADAPTIVEBF_SetTable_H
#define ADAPTIVEBF_SetTable_H

#include <set>
#include "GreyBoxFunction.h"

using namespace std;

class SetTable {

    vector<vector<set<string> > > tableVec;

public:
    SetTable();

    SetTable(size_t n, double eps);

    SetTable(size_t depth, size_t *sizeArray);


    /**
     * add s to all the relevant sets in SetTable.
     * @param s an element
     * @param hashIndex indexes in the BF filter , to whom s was mapped,
     * @param hashIndexSize number of hash functions that BF has.
     * @param depth the level in which the BF is.
     */
    void add(const string &s, size_t *hashIndex, size_t hashIndexSize, size_t depth);

    /**
     *
     * @param s
     * @param depth
     * @param index
     * @return true if s points to an element that is in SetTable, meaning it is in
     * the set in  set2DVec[depth][index].
     */
    bool find(string *s, size_t depth, size_t index);

    /**
     * Member getter.
     * @return
     */
    const vector<vector<set<string>>> &getTableVec() const;

    /**
     * Member setter.
     * @param set2DVec
     */
    void setTableVec(const vector<vector<set<string>>> &set2DVec);

    /**
     * Insert the sizes of the vector in tableVec to sizesArray.
     * @param sizesArray
     */
    void getSizes(size_t *sizesArray);

    /**
     * Returns iterator of the elements in tableVec[depth][index]
     * @param depth
     * @param index
     * @return
     */
    set<string>::iterator getElements(size_t depth, size_t index);

    set<string>::iterator getEnd(size_t depth, size_t index);

    /**
     * Clears the set in tableVec[depth][index]. Is called after adapt operation,
     * where the stale bit was turned on, meaning there will not be another search for an
     * element in this set.
     * @param depth
     * @param index
     */
    void deleteIndex(size_t depth, size_t index);

    ostream &printSizes(ostream &os);

};

ostream &operator<<(ostream &os, const SetTable &setTable);


#endif //ADAPTIVEBF_SetTable_H
