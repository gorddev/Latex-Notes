#include <iostream>

#include "../../helpers/primes.hpp"
#include "../../helpers/utilities.hpp"

int main() {
    long unsigned long m = 8;
    std::cout << "Mersenne Primes: \n";
    for (long i = 3; i < 20; i++) {
        std::cout << "2^" << i << " = " << (m - 1) << ":::" << gan::btostr(gmath::is_prime(m - 1)) << "\n";
        m*=2;
    }
    std::cout << std::endl;
    return 0;
}
