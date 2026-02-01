#pragma once
#include <vector>

#include "gcd.hpp"

namespace gmath {

    /// Contains all the linear combination information of a gcd calculation:
    /// - @code a, b@endcode › Numbers you want to find the linear combo of.
    /// - @code gcd@endcode › The gcd of the operation
    /// - @code x, y@endcode › The scalars of thelinear combination
    struct GCDLinearComboInfo {
        long a, b;
        long gcd;
        long x, y;
    };
    /// Linear combination calculator. Finds the gcd & linear combination.
    inline GCDLinearComboInfo linear_combination(long n1, long n2) {
        GCDLinearComboInfo info;
        if (n1 < n2)
            std::swap(n1, n2);
        info.a = n1;
        info.b = n2;
        info.gcd = gcd(n1, n2);

        long x = 1, y = 0;
        long result = x*n1 + y*n2;
        while (result != info.gcd) {
            if (result > 0)
                (n2 > 0) ? y-- : y++;
            else
                (n1 > 0) ? x++ : x--;
            result = (x*n1) + (y*n2);
        }
        info.x = x;
        info.y = y;
        return info;
    }
}
