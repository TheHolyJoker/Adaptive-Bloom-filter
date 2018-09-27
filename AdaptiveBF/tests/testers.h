//
// Created by tomer on 9/20/18.
//

#ifndef ADAPTIVEBF_TESTERS_H
#define ADAPTIVEBF_TESTERS_H

#include <iostream>
#include <cstring>
#include <set>
#include <unordered_set>
#include "../MurmurHash3.h"
#include "../Hash.h"
#include "../BloomFilter.h"
#include "../SetTable.h"
#include "../Helper.h"
#include "../Non_Adaptive/NonAdaptiveHelper.h"

#define DEFAULT_SHIFT 3

using namespace std;


string randString(int shift, int uni_size, int multiRatio = 4);

void sameString(size_t lim, int shift, int uni_size);

void charSetInit(size_t size, set<const char *> *mySet, int shift, int uni_size, int multiRatio = 4);

void setInit(size_t size, set<string> *mySet, int shift, int uni_size);

void testHelperNaiveCounter(size_t size, Helper *h, set<string> *mySet, int shift, int uni_size);

void testNonAdaptiveNaiveCounter(size_t size, NonAdaptiveHelper *h, set<string> *mySet, int shift, int uni_size);

void HelperSpecificSetInit(size_t size, Helper *h, set<string> *mySet, int shift, int uni_size);

void HelperTNsetInit(size_t size, Helper *h, set<string> *mySet, int shift, int uni_size);

void NonAdaptiveTNsetInit(size_t size, NonAdaptiveHelper *h, set<string> *mySet, int shift, int uni_size);

void NonAdaptiveSpecificSetInit(size_t size, NonAdaptiveHelper *h, set<string> *mySet, int shift,
                                int uni_size);

////Set Tests

double testDiffSetInit(size_t n, int shift, int uni_size);

double setInitTime(size_t size, int shift, int uni_size);

long double setInitRatio(size_t size, int shift, int uni_size);



////SetTable Tests

void testPrintSetMinimal(size_t depth, size_t *vectorSizesArray);

void testPrintSetTable(size_t depth, size_t *vectorSizesArray, size_t wordsInSet);


////Helper Tests

void testHelperInit(size_t n, double eps);

void testHelperInsertionTime(size_t n, double eps, int shift, int uni_size);

void testHelperRates(size_t n, double eps, size_t lim, int shift, int uni_size);

double testHelperNaiveLookup(size_t n, double eps, size_t lim, size_t naiveLim, int shift, int uni_size);

void testHelperFPTime(unsigned int n, double eps, unsigned int lim, int shift, int uni_size);

void testHelperFP(size_t n, double eps, size_t lim, int shift, int uni_size);

void testHelperTP(size_t n, double eps, int shift, int uni_size);

void testHelperTN(size_t n, double eps, size_t lim, int shift, int uni_size);


////NonAdaptiveHelper Tests

void testNAHelperInit(size_t n, double eps, int uni_size);

void testNonAdaptiveHelperInsert(size_t n, double eps, int shift, int uni_size);

void testNonAdaptiveHelperInsertionTime(unsigned int n, double eps, int shift, int uni_size);

double testNonAdaptiveNaiveLookup(size_t n, double eps, size_t lim, size_t naiveLim, int shift, int uni_size);

void testNonAdaptiveRates(size_t n, double eps, size_t lim, int shift, int uni_size);

void testNonAdaptiveFP(size_t n, double eps, size_t lim, int shift, int uni_size);

void testNonAdaptiveTP(size_t n, double eps, int shift, int uni_size);

void testNonAdaptiveTN(size_t n, double eps, size_t lim, int shift, int uni_size);

////HelperS tests



//// Print the result.

void testPrinter(size_t n, double eps, size_t lim, double setRatio, int *counter, double memberSetInitTime,
                 double nomSetInitTime, double initTime, double insertionTime, double lookupTime, double totalRunTime,
                 const string name);

void
testNaiveLookupPrinter(size_t n, double eps, size_t lim, size_t naiveLim, double nomSetRatio,
                       double naiveLookupSetRatio, int *counter, int *naiveLookupCounter, double memberSetInitTime,
                       double nomSetInitTime, double naiveLookupSetInitTime, double initTime, double insertionTime,
                       double lookupTime, double naiveLookupTime, double totalRunTime, string name);

void counterPrinter(int *counter);


