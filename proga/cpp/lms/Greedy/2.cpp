#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v;
    int n;
    
    std::cin >> n;
    for (int i = 0; i < 2*n; i++) {
        int tmp;
        std::cin >> tmp;
        v.push_back(tmp);
    }
    std::sort(v.begin(), v.end());
    int sum = 0;
    for (int i = 0; i < 2*n; i+=2) {sum+=v[i];}
    std::cout << sum;
}