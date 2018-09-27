#include <iostream>
#include <cstring>
#include <set>
#include <unordered_set>
#include "MurmurHash3.h"
#include "Hash.h"
#include "BloomFilter.h"
#include "SetTable.h"
#include "tests/testers.h"
#include "GlobalFunction.h"
//#include "rng.h"


using namespace std;

int main() {
    srand(2);
    cout << "Hello!" << endl;
    int uni_size = 64;
    int shift = 6;

    size_t factor = 4000;

    size_t n = 1 * factor;
    double eps = 0.01;
    size_t lim = 10 * factor;

//    set<string> mySet;
//    Helper h(n, eps);
//    NonAdaptiveHelper h(n, eps);


////    FP test
//    testHelperFP(n, eps, lim, shift, uni_size);
//    testNonAdaptiveFP(n, eps, lim, shift, uni_size);
//    srand(2);


////    TN test
//    testHelperTN(n, eps, lim, shift, uni_size);
//    testNonAdaptiveTN(n, eps, lim, shift, uni_size);


////    TP test
//    testNonAdaptiveTP(n, eps, shift, uni_size);
//    testHelperTP(n, eps, shift, uni_size);


//// Random test
    testHelperRates(n, eps, lim, shift, uni_size);
//    testNonAdaptiveRates(n, eps, lim, shift, uni_size);
//    testNonAdaptiveRates(n, eps, lim, shift, uni_size);


    /*set<string> memberSet, mySet;
      Helper h(n, eps);
      setInit(n, &memberSet, shift, uni_size);
      for(string s : memberSet) h.add(&s);

      size_t size = lim;
      size_t c = 0;
      int counter[3] = {0, 0, 0};
      while (mySet.size() < size) {
          string temp = randString(shift, uni_size);
          int index = h.naiveLookup(&temp);
          ++counter[index];
          if (1 == index) mySet.insert(temp);
      }
      cout << "setSize: " << mySet.size() << ".\t" << "ratio is:" << mySet.size() / (double(size)) << "\t";
      counterPrinter(counter);
  */
/*
    clock_t startRunTime = clock();
    set<string> memberSet, TNSet;//, naiveLookupSet;

    clock_t t0 = clock();
    setInit(n, &memberSet, shift, uni_size);
    double memberSetInitTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);

    t0 = clock();
    Helper h(n, eps);
    double initTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);

    t0 = clock();
    for (string s : memberSet) h.add(&s);
    double insertionTime = (clock() - t0) / ((double) CLOCKS_PER_SEC);
    cout << "MY insertion time: " << insertionTime;
    cout << "\t" << (n / insertionTime);
    cout << " el/s" << endl;
*/

    /*size_t naiveLim = 10 * factor;
    set<string> memberSet, TNSet;//, naiveLookupSet;

    clock_t t0 = clock();
    setInit(n, &memberSet, shift, uni_size);
    cout << (clock() - t0) / ((double) CLOCKS_PER_SEC) << endl;

    t0 = clock();
    Helper h(n, eps);
//    NonAdaptiveHelper h(n, eps);
    cout <<(clock() - t0) / ((double) CLOCKS_PER_SEC) << endl;

    t0 = clock();
    for (auto iter : memberSet) h.add(&iter);
    cout << (clock() - t0) / ((double) CLOCKS_PER_SEC) << endl;

    HelperSpecificSetInit(n, &h, &TNSet, 1, shift,uni_size);
//    testNonAdaptiveNaiveCounter(n, &h, &TNSet, 1, shift,uni_size);
    int lookupRes = 1;
*/

    cout << "End!" << endl;
    return 0;
}
//    testHelperInsertionTime(n, eps, shift, uni_size);
//    testHelperRates(n, eps, lim, shift, uni_size);
//    srand(2);
//    testNonAdaptiveFP(n, eps, lim, lookupRes, shift, uni_size);
//    testNonAdaptiveFP(n, eps, lim, 1, shift, uni_size);
//    testHelperTN(n, eps, lim, shift, uni_size);
//    testNonAdaptiveTN(n, eps, lim, shift, uni_size);
//    srand(2);
//    srand(2);
//    testNonAdaptiveTN(n, eps, lim, shift, uni_size);
//    srand(2);
//    testNonAdaptiveTN(n, eps, lim, shift, uni_size);
//    srand(2);
//    testNonAdaptiveTN(n, eps, lim, shift, uni_size);
//    testNonAdaptiveTN(n, eps, lim, shift, uni_size);
//    srand(2);
//    testHelperTN(n, eps, lim, shift, uni_size);
//    srand(2);
//    testNonAdaptiveTN(n, eps, lim, shift, uni_size);
//    srand(2);
//    testHelperTN(n, eps, lim, shift, uni_size);
//    srand(2);
//    testNonAdaptiveTN(n, eps, lim, shift, uni_size);
//    srand(2);
//    testNonAdaptiveTP(n, eps, shift, uni_size);
//    testHelperTP(n, eps, shift, uni_size);
//    srand(2);
//    testHelperTP(n, eps, shift, uni_size);
//    testHelperNaiveLookup( n, eps, lim, naiveLim, shift, uni_size);
//    srand(2);
//    testNonAdaptiveNaiveLookup( n, eps, lim, naiveLim, shift, uni_size);
//    srand(2);
//    testHelperNaiveLookup( n, eps, lim, naiveLim, shift, uni_size);
//    srand(2);
//    testNonAdaptiveNaiveLookup( n, eps, lim, naiveLim, shift, uni_size);
//    srand(2);


