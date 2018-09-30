//
// Created by tomer on 9/20/18.
//

#include "Helper.h"

Helper::Helper(size_t n, double eps) {
    HelpersDepth = getDepth(n, eps);
    size_t mList[HelpersDepth], kList[HelpersDepth];
    GetMList(n, eps, mList, HelpersDepth);
    GetKList(n, eps, kList, mList, HelpersDepth);
    for (int i = 0; i < HelpersDepth; ++i) bfVec.emplace_back(mList[i], kList[i], false);
    setTable = SetTable(HelpersDepth, mList);
}


void Helper::add(string *s, size_t depth, bool *reBuildCall) {
    for (size_t i = depth; i < HelpersDepth; ++i) {
        size_t hashIndex[bfVec[i].kHashFuncs.size()];
        int status = bfVec[i].lookup(s, hashIndex);
        if (status == -1) continue;
        else {
            bfVec[i].add(hashIndex);
            this->setTable.add(*s, hashIndex, bfVec[i].kHashFuncs.size(), i);
            return;
        }
    }
    *reBuildCall = true;
    this->reBuild();
    this->add(s);
}

int Helper::lookup(string *s) {
    for (size_t i = 0; i < HelpersDepth; ++i) {
        size_t hashIndex[bfVec[i].kHashFuncs.size()];
        int status = bfVec[i].lookup(s, hashIndex);
        if (status == -1) continue;
        else if (status) {
            //todo maybe searching in a smaller set.
            if (this->setTable.find(s, i, hashIndex[0])) return 2;
            size_t chosenIndex = chooseIndex(hashIndex, bfVec[i].kHashFuncs.size());
            bfVec[i].filterStaleVec[(chosenIndex << 1) ^ 1] = true;
            adapt(i, chosenIndex);
            return 1;
        } else return 0;
    }
    assert(false);
}

int Helper::naiveLookup(string *s) {
    for (size_t i = 0; i < HelpersDepth; ++i) {
        size_t hashIndex[bfVec[i].kHashFuncs.size()];
        int status = bfVec[i].lookup(s, hashIndex);
        if (status == 0) return 0;
        if (status == 1) return (this->setTable.find(s, i, hashIndex[0])) ? 2 : 1;
    }
    assert(false);
}

void Helper::adapt(size_t depth, size_t index) {
    auto iter = this->setTable.getElements(depth, index);
    auto end = this->setTable.getEnd(depth, index);
    bool reBuildCall = false;
    //todo write loop more efficiently.
    ++depth;
    while (iter != end) {
        string temp = (*iter);
        this->add(&temp, depth, &reBuildCall);
        if (reBuildCall) return;
        ++iter;
    }
    setTable.deleteIndex(--depth, index);
}

string Helper::getName() {
    return "Helper";
}

//Todo this function
size_t Helper::chooseIndex(size_t *hashIndex, size_t size) {
    return hashIndex[0];
}

void Helper::reBuild() {
    cout << "reBuild" << endl;
    clock_t t0 = clock();
    size_t sizeArray[HelpersDepth];
    this->setTable.getSizes(sizeArray);
    vector<vector<set<string> > > newVec(HelpersDepth);

    for (int i = 0; i < HelpersDepth; ++i) newVec[i].resize(sizeArray[i]);
    vector<vector<set<string> > > oldVec = this->setTable.getTableVec();

    this->setTable.setTableVec(newVec);

    vector<BloomFilter> newBFVec;
    for (int i = 0; i < HelpersDepth; ++i) newBFVec.emplace_back(&bfVec[i]);
    this->bfVec = newBFVec;

    for (auto vec : oldVec)
        for (auto set : vec)
            for (auto s : set)
                this->add(&s);

    double totalTime = double(clock() - t0) / CLOCKS_PER_SEC;
    cout << "totalTime " << totalTime << endl << "reBuild over" << endl;
}

const vector<BloomFilter> &Helper::getBfVec() const {
    return bfVec;
}

ostream &operator<<(ostream &os, const Helper &hp) {
    int i = -1;
    for (const auto &bfp : hp.getBfVec())os << ++i << ":" << endl << bfp;
    return os;
}

/*

void Helper::adaptTime(size_t depth, size_t index, double *totalTime) {
    clock_t t0 = clock();
    auto iter = this->setTable.getElements(depth, index);
    auto end = this->setTable.getEnd(depth, index);
    ++depth;
    while (iter != end) {
        string temp = (*iter);
        this->add(&temp, depth);
        ++iter;
    }
    setTable.deleteIndex(--depth, index);
    *totalTime += double(clock() - t0) / CLOCKS_PER_SEC;
}


int Helper::lookupTime(string *s, double *totalTime) {
    for (size_t i = 0; i < HelpersDepth; ++i) {
        BloomFilter *bf = &bfVec[i];
        size_t k = bf->kHashFuncs.size();
        size_t hashIndex[k];
        int status = bf->lookup(s, hashIndex);
        if (status == -1) continue;
        else if (status) {
            //todo maybe searching in a smaller set.
            if (this->setTable.find(s, i, hashIndex[0])) return 2;
            size_t chosenIndex = chooseIndex(hashIndex, k);
            bf->filterStaleVec[chosenIndex + 1] = true;
            adaptTime(i, chosenIndex, totalTime);
            return 1;
        } else return 0;
    }
    assert(false);
}
*/
