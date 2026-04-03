#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    long long total = 0;
    std::vector<long long> boxes;
    for (int i = 0; i<n; i++) {
        long long tmp1;
        long long tmp2;
        std::cin >> tmp1 >> tmp2;
        total+=tmp1;
        boxes.push_back(tmp2);
    }
    //std::cout << total << std::endl;
    std::sort(boxes.begin(), boxes.end(), std::greater<long long>());
    int count = 0;
    for (long long box: boxes) {
        while (total > 0) {
            total-=box;
            count++;
        }
    }
    std::cout << count;
    return 0;
}