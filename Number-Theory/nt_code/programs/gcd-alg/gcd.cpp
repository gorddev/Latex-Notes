#include <iostream>

#include "../../helpers/_utilities/arguments/arg_enforcer.hpp"
#include "../../helpers/_utilities/arguments/arg_grabber.hpp"

/*
	Implementation of the euclidean gcd algorithm in C++
*/

long main(long argc, char* argv[]) {
	// Holds our original inputted a and b
	long oa, ob;
	// Holds the a and b used for calculations.
	long a, b;

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

	// update original values for printing at the end
	oa = a; ob = b;

	// Swap our two inputs if one is biffer than the other
	if (b > a)
		std::swap(a, b);

	while (b != 0) {
		const long r = a % b;
		if (r == 0)
			break;
		a = b;
		b = r;
	}

	std::cout << "GCD of " << oa << " and " << ob << " is " << b << "" << std::endl;
}