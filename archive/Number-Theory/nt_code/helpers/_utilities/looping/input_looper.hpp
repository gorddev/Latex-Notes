#pragma once
#include <functional>

#include "../arguments/input_grabber.hpp"

namespace gan {
    ///
    /// @param user_func A function that returns a boolean that accepts a vector of longegers from the command loop.
    /// Return @code true@endcode to end the loop. If the user types "exit", the loops is also ended.
    inline void input_looper_ints(std::function<void(std::vector<long>)> user_func, std::vector<std::string> requests) {
        bool loop = true;
        while (loop) {
            std::vector<long> inputs = grab_ints(requests);
            if (inputs.empty()) {
                std::cout << "Exit protocol called." << std::endl;
                loop = false;
                break;
            }
            user_func(inputs);
        }
    }
}
