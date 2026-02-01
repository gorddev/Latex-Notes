#pragma once
#include "../../inc_all.hpp"
#include "../../helpers/_utilities/looping/input_looper.hpp"

void find_solutions(std::vector<long> args) {
    auto result = gmath::find_x_squared_equiv_neg_one_mod_p(args[0]);
    std::cout << "solutions: " << result[0] << ", " << result[1] << std::endl;
}

int main() {

    std::cout << "find solutions for equation: x^2 equiv -1 mod p" << std::endl;

    gan::input_looper_ints(
        &find_solutions,
        {"Enter modulus: "}
    );
}