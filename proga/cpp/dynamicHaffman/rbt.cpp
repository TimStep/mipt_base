#include <iostream>

struct Node {
    int data;
    int color;
    char c;
    Node* parent;
    Node* left;
    Node* right;

    Node(int data, int color = 1) : data(data), color(color), c(c), parent(nullptr), left(nullptr), right(nullptr) {}
};

class RedBlackTree {
private:
    void rotateLeft(Node* x) { //малый левый поворот
        Node* y = x->right;
        //левый сын y -> правый сын x обоюдно
        x->right = y->left;
        if (y->left != nullptr) {
            y->left->parent = x;
        }
        //общий родитель x и y
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        }
        //сохраняем сторону, теперь y сын обоюдно
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        //x левый сын y обоюдно
        y->left = x;
        x->parent = y;
    }

    void rotateRight(Node* x) { //малый правый поворот
        Node* y = x->left;

        x->left = y->right;
        if (y->right != nullptr) {
            y->right->parent = x;
        }

        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        }
        else if (x == x->parent->right) {
            x->parent->right = y;
        }
        else {
            x->parent->left = y;
        }
        
        y->right = x;
        x->parent = y;
    }

    void balance(Node* newNode) {
        while (newNode != root && newNode->color == 1 && newNode->parent->color == 1) {
            Node* parent = newNode->parent;
            Node* grandparent = parent->parent;

            if (parent == grandparent->left) { //отец слева

                Node* uncle = grandparent->right;

                if (uncle != nullptr && uncle->color == 1) {//case 1: дядя красный
                    grandparent->color = 1;
                    parent->color = 0;
                    uncle->color = 0;
                    newNode = grandparent;
                }
                else {
                    //case 2: дядя черный, отец справа - малый поворот налево через отцы
                    if (newNode == parent->right) {
                        newNode = parent; //передача отца в case 3
                        rotateLeft(newNode);
                    }
                    //остался case 3: дядя черный, отец слева - большой поворот направо через деда
                    newNode->parent->color = 0;
                    grandparent->color = 1;
                    rotateRight(grandparent);
                }
            }
            else { //отец справа

                Node* uncle = grandparent->left;

                if (uncle != nullptr && uncle->color == 1) {
                    grandparent->color = 1;
                    parent->color = 0;
                    uncle->color = 0;
                    newNode = grandparent;
                }
                else {
                    if (newNode == parent->left) {
                        newNode = parent;
                        rotateRight(newNode);
                    }

                    newNode->parent->color = 0;
                    grandparent->color = 1;
                    rotateLeft(grandparent);
                }
            }
        }
        root->color = 0;
    }

    //вставка по правилом обычного бинарного дерева
    void binaryInsert(Node* root, Node* newNode) {
        if (root->data > newNode->data) {
            if (root->left == nullptr) {
                root->left = newNode;
                newNode->parent = root;
            }
            else {
                binaryInsert(root->left, newNode);
            }
        } else {
            if (root->right == nullptr) {
                root->right = newNode;
                newNode->parent = root;
            }
            else {
                binaryInsert(root->right, newNode);
            }
        }
    }

public:
    Node* root;

    RedBlackTree() : root(nullptr) {}

    //вставка с балансировкой
    void insert(int data) {
        Node* newNode = new Node(data, 1);
        if (root == nullptr) {
            root = newNode;
            root->color = 0;
            return;
        }
        binaryInsert(root, newNode);
        balance(newNode);
    }

    void printTree(Node* root) {
        if (root == nullptr) {
            return;
        }
        printTree(root->left);
        std::cout << root->data << "(" << (root->color == 1 ? "Red" : "Black") << ")" << " ";
        printTree(root->right);
    }

};

int main() {
    RedBlackTree tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);

    tree.printTree(tree.root);
    std::cout << std::endl;
    std::cout << tree.root->data << std::endl;

    return 0;
}