#include <iostream>

class Tree {
    class Node {
        public:
            int data;
            int count;

            Node *left;
            Node *right;


            Node(int data, Node *left = nullptr, Node *right = nullptr) {
                this -> data = data;
                this -> count = 1;

                this -> left = left;
                this -> right = right;
            }
    };
    Node *root;
    

    public:
        Tree() {
            root = nullptr;
        }


    public:
        void add(int data, Node *left = nullptr, Node *right = nullptr) {
            if (root == nullptr) {
                root = new Node(data, left, right);
            } else {
                Node *current = this -> root;

                while (current != nullptr) {
                    if (current -> data > data && current -> left == nullptr) {
                        current -> left = new Node(data, left, right);
                        break;
                    }
                    if (current -> data < data && current -> right == nullptr) {
                        current -> right = new Node(data, left, right);
                        break;
                    }
                    if (current -> data == data) {
                        current -> count++;
                        break;
                    }

                    if (current -> data > data) {
                        current = current -> left;
                    } else {
                        current = current -> right;
                    }
                }
            }
        }


    public:
        void print() {
            Node *current = this -> root;
            std::cout << "Root:  " << current -> data << std::endl << std::endl;

            Node *tmp = current -> left;
            current = current -> right;

            std::cout << "Left:  ";
            while (tmp != nullptr) {
                std::cout << tmp -> data << " - " << tmp -> count << "\t";
                tmp = tmp -> left;
            }
            std::cout << std::endl << "Right:  ";
            while (current != nullptr) {
                std::cout << current -> data << " - " << current -> count << "\t";
                current = current -> right;
            }

            std::cout << std::endl;
        }
};


int main() {
    srand(time(NULL));
    Tree bt;

    std::cout << "Nums:  ";
    for (int i = 1; i < 11; i++) {
        if (i % 2 == 0) {
            std::cout << i << ", ";
            bt.add(i);
        } else {
            std::cout << 10- i << ", ";
            bt.add(10 - i);
        }
    }
    std::cout << std::endl << std::endl;
    bt.print();

    return 0;
}
