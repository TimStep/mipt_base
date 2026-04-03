#include <iostream>
#include <chrono>
#include <algorithm>
#include <time.h>
#include <fstream>


const unsigned ARRLEN = 1e6;
const unsigned RANDOM_NUMBERS_RANGE = 1e5;
const unsigned LAUNCHES_NUMBER = 1e6;
const unsigned NUMBER_OF_CYCLES = 1;
const std::string OUTPUT_FILE_PATH = "/Users/daniil/Desktop/C++/Labs/Lab1/experiment5.txt";

const bool MEDIUM_CASE = false;

int array[ARRLEN];


int binary_search(unsigned search_range, int digit = -1) {
    unsigned l_idx = 0, r_idx = search_range;
    int count = 0;

    while (l_idx < r_idx) {
        count++;
        unsigned pivot_idx = (l_idx + r_idx) / 2;
        if (digit < array[pivot_idx]) {
            r_idx = pivot_idx;
        } else if (array[pivot_idx] < digit) {
            l_idx = pivot_idx + 1;
        } else {
            std::cout << count << std::endl;
            return 1;
        }
    }

    //std::cout << count << std::endl;

    return 0;
}


int exaustive_search(unsigned search_range, int digit = -1) {

    for (unsigned i = 0; i != search_range; ++i) {
        if (array[i] == digit) {
            return 1;
        }
    }
    return 0;
}


int random_number() {
    return rand() % RANDOM_NUMBERS_RANGE;
}


void fill_array_with_random_numbers() {
    for(unsigned i = 0; i <= ARRLEN - 1; ++i) {
        array[i] = random_number();
    }
}


int time_counsumption(unsigned search_range, bool medium_case = false) {
    int digit_to_be_found = -1;

    if (medium_case) {
        std::sort(array, array + search_range);
        digit_to_be_found = random_number();
    }

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (unsigned cnt = LAUNCHES_NUMBER; cnt != 0; --cnt) {
        binary_search(search_range, digit_to_be_found);
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::milliseconds time_span = 
    std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    return time_span.count();
}


void write_data_to_file(std::string output_file_name, std::string data_to_write) {
    std::ofstream output_file(output_file_name);

    if (output_file.is_open()) {
        output_file << data_to_write;
        output_file.close();
    } else
        std::cout << "Error!" << std::endl;
}

/*
int main() {
    unsigned const NUMBER_OF_EXPERIMENTS = 500;
    unsigned arrays_lengths[NUMBER_OF_EXPERIMENTS];

    for(int N = 1000; N <= 500000; N += 1000) {
            arrays_lengths[N / 1000 - 1] = N;
    }

    // srand(time(0));
    fill_array_with_random_numbers();

    std::ofstream output_file(OUTPUT_FILE_PATH, std::ios_base::out);

    output_file << "# " << "RANDOM_NUMBERS_RANGE = " << RANDOM_NUMBERS_RANGE << std::endl;
    output_file << "# " << "LAUNCHES_NUMBER = " << LAUNCHES_NUMBER << std::endl;
    output_file << "# " << "NUMBER_OF_CYCLES = " << NUMBER_OF_CYCLES << std::endl;

    //for (unsigned counter = 0; counter != NUMBER_OF_EXPERIMENTS; ++counter) {
        //output_file << arrays_lengths[counter] << ", ";
    //}

    std::cout << "START\n";

    for(int cycle_counter = 0; cycle_counter != NUMBER_OF_CYCLES; ++cycle_counter) {
        
        for(unsigned counter = 0; counter != NUMBER_OF_EXPERIMENTS; ++counter) {
            output_file << time_counsumption(arrays_lengths[counter], MEDIUM_CASE) << ", ";
        }

        if (MEDIUM_CASE) {
            srand(time(0));
            fill_array_with_random_numbers();
        }

        output_file << "\nEND OF CYCLE " << cycle_counter + 1 << std::endl;
        std::cout << "\nEND OF CYCLE " << cycle_counter + 1 << std::endl;
    
    }

    output_file.close();

    std::cout << "\nEND\n";

    return 0;
}
*/

int main() {

    fill_array_with_random_numbers();
    //binary_search(131070, -1);
    //binary_search(131071, -1);
    //binary_search(131072, -1);
    //binary_search(131073, -1);
    //std::cout << time_counsumption(131070) << std::endl;
    //std::cout << time_counsumption(131071) << std::endl;
    //std::cout << time_counsumption(131072) << std::endl;
    //std::cout << time_counsumption(131073) << std::endl;
    int asymp[2] = {100, 0};
    for (int i = 130000; i < 150000; i++) {
        asymp[1] = time_counsumption(i);
        if (asymp[1] - asymp[0] > 20) {
            std::cout << i << ' ' << asymp[1] << std::endl;
            break;
        }
        asymp[0] = asymp[1];
        //std::cout << i << std::endl;
    }
    return 0;
}