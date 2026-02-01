#pragma once
#include "get_divisors.hpp"

namespace gmath {

    /// Calculates the sum of the positive divisors
    long nt_sigma_force(long val) {
        auto res = get_divisors(val);
        long sum = 0;
        for (auto& r: res) {
            sum += r;

        }
        return sum;
    }
}
