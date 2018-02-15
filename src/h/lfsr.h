#ifndef _LFSR_H_
#define _LFSR_H_
#include <vector>
#include <stdint.h>
#include <stdlib.h>

#include <array>

class lfsr {
private:
    uint64_t mask;
    uint64_t state;
    size_t size;

    std::vector<int> taps;
public:
    lfsr(uint64_t seed, size_t size);
    void set_taps(std::vector<int> taps);

    int clock();
    uint64_t generate(size_t n);

    int feedback();
    void print_state();
};

#endif