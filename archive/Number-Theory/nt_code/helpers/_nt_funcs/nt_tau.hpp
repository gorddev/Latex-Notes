#pragma once
#include <cstdint>

#include "get_divisors.hpp"

namespace gmath {

    /// calculates the number of divisors
    inline uint64_t nt_tau_force(long val) {
        return get_divisors(val).size();
    }
}
