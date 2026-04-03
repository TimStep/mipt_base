#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int N;
    std::vector<int> v;
    int L;
    std::cin >> N;
    for (int i = 0; i < N; i++) {
        int tmp;
        std::cin >> tmp;
        v.push_back(tmp);
    }
    std::cin >> L;

    long long s = 0;
    for (int n: v) {
        s+=n;
    }

    if (s<L) {
        std::cout << N;
        return 0;
    }

    int count = N;
    int lp = 0;
    int rp = N-1;

    //std::cout << lp;
    //std::cout << rp;
    //return 0;
    //std::cout << s << std::endl;
    while ((s-v[lp]>=L || s-v[rp]>=L) && lp < rp) {
        std::cout << "left " << lp << " right " << rp << std::endl;
        if (v[lp] <= v[rp]) {
            //std::cout << v[lp] << " ";
            s-=v[lp];
            lp++;
        }
        else {
            //std::cout << v[rp] << " ";
            s-=v[rp];
            rp--;
        }
        count--;
        //std::cout << s << std::endl;
    }
    std::cout << count;
    return 0;
}