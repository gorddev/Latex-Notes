#include "../../inc_all.hpp"
#include "../../helpers/_mods/quadratics/find_y^2_vals.hpp"
#include "../../helpers/_utilities/looping/input_looper.hpp"

void print_quad_sols(std::vector<long> args) {
    auto y_vals = gmath::find_y_squared_vals({args[0], args[1], args[2]}, args[3]);
    auto result = gmath::find_quadratic_solutions({args[0], args[1], args[2]}, args[3]);
    int count = 0;

    std::cout << "y = 2(" << (args[0]) << ")x + " << args[1] << std::endl;
    std::cout << "d = 4(" << (args[0]) << ")(" << args[2] << ") = " << ((args[1]*args[1])-(4*args[0]*args[2]))%args[3] << std::endl;
    std::cout << "y^2-vals: ";
    for (auto& y: y_vals) {
        std::cout << y << " ";
    }
    std::cout << std::endl;
    std::cout << "Solutions: ";
    for (auto& i: result) {
        std::cout << i << " ";
        if (count != 0 && count > 8)
            std::cout << "\n";
        count++;
    }
    std::cout << std::endl;
}

int main() {

    gan::input_looper_ints(&print_quad_sols,
        {
        "Enter equation <ax^2 + bx + c = d (mod n)>\na: ",
            "b: ",
            "c: ",
            "n: "
        }
    );
}