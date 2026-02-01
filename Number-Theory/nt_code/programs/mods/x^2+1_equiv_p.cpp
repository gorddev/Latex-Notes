#include "../../inc_all.hpp"
#include "../../helpers/_utilities/looping/input_looper.hpp"


int main() {

    auto result = gmath::find_x_pow_2_plus_1_primes(200);
    for (long i =0; i < result.size(); i++) {
        std::cout << result[i] << "\t";
        if (i %20 == 0 &&  i != 0)
            std::cout << std::endl;
    }
    return 0;
}