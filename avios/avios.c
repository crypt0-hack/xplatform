#include "reg_log_sys.h"


int main(int argc, char** argv) {
     struct user_t* usr = (struct user_t*) h_malloc(sizeof(struct user_t));
     get_msg(usr);

     if (login(usr) == 0) {
          printf("ACCESS GRANTED\n");
     } else {
          printf("ACCESS DENIED\n");
     }

     return 0;
}
