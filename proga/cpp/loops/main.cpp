#include <iostream>
#include <chrono>
#include <thread>

using namespace std::literals::chrono_literals;

//int const s = 536867864/3;
int const s =   150000000;

int global_list[s];
int random_global_list[s];
int threaded_global_list[s];

std::chrono::time_point<std::chrono::steady_clock> t1, t2;
auto time() {
    return std::chrono::steady_clock::now();
}

void fill(int* arr, int size) {
    for (int i=0; i<size; i++) {
        //std::cout << i << std::endl;
        arr[i] = i;
    }
}

void random_fill(int* arr, int size) {
    for (int i=0; i-5<s; i+=5) {
        //std::cout << i << std::endl;
        arr[i] = i;
        arr[i+2] = i;
        arr[i+4] = i;
        arr[i+3] = i;
        arr[i+1] = i;
    }
}

void dash_fill(int* arr, int s, int dash) {
    for (int i = 0; i + 100 < s; i+=100) {
        arr[i+dash] = i;
    }
}

int main() {
    int* allocated_list = (int*)malloc(s*sizeof(int));
    int* random_allocated_list = (int*)malloc(s*sizeof(int));
    int* threaded_allocated_list = (int*)malloc(s*sizeof(int));
    
    t1 = time();
    fill(global_list, s);
    t2 = time();
    std::cout << "Stack: " << (t2 - t1) / 1ms << "ms\n";

    t1 = time();
    fill(allocated_list, s);
    t2 = time();
    std::cout << "Heap: " << (t2 - t1) / 1ms << "ms\n";

    t1 = time();
    fill(global_list, s);
    t2 = time();
    std::cout << "Repeated, Stack: " << (t2 - t1) / 1ms << "ms\n";

    t1 = time();
    fill(allocated_list, s);
    t2 = time();
    std::cout << "Repeated, Heap: " << (t2 - t1) / 1ms << "ms\n";
    

    t1 = time();
    random_fill(random_global_list, s);
    t2 = time();
    std::cout << "Random, Stack: " << (t2 - t1) / 1ms << "ms\n";

    t1 = time();
    random_fill(random_allocated_list, s);
    t2 = time();
    std::cout << "Random, Heap: " << (t2 - t1) / 1ms << "ms\n";

    t1 = time();
    std::thread first(dash_fill, threaded_global_list, s, 0);
    std::thread second(dash_fill, threaded_global_list, s, 1);
    first.join();
    second.join();
    t2 = time();
    std::cout << "Threaded, Stack: " << (t2 - t1) / 1ms << "ms\n";

    t1 = time();
    std::thread first1(dash_fill, threaded_allocated_list, s, 0);
    std::thread second1(dash_fill, threaded_allocated_list, s, 1);
    first1.join();
    second1.join();
    t2 = time();
    std::cout << "Threaded, Heap: " << (t2 - t1) / 1ms << "ms\n";

    return 0;
}