#pragma once
#include <string>

namespace gan {
    /// If the user-specified conditions are not satisfied, this function will throw an error.
    /// @details For example, if the user has a desired arg count, and @code allow_more_args = false, allow_no_args = false@endcode,
    /// unless the exact number of arguments is provided, this function will throw an error.
    /// @param argc Number of arguments from command line
    /// @param argv Vector containing arguments from command line
    /// @param desired_argc The desired argument count the user wants
    /// @param allow_more_args Allows for more arguments than requested, and will not throw error
    /// @param allow_no_args Allows for no arguments to be requested, and will not throw error
    /// @return Will return false if the @code allow_no_args@endcode flag is set to true, and the user adds no additional arguments.
    bool arg_enforcer(long argc, char* argv[], long desired_argc, bool allow_more_args = false, bool allow_no_args = false) {
        if (allow_more_args) {
            if (argc >= desired_argc)
                return true;
            if (!allow_no_args || argc != 1) {
                std::string err = "Err: Program ";
                err += argv[0];
                err += " requires " + std::to_string(desired_argc) + " arguments or more.";
                throw std::runtime_error(err);
            }
        }
        else {
            if (argc == desired_argc)
                return true;
            if (!allow_no_args || argc != 1) {
                std::string err = "Err: Program ";
                err += argv[0];
                err += " requires " + std::to_string(desired_argc) + " arguments.";
                throw std::runtime_error(err);
            }
        }
        return false;
    }
}
