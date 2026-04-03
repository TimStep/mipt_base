#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

string s = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";

class HNode{
public:
    char c;
    int n;
    HNode* left;
    HNode* right;
    HNode(char c, int n):
        c(c),
        n(n),
        right(nullptr),
        left(nullptr) {}
    
    //int N() {return n;}
    //char C() {return c;}
};

bool less_freq(const HNode& Node1, const HNode& Node2) {return Node1.n > Node2.n;}

HNode* buildHTree(vector<HNode>& nodes) {
    while (nodes.size() > 1) {
        HNode* l = &nodes.back();
        nodes.pop_back();
        HNode* r = &nodes.back();
        nodes.pop_back();

        HNode father = HNode('$', l->n + r->n);
        father.left = l;
        father.right = r;

        nodes.push_back(father);
        //std::cout << father.n << std::endl;
        sort(nodes.begin(), nodes.end(), less_freq);
    }

    return &nodes.front();
}

void generateBytes(HNode* root, string code, unordered_map<char, string>& codes) {
    if (root->c != '$') {std::cout << root->c << std::endl; codes[root->c]=code;}
    if (root->left != nullptr) {generateBytes(root->left, code + '0', codes);} 
    if (root->right != nullptr) {generateBytes(root->right, code + '1', codes);} 
}

int main() {

    unordered_map<char, int> data;
    for (char c: s) {data[c]++;}

    //for (const auto &[c ,n] : data) {std::cout << c << ' ' << n << std::endl;}

    vector<HNode> dat;
    for (const auto &[c ,n] : data) {dat.push_back(HNode(c, n));}
    sort(dat.begin(), dat.end(), less_freq);
    for (const auto& element : dat) {
        std::cout << element.c << ' ' << element.n << std::endl;
    }

    HNode* root = buildHTree(dat);
    //std::cout << root->c << ' ' << root->n << std::endl;
    //std::cout << dat[0].c << std::endl;
    unordered_map<char, string> codes;
    generateBytes(root, "", codes);

    return 0;
}