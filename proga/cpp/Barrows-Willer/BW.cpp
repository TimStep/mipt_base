#include <iostream>
#include <vector>
#include <algorithm>

bool srt (std::string a, std::string b) {return a<b;}

std::vector<std::string> cyclic(std::string s) {
    std::vector<std::string> permutations;
    for (int i = 0; i<s.length(); i++) {
        std::rotate(s.begin(), s.begin()+1, s.end());
        permutations.push_back(s);
        //std::cout << s << std::endl;
    }

    std::sort(permutations.begin(), permutations.end(), srt);

    int pos = std::find(permutations.begin(), permutations.end(), s) - permutations.begin();
    permutations.push_back(std::to_string(pos));

    return permutations;
}

std::vector<std::string> encode(std::vector<std::string> permutations) {
    std::vector<std::string> code;
    for (const auto& p: permutations) {
        std::string s{p.back()};
        code.push_back(s);
    }
    //std::reverse(code.begin(), code.end());

    return code;
}

std::string decode(std::vector<std::string> code, int pos) {

    std::vector<std::string> decoded = code;
    for (int i = 0; i<code.size()-1; i++) {
        std::sort(decoded.begin(), decoded.end(), srt);
        for (int j = 0; j<code.size(); j++) {
            std::string tmp = decoded[j];
            decoded[j] = code[j] + tmp;
        }
    }

    std::sort(decoded.begin(), decoded.end(), srt);
    //for (const auto& d: decoded) {std::cout << d << std::endl;}
    return decoded[pos];
}

int main() {

    std::string s = "ABACABA";
    std::vector<std::string> perm = cyclic(s);
    int pos = std::stoi(perm.back());
    perm.erase(perm.end());

    //for (const auto& p: perm) {std::cout << p << std::endl;}
    //std::cout << pos << std::endl;

    std::vector<std::string> code = encode(perm);
    for (const auto& c: code) {std::cout << c;}
    std::cout << std::endl << std::endl;

    std::cout << decode(code, pos);
    std::cout << std::endl;

    return 0;
}