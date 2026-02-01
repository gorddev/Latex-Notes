#include <iostream>
#include "EuclidResult.hpp"

std::vector<Equation> euclid_forward(long a, long b) {
    std::vector<Equation> results;
    // swap if a is less than
    if (a < b) std::swap(a, b);
    // get our result to the back of our vector
    results.emplace_back(a, b);
    // while the back of our vector has a nonzero remainder
    while (results.back().remainder != 0) {
        // each iteration, add a new euclid equation to the back of the vector
        results.emplace_back(
            results.back().terms[0].base,
            results.back().remainder
        );
    }

    return results;
}


std::vector<Equation> euclidean_backwards(std::vector<Equation> forwards) {
    std::vector<Equation> backwards;

    long L = forwards.size();
    if (forwards.size() > 1) {
        Equation curr = {forwards[L-1].terms[0].base, 1};
        curr.terms = {forwards[L-1].result};
        backwards.push_back(curr);
        long target = forwards[L-1].result.base;
        for (long i = static_cast<long>(forwards.size()) - 2; i >= 0; i--) {
            Equation subby = forwards[i];
            curr.substitute_term(target, {subby.result, subby.terms[0]*-1});
            backwards.push_back(curr);
            target = forwards[i+1].result.base;
        }
    }
    return backwards;
}

EuclidResult euclidean_alg(long a, long b) {
    // Create a result object to return
    EuclidResult result;
    // Get our a and get our b
    result.set_ab(a, b);
    // Get our forward euclidean equation:
    result.set_forward(euclid_forward(a, b));
    // Get our backwards terms
    result.backward = euclidean_backwards(result.forward);
    // Now, we need to get the backwards direction, which is a bit trickier
    return result;
}


long main(long argc, char* argv[]) {
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

    auto result = euclidean_alg(a, b);

    std::cout << "------------------------\n";
    std::cout << result.to_string().str() << std::endl;
    std::cout << "Verification: ";
    std::cout << result.backward.back().terms[0].val() + result.backward.back().terms[1].val() << std::endl;
}