#pragma once
#include <iostream>
#include <regex>
#include <vector>

#include "../input_parsing/parse_equation.hpp"

namespace gan {

    inline void case_algebra_mode() {
        std::string a = "";
        std::cout << "\n--Algebra Mode--" << std::endl;
        std::cout << "> ";
        std::getline(std::cin, a);
        while (a != "exit") {
            std::cout << ":::" << gmath::parse_equation_from_arg(a) << "\n> ";
            std::getline(std::cin, a);
        }
        std::cout << "~Returning to program...\n" << std::endl;
    }

    inline std::vector<long> grab_ints(const std::vector<std::string> &requests) {
        std::vector<long> result;
        result.reserve(requests.size());

        // enables algebra restart
        bool algebra = true;
        while (algebra) {
            // Clears results in case of algebra mode
            algebra = false;
            result.clear();
            for (auto&i: requests) {
                std::string a;
                std::cout << i;
                std::getline(std::cin, a);
                if (a == "exit")
                    return {};

                // enters algebra mode
                if (a == "algebra") {
                    algebra = true;
                    case_algebra_mode();
                    break;
                }
                try {
                    result.push_back(gmath::parse_equation_from_arg(a));
                }
                catch (std::invalid_argument& e) {
                    std::cerr << e.what();
                    throw std::invalid_argument("");
                }


            }
        }
        return result;
    }
}
