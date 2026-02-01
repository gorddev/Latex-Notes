#pragma once
#include <string>
#include <unordered_map>
#include "prime-list.hpp"

namespace gmath {
    struct PrimeExponent {
        uint64_t p;
        uint64_t pow;
        PrimeExponent(uint64_t p, uint64_t pow) : p(p), pow(pow) {}
    };

    struct PrimeFactorization {
    private:
        const long n;
        /// Map from primes to exponent of said primes.
        std::vector<PrimeExponent> factors;
        /// Contains a bucket that just contains factors and their exponents
        std::unordered_map<uint64_t, uint64_t> factor_map;

    public:
        PrimeFactorization(uint64_t n) : n(abs(static_cast<long>(n))) {
            n = abs(static_cast<long>(n));
            for (long i = 0; i < primes.size(); i++) {
                // goes through and does factorization on everything
                if (n % primes[i] == 0) {
                    factors.emplace_back(primes[i], 1);
                    factor_map[primes[i]] = 1;
                    n /= primes[i];
                    while (n % primes[i] == 0) {
                        factors.back().pow++;
                        factor_map[primes[i]]++;
                        n /= primes[i];
                    }
                }
                if (n == 1)
                    break;
            }
        }

        bool contains_factor(uint64_t p) {
            return factor_map.count(p);
        }

        /// Grabs the specific exponent of the factor desired.
        uint64_t operator[](uint64_t p) {
            if (!contains_factor(p)) {
                std::string ret = "PrimeFactorization::operator[]. This factorization does not contain ";
                ret += std::to_string(p);
                throw std::runtime_error(ret);
            }
            return factor_map[p];
        }

        /// gets the string of the prime factorization
        std::string to_string() {
            std::string ret = "[p-fact of " + std::to_string(n) + "]: ";
            for (auto& pe: factors)
                ret += std::to_string(pe.p) + "^" + std::to_string(pe.pow) + " ";
            return ret;
        }
    };

    inline std::string prime_factor_string(uint64_t n) {
        PrimeFactorization factors(n);
        return factors.to_string();
    }
}