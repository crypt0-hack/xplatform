#include "secure.h"

void copy(std::string tmp, char *msg, int sz);


int main() {
    // A - 41   Z - 90
    // a - 97  z - 122
    // 8 bits per machine word
    std::string tmp;
    std::cout << "Enter msg:  ";
    std::cin >> tmp;

    // if len > 15  =>  msg divise to two parts
    int sz = tmp.size();
    char *msg = (char *) malloc(sz);
    copy(tmp, msg, sz);

    int bin[sz * BIN_LEN];
    int k[KEY_SZ];
    std::cout << sz << std::endl;

    crypt(msg, sz, bin, k);
    free(msg);
    decrypt(bin, sz * BIN_LEN, k);

    std::cout << std::endl;
    return 0;
}


void copy(std::string tmp, char *msg, int sz) {
    for (int i = 0; i < sz; i++) {
        msg[i] = tmp[i];
    }

    msg[sz] = '\0';
}
