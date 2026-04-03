#include <iostream>

bool can_place_musicians(bool *begin, bool *past_the_last, unsigned M) {
    unsigned availible = 0;
    bool *current = begin;
    while (current != past_the_last) {
        if (*current && (current-1 == nullptr || *(current-1)) && (current+1 == past_the_last || *(current+1)) ) {
            availible++;
            *current=false;
        }
        current++;
    }
    std::cout << availible << std::endl;
    if (availible >= M) {return true;}
    return false;
}

int main() {
    unsigned const N = 5;
    bool rooms[N];

    std::cin >> std::boolalpha;
    for (unsigned i = 0; i != N; ++i)
    std::cin >> rooms[i];

    unsigned M;
    std::cin >> M;

    std::cout << can_place_musicians(rooms, rooms + 5, M);
}