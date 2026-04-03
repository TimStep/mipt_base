#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

string s0 = "abcde";
string s = "abacabadabacabae";//01025039864
string s_ = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
string test = "abcdababc";

/*
vector<string> v;
map<string, int> mp;
string tmp = "";
string tmp_ = "";
string s2 = "";
string s_2 = "";
*/

map<string, int> divbychar(string s) {

  map<string, int> mp;

  for(char& c : s0) {
    string tm(1, c);
    if (mp.find(tm) == mp.end()) {
      mp[tm] = mp.size();
    } 
  }

  return mp;
}

vector<int> encode(const string& input) {
    map<string, int> dictionary = divbychar(input);
    vector<int> result;
    int nextCode = dictionary.size();
    //std::cout << nextCode << std::endl;

    string currentString;
    for (char c : input) {
        string newString = currentString + c;
        if (dictionary.find(newString) != dictionary.end()) {
            currentString = newString;
        }
        else {
            result.push_back(dictionary[currentString]);
            dictionary[newString] = nextCode;
            nextCode++;
            currentString = string(1, c);
        }
    }

    if (!currentString.empty()) {
        result.push_back(dictionary[currentString]);
    }

    return result;
}

int main() {

  map<string, int> mp1 = divbychar(s);
  for (const auto& elem: mp1) {
    std::cout << elem.first << ' ' << elem.second << std::endl;
  }

  vector<int> code = encode(s);
  for (const auto& elem: code) {
    std::cout << elem << ' ';
  }
  std::cout << endl;

  vector<int> lore = encode(s_);
  for (const auto& elem: lore) {
    std::cout << elem << ' ';
  }

  return 0;
}