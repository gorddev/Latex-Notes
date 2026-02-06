#pragma once
#include <__utility/swap.h>

namespace gmath {
    long gcd(long a, long b) {
        if (a < b)
            std::swap(a, b);
        while (b != 0) {
            const long r = a % b;
            if (r == 0)
                break;
            a = b;
            b = r;
        }
        return b;
    }
}
