#pragma once
#include <utility>
#include <vector>
#include "Equation.hpp"

struct EuclidResult {
    // contains the gcd
    long gcd;
    // contains the x and y;
    long x, y;
    // contains the a, b
    long a, b;
    // Contains the vector of forward equations
    std::vector<Equation> forward;
    // Contains the vector of backwards equations
    std::vector<Equation> backward;

    // converts the forward operation longo a string
    std::stringstream to_string(){
        std::stringstream ss;
        ss << "GCD of " << a << " and " << b << " is " << gcd << "\tx: " << x << "y: " << y << "\n";
        ss << "Forward Direction: \n";
        for (auto& i: forward)
            ss << i.to_string() << "\n";
        ss << "\nBackward Direction: \n";
        for (auto& i: backward)
            ss << i.to_string() << "\n";
        return ss;
    }

    void set_ab(long new_a, long new_b) {
        a = new_a;
        b = new_b;
    }

    void set_forward(std::vector<Equation> new_forward) {
        forward = std::move(new_forward);
        gcd = forward.back().terms[0].base;
    }
};
