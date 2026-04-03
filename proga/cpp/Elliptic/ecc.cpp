#include <iostream>
#include <vector>
#include <map>

struct ECC {
    std::vector<std::vector<int>> &arr;
    int key;
    int mult(int m);
};

int ECC::mult(int m) {

    int res = m;
    int temp;
    int tempkey = key;

    while (tempkey > 1) {
        temp = arr[m][res];
        res = temp;
        //std::cout << res << std::endl;
        tempkey--;
    }
    return res;
}

int main() {

    std::vector<std::vector<int>> arr = 
        {{0,1,2,3,4,5,6},
        {1,4,0,2,6,3,5},
        {2,0,3,5,1,6,4},
        {3,2,5,6,0,4,1},
        {4,6,1,0,5,2,3},
        {5,3,6,4,2,1,0},
        {6,5,4,1,3,0,2}};

    ECC A = {arr, 3};
    ECC B = {arr, 4};

    //single encoding
    int m = 1;

    int mA = A.mult(m);
    int mB = B.mult(m);

    std::cout << mA << ' ' << mB << std::endl;
    
    int mAB = B.mult(mA);
    int mBA = A.mult(mB);

    std::cout << mAB << ' ' << mBA << std::endl;

    //arr[0] endcoding
    std::map<int, int> marr0{{}};
    for (int i = 0; i < 7; i++) {
        marr0[arr[0][i]] = A.mult(B.mult(arr[0][i]));
    }

    for (const auto &[k, v] : marr0) {
        std::cout << k << ' ' << v << std::endl;
    }
    return 0;
}