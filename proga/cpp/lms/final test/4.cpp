#include <iostream>
#include <vector>

int main() {
    int P;
    std::cin >> P;
    std::vector<int> v;
    for (int i = 0; i<P; i++) {
        int tmp;
        std::cin >> tmp;
        v.push_back(tmp);
    }
    int K;
    std::cin >> K;
    int count;
    int curr;
    for (int l = 1; l<P; l++) {
        curr = 0;
        count = 0;
        while (curr < P-1 && count < K+1) {
            curr+=l;
            while (v[curr] == 0) {curr--;};
            count++;
        }
        if (count <= K) {
            std::cout << l;
            return 0;
            //std::cout << count << std::endl;
        }
    }
    std::cout << P-1;
    //v.clear();
    return 0;
}