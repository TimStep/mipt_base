#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <stdio.h>
#include <vector>

std::string server_url  = "https://www.avito.ru/dolgoprudnyy/kvartiry/prodam-ASgBAgICAUSSA8YQ?context=H4sIAAAAAAAA_0q0MrSqLraysFJKK8rPDUhMT1WyLrYyNLNSKk5NLErOcMsvyg3PTElPLVGyrgUEAAD__xf8iH4tAAAA";

std::string name_start = " target=\"_blank\" rel=\"noopener\" title=\"";
std::string name_end = "";

std::string price_start = "<meta itemProp=\"price\" content=\"";
std::string price_end = "\"/><meta itemProp=\"availability\" content=\"";

std::string link_start = "class=\"iva-item-titleStep-zichc\"><div class=\"iva-item-title-CdRXl\"><a itemProp=\"url\" rel=\"noopener\" target=\"_blank\" title=\"";
std::string link_end = "class=\"iva-item-titleStep-zichc\"><div class=\"iva-item-title-CdRXl\"><a itemProp=\"url\" rel=\"noopener\" target=\"_blank\" title=\"";

std::vector<std::string> split(std::string s, std::string start, std::string end) {
    std::vector<std::string> tokens;
    size_t l = 0;
    size_t r = 0;
    while ((r = s.find(end)) != std::string::npos) {
        l = s.find(start) + start.length();
        std::string token = s.substr(l, r-l);
        tokens.push_back(token);
        //std::cout << "Found " + token << " from " << l << " to " << r << ". ";
        s.erase(0, r+end.length());
        //std::cout << "Updated string: " << s << std::endl;
    }
    //tokens.push_back(s);
    return tokens;
}

int main() {

    //std::string cmd = "curl "+server_url+" -o avito.txt";
    //system(cmd.c_str());

    std::ifstream inFile ("avito.txt");
    
    std::stringstream strStream;
    strStream << inFile.rdbuf();
    std::string avito_string = strStream.str();

    /*
    std::string test = "+abc-1010+def-1212+g-";
    std::vector<std::string> tokens = split(test, "+", "-");
    for (auto t: tokens) {std::cout << t << std::endl;}
    std::cout << test;
    */

    //std::cout << avito_string << std::endl;
    std::string test = price_start + "abc" + price_end + "spam" + price_start + "bcd" + price_end + "eggs";
    //std::cout << test << std::endl;
    std::vector<std::string> prices = split(avito_string, price_start, price_end);
    std::vector<std::string> links = split(avito_string, link_start, link_end);
    //for (auto p: prices) {std::cout << p << std::endl;}
    for (auto l: links) {std::cout << l << std::endl;}
    return 0;
}