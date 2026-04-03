#include <iostream>

unsigned long long collatz_conjecture_count(unsigned long long a) {
    // Code goes here;
    int count = 0;
    unsigned long long curr = a;
    unsigned long long next;
    while (curr != 1) {
        count += 1;
        if (curr % 2 == 0) {next = curr/2;}
        else {next = 3*curr + 1;}
        curr = next;
    }
    return count;
}

int main() {
    std::cout << collatz_conjecture_count(1) << std::endl;
    std::cout << collatz_conjecture_count(2) << std::endl;
    std::cout << collatz_conjecture_count(3) << std::endl;
}