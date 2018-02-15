#include "lfsr.h"
#include "bitlib.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

lfsr::lfsr(size_t size, uint64_t seed) : state(seed), size(size) {
    //delete bits of seed that exceed size
    uint64_t mask = 0;
    for (int i = 0; i < size; i++) 
        mask |= 1 << i;
    state &= mask;
}

void lfsr::set_taps(vector<int> t) {
    sort(t.begin(), t.end());
    taps = t;
}

int lfsr::feedback() {
    int f = 0;
    for (int i = 0; i < taps.size(); i++) {
        f += (state >> taps[i]) & 1;
    }

    return f % 2;
}

int lfsr::clock() {
    int o = (state >> (size - 1)) & 1; // save output bit

    state = (state << 1) | feedback(); //linear feedback + shift register

    //print_state();

    return o;
}

uint64_t lfsr::generate(size_t n) {
    uint64_t ret = 0;

    for (size_t i = 0; i < n; i++) {
        ret |= clock();
        ret <<= 1;
    }

    return ret;
}

void lfsr::print_state() {
    print_uint64(state);
}