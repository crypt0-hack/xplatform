#include <iostream>

template <typename T> class List {
    class Node {
        public:
            Node *next;
            T data;

            Node(T data = T(), Node *next = nullptr) {
                this -> data = data;
                this -> next = next;
            }
    };
    Node *head;
    int sz;


    public:
        List() {
            sz = 0;
            head = nullptr;
        }
        ~List() {
            clear();
        }


    public:
        T& operator[] (const int index) {
            Node *current = this -> head;

            for (int i = 0; current -> next != nullptr; i++) {
                if (i == index) {
                    return current -> data;
                }
                current = current -> next;
            }

            return current -> data;
        }


    public:
        int size() {
            return sz;
        }
        void push_back(T data) {
            if (head == nullptr) {
                head = new Node(data);
            } else {
                Node *current = this -> head;

                while (current -> next != nullptr) {
                    current = current -> next;
                }

                current -> next = new Node(data);
            }

            sz++;
        }
        void push_front(T data) {
            head = new Node(data, head);
            sz++;
        }
        void insert(T data, int index) {
            if (index == 0) {
                push_front(data);
            } else {
                Node *previos = this -> head;

                for (int i = 0; i < index - 1; i++) {
                    previos = previos -> next;
                }

                previos -> next = new Node(data, previos -> next);

                sz++;
            }
        }

        void pop_back() {
            remove(sz - 1);
        }
        void pop_front() {
            Node *tmp = this -> head;

            head = head -> next;
            delete tmp;
            sz--;
        }
        void remove (int index) {
            if (index == 0) {
                pop_front();
            } else {
                Node *previos = this -> head;

                for (int i = 0; i < index - 1; i++) {
                    previos = previos -> next;
                }

                Node *to_delete = previos -> next;
                previos -> next = to_delete -> next;

                delete to_delete;
                sz--;
            }
        }

        void clear() {
            while (sz) {
                pop_front();
            }
        }
        void print() {
            Node *current = this -> head;
            while (current != nullptr) {
                std::cout << current -> data << std::endl;
                current = current -> next;
            }
            std::cout << std::endl << std::endl;
        }
};
template<typename T> void LRU(List<T> &lst, int index);


int main() {
    srand(time(NULL));
    List<int> lst;

    int n;
    std::cout << "Enter list size:  ";
    std::cin >> n;
    std::cout << std::endl;

    for (int i = 0; i < n; i++) {
        lst.push_back(i);
    }
    lst.print();

    LRU(lst, n / 2);
    lst.print();

    return 0;
}


template<typename T> void LRU(List<T> &lst, int index) {
    T tmp = lst[index];

    std::cout << "Work with " << tmp << std::endl << std::endl;
    lst.remove(index);
    lst.push_front(tmp);
}
