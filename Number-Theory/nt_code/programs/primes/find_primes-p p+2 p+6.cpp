#include <iostream>

#include "../../helpers/primes.hpp"

int main() {
    long count = 0;
    long i = 1;
    std::cout << "Print longing prime triplets: " << std::endl;
    auto begin_align_n = "\\begin{align*}\n";
    std::cout << begin_align_n;
    while (true) {
        if (gmath::is_prime(i) && gmath::is_prime(i+2) && gmath::is_prime(i+6)) {
            std::cout << "\t&" << i << ", " << i+2 << ", " << i+6 << "\\\\" << std::endl;
            if (++count >= 10)
                break;
        }
        i++;
    }
    std::cout << "\\end{align*}" << std::endl;
    return 0;
}