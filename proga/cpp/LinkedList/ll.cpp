#include <iostream>

struct Node {
    int data;
    Node* next;
    Node(int data) : data(data), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insert(int data) {
        Node* newNode = new Node(data);
        newNode->next = head;
        head = newNode;
    }

    void printReverse() {
        printReverseUtil(head);
    }

private:

    void printReverseUtil(Node* node) {
        if (node == nullptr)
            return;
        std::cout << node->data << " ";
        printReverseUtil(node->next);
    }
};

int main() {
    LinkedList list;

    int N;
    std::cin >> N;

    for (int i = 0; i < N; ++i) {
        int num;
        std::cin >> num;
        list.insert(num);
    }

    list.printReverse();

    return 0;
}