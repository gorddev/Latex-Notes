#include <iostream>


#include "../../helpers/_gcd/gcd.hpp"


constexpr long num = 30;

long main () {

    long count = 0;
    for (long i = 2; i < 10000; i++) {
        if (gmath::gcd(i, num) == 1 && !gmath::is_prime(i)) {
            std::cout << "Rel prime: " << i << std::endl;
            if (++count > 10)
                break;
        }

    }
    return 0;
}