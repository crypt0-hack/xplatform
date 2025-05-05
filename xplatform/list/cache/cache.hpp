#include <iostream>
#include <fstream>
#define MAX 10

template <typename T> struct SS {  // search system
    int page;
    T data;
};


template <typename T> class List {
    class Node {
        public:
            Node *next;
            T data;
            int page;

            Node(T data = T(), int page = 0, Node *next = nullptr) {
                this -> data = data;
                this -> page = page;
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
        bool is_full() {
            if (sz == MAX) {
                return true;
            }
            return false;
        }
        int get_index(int page) {
            Node *current = this -> head;

            for (int i = 0; current != nullptr; i++) {
                if (current -> page == page) {
                    return i;
                }
                current = current -> next;
            }

            return -1;
        }


    public:
        void push_back(T data, int page) {
            if (head == nullptr) {
                head = new Node(data, page);
            } else {
                Node *current = this -> head;

                while (current -> next != nullptr) {
                    current = current -> next;
                }

                current -> next = new Node(data, page);
            }

            sz++;
        }   
        void push_front(T data, int page) {
            head = new Node(data, page, head);    
            sz++;
        }
        void insert(T data, int page, int index) {
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
                std::cout << "Data:  " << current -> data << "\t" << "Page:  " << current -> page << std::endl;
                current = current -> next;
            }
            std::cout << std::endl << std::endl;
        }


    public:
        void find(int page, struct SS<T> &tmp) {
            Node *current = this -> head;

            while (current -> next != nullptr) {
                if (current -> page == page) {
                    tmp.page = current -> page;
                    tmp.data = current -> page;
                    return;
                }

                current = current -> next;
            }
            tmp.page = current -> page;
            tmp.data = current -> data;
        }
};
