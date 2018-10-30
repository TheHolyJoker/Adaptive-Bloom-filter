//
// Created by tomer on 10/25/18.
//

#ifndef INHERITANCE_VLTESTS_H
#define INHERITANCE_VLTESTS_H

#include "VLHelper.h"
#include "../tests/Tests.h"

#include <set>


bool VLtpLookup(size_t q, size_t r, size_t elNum, size_t vLength);

void vlt1();

void vlt2();

void vlt3();

void vlt4();

void vlt5();

void vlt6();

void vlt7();

bool vlRandom(size_t q, size_t r, size_t vLength, BLOCK_TYPE reps);

void elementInit(BLOCK_TYPE* elements[], size_t vLength, BLOCK_TYPE reps, size_t mod);

#endif //INHERITANCE_VLTESTS_H
