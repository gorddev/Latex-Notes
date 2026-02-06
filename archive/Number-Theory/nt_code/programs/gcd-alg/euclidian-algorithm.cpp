

#include <iostream>
#include "../../helpers/gcd.hpp"

int main(int argc, char* argv[]) {
    // Holds the a and b used for calculations.
    long a, b;

    // Allows for command line arguments
    if (argc > 1) {
        // If we don't have enough arguments.
        if (argc == 2) {
            std::cerr << "Uh oh you gotta provide three arguments to find gcd. Usage: <gcd.cpp> a b";
            return 1;
        }
        // Update a and b with our command line arguments. Use a try catch block
        try {
            a = std::stol(argv[1]);
            b = std::stol(argv[2]);
        }
        catch (...) {
            std::cerr << "Err (std::stol): arguments not parsable" << std::endl;
            return 1;
        }
    }
    else {
        // Get both of our numbers
        std::cout << "Enter first number (a):\n> ";
        std::cin >> a;
        std::cout << "Enter second number (b):\n> ";
        std::cin >> b;
    }

    auto result = gmath::euclidean_alg(a, b);

    std::cout << "------------------------\n";
    std::cout << result.to_string().str() << std::endl;
    std::cout << "Verification: ";
    std::cout << result.backward.back().terms[0].val() + result.backward.back().terms[1].val() << std::endl;
}
