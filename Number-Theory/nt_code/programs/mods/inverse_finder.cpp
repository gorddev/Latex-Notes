#include "../../helpers/_mods/inverse_finder.hpp"

#include "../../inc_all.hpp"
#include "../../helpers/_utilities/looping/input_looper.hpp"

void solve_inverses(std::vector<long> args) {
    auto result = gmath::mod_inverse_finder(args[0]);

    std::cout << "Print longing mod inverses: " << args[0] << '\n';
    std::cout << "num inverses: " << result.size() << std::endl;
    for (auto&i: result) {

        std::cout << "a: " << i.first << "\tb: " << i.second << '\n';
    }
    std::cout << std::endl;
}

int main() {

    gan::input_looper_ints(
    &solve_inverses,
{
            "Enter modulus: "
        }
    );
}
