#pragma once
#include <vector>

#include "../_primes/is_relatively_prime.hpp"

namespace gmath {

    /// returns a vector containing all the relatively prime values
    inline std::vector<uint64_t> get_relative_primes(long val) {
        std::vector<uint64_t> res;
        for (long i = 1; i < val; i++) {
            if (is_relatively_prime(i, val))
                res.push_back(i);
        }
        return res;
    }
}
