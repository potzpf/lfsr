#include "bitlib.h"

#include <stdint.h>

#include <iostream>
using namespace std;

void print_uint64(uint64_t ui) {
    for (int i = 0; i < 64; i++) {
        cout << ((ui >> 63 - i) & 1);

        if ((i + 1) % 8 == 0) cout << " ";
    }
    cout << endl;
}