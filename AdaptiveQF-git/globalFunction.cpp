//
// Created by tomer on 10/26/18.
//

#include "globalFunction.h"

void arrayPrinter(uint16_t *a, size_t length) {
    cout << "[" << a[0];
    for (int i = 1; i < length; ++i) {
        cout << ", " << a[i];
    }
    cout << "]" << endl;
}

void arrayPrinter(size_t *a, size_t length) {
    cout << "[" << a[0];
    for (int i = 1; i < length; ++i) {
        cout << ", " << a[i];
    }
    cout << "]" << endl;
}
