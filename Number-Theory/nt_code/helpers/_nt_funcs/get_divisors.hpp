#pragma once
#include <vector>

namespace gmath {

    /// returns a vector containing all the divisors of a number
    std::vector<long> get_divisors(long val) {
        std::vector<long> result;
        for (long i = 1; i <= val/2; i++) {
            if (val %i == 0)
                result.push_back(i);
        }
        result.push_back(val);
        return result;
    }
}
