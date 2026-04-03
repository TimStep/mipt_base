#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <stdio.h>
#include <vector>

std::string server_url  = "https://search.wb.ru/exactmatch/ru/common/v7/search?ab_testing=false&appType=1&curr=rub&dest=-1257786&query=\%D1\%87\%D0\%B5\%D1\%85\%D0\%BE\%D0\%BB\%20\%D0%BD\%\%B0\%20iphone\%2013\%20pro&resultset=catalog&sort=popular&spp=30&suppressSpellcheck=false";
std::string cmd = "curl " + server_url + " -o catalog.json";

std::vector<std::string> split(std::string s, std::string start, std::string end) {
    std::vector<std::string> tokens;
    size_t l = 0;
    size_t r = 0;
    while ((r = s.find(end)) != std::string::npos) {
        l = s.find(start) + start.length();
        std::string token = s.substr(l, r-l);
        tokens.push_back(token);
        //std::cout << "Found " << "from " << l << " to " << r << ". " << std::endl;
        s.erase(0, r+end.length());
        //std::cout << "Updated string: " << s << std::endl;
    }
    //tokens.push_back(s);
    return tokens;
}

std::vector<std::string> split2(std::string s, std::string start, std::string end) {
  size_t pos_start = 0, pos_end, end_len = end.length(), start_len = start.length();
  std::string token;
  std::vector<std::string> res;
  while (((pos_end = s.find(end, pos_start)) != std::string::npos) &&
    ((pos_start = s.find(start, pos_start)) != std::string::npos)) {
      token = s.substr (pos_start + start_len, pos_end - pos_start - start_len);
      pos_start = pos_end + end_len;
        res.push_back (token);      
  }
  return res;
}


int main() {

    //std::cout << server_url << std::endl;
    //system(cmd.c_str());

    std::ifstream inFile ("catalog.json");
    
    std::stringstream strStream;
    strStream << inFile.rdbuf();
    std::string catalog = strStream.str();

    std::vector<std::string> names = split(catalog, "name", ",");
    //std::vector<std::string> ids = split2(catalog, "\"dist\":", ",\"root\":");
    //for (auto name: names) {std::cout << name << std::endl;}
    std::cout << names[0] << std::endl;
    return 0;
}