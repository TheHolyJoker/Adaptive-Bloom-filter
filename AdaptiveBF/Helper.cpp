//
// Created by tomer on 9/20/18.
//

#include "Helper.h"

Helper::Helper(size_t n, double eps) {
    nForReBuild = n, epsForReBuild = eps;
    Helpersdepth = getDepthByMinNM(n, eps);
    size_t mList[Helpersdepth], kList[Helpersdepth];
    GetMList(n, eps, mList, Helpersdepth);
    GetKList(n, eps, kList, mList, Helpersdepth);
    BF2DArray = new BloomFilter *[Helpersdepth];
    for (int i = 0; i < Helpersdepth; ++i) BF2DArray[i] = new BloomFilter(mList[i], kList[i], false);
    setTable = new SetTable(Helpersdepth, mList);
}
//
//void Helper::add(string s, size_t depth) {
//    add(&s,depth);
//}

Helper::~Helper() {
    for (int i = 0; i < Helpersdepth; ++i) delete BF2DArray[i];
    delete[] BF2DArray;
    delete setTable;
}


void Helper::add(string *s, size_t depth) {
    for (size_t i = depth; i < Helpersdepth; ++i) {
        //Todo pointer ot not.
        BloomFilter *bf = BF2DArray[i];
        size_t k = bf->kHashFuncs.size();
        size_t hashIndex[k];
        int status = bf->getElementStatus(s, hashIndex);
        if (status == -1) continue;
        else {
            bf->add(hashIndex);
            this->setTable->add(*s, hashIndex, k, i);
            return;
        }
    }
    this->reBuilt();
    this->add(s);
    /*
//    assert(false);
//    this->lastLevelFalse();
//    this->add(s, Helpersdepth - 1);
    const Helper& h  = *this;
    cout << endl<< endl <<"Can't add. Helper is:" << endl << h << endl << endl;
    assert(false);*/
}

int Helper::lookup(string *s) {
    for (size_t i = 0; i < Helpersdepth; ++i) {
        BloomFilter *bf = BF2DArray[i];
        size_t k = bf->kHashFuncs.size();
        size_t hashIndex[k];
        int status = bf->getElementStatus(s, hashIndex);
        if (status == -1) continue;
        else if (status) {
            //todo where to search
            if (this->setTable->find(s, i, hashIndex[0])) return 2;
            size_t chosenIndex = chooseIndex(hashIndex, k);
            bf->stale[chosenIndex] = true;
            adapt(i, chosenIndex);
            return 1;
        } else return 0;
    }
    assert(false);
}

int Helper::naiveLookup(string *s) {
    for (size_t i = 0; i < Helpersdepth; ++i) {
        BloomFilter *bf = BF2DArray[i];
        size_t k = bf->kHashFuncs.size();
        size_t hashIndex[k];
        int status = bf->getElementStatus(s, hashIndex);
        if (status == 0) return 0;
        if (status == 1) return (this->setTable->find(s, i, hashIndex[0])) ? 2 : 1;
    }
    assert(false);
}

void Helper::adapt(size_t depth, size_t index) {
    auto iter = this->setTable->getElements(depth, index);
    auto end = this->setTable->getEnd(depth, index);
    ++depth;
    //todo change order
    while (iter != end) {
        string temp = (*iter);
        this->add(&temp, depth);
        ++iter;
    }
    setTable->deleteIndex(--depth, index);
}

void Helper::lastLevelFalse() {
    BloomFilter **tempAddres = this->BF2DArray;
    BF2DArray = new BloomFilter *[++Helpersdepth];
    for (int i = 0; i < Helpersdepth - 1; ++i) BF2DArray[i] = tempAddres[i];
    BF2DArray[Helpersdepth - 1] = new BloomFilter(BF2DArray[Helpersdepth - 2]);
    setTable->lastLevelFalse();
    free(tempAddres);
}

size_t Helper::getVecSize() const {
    return Helpersdepth;
    //    this->bfVec.size();
}

const BloomFilter &Helper::getBloomI(int i) const {
    return *BF2DArray[i];
    //    return this->bfVec[i];
}

string Helper::getName() {
    return "Helper";
}

//Todo this function
size_t Helper::chooseIndex(size_t *hashIndex, size_t size) {
    return hashIndex[0];
}

void Helper::reBuilt() {
    cout << "reBuilt" << endl;
    Helper *h = new Helper(nForReBuild, epsForReBuild);
    /*for (int i = 0; i < Helpersdepth; ++i) delete BF2DArray[i];
    size_t mList[Helpersdepth], kList[Helpersdepth];
    GetMList(nForReBuild, epsForReBuild, mList, Helpersdepth);
    GetKList(nForReBuild, epsForReBuild, kList, mList, Helpersdepth);
    for (int i = 0; i < Helpersdepth; ++i) BF2DArray[i] = new BloomFilter(mList[i], kList[i], false);
    this->setTable->clear();
*/
    set<string> allSet = this->setTable->getAllElements();
    for (auto s : allSet) h->add(&s);
    delete[] this->BF2DArray;
    delete this->setTable;

    this->BF2DArray = h->BF2DArray;
    this->setTable = h->setTable;
//    const vector<vector<set<string> *>> *old2DTable = &(this->setTable->getSet2DVec());
//    SetTable *oldSetTabelAddr = this->setTable;
//    vector<vector<set<string> *>> *oldVecAddress = this->setTable->set2DVec;
//    auto old2DTable = *oldVecAddress;
//    SetTable *newSetTable = new SetTable(Helpersdepth, mList);
//    this->setTable = new SetTable(Helpersdepth, mList);
//    for (vector<set<string> *> vec : *old2DTable) {
//        for (set<string> *mySet : vec)
//            if (mySet != nullptr) {
//                for (string s : *mySet) this->add(&s);
//            }
//    }
//    delete old2DTable;
    cout << "reBuilt over" << endl;
}


ostream &operator<<(ostream &os, const Helper &hp) {
    for (int i = 0; i < hp.getVecSize(); ++i) {
        const BloomFilter &bfp = hp.getBloomI(i);
        os << i << ":" << endl << bfp;
    }
    return os;
}
