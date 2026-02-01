#pragma once
#include <vector>

namespace gmath {

    struct Base {
        uint64_t original_num;
        uint64_t base;
        std::vector<uint64_t> numbers;

        Base(uint64_t num, uint64_t base) : original_num(num), base(base) {
            // error if it doesn't work.
            if (base <= 1)
                throw std::out_of_range("Base::Base(), template must be greater than or equal to 2");
            uint64_t itemp = 1;
            long count = 1;
            // go through and increase our itemp as necessary
            while (itemp <= num / base) {
                itemp = itemp * base;
                count++;
            }
            // resize so we fit all of our longegers
            numbers.resize(count);
            // then we start diving and conquering.
            // then iterate through our counter
            for (long i = 0; i < count; i++) {
                uint64_t div = num / itemp;
                numbers[i] = div;
                num %= itemp;
                itemp /= base;
            }
        }

        std::string to_string() const {
            std::string ret = "Base<";
            ret += std::to_string(base) + "> of " + std::to_string(original_num) + " = ";
            for (auto&i : numbers)
                ret += std::to_string(i) + " ";
            return ret;
        }

        std::string to_string_verbose() const {
            std::string ret = "Base<";
            ret += std::to_string(base) + "> of " + std::to_string(original_num) + " = ";
            for (auto&i : numbers)
                ret += std::to_string(i) + " ";
            ret+="\nFull = ";
            long count = numbers.size() -1;
            for (auto&i : numbers) {
                ret += std::to_string(base) + "^" + std::to_string(count) + "*(" + std::to_string(i) + ") ";
                count--;
            }
            return ret;
        }
    };
}
