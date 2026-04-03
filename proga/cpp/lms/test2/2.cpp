#include <iostream>

unsigned long long redux(unsigned long long a) {
    // Code goes here;
    unsigned long long res = a;
    unsigned long long temp;
    while (res > 9) {
        temp = 0;
        while (res > 0) {
            temp += res % 10;
            res /= 10;
        }
        res = temp;
    }
    return res;
}

int main() {
    std::cout << redux(63) << std::endl;
    std::cout << redux(999) << std::endl;  
    std::cout << redux(9991) << std::endl;  
}