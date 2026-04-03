#include <iostream>

struct Node {
  int num;
  int red;
  Node *parent = nullptr;
  Node *left = nullptr;
  Node *right = nullptr;
  Node(int num, int red=1) : num(num), red(red){}
  
};

class RedBlackTree {
public:
  Node *root = nullptr;
};

int main() {
  std::cout << "Ok\n";
  RedBlackTree tree;
  tree.root = new Node(13, 0); // 0 - black, 1 - red
  tree.root->left = new Node(8, 1);

  // ---
  tree.root->left->left = new Node(1, 0);
  tree.root->left->left->left = new Node(0, 0);
  tree.root->left->left->right = new Node(6, 1);
  tree.root->left->left->right->left = new Node(3, 1);
  // ---

  tree.root->left->right = new Node(11, 0);
  tree.root->left->right->right = new Node(12, 1);

  tree.root->right = new Node(17, 1);
  tree.root->right->left = new Node(15, 0);
  tree.root->right->right = new Node(25, 0);
  tree.root->right->right->left = new Node(22, 1);
  tree.root->right->right->right = new Node(27, 1);
}