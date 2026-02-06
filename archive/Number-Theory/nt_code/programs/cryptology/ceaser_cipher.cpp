#include "../../inc_all.hpp"
#include "../../helpers/_utilities/looping/input_looper.hpp"

void ceaser_encode(std::vector<long> args) {
    std::cout << "String: ";
    std::string str;
    std::getline(std::cin, str);
    std::cout << "Encoded: " << gmath::ceaser_cipher(str, args[0], args[1]) << "\n" << std::endl;
}

int main() {
    gan::input_looper_ints(&ceaser_encode,
        {"Scalar: ", "Shift: "}

    );
    return 0;
}