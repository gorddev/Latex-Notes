#pragma once
#include <cstdint>

namespace gmath {

    long factorial(uint32_t val) {
        if (val == 0) return 1;
        long mult = 1;
        for (long i = 2; i <= val; i++) {
            mult *= i;
        }
        return mult;
    }
}
