#include "../../inc_all.hpp"
#include "../../helpers/_utilities/looping/input_looper.hpp"

void solve_nt_funcs(std::vector<long> args) {

    auto& val = args[0];
    std::cout << "tau: " << gmath::nt_tau_force(val) << std::endl;
    std::cout << "sigma: " << gmath::nt_sigma_force(val) << std::endl;
    std::cout << "phi: " << gmath::nt_phi_force(val) << std::endl << std::endl;;
}

int main() {

    gan::input_looper_ints(
        &solve_nt_funcs,
        {"Enter val: "
        });;
}