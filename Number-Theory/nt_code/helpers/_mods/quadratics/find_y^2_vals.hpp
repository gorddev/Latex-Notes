#pragma once
#include <vector>

#include "QuadraticFormula.hpp"

namespace gmath {

    inline std::vector<int> find_y_squared_vals(QuadraticFormula f, long mod) {
        std::vector<int> result;
        long d = (f.b*f.b) - (4*f.a*f.c);
        while (d < 0)
            d+= mod;
        d%= mod;

        for (int y = 0; y < d; y++) {
            long res = (y*y)%mod;
            if (res == d) {
                result.push_back(y);
            }
        }
        return result;
    }
}
