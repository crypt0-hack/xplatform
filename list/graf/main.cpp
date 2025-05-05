#include "../list.hpp"

template <typename T> class Graf {
    int sz;

    class Node {
        T data;
        Graf *links;

        void copy(Graf *links) {
            this -> links = (T*) malloc(links.size());
            for (int i = 0; i < links.size(); i++) {
                this -> links[i] = links[i];
            }
        }


        public:
            Node(T data = T(), int graf_size = 0, Graf *links = nullptr) {
                this -> data = data;
                if (graf_size) {
                    this -> links = (T*) malloc(graf_size);
                } else {
                    copy(links);
                }
            }
            ~Node() {
                delete[] links;
            }
    };


    public:
        int size() {
            return this -> sz;
        }
};


int main() {


    return 0;
}
