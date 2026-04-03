#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

struct Node {
    char c;
    int freq;
    Node* left;
    Node* right;
    Node* parent;

    Node(char c, int freq) : c(c), freq(freq), left(nullptr), right(nullptr), parent(nullptr) {}
};

class dynamicHTree {
private:
    std::unordered_map<char, Node*> leaves;

    Node* find_leaf(char c) {
        return leaves[c];
    }

    void balance(Node* leaf) {
        while (leaf->parent) {
            Node* sibling = (leaf->parent->left == leaf) ? leaf->parent->right : leaf->parent->left;
            Node* min_node = sibling;
            while (sibling) {
                if (sibling->freq < min_node->freq) {
                    min_node = sibling;
                }
                sibling = sibling->right;
            }
            if (min_node != leaf && min_node != nullptr) {
                std::swap(leaf->c, min_node->c);
                std::swap(leaf->freq, min_node->freq);
                leaves[leaf->c] = leaf;
                leaves[min_node->c] = min_node;
            }
            leaf->freq++;
            leaf = leaf->parent;
        }
        root->freq++;
    }
public:

    Node* root;
    dynamicHTree() : root(nullptr) {}

    void insert(char c) {
        if (!root) {
            root = new Node(c, 1);
            leaves[c] = root;
        }
        Node* leaf = find_leaf(c);
        if (!leaf) {
            Node* new_leaf = new Node(c, 1);
            leaves[c] = new_leaf;
            Node* temp = root;
            while (temp->left) {
                temp = temp->left;
            }
            new_leaf->parent = temp;
            temp->left = new_leaf;
            balance(new_leaf);
        }
        else {balance(leaf);}
    }

    /*
    Node* find(std::vector<char> code, Node* nod) {
        if (code.size() == 0) {return nod;}
        char p = code[0];

        std::reverse(code.begin(), code.end());
        code.pop_back();
        std::reverse(code.begin(), code.end());

        if (p == '0') {return find(code, nod->left);}
        else {return find(code, nod->right);}
    }
    */

   void printTree(Node* root) {
        if (root == nullptr) {
            return;
        }
        printTree(root->left);
        std::cout << root->c << "(" << root->freq << ") ";
        printTree(root->right);
    }
};

int main() {

    dynamicHTree tree;
    std::string s = "abb";
    for (char c: s) {tree.insert(c);}

    tree.printTree(tree.root);

    return 0;
}