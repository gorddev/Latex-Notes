#pragma once
#include <vector>
#include "../../inc_all.hpp"

namespace gmath {

    inline std::vector<long> find_x_pow_2_plus_1_primes(long num_primes) {
        std::vector<long> result;
        for (long i = 0; i < num_primes; i++) {
            bool found_prime = false;
            for (long j = 0; j < primes[i]; j++) {
                if ((j*j + 1) % primes[i] == 0) {
                    result.push_back(primes[i]);
                    found_prime = true;
                    break;
                }
            }
            if (!found_prime)
                std::cerr << "did not find prime: " << primes[i] << std::endl;
        }
        return result;
    }
}