//    testHelperRates(n, eps, lim, shift, uni_size);
//    testNonAdaptiveRates(n, eps, lim, shift, uni_size);

//    int m = (1 << 4);
//    cout  << m << endl;
//    vector<set<string> *> myVec(m);

//    cout << (myVec[1] == nullptr) << endl;
//    for (int k = 0; k < m ; k += 4) myVec[k] = new set<string>;
//    for (int k = 0; k < m ; k += 4) cout << (myVec[k] != nullptr) << ",";
//    cout << endl;
//    for (int i = 1; i < 4 ; ++i)
//    {
//        for (int k = i; k < m ; k += 4) cout << (myVec[k] == nullptr) << ",";
//        cout << endl;
//    }
//
//

//    for(int i = 0 ; i < 3; ++i) {
//        srand(1);
//    }


//    testNonAdaptiveRates(n, eps, lim, shift, uni_size);
//    srand(1);
//    testHelperRates(n, eps, lim, shift, uni_size);
//    srand(1);
//    testNonAdaptiveRates(n, eps, lim, shift, uni_size);
//    srand(1);

//    cout << "End!" << endl;
//}

/*
//        testHelperInsertionTime(n, eps, shift, uni_size);
//    set<const char*> mySet;
//    charSetInit(factor,&mySet,shift,uni_size);
//    cout << mySet.size() << endl;
//    for (auto iter : mySet) cout << *iter << ", ";
//
//    testHelperNaiveLookup(n, eps, lim, shift, uni_size);
//    testHelperFPTime(n, eps, lim, shift, uni_size);
//    testNonAdaptiveFP(n, eps, lim, shift, uni_size);
//
//    int rep = 5;
//    for (int i = 0; i < rep; ++i) {
//        srand(1);
//        testHelperInsertionTime(n, eps,shift, uni_size);
//        testNonAdaptiveHelperInsertionTime(n, eps,shift, uni_size);
//    }
//    int k = 100;
//    int a[k];
//    for(int i = 0 ; i < k; ++i ) a[i] = rand();
//    srand(1);
//    for(int i = 0 ; i < k; ++i ) a[i] -= rand();
//    for(int i = 0 ; i < k; ++i ) if(a[i]) cout << a[i] << endl;
//
//    srand(1);
//    testHelperInsertionTime(n, eps,shift, uni_size);
//    srand(1);
//    testHelperInsertionTime(n, eps,shift, uni_size);
//    srand(1);
//    testHelperInsertionTime(n, eps,shift, uni_size);
//    srand(1);
//    testHelperInsertionTime(n, eps,shift, uni_size);
//    srand(1);
//
//    testHelperInsertionTime(n, eps,shift, uni_size);
//    srand(1);
//    testNonAdaptiveHelperInsertionTime(n, eps,shift, uni_size);
//    srand(1);
//
//    testNonAdaptiveHelperInsertionTime()
//    testHelperFP(n, eps, lim, shift, uni_size);
//    testNonAdaptiveFP(n, eps, lim, shift, uni_size);
//    testHelperRates(n, eps, lim, shift, uni_size);
//    int x = 5;
//
//
//    sameString(100000, shift, uni_size);
//    cout << setInitRatio(1000, shift, uni_size) << endl;
//    int multiRatio = 4;
//    char temp = rand() % multiRatio;
//    int len = ++temp << shift;
//    cout << len << endl;
//    cout << (rand() % uni_size) << endl;
//
//    testNonAdaptiveHelperInsert(n,eps,lim,3);
//    testNonAdaptiveRates(n, eps, lim, shift, uni_size);
*/
