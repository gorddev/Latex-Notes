#include <iostream>
#include "../../inc_all.hpp"
#include "../../helpers/_utilities/looping/input_looper.hpp"


int main() {

    uint64_t mod;
    std::cout << "Enter mod: ";
    std::cin >>  mod;

    auto mylam = [&](std::vector<long> args) {
        uint64_t mult = args[0];
        for (long i = 2; i < mod; i++) {
            mult *= args[0];
            mult %= mod;
            std::cout << "Result: " << args[0] << "^" << i << ": " << mult << std::endl;
        }
        std::cout << std::endl;
    };

    gan::input_looper_function myfunc;

    gan::input_looper_ints(mylam, {"Number: "});
}
