#include "secure.h"


void crypt(char *msg, int sz, int *bin, int *k) {
    int bin_sz = sz * BIN_LEN;
    init(bin, bin_sz);
    init(k, KEY_SZ);

    int i, st;
    for (i = 0, st = BIN_LEN - 1; i < sz; i++, st += 16) {
        to_bin(msg[i], bin, st, (i + 1));
    }
    std::cout << "bin msg:" << std::endl;
    print(bin, bin_sz);
    std::cout << std::endl << std::endl;

    to_bin(pow(sz, 3), k, KEY_SZ);

    std::cout << "key:" << std::endl;
    print(k, KEY_SZ);
    std::cout << std::endl << std::endl;

    Xor(bin, k, bin_sz, KEY_SZ);
    std::cout << "encrypted msg:" << std::endl;
    print(bin, bin_sz);
    std::cout << std::endl << std::endl;
}
void decrypt(int *bin, int b_sz, int *k) {
    std::cout << "decrypted msg (without shift):" << std::endl;
    Xor(bin, k, b_sz, KEY_SZ);
    print(bin, b_sz);
    std::cout << std::endl << std::endl;

    std::cout << "decrypted (with shift):" << std::endl;
    from_bin(bin, b_sz);
}
void to_bin(char c, int *bin, int st, int i) {
    int n = ((int) c) + i;
    // std::cout << n << std::endl;

    for (; n > 0; st--, n /= 2) {
        bin[st] = n % 2;
    }
}
void to_bin(int n, int *b, int sz) {
    for (int i = (sz - 1); n > 0; i--, n /= 2) {
        b[i] = n % 2;
    }
}
void from_bin(int *b, int b_sz) {
    for (int i = 0, pos = 1; i < b_sz; i += 16, pos++) {
        int n = 0;
        for (int j = i, p = 15; j < (i + 16); j++, p--) {
            n += b[j] * two_pow(2, p);
        }
        n -= pos;
        std::cout << (char)n;
    }
    std::cout << std::endl;
}
void init(int *bin, int sz) {
    for (int i = 0; i < sz; i++) {
        bin[i] = 0;
    }
}
void init(char *m, char c) {
    for (int i = 0; i < MAX; i++) {
        m[i] = c;
    }
}
void print(int *bin, int sz) {
    for (int i = 0; i < sz; i++) {
        if (i % 16 == 0 && i != 0) {
            std::cout << std::endl;
        }
        std::cout << bin[i];
    }
}
void print(char *m, int sz) {
    for (int i = 0; i < sz; i++) {
        std::cout << m[i];
    }

    std::cout << std::endl;
}
void Xor(int *bin, int *key, int sz, int k_sz) {
    for (int i = 0; i < k_sz; i++) {
        for (int j = 0; j < sz; j++) {
            bin[j] = bin[j] xor key[i];   // every bit of the message is encrypted using xor with every bit of the key (the length of the entire message (without spaces))
        }
        // bin[i] = bin[i] xor key[i];
    }
}
int get_len(char *s, int max) {
    int i = max - 1;
    for (; s[i] == 126; i--) {
        ;
    }

    return ++i;
}
int pow(int x, int y) {
    if (y == 0) {
        return 1;
    }

    for (int i = 0; i < y - 1; i++, x *= x) {
        // std::cout << x << ' ';
    }

    // std::cout << std::endl;
    return x;
}
int two_pow(int x, int y) {
    if (y == 0) {
        return 1;
    }

    for (int i = 0; i < y - 1; i++, x *= 2) {
        // std::cout << x << ' ';
    }

    // std::cout << std::endl;
    return x;
}
void copy(char *m, char *f, int len, int st) {
    for (int i = 0; i < len; i++) {
        f[i] = m[i];
    }
}
