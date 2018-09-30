//
// Created by tomer on 9/17/18.
//

#include "SetTable.h"

SetTable::SetTable() {
    tableVec.resize(1);
}

SetTable::SetTable(size_t n, double eps) {
    size_t depth = getDepth(n, eps);
    size_t mList[depth];
    GetMList(n, eps, mList, depth);
    tableVec.resize(depth);
    for (int i = 0; i < depth; ++i) tableVec[i].resize(mList[i]);
}


SetTable::SetTable(size_t depth, size_t *sizeArray) {
    tableVec.resize(depth);
    for (int i = 0; i < depth; ++i) tableVec[i].resize(sizeArray[i]);
}


void SetTable::add(const string &s, size_t *hashIndex, size_t hashIndexSize, size_t depth) {
    for (int i = 0; i < hashIndexSize; ++i) tableVec[depth][hashIndex[i]].insert(s);
}


bool SetTable::find(string *s, size_t depth, size_t index) {
    return (tableVec[depth][index].find(*s) != tableVec[depth][index].end());
}

set<string>::iterator SetTable::getElements(size_t depth, size_t index) {
    return tableVec[depth][index].begin();
}

set<string>::iterator SetTable::getEnd(size_t depth, size_t index) {
    return tableVec[depth][index].end();
}

void SetTable::deleteIndex(size_t depth, size_t index) {
    tableVec[depth][index].clear();
}


void printSet(ostream &os, const set<string> *mySet) {
    auto iter = mySet->begin();
    if (iter == mySet->end()) {
        os << "{EMPTY}" << endl;
        return;
    }
    os << "{" << *iter;
    ++iter;
    while (iter != mySet->end()) {
        os << ", " << *iter;
        ++iter;
    }
    os << "}" << endl;
}

void SetTable::getSizes(size_t *sizesArray) {
    for (const auto &vec: this->tableVec) {
        *sizesArray = vec.size();
        ++sizesArray;
    }
}

ostream &SetTable::printSizes(ostream &os) {
    os << this->tableVec.size() << endl;
    for (const auto &vec: tableVec) cout << vec.size() << endl;
    return os;
}

const vector<vector<set<string>>> &SetTable::getTableVec() const {
    return tableVec;
}

void SetTable::setTableVec(const vector<vector<set<string>>> &set2DVec) {
    SetTable::tableVec = set2DVec;
}
