#pragma once
#include <cstdint>

#include "../_gcd/gcd.hpp"

namespace gmath {

    /// returns whether two numbers are relatively prime
    inline bool is_relatively_prime(uint64_t i1, uint64_t i2) {
        return (gcd(i1, i2) == 1);
    }
}
