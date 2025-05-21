#include <stdio.h>

#define ALLOC 1024

typedef long align;

union header {
     struct {
          union header* ptr;
          unsigned sz;
     } s;
     align x;
};

typedef union header HEADER;


static HEADER* more_core(unsigned);

void* h_malloc(unsigned);
void h_free(void*);
