//
// Created by tomer on 10/22/18.
//

#include "Helper.h"

Helper::Helper(size_t q, size_t r) : depth(1) {
    fVec.push_back(new RegularQF(q, r));
}

Helper::Helper(size_t q, size_t r, bool isAdaptive) {
    depth = calcDepthByQ(q, r);
    fVec.resize(depth);
    size_t qArr[depth];
    size_t rArr[depth];
    qArr[0] = q;
    rArr[0] = r;
    getArraysSizes(qArr, rArr, depth);
//    arrayPrinter(qArr, depth);
//    arrayPrinter(rArr, depth);
    for (int i = 0; i < depth; ++i)
        fVec[i] = new AdaptQF(qArr[i], rArr[i]);
}

void Helper::add(string *s, size_t level) {
    if (depth == 1)
        return singleAdd(s);
    for (size_t i = level; i < depth; ++i) {
        size_t qIndex;
        BLOCK_TYPE data;
        fVec[i]->convert(s, &qIndex, &data);
        if (fVec[i]->add(s)) {
            memberMap[pair<size_t, size_t>(qIndex, data)] = *s;
            return;
        }
    }
}

/*
void Helper::add(string *s, size_t level, size_t vLength) {
    if (depth == 1)
        return singleAdd(s, vLength);
    for (size_t i = level; i < depth; ++i) {
        size_t qIndex;
        uint64_t data;
        fVec[i]->convert(s, &qIndex, &data);
        if (fVec[i]->add(s)) {
            memberMap[pair<size_t, size_t>(qIndex, data)] = *s;
            return;
        }
    }
}
*/

void Helper::singleAdd(string *s) {
    size_t qIndex;
    BLOCK_TYPE data;
    fVec[0]->convert(s, &qIndex, &data);
    fVec[0]->add(s);
    memberMap[pair<size_t, size_t>(qIndex, data)] = *s;
}

/*void Helper::singleAdd(string *s, size_t vLength) {
    size_t qIndex;
    BLOCK_TYPE data;
    fVec[0]->convert(s, &qIndex, &data);
    fVec[0]->add(s, vLength);
    memberMap[pair<size_t, size_t>(qIndex, data)] = *s;
}*/

int Helper::singleLookup(string *s) {
    int res = fVec[0]->lookup(s);
    if (res == 1) {
        size_t qIndex;
        BLOCK_TYPE data;
        fVec[0]->convert(s, &qIndex, &data);
        if (memberMap[pair<size_t, size_t>(qIndex, data)] == *s)
            return 2;
        return 1;
    } else if (res == 0)
        return 0;
    else {
        cout << res << endl;
        assert(false);
    }
}

/*int Helper::singleLookup(string *s, size_t vLength) {
    int res = fVec[0]->lookup(s, vLength);
    if (res == 1) {
        size_t qIndex;
        BLOCK_TYPE data;
        fVec[0]->convert(s, &qIndex, &data);
        if (memberMap[pair<size_t, size_t>(qIndex, data)] == *s)
            return 2;
        return 1;
    } else if (res == 0)
        return 0;
    else {
        cout << res << endl;
        assert(false);
    }
}*/

int Helper::lookup(string *s) {
    if (depth == 1)
        return singleLookup(s);
    size_t fpIndex = 0;
    for (int i = 0; i < depth; ++i) {
        int res = fVec[i]->lookup(s, &fpIndex);
        if (res == 0)
            return 0;
        if (res == 1) {
            size_t qIndex;
            BLOCK_TYPE data;
            fVec[0]->convert(s, &qIndex, &data);
            if (memberMap[pair<size_t, size_t>(qIndex, data)] == *s)
                return 2;
            adapt(qIndex, data, fpIndex, i);
            return 1;
        }
//        cout << "res is: " << res << endl;
    }
//    lookup(s);
    size_t erIndex;
    BLOCK_TYPE ad;
    for (int j = 0; j < depth; ++j) {
        fVec[j]->convert(s, &erIndex, &ad);
        cout << "level " << j << "error with: " << erIndex << endl;
    }
    assert(false);
}

/*int Helper::lookup(string *s, size_t vLength) {
    if (depth == 1)
        return singleLookup(s, vLength);
    size_t fpIndex = 0;
    for (int i = 0; i < depth; ++i) {
        int res = fVec[i]->lookup(s, &fpIndex);
        if (res == 0)
            return 0;
        if (res == 1) {
            size_t qIndex;
            BLOCK_TYPE data;
            fVec[0]->convert(s, &qIndex, &data);
            if (memberMap[pair<size_t, size_t>(qIndex, data)] == *s)
                return 2;
            adapt(qIndex, data, fpIndex, i);
            return 1;
        }
//        cout << "res is: " << res << endl;
    }
//    lookup(s);
    size_t erIndex;
    BLOCK_TYPE ad;
    for (int j = 0; j < depth; ++j) {
        fVec[j]->convert(s, &erIndex, &ad);
        cout << "level " << j << "error with: " << erIndex << endl;
    }
    assert(false);
}*/

void Helper::adapt(size_t qIndex, BLOCK_TYPE data, size_t fpIndex, size_t level) {
    string s = memberMap[pair<size_t, size_t>(qIndex, data)];
    fVec[level]->setFP(fpIndex);
    add(&s, ++level);

}

Helper::~Helper() {
    for (auto vec: fVec)
        delete vec;
}

size_t calcDepthByQ(size_t q, size_t r) {
//    cout << "calcDepthByQ:" << endl;
    double doubleQ = double(q);
    size_t counter = 0;
//    cout << "(" << doubleQ << ", " << r << ")" << endl;
    while (doubleQ > 1) {
        double exp = pow(2, doubleQ) / SL(r);
        double whpConst = (1 + 1.0 / doubleQ);
        doubleQ = log2(exp * whpConst);
        r *= r;
        ++counter;
//        cout << "(" << doubleQ << ", " << r << ")" << endl;
    }
//    cout << counter << endl;
    return counter;
}

void getArraysSizes(size_t *qArr, size_t *rArr, size_t length) {
    double doubleQ = double(qArr[0]);
    size_t counter = 0;
    for (int i = 1; i < length; ++i) {
        double exp = SL(qArr[i - 1]) / SL(rArr[i - 1]);
        double whpConst = (1 + 1.0 / doubleQ);
        doubleQ = log2(exp * whpConst);
//        cout << doubleQ;
        qArr[i] = int(round(++doubleQ));
//        cout << ", " << qArr[i] << endl;
        rArr[i] = rArr[i - 1] * rArr[i - 1];
    }
}

/*
void arrayPrinter(size_t *a, size_t length) {
    cout << "[" << a[0];
    for (int i = 1; i < length; ++i) {
        cout << ", " << a[i];
    }
    cout << "]" << endl;
}
*/

void Helper::statusCorrectness() {
    for (int i = 0; i < depth; ++i) {
        cout << i << ": ";
        this->fVec[i]->statusCorrectness();
    }
}

ostream &Helper::statisticsPrint(ostream &os) {
    for (int i = 0; i < depth; ++i) {
        os << i << ": " << endl;
        this->fVec[i]->statisticsPrint(os);
    }
    return os;
}