void speedPrinter(size_t n, size_t lim, size_t naiveLim, double nomSetRatio, double naiveLookupSetRatio,
                  double insertionTime, double lookupTime, double naiveLookupTime, double totalRunTime, string name);

void TPPrinter(size_t n, double initTime, double insertionTime, double totalRunTime, string name);

#endif //ADAPTIVEBF_TESTERS_H

/*
 *Old functions
 *
//void testParamCalc(size_t a, size_t b);
//
//char *randomChar();
//
//string randString(int shift = 3);
//
//double setInitTime(size_t size, int shift);
//
//void setInit(size_t size, unordered_set<string> *mySet,int shift = 3);
//
//string randomString(int len = 16);
//
//string randomString(int minLength, int maxLength);
//
//double testDiffSetInit(size_t n, size_t minLength, size_t maxLength);
//
//void testHelperInit(size_t n, double eps);
//
//double testBloomFilterFP(unsigned int n, float eps, unsigned int lim, unsigned int universe_power);
//
//double testHelperFP(unsigned int n, float eps, unsigned int lim, unsigned int universe_power);
//
//double testHelperRates(unsigned int n, double eps, unsigned int lim, int shift = 3);
//
//void addElementsFromSet(BloomFilter *bfp, unordered_set<string> *mySet, unsigned int *resCounter);
//
//double NABFPCount(unsigned int n, float eps, unsigned int lim, unsigned int universe_power);
//
////static const char alphanum[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
//
//void testBFOnBits(BloomFilter *bfp);
//
//unsigned int testFP(unsigned int N, unsigned int M, unsigned int K);
//
//void testPrintSetMinimal(size_t depth, size_t *vectorSizesArray);
//
//void testPrintSetTable(size_t depth, size_t *vectorSizesArray, size_t wordsInSet);
//
//
//void
//testPrinter(size_t n, double eps, size_t lim, double setRatio, int tnc, int fpc, int tpc, double memberSetInitTime,
//            double nomSetInitTime, double HelperInitTime, double HelperInsertionTime, double HelperLookupTime,
//            double totalRunTime);
//

//void randomString(char *s, int len = 16);
//
//void sqrtArrayTest(int n) {
//    int a[n];
//    for (int i = 0; i < n; ++i) a[i] = i * i;
//    printArray<>(a, n);
//}


unsigned int testFP(unsigned int N, unsigned int M, unsigned int K)
//{
    string key = "foo";
////    string value = "bar";
////    cout << "write Key:" << key << " and value:" << value << endl;
////    status = db->Put(leveldb::WriteOptions(), key, value);
////    assert(status.ok());
////    string value_back;
////    status = db->Get(leveldb::ReadOptions(), key, &value_back);
////    cout << "Read back:" << value_back << endl;
////    assert(status.ok());
////    assert(value == value_back);
////    delete db;
//    leveldb::DB* db;
//    leveldb::Options options;
//    options.create_if_missing = true;
//    leveldb::Status status = leveldb::DB::Open(options, "/home/tomer/Desktop/Project/murmurhash Test/tmp/testdb", &db);
//    assert(status.ok());
//
//    BloomFilter bf = BloomFilter(M,K);
//    for (int i = 0; i < N; ++i)
//    {
//        unsigned int randint = udr(0,PRIME);
//        string s = to_string(randint);
//        bf.add(&s);
//        status = db->Put(leveldb::WriteOptions(), s, s);
//        assert(status.ok());
//    }
//
//    unsigned int fpCounter = 0;
//
//    for (int i = 0; i < N; ++i)
//    {
//        unsigned int randint = udr(0,PRIME);
//        string s = to_string(randint);
//        if(bf.status(&s))
//        {
//            string value_back;
//            getElementStatus = db->Get(leveldb::ReadOptions(), s, &value_back);
//            if (value_back.empty()) ++fpCounter;
//        }
//    }
//    delete db;
//    return fpCounter;
//
//}

//    unsigned int a[20] = {1804289383, 846930886, 1681692777, 1714636915, 1957747793, 424238335, 719885386, 1649760492, 596516649, 1189641421, 1025202362, 1350490027, 783368690, 1102520059, 2044897763, 1967513926, 1365180540, 1540383426, 304089172, 1303455736}

//void randomString(char *s, int len) {
//    static const char alphanum[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E',
//                                      'F'};
//
//    for (int i = 0; i < len; ++i) s[i] = alphanum[udr(0, 15)];
//    s[len] = 0;
//}

*/