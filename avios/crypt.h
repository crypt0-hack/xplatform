#include "malloc.h"
#include <stdio.h>

#define LOG_SZ 100u
#define PASS_SZ 1000u

struct user_t {
     char login[LOG_SZ];
     char pwd[PASS_SZ];
};
struct crypted {
     int bin_log[LOG_SZ];
     int bin_pwd[PASS_SZ];
};

unsigned h_getline(char*, unsigned);
unsigned h_strlen(const char*);

void get_msg(struct user_t*);
unsigned h_pow(const unsigned, unsigned);
unsigned key_gen();

void h_strcpy(char*, unsigned, int*);
void crypter(unsigned*, int*, int*, const struct user_t*);
struct user_t* decrypter(unsigned*, int*, int*, unsigned, unsigned);
