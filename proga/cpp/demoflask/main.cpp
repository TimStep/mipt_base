#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <thread>

std::vector<std::thread*> th;
std::vector<int> keys = {1, 13, 12, 20, 25};
std::string server_url  = "https://d963e926-67da-4275-88f6-32255cce45bf-00-3sh530zoln2nk.picard.replit.dev/data/name/";


void get(int key) {

    int node_id = 0;
    std::string url = server_url+std::to_string(key%2)+"/"+std::to_string(node_id)+"/"+std::to_string(key)+"/";
    std::string cmd = "curl "+url+" --max-time 3";
    system(cmd.c_str());
    node_id+=1;
    node_id%=2;
    std::string url1 = server_url+std::to_string(key%2)+"/"+std::to_string(node_id)+"/"+std::to_string(key)+"/";
    std::string cmd1 = "curl "+url+" --max-time 3";
    system(cmd1.c_str());
    std::cout << "\n";
}

int main() {
    for (int i = 0; i < keys.size(); i++) {
        std::thread* t = new std::thread(get, keys[i]);
        th.push_back(t);
    }
    for(int i = 0; i < th.size(); i++)
        th[i]->join();
    return 0;
}