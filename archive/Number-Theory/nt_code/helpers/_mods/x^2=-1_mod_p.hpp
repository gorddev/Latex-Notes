#pragma once
#include <vector>

namespace gmath {

    inline std::vector<int> find_x_squared_equiv_neg_one_mod_p(long mod) {
        std::vector<int> result;
        for (int x = 1; x < mod; x++) {
            if ((x*x)% mod == (mod-1))
                result.push_back(x);
        }
        return result;
    }
}
