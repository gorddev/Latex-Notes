#include <iostream>

#include "../../helpers/_utilities/arguments/arg_enforcer.hpp"
#include "../../helpers/_utilities/arguments/arg_grabber.hpp"

/*
    Implementation of the berliner's gcd combo algorithm in C++
*/

long main(long argc, char* argv[]) {
    // Holds the a and b used for calculations.
    long a, b;

    // Allows for command line arguments
    if (gan::arg_enforcer(argc, argv, 3, false, true)) {
        auto args = gan::args_parse_ints(argc, argv);
        a = args[1];
        b = args[2];
    }
    else {
        // Get both of our numbers
        std::cout << "Enter first number:\n> ";
        std::cin >> a;
        std::cout << "Enter second number:\n> ";
        std::cin >> b;
    }

    if (b > a)
        std::swap(a, b);

    long ta = a, tb = b;

    // Find the gcd here
    while (tb != 0) {
        // Find the remainder
        const long r = ta % tb;
        // If r ia 0
        if (r == 0)
            break;
        ta = tb;
        tb = r;
    }

    // gcd is tb
    long gcd = tb;
    std::cout << "GCD is " << gcd << std::endl;

    long x = 1, y = 0;
    long result = x*a + y*b;
    while (result != gcd) {
        if (result > 0)
            (b > 0) ? y-- : y++;
        else
            (a > 0) ? x++ : x--;
        result = (x*a) + (y*b);
    }

    std::cout << "Linear combination is [" << x << " * (" << a << ")] + [" << y << " * (" << b << ")]" << std::endl;
}