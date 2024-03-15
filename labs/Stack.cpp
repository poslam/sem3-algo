#include <iostream>
#include <vector>

template<typename T>
struct Node {
    T value;
    Node<T> *prev;

    Node(T val, Node<T> *p) : value(val), prev(p) {}
};

template<typename T>
class PersistentStack {
private:
    std::vector<Node<T> *> heads;
public:
    PersistentStack() {
        heads.push_back(nullptr);
    }

    void push(T x, int version) {
        Node<T> *newNode = new Node<T>(x, heads[version]);
        heads.push_back(newNode);
    }

    T pop(int version) {
        T value = heads[version]->value;
        Node<T> *prev = heads[version]->prev;
        heads.push_back(prev);
        return value;
    }

    void print(int version) {
        Node<T> *current = heads[version];
        while (current != nullptr) {
            std::cout << current->value << " ";
            current = current->prev;
        }
        std::cout << std::endl;
    }
};

int main() {
    PersistentStack<int> stack;

    stack.push(1, 0);
    stack.push(2, 1);
    stack.push(3, 2);
    stack.print(2);

    stack.push(4, 3);
    stack.push(5, 4);
    stack.print(4);

    stack.pop(5);
    stack.print(5);

    stack.push(5, 0);
    stack.push(10, 1);
    stack.push(6, 0);
    stack.pop(1);
    stack.pop(2);


    return 0;
}