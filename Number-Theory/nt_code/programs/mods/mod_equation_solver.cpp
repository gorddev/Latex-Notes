#include "../../helpers/_mods/mod_equation_solver.hpp"

#include <iostream>

#include "../../inc_all.hpp"
#include "../../helpers/_utilities/looping/input_looper.hpp"

void solve_mods(std::vector<long> args) {
    auto result = gmath::multi_mod_solver(args[0], args[1], args[2]);
    std::cout << "Solved mods for <" << args[0] << "x = " << args[1] << " (mod " << args[2] << ")>" << std::endl;
    if (result.empty())
        std::cout << "No solutions.";
    else {
        std::cout << "x = ";
        for (auto& sol: result) {
            std::cout << sol << ", ";
        }
    }
    std::cout << std::endl;
}

int main() {

    std::cout << "Solve Modulus equation: \nscalar * x = result (mod modulus)"<<std::endl;

    gan::input_looper_ints(&solve_mods,
        {
            {"----------\nScalar: "},
            {"Result: "},
            {"Modulus: "}
        }
    );

    return 0;
}
