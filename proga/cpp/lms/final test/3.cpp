#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main() {
    int N;
    std::cin >> N;
    std::vector<int> v;
    for (int i = 0; i<N; i++) {
        int tmp;
        std::cin >> tmp;
        v.push_back(tmp);
    }
    std::sort(v.begin(), v.end());
    std::reverse(v.begin(), v.end());
    std::string ans;
    for (int n: v) {
        ans+=std::to_string(n);
    }
    std::cout << ans;
}