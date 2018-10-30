/*
//
// Created by tomer on 10/22/18.
//

#include "Filter.h"

Filter::Filter(size_t q, size_t r) : q(q), r(r), A(RegularQF(q, r)), h(Hash(SL(r + q))) {}

Filter::Filter(size_t q, size_t r, bool isAdaptive) : q(q), r(r), A(AdaptQF(q, r)), h(Hash(SL(r + q))) {}

bool Filter::add(string *s) {
    size_t qIndex;
    BLOCK_TYPE data;
    convert(s, &qIndex, &data);
    return A.add(data, qIndex);
}

int Filter::lookup(string *s) {
    size_t qIndex;
    BLOCK_TYPE data;
    convert(s, &qIndex, &data);
    return A.lookup(data, qIndex);
}

int Filter::lookup(string *s, size_t *fpIndex) {
    size_t qIndex;
    BLOCK_TYPE data;
    convert(s, &qIndex, &data);
    return A.lookup(data, qIndex, fpIndex);
}


void Filter::convert(string *s, size_t *qIndex, BLOCK_TYPE *data) {
    uint64_t hashVal = h.calc(s);
    *qIndex = (hashVal >> r) ;//% SL(q);
    *data = (hashVal % SL(r)); // Todo
}

void Filter::setFP(size_t fpIndex) {
    A.setFP(fpIndex);
}

//Filter::Filter(const PackedArray &A) : A(A) {}
*/
