#include "crypt.h"

unsigned h_getline(char* s, unsigned lim) {
     unsigned c, i;

     for (i = 0; i < lim - 1 && ((c = getchar()) != EOF && c != '\n'); i++) {
          s[i] = c;
     }

     s[i] = '\0';
     return i;
}
unsigned h_strlen(const char* s) {
     unsigned len = 0;

     for (; *s != '\0'; s++) {
          len++;
     }

     return len;
}

void get_msg(struct user_t* usr) {
     h_getline(usr -> login, LOG_SZ);
     h_getline(usr -> pwd, PASS_SZ);
}
unsigned h_pow(const unsigned base, unsigned power) {
     unsigned n = base;

     for (unsigned i = 1; i < power; i++) {
          n *= base;
     }

     return n;
}
unsigned key_gen() {
     return (h_pow(sizeof(struct crypted), 2u));
}

void crypter(unsigned* key, int* bin_log, int* bin_pwd, const struct user_t* usr) {
     for (unsigned i = 0; i < h_strlen(usr -> login); i++) {
          if (bin_log[i] != '\0') {
               bin_log[i] = ((int)(usr -> login[i]) + ((i + 1) * 3));
          }
     }
     for (unsigned i = 0; i < h_strlen(usr -> login); i++) {
          if (bin_log[i] != '\0') {
               bin_log[i] = bin_log[i] ^ (*key);
          }
     }

     for (unsigned i = 0; i < h_strlen(usr -> pwd); i++) {
          if (bin_pwd[i] != '\0') {
               bin_pwd[i] = ((int)(usr -> pwd[i]) + ((i + 1) * 3));
          }
     }
     for (unsigned i = 0; i < h_strlen(usr -> pwd); i++) {
          if (bin_pwd[i] != '\0') {
               bin_pwd[i] = bin_pwd[i] ^ (*key);
          }
     }
}
void h_strcpy(char* target, unsigned sz, int* source) {
     for (unsigned i = 0; i < sz; i++) {
          target[i] = source[i];
     }
}
struct user_t* decrypter(unsigned* key, int* bin_log, int* bin_pwd, unsigned log_sz, unsigned pwd_sz) {
     for (unsigned i = 0; i < log_sz; i++) {
          if (bin_log[i] == '\0') {
               break;
          }
          bin_log[i] = bin_log[i] ^ (*key);
     }
     for (unsigned i = 0; i < log_sz; i++) {
          if (bin_log[i] == '\0') {
               break;
          }
          bin_log[i] = ((char)(bin_log[i] - ((i + 1) * 3)));
     }

     for (unsigned i = 0; i < pwd_sz; i++) {
          if (bin_pwd[i] == '\0') {
               break;
          }
          bin_pwd[i] = bin_pwd[i] ^ (*key);
     }
     for (unsigned i = 0; i < pwd_sz; i++) {
          if (bin_pwd[i] == '\0') {
               break;
          }
          bin_pwd[i] = ((char)(bin_pwd[i] - ((i + 1) * 3)));
     }

     struct user_t* usr = (struct user_t*) h_malloc(sizeof(struct user_t)); 
     h_strcpy(usr -> login, LOG_SZ, bin_log);
     h_strcpy(usr -> pwd, PASS_SZ, bin_pwd);

     return usr;
}
