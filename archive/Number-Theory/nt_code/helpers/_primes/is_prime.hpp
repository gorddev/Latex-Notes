#pragma once

namespace gmath {
    bool is_prime(long p) {
        if (p == 2)
            return true;
        if (p %2 == 0)
            return false;
        for (long i = 3; i < p; i+=2)
            if (p % i == 0)
                return false;
        return true;
    }
}