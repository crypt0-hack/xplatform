#include "../crypto/crypt.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <termio.h>
#include <stdint.h>
#include <unistd.h>

void user_print(const struct user_t*);

void echo_disable();
void echo_enable();

void enter(struct user_t*);

unsigned login(const struct user_t*);
void exit_sys();
void new_usr(const struct user_t*);
