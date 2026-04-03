#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>

using namespace std::literals::chrono_literals;

int swaps = 0;
//int swaps_threaded = 0;
//std::atomic<int> swaps(0);
std::atomic<int> swaps_threaded(0);
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
                swaps++;
            }
        }
    }
}

void bubbleSort_threaded_mutex(int* arr, int size) {
    for (int i = 0; i < size-1; i++) {
        for (int j = 0; j < size-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
                mua.lock();
                swaps_threaded++;
                mua.unlock();

            }
        }
    }
}
void bubbleSort_threaded_locked1(int* arr, int size) {
    mua.lock();
    mub.lock();
    for (int i = 0; i < size-1; i++) {
        for (int j = 0; j < size-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
                
                swaps_threaded++;
            }
        }
    }
    mub.unlock();
    mua.unlock();
}

void bubbleSort_threaded_locked2(int* arr, int size) {
    mub.lock();
    mua.lock();
    for (int i = 0; i < size-1; i++) {
        for (int j = 0; j < size-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
                
                swaps_threaded++;
            }
        }
    }
    mub.unlock();
    mub.unlock();
}

int main() {
    
    int const s = 1000;
    int arr[s];
    make_randarr(arr, s);
    int *arr1 = arr;
    int *arr2 = arr + s/2;
    
    int arrr1[s/2];
    int arrr2[s/2];
    int arrr1_threaded[s/2];
    int arrr2_threaded[s/2];

    copy_arr(arr1, arrr1, s/2);
    copy_arr(arr2, arrr2, s/2);
    copy_arr(arr1, arrr1_threaded, s/2);
    copy_arr(arr2, arrr2_threaded, s/2);

    //bubbleSort(arrr1, s/2);
    //bubbleSort(arrr2, s/2);
    std::thread first(bubbleSort_threaded_mutex, arrr1_threaded, s/2);
    std::thread second(bubbleSort_threaded_mutex, arrr2_threaded, s/2);
    //bubbleSort(arrr2, 4);

    first.join();
    second.join();

    for (int i = 0; i < 4; i++) {
        std::cout << arrr2[i] << " " << arrr2_threaded[i] << std::endl;
    }

    //std::cout << "Swaps without threads: " << swaps << std::endl;
    std::cout << "Swaps with threads: " << swaps_threaded << std::endl; 
}