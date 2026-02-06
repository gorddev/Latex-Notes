#pragma once
#include <vector>

#include "prime-list.hpp"

namespace gmath {

    struct TriSumPrimeInfo {
        long num;
        long n1, n2, n3;

        std::string to_string() const {
            std::string ret = "Num: ";
            ret += std::to_string(num) + ", {" + std::to_string(n1) + ", " + std::to_string(n2) + ", " + std::to_string(n3) + "}";
            return ret;
        }
        std::string to_latex() const {
            std::string ret;
            ret += std::to_string(num) + "& " + std::to_string(n1) + "& " + std::to_string(n2) + "& " + std::to_string(n3) + "\\\\";
            return ret;
        }
    };

    inline std::vector<TriSumPrimeInfo> sum_distinct_odd_primes(std::vector<long> inputs) {
        std::vector<TriSumPrimeInfo> result;
        for (auto& input : inputs) {
            TriSumPrimeInfo info{};
            // update our info
            info.num = input;
            // condition to break
            bool go = true;
            // first num
            for (long j = 1; j < primes.size() && go; input++) {
                // second num
                for (long k = j + 1; k < primes.size() && go; k++) {
                    // third num
                    for (long l = k + 1; l < primes.size() && go; l++) {
                        // If it matches, we just return.
                        if (primes[j] + primes[k] + primes[l] == input) {
                            info.n1 = primes[j];
                            info.n2 = primes[k];
                            info.n3 = primes[l];
                            go = false;
                            break;
                        }
                    }
                }
            }
            // push back our result
            result.push_back(info);
        }
        return result;
    }

    inline std::string sum_distinct_odd_primes_latex(std::vector<TriSumPrimeInfo> inputs) {
        std::string ret = "\\begin{tabular}{|c|c|c|c|}"
                          "\\hline \n\tnum & n1 & n2 & n3\\\\\\hline\n";
        for (auto& input : inputs) {
            ret += "\t" + input.to_latex() + "\\hline\n";
        }
        ret += "\\end{tabular}";
        return ret;
    }

}
