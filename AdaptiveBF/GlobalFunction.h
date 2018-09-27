//
// Created by tomer on 9/20/18.
//

#ifndef ADAPTIVEBF_GLOBALFUNCTION_H
#define ADAPTIVEBF_GLOBALFUNCTION_H


#include <iostream>
#include <string>
#include <cstring>
#include <random>
#include <vector>
#include <math.h>
#include <assert.h>

#define DOLLAR_SIGN_NL "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"
#define MISTAKE DOLLAR_SIGN_NL DOLLAR_SIGN_NL DOLLAR_SIGN_NL

#define DEFUALT_SEED 2
#define SECOND_SEED 42
#define MIN_M_LOG_VAL 8
#define MIN_N_LOG_VAL 3

#define MAX_LOOP 10

using namespace std;

static string WORDS[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
                         "eleven",
                         "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen",
                         "nineteen", "twenty",
                         "twenty-one", "twenty-two", "twenty-three", "twenty-four", "twenty-five", "twenty-six",
                         "twenty-seven", "twenty-eight", "twenty-nine", "thirty", "thirty-one", "thirty-two",
                         "thirty-three", "thirty-four", "thirty-five", "thirty-six", "thirty-seven",
                         "thirty-eight",
                         "thirty-nine", "forty", "forty-one", "forty-two", "forty-three", "forty-four",
                         "forty-five",
                         "forty-six", "forty-seven", "forty-eight", "forty-nine", "fifty", "fifty-one",
                         "fifty-two",
                         "fifty-three", "fifty-four", "fifty-five", "fifty-six", "fifty-seven", "fifty-eight",
                         "fifty-nine",
                         "sixty", "sixty-one", "sixty-two", "sixty-three", "sixty-four", "sixty-five", "sixty-six",
                         "sixty-seven", "sixty-eight", "sixty-nine", "seventy", "seventy-one", "seventy-two",
                         "seventy-three",
                         "seventy-four", "seventy-five", "seventy-six", "seventy-seven", "seventy-eight",
                         "seventy-nine",
                         "eighty", "eighty-one", "eighty-two", "eighty-three", "eighty-four", "eighty-five",
                         "eighty-six",
                         "eighty-seven", "eighty-eight", "eighty-nine", "ninety", "ninety-one", "ninety-two",
                         "ninety-three",
                         "ninety-four", "ninety-five", "ninety-six", "ninety-seven", "ninety-eight", "ninety-nine",
                         "one-hundred"};

unsigned int udr(unsigned int a, unsigned int b);

size_t udr(size_t a, size_t b);

size_t calcM(size_t n, double eps);

double calcM(size_t n, double eps, bool overload);

size_t calcK(size_t n, size_t m);

size_t getDepthByMinNM(size_t n, double eps);

void GetMList(size_t n, double eps, size_t *mList, size_t depth);

void GetKList(size_t n, double eps, size_t *kList, size_t *mList, size_t depth);

//void lastPrintMK(size_t n, double eps);

//void mk_test();


//size_t getMi(size_t n0, double previousEps);
//
//double getMi(size_t n0, double previousEps, bool overload);
//
//bool isMSmall(size_t n);
//
//bool isNSmall(size_t n);
//
//size_t getNiExp(size_t previousN, double previousEps);
//
//double niUpperConst(size_t n0);
////size_t *getMiList(size_t n0, double previousEps, size_t depth);
//
//size_t getNi(size_t n0, size_t previousN, double previousEps);
//
////size_t *getNiList(size_t n0, double previousEps);
//
//unsigned int logStar(unsigned int n);
//
//unsigned int myGetDepth(size_t n, double eps);
//
//size_t softGetDepth(size_t n, double eps);
//
//
//size_t myMList(size_t n, double eps, size_t *mList, size_t depth);
//
//size_t myNList(size_t n, double eps, size_t *nList, size_t depth);
////void softMKList(size_t n, double eps, size_t* mkList[], size_t depth);
//
//void softMList(size_t n, double eps, size_t mList[], size_t depth);
//
//void softKList(size_t n, double eps, size_t *kList, size_t depth);
//
//unsigned int getDepth(unsigned int n, float eps);
//
//size_t getTotalSize(size_t n, double eps);
//
//size_t getBloomFilterSize(size_t, double eps);
//
//ostream &printN_M_K(ostream &os, size_t n, double eps);
//
//ostream &printN_M_K_single(ostream &os, size_t n, size_t m, size_t k);
//
//ostream &printN_M_K_single(ostream &os, size_t n, size_t m);
//
//
////unsigned int getTableSize(unsigned int n, float eps);
////double myGetNextN(double currN, double currEps);
////double myGetNextN(size_t currN, double currEps);
////size_t getNextM(size_t initN, double previousEps);
////double getNextEps(double eps);
////
//
////template <typename T>
////void printArray(T array, size_t size);



#endif //ADAPTIVEBF_GLOBALFUNCTION_H
