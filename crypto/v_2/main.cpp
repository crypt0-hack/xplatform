#include <iostream>

#define BIN_LEN 16
#define KEY_SZ BIN_LEN * 4


void init(int16_t *bin, int b_sz);
int pow(int n, int y);

void copy(std::string source, char *targ, int sz);
void print(int16_t *bin, int b_sz);


int main() {
    std::string tmp;
    std::cout << "Enter message:  ";
    std::getline(std::cin, tmp);

    int sz = tmp.size() + 1;
    int b_sz = sz - 1;
    char *msg = (char *) malloc(sz);
    copy(tmp, msg, sz);

    int16_t bin[b_sz];
    int64_t key = pow(sz, 2);
    std::cout << "K:  " << key << std::endl << std::endl;
    init(bin, b_sz);
    for (int i = 0; i < b_sz; i++) {
        bin[i] = ((int)(msg[i]) + ( (i + 1) * 2 ));
    }
    print(bin, b_sz);

    std::cout << std::endl << "Encrypted:" << std::endl;
    for (int i = 0; i < b_sz; i++) {
        bin[i] = bin[i] ^ key;
    }
    print(bin, b_sz);

    std::cout << std::endl << "Decrypted (without shift):" << std::endl;
    for (int i = 0; i < b_sz; i++) {
        bin[i] =  bin[i] ^ key;
    }
    print(bin, b_sz);
    std::cout << std::endl << "Decrypted:" << std::endl;
    for (int i = 0; i < b_sz; i++) {
        std::cout << ((char)(bin[i] - ( (i + 1) * 2)) ); 
    }
    std::cout << std::endl;

    return 0;
}


void copy(std::string source, char *targ, int sz) {
    for (int i = 0; i < sz; i++) {
        targ[i] = source[i];
    }
    targ[sz] = '\0';
}
void init(int16_t *bin, int b_sz) {
    for (int i = 0; i < b_sz; i++) {
        bin[i] = 0;
    }
}
void print(int16_t *bin, int b_sz) {
    for (int i = 0; i < b_sz; i++) {
        std::cout << bin[i] << "  ";
    }

    std::cout << std::endl;
}
int pow(int n, int y) {
    for (int i = 0; i < y; i++) {
        n *= n;
    }

    return n;
}
