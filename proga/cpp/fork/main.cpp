#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std::literals::chrono_literals;

std::atomic<int> swaps(0);
//int swaps = 0;
static int *glob_var;
std::mutex mua;
std::mutex mub;


std::chrono::time_point<std::chrono::steady_clock> t1, t2;
auto time() {
    return std::chrono::steady_clock::now();
}

void make_randarr(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand();
    }
}

void copy_arr(const int* src, int* dest, int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

void bubbleSort(int* arr, int size) {
    for (int i = 0; i < size-1; i++) {
        for (int j = 0; j < size-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
                *glob_var=*glob_var+1;
            }
        }
    }
}


int main() {
    
    int const s = 100000;
    int arr[s];
    make_randarr(arr, s);
    int *arr1 = arr;
    int *arr2 = arr + s/4;
    int *arr3 = arr + s/2;
    int *arr4 = arr + 3*s/4; 
    
    int arrr1[s/4];
    int arrr2[s/4];
    int arrr3[s/4];
    int arrr4[s/4];

    copy_arr(arr1, arrr1, s/4);
    copy_arr(arr2, arrr2, s/4);
    copy_arr(arr3, arrr3, s/4);
    copy_arr(arr4, arrr4, s/4);

    /*
    std::thread th1(bubbleSort, arrr1, s/4);
    std::thread th2(bubbleSort, arrr2, s/4);
    std::thread th3(bubbleSort, arrr3, s/4);
    std::thread th4(bubbleSort, arrr4, s/4);

    th1.join();
    th2.join();
    th3.join();
    th4.join();
    */

    //std::cout << "Swaps without threads: " << swaps << std::endl;
    std::cout << "Swaps with threads: " << swaps << std::endl;

    glob_var = static_cast<int*>(mmap(NULL, sizeof *glob_var,
    PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0));

    *glob_var = 0;
    *glob_var=*glob_var+1;
    printf("%d\n", *glob_var);

    int n1 = fork();
    int n2 = fork();

    if (n1>0) {
        //std::cout << n1 << std::endl;
        if (n2>0) {
            bubbleSort(arrr1, s/4);
            //std::cout << n2 << std::endl;
        }
        else if (n2==0) {
            bubbleSort(arrr2, s/4);
            //std::cout << n2 << std::endl;
        }
    }
    else if (n1==0) {
        //std::cout << n1 << std::endl;
        if (n2>0) {
            bubbleSort(arrr3, s/4);
            //std::cout << n2 << std::endl;
        }
        else if (n2==0) {
            bubbleSort(arrr4, s/4);
            //std::cout << n2 << std::endl;
        }
    }
    
    printf("%d\n", *glob_var);
    return 0;
}