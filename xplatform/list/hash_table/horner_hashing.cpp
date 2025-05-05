#include <iostream>

uint64_t horner_hash(const std::string &s, const int key);


int main() {
    std::string s = "31337";
    int key = 31337;
    std::cout << horner_hash(s, key) << std::endl;

    return 0;
}


uint64_t horner_hash(const std::string &s, const int key) {
    uint64_t hash = 0;

    for (uint i = 0; i != s.size(); i++) {
        hash = (key * hash + s[i]) % INT64_MAX;
    }
    hash = (hash * 2 + 1) % INT64_MAX;

    return hash;
}
