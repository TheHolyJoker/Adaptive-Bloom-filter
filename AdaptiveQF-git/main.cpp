#include <iostream>
#include "tests/Tests.h"
#include "VariableLengthFingerPrint/VLTests.h"

int main() {
    cout << "Hello, World!" << endl;

    double loadFactor = 0.5;
    size_t q = 8, r = 7, reps = int(SL(q) * loadFactor);

//    vlt4();
//    vlt5();
//    vlt6();
    vlt7();


    //    tr1();
//    srand(time(NULL));
    /*uint c = 0;
    for (int i = 0; i < SL(10); ++i) {
        if(!vlRandom(4, 5, 3, 4)) {
            ++c;
            if (c == 2)
                break;
        }
    }*/

/*
    for (int i = 0; i < 1000; ++i) {
        if(!vlRandom(6, 5, 5, 1))
            cout << "error" << endl;
    }
*/
//    vlt2();
//    vlt3();
//        VLtpLookup(q, r, reps, 4);
//    VLFingerPrint(q,r,reps);
//    cout << "reps is: " << reps << endl;
//    Helper h(q,)
//    srand(time(NULL));
//    for (int i = 0; i < q; ++i) {
//        hTPLookup(q, r, 3, reps);
//    }
//    rates(q, r, 0.6, 10000);
//    statusCorrectness(q,r,SL(11) + SL(10));
//    hpAdaptiveTest(q, r, reps, reps>>1);
//    callAll();
    cout << "End!" << endl;
    return 0;
}