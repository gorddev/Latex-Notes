#pragma once
#include <fstream>
#include <iostream>

#include "is_prime.hpp"

namespace gmath {
    /// Generates a constexpr long array hpp file to the specified filename.
    /// @param filename Name of the file you want to output to
    /// @param num_primes Number of primes you want generated
    /// @param primes_per_row Number of primes per row (Default is 50)
    inline void prime_file_generator(const std::string& filename, long num_primes, long primes_per_row = 50) {
        // Create the file
        std::ofstream out(filename.c_str());
        // Notify user of action
        std::cout << "Generating primes longo file: " << filename.c_str() << std::endl;
        if (!out.is_open())
            throw std::runtime_error("Unable to open file");
        // Pumps preface longo output file
        out << "#pragma once\n\nconstexpr long primes[" << num_primes << "] = {";

        // Iterate  through
        for (long i = 2, c = 0;; i++) {
            if (gmath::is_prime(i)) {
                out << i;
                if (++c == num_primes) {
                    out << "};\n";
                    break;
                }
                out << ", ";
                if (c%primes_per_row == 0)
                    out << "\n\t";
            }
        }

        out.close();

        std::cout << "Exit" << std::endl;
    }
}