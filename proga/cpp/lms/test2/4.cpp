#include <iostream>

int is_powerof2(int uint64_t) {
    if ((uint64_t & (uint64_t - 1)) == 0) {return 1;}
    else {return 0;}
}

int main() {
    //std::cout << (1024 & 1023) << std::endl;

    std::cout << is_powerof2(1) << std::endl;
    std::cout << is_powerof2(3) << std::endl;
    std::cout << is_powerof2(1024) << std::endl;
    std::cout << is_powerof2(68) << std::endl;
    return 0;
}