#pragma once
#include <cstdint>

#include "get_relative_primes.hpp"

namespace gmath {

    /// returns the number of longegers between 1 and n that are relatively prime to n
    uint64_t nt_phi_force(long val) {
        return get_relative_primes(val).size();
    }
}
