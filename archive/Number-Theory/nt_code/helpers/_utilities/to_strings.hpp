#pragma once

#include <string>

namespace gan {
    std::string btostr(bool truth) {
        return (truth) ? "true" : "false";
    }

    template<typename T>
    std::string vec_to_string(std::vector<T> vec, int div = 8) {
        std::stringstream ss;
        ss << "---Vector to string:---\n";
        int count = 0;
        for (auto& t: vec) {
            ss << t << " ";
            if (count++ != 0 && count % div == 0)
                ss << "\n";
        }
        ss << "\n------End Vector----- ~";
        return ss.str();
    }
}

