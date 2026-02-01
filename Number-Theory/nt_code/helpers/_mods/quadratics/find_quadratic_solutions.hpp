#pragma once
#include <vector>

#include "QuadraticFormula.hpp"

namespace gmath {

    long modInverse(long a, long m) {
        a %= m;
        for (long x = 1; x < m; x++) {
            if ((a * x) % m == 1) return x;
        }
        return -1; // Inverse does not exist
    }

    inline std::vector<int> find_quadratic_solutions(QuadraticFormula f, long mod) {
        std::vector<int> good_values;

        long d = ((f.b * f.b) - (4 * f.a * f.c)) % mod;
        if (d < 0) d += mod;

        long inv2a = modInverse(2 * f.a, mod);
        if (inv2a == -1) return {};

        for (long y = 0; y < mod; y++) {
            if ((y * y) % mod == d) {
                long x = ((y - f.b) * inv2a) % mod;
                if (x < 0) x += mod;

                bool exists = false;
                for (int val : good_values) if (val == x) exists = true;
                if (!exists) good_values.push_back((int)x);
            }
        }
        return good_values;
    }
}
