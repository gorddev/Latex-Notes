#pragma once

struct Number {
    long base;
    long scalar = 1;
    // Default constructor
    Number(long num) : base(num) {}
    // Two param constructor
    Number(long num, long scalar) : base(num), scalar(scalar) {}
    // Operator overloads
    // multiplication
    Number operator*(long scl) { return {this->base, this->scalar*scl}; }
    void operator*=(long scl) { this->scalar *= scl; }
    // addition
    Number operator+(Number& other) {
        if (other.base != base)
            throw std::runtime_error("Uh oh two numbers of different bases cannot be added together");
        return {base, scalar + other.scalar};
    }
    void operator+=(Number& other) {
        if (other.base != base)
            throw std::runtime_error("Uh oh two numbers of different bases cannot be added together");
        this->scalar += other.scalar;
    }

    // to string
    std::string to_string() {
        std::string ret = std::to_string(scalar) + "(" + std::to_string(this->base) + ")";
        return ret;
    }

    long val() {
        return scalar*base;
    }
};