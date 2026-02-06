#pragma once
#include <sstream>
#include <utility>

#include "Number.hpp"

struct Equation {
    // Imagine it like this: 10 = 2(3) + 1
    // So it will be result = divisor + remainder
    Number result = {-1, 0};
    std::vector<Number> terms;
    long remainder = -1;

    // Default constructor
    Equation() = default;
    // Parameterized constructor for forwards direction
    Equation(long res, long div) : result{res, 1} {
        terms = {{div, res/div}};
        remainder = res%div;
    }
    // Parameterized constructor for backwards size
    Equation(long res, Number div, long remainder)
        : result{res, 1}, remainder(remainder), terms({div}) {
    }

    Equation(long res, std::vector<Number> terms) : result(res, 1){
        this->terms = std::move(terms);
    }

    // to string function
    std::string to_string() {
        std::stringstream ss;
        ss << result.base << " = ";
        bool first = true;
        for (auto&i : terms){
            if (first)
                first = false;
            else
                ss << ((i.scalar < 0) ? " " : " + ");
            ss << i.to_string();
        }
        if (remainder != 0)
            ss << " + " << remainder;
        return ss.str();
    }

    // adds a term to the equation
    void add_term(Number n) {
        for (auto& i : terms) {
            if (i.base == n.base) {
                i.scalar += n.scalar;
                return;
            }
        }
        terms.push_back(n);
    }

    // substitute a term in for another
    void substitute_term(long num, std::vector<Number> subs) {
        for (auto it = terms.begin(); it != terms.end(); ++it) {
            if (it->base == num) {
                auto oterm = *it;
                terms.erase(it);
                for (auto&s: subs)
                    add_term(s*oterm.scalar);
                return;
            }
        }
        //throw std::runtime_error("Err: no substition found for number");
    }
};
