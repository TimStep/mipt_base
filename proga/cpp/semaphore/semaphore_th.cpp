#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <thread>
#include <vector>
#include <signal.h>
#include <semaphore.h>
#include <mutex>

std::vector<std::thread*> th;
static sem_t semaphore;
std::mutex mu;
/*
void event(int index)
{

    static long count = 0;
    sem_wait(&semaphore);
    std::cout << "Thread:" << index << " Count:" << count << std::endl;
    count++;
    usleep(1000000);
    sem_post(&semaphore);

}
*/

void search_and_destroy(int nfile) {
    std::ifstream file ("file" + std::to_string(nfile));
    std::string str;
    while (file) {
        file >> str;
        size_t found = str.find("in");
        std::cout << str << std::endl;
        if (found != (std::size_t)std::string::npos) {
            mu.lock();
            std::ofstream ofile ("in.txt");
            ofile << str << "\n";
            std::cout << found << std::endl;
            ofile.close();
            mu.unlock();
        }
    }
}

int main()
{   
    std::ifstream myfile ("1.txt");
    std::ofstream outfile;

    std::string mystring;

    for (int nfile=1; nfile<6; nfile++) {
        outfile.open("file"+std::to_string(nfile));
        while (myfile) {
            for (int i=0; i<5; i++) {
                myfile >> mystring; outfile << mystring << "\n";
            }
            break;
        }
        outfile.close();
    }

    
    int MAX_THREAD = 5;
    if (sem_init(&semaphore, 0, 2) == -1)
        std::cerr << "Error: semaphore" << std::endl;
    for(int i = 1; i < MAX_THREAD+1; i++)
    {
        std::thread* t = new std::thread(search_and_destroy, i);
        th.push_back(t);
    }
    for(int i = 0; i < th.size(); i++)
        th[i]->join();
    
    size_t a = std::string::npos;
    std::cout << a;

    return 0;
    
}