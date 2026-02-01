#pragma once
#include <vector>

namespace gmath {

    inline std::vector<long> find_divisors(long n) {
        std::vector<long> result;
        for (long i = 1; i <= n; i++) {
            if (n% i == 0)
                result.push_back(i);
        }
        return result;
    }
}
