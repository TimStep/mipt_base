#include <iostream>
#include <vector>
#include <numeric>

int main() {
    std::vector<long long> v;
    int N;
    std::cin >> N;
    for (int i = 0; i < N; i++) {
        int tmp;
        std::cin >> tmp;
        v.push_back(tmp);
    }

    //long long s = std::accumulate(v.begin(), v.end(), 0);
    long long s = 0;
    for (long long num: v) {
        s+=num;
    }
    //std::cout << s << std::endl;
    long long curr_sum = 0;
    for (int i = 0; i < N; i++) {
        curr_sum+=v[i];
        s-=v[i];
        //std::cout << curr_sum << " " << s << std::endl;
        if (curr_sum == s) {
            std::cout << i+1;
            return 0;
        }
    }
    std::cout << N;
    return 0;
}