#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "../generic_math/factorial.hpp"

namespace gmath {

    constexpr long parse_operation_size = 5;
    constexpr char parse_modulus_text[4] = {"mod"};
    constexpr char parse_operations[parse_operation_size] = {'^', '*', '/', '+', '-'};

    /// Returns true if we find a multi-character operation
    inline bool equals_operation(std::string& r_arg, long& pos, const char op[]) {
        long tpos = 0;

        while (op[tpos] != '\0') {
            char ste1 = r_arg[pos+tpos];
            char ste2 = op[tpos];
            if (ste1 != ste2)
                return false;
            tpos++;
        }
        return true;
    }

    /// holds information regarding the parsing of string numbers
    struct IntegerParseInfo {
        long n1, n2;
        long back, front;
        long result;
    };

    /// Finds the substrings that make up the two surrounding numbers
    inline IntegerParseInfo find_equation_operands(std::string& r_arg, long pos, long forward_offset = 1) {
        // go backwards and get the first number
        long b = pos, f = pos;
        // find where the first number starts
        bool space_flip = false;
        for (b = pos - 1; b >= 0 && (!space_flip || (r_arg[b] >= '0' && r_arg[b] <= '9')); b--) {
            if (!space_flip && r_arg[b] >= '0' && r_arg[b] <= '9')
                space_flip = true;
            else if (space_flip && r_arg[b] == ' ')
                break;
        }
        b++;
        // find where the second number ends
        space_flip = false;
        for (f = std::min(pos + forward_offset, static_cast<long>(r_arg.length()) - 1); f < r_arg.length() && (!space_flip || (r_arg[f] >= '0' && r_arg[f] <= '9')); f++) {
            if (!space_flip && r_arg[f] >= '0' && r_arg[f] <= '9')
                space_flip = true;
            else if (space_flip && r_arg[f] == ' ')
                break;
        }
        f--;
        // then we perform the operation simplifying the expression
        IntegerParseInfo result{};
        auto str1 = r_arg.substr(b, (pos) - b );
        auto str2 = r_arg.substr(pos+forward_offset, f - (pos+forward_offset -1));
        if (!str1.empty())
            result.n1 = std::stol(str1);
        if (!str2.empty())
            result.n2 = std::stol(str2);
        result.back = b;
        result.front = f;
        return result;
    }

    inline IntegerParseInfo find_left_operand(std::string& r_arg, long pos, long forward_offset = 1) {
        // go backwards and get the first number
        long b = pos;
        // find where the first number starts
        bool space_flip = false;
        for (b = pos - 1; b >= 0 && (!space_flip || (r_arg[b] >= '0' && r_arg[b] <= '9')); b--) {
            if (!space_flip && r_arg[b] >= '0' && r_arg[b] <= '9')
                space_flip = true;
            else if (space_flip && r_arg[b] == ' ')
                break;
        }
        b++;
        // then we perform the operation simplifying the expression
        IntegerParseInfo result{};
        auto str1 = r_arg.substr(b, (pos) - b );
        if (!str1.empty())
            result.n1 = std::stol(str1);
        result.back = b;
        result.front = pos;
        return result;
    }

    inline void refactor_string_with_parse_info(std::string& r_arg, IntegerParseInfo& n) {
        int mod = (n.front < r_arg.length()) ? 1: 0;
        r_arg = r_arg.substr(0 , n.back) + std::to_string(n.result) + r_arg.substr(n.front + mod);
    }


    inline long recursive_step_parse_equation_from_arg(std::string r_arg) {

        // loop through and evaluate everything in parenthesis
        for (long i = 0; i < r_arg.length(); i++) {
            // if we encounter an open parenthesis
            if (r_arg[i] == '(') {
                // find the next parenthesis
                for (long j = static_cast<long>(r_arg.length()) - 1; j > i; j--) {
                    if (r_arg[j] == ')') {
                        // Grab the size we need to replace
                        long substr_size = j - i - 1;
                        // Apply our recursive step and grab the number
                        long new_number = recursive_step_parse_equation_from_arg(
                            r_arg.substr(
                                i + 1,
                                substr_size
                            )
                        );
                        // change our string to be something new with the number evaluation
                        r_arg = r_arg.substr(0,(i))
                            + std::to_string(new_number)
                            + r_arg.substr(j + 1);
                    }
                }
            }
        }

        // first we loop through our special operations


        for (long s = 0; s < r_arg.length(); s++) {
            // FACTORIAL
            if (r_arg[s] == '!') {
                auto n = find_left_operand(r_arg, s + 1);
                n.result = factorial(n.n1);
                refactor_string_with_parse_info(r_arg, n);
                s = -1;
                continue;
            }
            // MODULUS
            if (s < static_cast<long>(r_arg.length() - 2) && equals_operation(r_arg, s, parse_modulus_text)) {
                auto n = find_equation_operands(r_arg, s, 3);
                n.result = n.n1 % n.n2;
                refactor_string_with_parse_info(r_arg,n);
                s = -1;
                continue;
            }
        }

        // now we loop through each of our standard operations:
        for (long i = 0; i < parse_operation_size; i++) {
            for (long s = 0; s < r_arg.length(); s++) {
                if (r_arg[s] == parse_operations[i]) {
                    // grab our results
                    auto n = find_equation_operands(r_arg, s);
                    // switch through each of our operations
                    switch (parse_operations[i]) {
                        case '^':
                            n.result = std::pow(n.n1, n.n2);
                            break;
                        case '*':
                            n.result = n.n1*n.n2;
                            break;
                        case '+':
                            n.result = n.n1 + n.n2;
                            break;
                        case '-':
                            n.result = n.n1 - n.n2;
                            break;
                        case '/':
                            n.result = n.n1 / n.n2;
                            break;
                        default:
                            n.result = n.n1;
                    }
                    refactor_string_with_parse_info(r_arg, n);
                    i = 0;
                    s = -1;
                    continue;
                }
            }
        }
        long b, f;
        for (b = 0; b < r_arg.length() && !(r_arg[b] >= '0' && r_arg[b] <= '9'); b++) {}
        // find where the second number ends
        for (f = b + 1; f < r_arg.length() && (r_arg[f] >= '0' && r_arg[f] <= '9'); f++) {}
        return std::stol(r_arg.substr(b, f - b));
    }

    inline long parse_equation_from_arg(std::string arg) {

        // first we parse for lack of multiplication with parenthesis
        for (long i = 0; i < arg.length(); i++) {
            if (arg[i] == '(') {
                if (i > 0) {
                    bool add_mult = false;
                    // loop backwards to add in multiplication sign if parenthesis
                    for (long j = i - 1; j < arg.length(); j--) {
                        if (arg[j] != ' ') {
                            if (arg[j] == '/' ||
                                arg[j] == '-' ||
                                arg[j] == '+' ||
                                arg[j] == '^' ||
                                arg[j] == '!' ||
                                arg[j] == '(')
                                break;
                            add_mult = true;
                            break;
                        }
                    }
                    if (add_mult) {
                        arg.insert(i, "*");
                        i++;
                    }
                }
            }
        }
        return recursive_step_parse_equation_from_arg(arg);
    }
}
