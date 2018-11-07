//
// Created by tomer on 11/7/18.
//

#ifndef INHERITANCE_DB_H
#define INHERITANCE_DB_H

#include "Filter.h"
#include <map>

class DB {
    vector<Filter *> filtersVec;
    map<KEY_TYPE, vector<string>> memberMap;
    size_t depth;
    bool isAdaptive;

public:
    DB(size_t q, size_t r, bool isAdaptive);

    ~DB();

    void add(string *s, size_t level = 0);

    int lookup(string *s);


private:
    void adapt(vector<string> *elementVec, size_t fpIndex, size_t level);

    int nonAdaptiveLookup(string *s);

    bool nonAdaptiveAdd(string *s);

};


#endif //INHERITANCE_DB_H
