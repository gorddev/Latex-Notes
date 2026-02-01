#pragma once
#include <iostream>
#include <vector>

namespace gmath {

    inline std::vector<std::pair<uint64_t, uint64_t>> mod_inverse_finder(uint64_t mod) {
        std::vector<std::pair<uint64_t, uint64_t>> pairs;
        for (long m = 1; m < mod; m++) {
            for (long j = 1 ; j < mod; j++) {
                if (((m*j)%mod) == 1)
                    pairs.push_back(std::pair<uint64_t, uint64_t>(m, j));
            }
        }
        return pairs;
    }
}
