#include <iostream>
#include <vector>
#include <algorithm>

unsigned max_unique_subarray_length(char const symbols[], unsigned size) {
    int res = 0;
    std::vector<char> sub;
    for (unsigned int i = 0; i < size; i++) {
        std::cout << symbols[i] << std::endl;
        if (std::find(sub.begin(), sub.end(), symbols[i]) == sub.end()) {sub.push_back(symbols[i]);}
        else {
            sub.erase(sub.begin(), std::find(sub.begin(), sub.end(), symbols[i])+1);
            sub.push_back(symbols[i]);
        }
        if (sub.size() > res) {res = sub.size();}
        for (int i = 0; i < sub.size(); i++) {std::cout << sub[i];}
        std::cout << std::endl;
    }
    
    return res;
}

int main() {
    char test[11] = {'a', 'b', 'b', 'c', 'd', 'a', 'e', 'f', 'g', 'a', 'b'};
    std::cout << max_unique_subarray_length(test, 11);
}