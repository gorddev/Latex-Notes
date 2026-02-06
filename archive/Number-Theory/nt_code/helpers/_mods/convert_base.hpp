#pragma once

#include <iostream>

#include "Base.hpp"

namespace gmath {

    void print_base(uint64_t num, uint64_t base, bool verbose = false) {
        Base mybase(num, base);
        if (!verbose)
            std::cout << mybase.to_string() << std::endl;
        else
            std::cout << mybase.to_string_verbose() << std::endl;
    }

}