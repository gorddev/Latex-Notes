#pragma once
#include <iostream>

namespace gmath {
    /// Solves the modulus equation scalar*x = result mod(modulus) for one solution
    /// @param scalar Scalar you multiply the "x" to solve the equation by
    /// @param modulus Modulus of the equation
    /// @param result Desired result of the equation
    /// @return The solution to the equation, or -1 if no solution.
    long mod_solver(long scalar, long result, long modulus) {
        for (long i = 1; i < modulus; i++) {
            if ((scalar*i) % modulus == result)
                return i;
        }
        return -1;
    }

    /// Solves the modulus equation scalar*x = result mod(modulus) for all solutions.
    /// @param scalar Scalar you multiply the "x" by
    /// @param result Result of the equation
    /// @param modulus The modulus you are working under
    /// @return A vector containing all solutions to the modulus equation
    std::vector<long> multi_mod_solver(long scalar, long result, long modulus) {
        std::vector<long> ret;
        for (long i = 1; i < modulus; i++) {
            if ((scalar*i) % modulus == result)
                ret.push_back(i);
        }
        return ret;
    }
}
