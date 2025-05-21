#include "reg_log_sys.h"

void user_print(const struct user_t* usr) {
     printf("Login: %s\nPWD: %s\n", usr -> login, usr -> pwd);
}

void echo_disable() {
     struct termios term;

     tcgetattr(STDIN_FILENO, &term);
     term.c_lflag &= ~ECHO;
     tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
void echo_enable() {
     struct termios term;

     tcgetattr(STDIN_FILENO, &term);
     term.c_lflag |= ECHO;
     tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
void enter(struct user_t* usr) {
     printf("Enter login: ");
     scanf("%s", usr -> login);

     printf("Enter password: ");
     echo_disable();
     scanf("%s", usr -> pwd);
     echo_enable();
     printf("\n");
}

unsigned login(const struct user_t* usr) {
     FILE* base = fopen("./base.bin", "rb");
     if (base == NULL){
          fprintf(stderr, "error with userbase\n");
          return -2;
     }

     struct user_t read;
     unsigned base_sz = fseek(base, 0, SEEK_END) / (sizeof(struct user_t));
     fseek(base, 0, SEEK_SET);

     for (unsigned i = 0; i < base_sz; i++) {
          struct crypted* crypted_usr = (struct crypted*) h_malloc(sizeof(struct crypted));
          fread((char*)crypted_usr, sizeof(struct crypted), 1, base);
          unsigned key = key_gen();
          struct user_t* usr = decrypter(&key, crypted_usr -> bin_log, crypted_usr -> bin_pwd, LOG_SZ, PASS_SZ);
          printf("%s %s\n", usr -> login, usr -> pwd);

          if (usr -> login == read.login && usr -> pwd == read.pwd) {
               return 0;
          }
     }

     return -1;
}
void exit_sys() {
     system("clear");
}
void new_usr(const struct user_t* usr) {
     FILE* base = fopen("./base.bin", "ab");
     
     struct crypted* crypted_usr = (struct crypted*) h_malloc(sizeof(struct crypted));
     unsigned key = key_gen();
     crypter(&key, crypted_usr -> bin_log, crypted_usr -> bin_pwd, usr);

     fwrite((char*)crypted_usr, sizeof(struct crypted), 1, base);
     fflush(base);

     fclose(base);
}
