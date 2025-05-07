#include <iostream>
#include <vector>

#define MAX 1290
#define BIN_LEN 16
#define KEY_SZ BIN_LEN * 4
#define INIT_C 126

void crypt(char *msg, int sz, int *bin, int *k);
void init(int *bin, int sz);
void init(char *m, char c);
int get_len(char *s, int max);


void to_bin(char c, int *bin, int st, int i);
void to_bin(int n, int *b, int sz);
void print(int *b, int sz);
void print(char *m, int sz);
void Xor(int *bin, int *key, int sz, int k_sz);
int pow(int x, int y);
int two_pow(int x, int y);

void decrypt(int *cm, int b_sz, int *k);
void from_bin(int *b, int b_sz);
