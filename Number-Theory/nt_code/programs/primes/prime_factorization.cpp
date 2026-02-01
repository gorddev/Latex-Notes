#include <complex>

#include "../../inc_all.hpp"
#include "../../helpers/_utilities/looping/input_looper.hpp"

long main(long argc, char* argv[]) {

    if (gan::arg_enforcer(argc, argv, 2, true, true)) {
        auto args = gan::args_parse_ints(argc, argv);
        for (auto& arg: args) {
            std::cout << gmath::prime_factor_string(static_cast<uint64_t>(arg)) << std::endl;
        }
    }
    else {
        auto mylam = [&](std::vector<long> args) {
            std::cout << gmath::prime_factor_string(static_cast<uint64_t>(args[0])) << std::endl;
        };

        gan::input_looper_ints(mylam, {"Enter number to prime factorize: "});
    }
}
