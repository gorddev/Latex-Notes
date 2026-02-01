#pragma once
#include <iostream>
#include <vector>

namespace gan {

    /// @param argc Number of arguments provided via command line
    /// @param argv Vector of characters provided from the command line
    /// @return Vector containing each arguments containing an longeger. First argument is always negative 1.
    inline std::vector<long> args_parse_ints(long argc, char* argv[]) {
        std::vector<long> result = {-1};
        for (long i = 1; i < argc; ++i) {
            try {
                long a = std::stol(argv[i]);
                result.push_back(a);
            }
            catch (...) {
                throw std::runtime_error("Err (std::stol): arguments not parsable");
            }
        }
        return result;
    }


}
