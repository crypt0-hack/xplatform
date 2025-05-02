#include <iostream>

#define D_SZ 20

class hash_table {
    uint64_t horner_hash(const std::string &s, uint32_t table_size, const int key) {
        uint64_t hash = 0;

        for (uint i = 0; i != s.size(); i++) {
            hash = (key * hash + s[i]) % table_size;
        }
        hash = (hash * 2 + 1) % table_size;

        return hash;
    }

    uint64_t single_hash(const std::string &s, uint32_t table_size) {
        return horner_hash(s, table_size, table_size - 1);
    }
    uint64_t doubly_hash(const std::string &s, uint32_t table_size) {
        return horner_hash(s, table_size, table_size + 1);
    }


    int lock_check(int8_t n) {
        return ( n & (1 << 6) );
    }
    int del_check(int8_t n) {
        return ( n & 1 );
    }


    class Node {
        public:
            std::string data;
            int8_t lock_del;

        public:
            Node() {
                data = "";
                lock_del = 0;
            }
    };
    Node *arr;
    uint32_t sz;


    public:
        hash_table() {
            arr = (Node *) malloc(sizeof(Node *) * D_SZ);
            sz = 0;
        }
        ~hash_table() {

        }


    public:
        void add(std::string &s) {
            // if ( !(find(s)) ) {
                sz++;

                uint64_t id = single_hash(s, sz);
                std::cout << "hash = " << id << std::endl;

                if (lock_check(arr[id].lock_del)) {
                    if (del_check(arr[id].lock_del)) {
                        arr[id].data = s;
                        arr[id].lock_del &= (1 << 6);
                    } else {
                        id = doubly_hash(s, sz);
                    }
                }

                arr[id].data = s;
                arr[id].lock_del = (1 << 6);
            // }
        }


    public:
        uint8_t find(std::string &s) {
            if (arr[single_hash(s, sz)].data == s || arr[doubly_hash(s, sz)].data == s) {
                return 1;
            }

            return 0;
        }
};


int main() {
    hash_table ht;
    std::string s = "tst";
    std::string s2 = "new_tst";

    ht.add(s);
    ht.add(s2);

    std::cout << std::endl;
    std::cout << s << " = " << (int) ht.find(s) << std::endl;
    std::cout << s2 << " = " << (int) ht.find(s2) << std::endl;

    return 0;
}
