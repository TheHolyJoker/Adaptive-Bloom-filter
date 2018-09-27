//
// Created by tomer on 9/17/18.
//

#include "SetTable.h"

SetTable::SetTable(size_t n, double eps) {
    size_t depth = getDepthByMinNM(n, eps);
    size_t mList[depth];
    GetMList(n, eps, mList, depth);
    set2DVec.resize(depth);
    for (int i = 0; i < depth; ++i) set2DVec[i].resize(mList[i]);
}


SetTable::SetTable(size_t depth, size_t *sizeArray) {
    set2DVec.resize(depth);
    for (int i = 0; i < depth; ++i) set2DVec[i].resize(sizeArray[i]);
//        for (int j = 0; j < sizeArray[i]; ++j) set2DVec[i][j] = new set<string>};
}

//void SetTable::add(const char *s, size_t *hashIndex, size_t hashIndexSize, size_t depth) {
//    for (int i = 0; i < hashIndexSize; ++i) set2DVec[depth][hashIndex[i]]->insert(s);
//}

void SetTable::add(const string &s, size_t *hashIndex, size_t hashIndexSize, size_t depth) {
    for (int i = 0; i < hashIndexSize; ++i) {
        if (set2DVec[depth][hashIndex[i]] == nullptr) set2DVec[depth][hashIndex[i]] = new set<string>;
        set2DVec[depth][hashIndex[i]]->insert(s);
    }
}


SetTable::~SetTable() {
    for (int i = 0; i < set2DVec.size(); ++i) {
        for (set<string> *mySet : set2DVec[i]) delete (mySet);
        set2DVec[i].clear();
    }
    set2DVec.clear();
}

bool SetTable::find(string *s, size_t depth, size_t index) {
    return (set2DVec[depth][index]->find(*s) != set2DVec[depth][index]->end());
}

set<string>::iterator SetTable::getElements(size_t depth, size_t index) {
    return set2DVec[depth][index]->begin();
}

set<string>::iterator SetTable::getEnd(size_t depth, size_t index) {
    return set2DVec[depth][index]->end();

}

void SetTable::deleteIndex(size_t depth, size_t index) {
    set2DVec[depth][index]->clear();
//    delete set2DVec[depth][index];
}

void SetTable::addVecToTable(BloomFilter *bf) {
    size_t m = bf->getSize();
    vector<set<string> *> myVec(m);
    for (int i = 0; i < m; ++i) myVec[i] = new set<string>;
    this->set2DVec.push_back(myVec);
}



//
//set<string>::iterator SetTable::getElements(size_t depth, size_t index) {
//    return set2DVec[depth][index]->begin();
//}
//
//set<string>::iterator SetTable::getEnd(size_t depth, size_t index)
//{
//    return set2DVec[depth][index]->end();
//}



void SetTable::lastLevelFalse() {
    size_t m = set2DVec[set2DVec.size() - 1].size();
    vector<set<string> *> myVec(m);
    this->set2DVec.push_back(myVec);
}

size_t SetTable::getSize() {
    return set2DVec.size();
}

size_t SetTable::getILength(int i) {
    return set2DVec[i].size();
}

const vector<vector<set<string> *>> &SetTable::getSet2DVec() const {
    return set2DVec;
}

set<string> SetTable::getAllElements() {
    set<string> allSet;
    for (auto vec : set2DVec) {
        for (auto tempSet : vec)
            if (tempSet != nullptr) {
                for (const auto &s : *tempSet) {
                    allSet.insert(s);
                }
            }
    }
    return allSet;
}

void SetTable::clear() {
    for (int i = 0; i < set2DVec.size(); ++i) for (auto mySet : set2DVec[i]) if(mySet != nullptr) mySet->clear();
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

//
//ostream &operator<<(ostream &os, const SetTable &setTable) {
//    string tabs = "\t";
//    auto table = setTable.getSet2DVec();
//    size_t vecCounter = 0, setCounter = 0;
////    for (vector<set<string> *> vec: table) {
//    for (auto vec: table) {
//        os << vecCounter++ << " vector:" << endl;
////        for (set<string> *mySet: vec)
//        for (auto mySet: vec) printSet(os, mySet);
//        os << endl;
//    }
//    return os;
//}

//void printSet(ostream &os, set<string> *mySet)

//void printSet(ostream &os, set<string> *mySet) {
//    auto iter = mySet->begin();
//    if (iter == mySet->end()) {
//        os << "{EMPTY}" << endl;
//        return;
//    }
//    os << "{" << *iter;
//    ++iter;
//    while (iter != mySet->end()) {
//        os << ", " << *iter;
//        ++iter;
//    }
//    os << "}" << endl;
//}


//void printSet(ostream &os, const set<string> &mySet) {
//    auto iter = mySet.begin();
//    if (iter == mySet.end()) {
//        os << "{EMPTY}" << endl;
//        return;
//    }
//    os << "{" << *iter;
//    while (iter != mySet.end()) {
//        os << ", " << *iter;
//        ++iter;
//    }
//    os << "}" << endl;
//}

/*
//setArray::setArray(unsigned int initSize, double initEps) {
//    unsigned int totalSize = getTotalSize(initSize, initEps);
//    this->setPointerArray
//
//
//}

unsigned int * getTotalSize(unsigned int initSize, double initEps)
{
    unsigned int maxDepth = getMaxDepth(initSize);
    auto *sizeArr = new unsigned int[maxDepth];
    sizeArr[0] = initSize;
    double tempEps = initEps;
    for (int i = 1; i < maxDepth; ++i) {
        tempEps *= tempEps;
        sizeArr[i] = getNextSize(sizeArr[i-1], tempEps);
    }
    return sizeArr;
}

unsigned int getNi(unsigned int currentSize, double currentEps)
{
    if (currentSize < MIN_SIZE) return MIN_SIZE;
    return (unsigned int) (currentSize/2.0 + 1);
}
void changeSizeParam(unsigned int *currentSize, double *currentEps)
{
    if (*currentSize > MIN_SIZE)
    {
        *currentSize = (unsigned int) (*currentSize/2.0 + 1);
    }
    *currentEps *= *currentEps;
}


unsigned int getMaxDepth(unsigned int initSize)
{
    return (unsigned int) (initSize/(3*log(initSize)) + 1);
}
*/

//SetTable::SetTable(size_t depth, size_t *sizeArray, size_t lim) {
//    cout << "Should be call only as a basic test to print a tableSet" << endl;
//    set2DVec.resize(depth);
//    int wc = 0;
//    for (int i = 0; i < depth; ++i) {
//        size_t temp = sizeArray[i];
//        set2DVec[i].resize(temp);
//        for (int j = 0; j < temp; ++j) {
//            set2DVec[i][j] = new set<string>;
//            set2DVec[i][j]->insert(WORDS[++wc]);
//        }
//    }
//}
