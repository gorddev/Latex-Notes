#pragma once
#include <string>

namespace gmath {

    inline std::string ceaser_cipher(std::string text, uint32_t scalar, uint16_t shift) {
        std::string ret;

        for (auto& s: text) {
            if (s >= 'A' && s <= 'Z') {
                s -= 'A';
                ret += (((scalar*s) + shift) % 26) + 'A';
            }
            else if (s >= 'a' && s <= 'z') {
                s -= 'a';
                ret += (((scalar*s) + shift) % 26) + 'a';
            }
            else
                ret += s;
        }
        return ret;
    }
}
