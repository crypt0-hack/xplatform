#include <iostream>

template<typename T> class DLL {
    class Node {
        public:
            Node *next;
            Node *prev;
            T data;

        Node(T data = T(), Node *prev = nullptr, Node *next = nullptr) {
            this -> data = data;
            this -> prev = prev;
            this -> next = next;            
        }
    };
    Node *head;
    int sz;


    public:
        DLL() {
            sz = 0;
            head = nullptr;
        }
        ~DLL() {
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
            if (this -> head == nullptr) {
                this -> head = new Node(data);
            } else {
                Node *last = this -> head;
                while (last -> next != nullptr) {
                    last = last -> next;
                }
                
                last -> next = new Node(data, last);
            }

            sz++;
        }
        void push_front(T data) {
            if (head == nullptr) {
               Node *new_node = new Node(data);

                head = new_node;
            } else {
                Node *new_node = new Node(data, nullptr, head);

                head -> prev = new_node;
                head = new_node;
            }

            sz++;
        }
        void insert(T data, int index) {
            if (index == 0) {
                push_front(data);
            } else {
                Node *previos = head;
                for (int i = 0; i < index - 1; i++) {
                    previos = previos -> next;
                }

                Node *tmp = previos -> next;
                previos -> next = new Node(data, previos, previos -> next);
                tmp -> prev = previos;
            }
            sz++;
        }

        void pop_back() {
            Node *previos = this -> head;
            while (previos -> next != nullptr) {
                previos = previos -> next;
            }

            Node *tmp = previos;
            Node *last = previos -> prev;

            last -> next = nullptr;

            delete tmp;
            sz--;
        }
        void pop_front() {
            if (head == nullptr) {
                std::cout << "The list is already empty" << std::endl;
            } else {
                Node *tmp = head;
                head = head -> next;
                if (head != nullptr) {
                    head -> prev = nullptr;
                }

                delete tmp;
            }
            
            sz--;
        }
        void remove(int index) {
            if (index == 0) {
                pop_front();
            } else if (index == sz - 1) {
                pop_back();
            }  else {
                Node *previos = this -> head;
                for (int i = 0; i < index - 1; i++) {
                    previos = previos -> next;
                }

                Node *to_delete = previos -> next;
                Node *nn = to_delete -> next;

                previos -> next = nn;
                nn -> prev = previos;
                

                delete to_delete;
                sz--;
            }
        }
        void clear() {
            while (sz) {
                pop_front();
            }
        }


    public:
        void printf() {
            Node *current = this -> head;

            while (current != nullptr) {
                std::cout << '\t' << current -> data << std::endl;
                current = current -> next;
            }
            std::cout << std::endl << std::endl;
        }
        void printr() {
            Node *last = this -> head;

            while (last -> next != nullptr) {
                last = last -> next;
            }

            while (last != nullptr) {
                std::cout << last -> data << std::endl;
                last = last -> prev;
            }
        }
};
template<typename T> struct Catalog {
    char name;
    DLL<T> dll;

    void print() {
        std::cout << name << std::endl;
        dll.printf();
    }
};
template<typename T> void LRU(DLL<T> &dll, int index);
template<typename T> void LRU(Catalog<T> *ctlg, int catalog_index, int list_index);


int main() {
    srand(time(NULL));
    // DLL<int> dll;

    // for (int i = 0; i < 10; i++) {
    //     dll.push_back( (rand() % 10) + 1 );
    // }
    // dll.forward_print();

    // for (int i = 0; i < 10; i++) {
    //     LRU(dll, 0(rand() % 1) );
    //     dll.forward_print();
    // }


    struct Catalog<int> ctlg[5];
    for (int i = 0; i < 5; i++) {
        ctlg[i].name = 'A' + i;
        for (int j = 0; j < 10; j++) {
            ctlg[i].dll.push_back( (rand() % 10) + 1 );
        }
    }

    for (int i = 0; i < 5; i++) {
        ctlg[i].print();
    }

    LRU(ctlg, 1, 9);
        for (int i = 0; i < 5; i++) {
        ctlg[i].print();
    }

    return 0;
}


template<typename T> void LRU(DLL<T> &dll, int index) {
    T tmp = dll[index];

    std::cout << "Work with " << tmp << std::endl << std::endl;
    dll.remove(index);
    dll.push_front(tmp);
}
template<typename T> void LRU(Catalog<T> *ctlg, int catalog_index, int list_index) {
    T tmp = ctlg[catalog_index].dll[list_index];

    std::cout << "Work with " << tmp << std::endl << std::endl;
    ctlg[catalog_index].dll.remove(list_index);
    ctlg[catalog_index].dll.push_front(tmp);
}
