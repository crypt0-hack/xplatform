#include "malloc.h"

static HEADER base;
static HEADER* free_p = NULL;

static HEADER* more_core(unsigned units) {
     char* cp,* sbrk(int);
     HEADER* up;

     if (units < ALLOC) {
          units = ALLOC;
     }

     cp = sbrk(units * sizeof(HEADER));
     if (cp == (char*)-1) {
          return NULL;
     }
     up = (HEADER*)cp;
     up -> s.sz = units;

     h_free((void*)(up + 1));
     return free_p;
}

void* h_malloc(unsigned bytes) {
     HEADER* p,* prev_p;
     HEADER* more_core(unsigned);
     unsigned units;

     units = (bytes + sizeof(HEADER) - 1) / sizeof(HEADER) + 1;
     if ((prev_p = free_p) == NULL) {
          base.s.ptr = free_p = prev_p = &base;
          base.s.sz = 0;
     }

     for (p = prev_p -> s.ptr; ; prev_p = p, p = p -> s.ptr) {
          if (p -> s.sz >= units) {
               if (p -> s.sz == units) {
                    prev_p -> s.ptr = p -> s.ptr;
               } else {
                    p -> s.sz -= units;
                    p += p -> s.sz;
                    p -> s.sz = units;
               }

               free_p = prev_p;
               return (void*)(p + 1);
          }

          if (p == free_p) {
               if ((p = more_core(units)) == NULL) {
                    return NULL;
               }
          }
     }
}
void h_free(void* tfp) { // to free pointer
     HEADER* bp,* p;

     bp = (HEADER*)tfp - 1;
     for (p = free_p; !(bp > p && bp < p -> s.ptr); p = p -> s.ptr) {
          if (p >= p -> s.ptr && (bp > p || bp < p -> s.ptr)) {
               break;
          }
     }

     if (bp + bp -> s.sz == p -> s.ptr) {
          bp -> s.sz += p -> s.ptr -> s.sz;
          bp -> s.ptr = p -> s.ptr -> s.ptr;
     } else {
          bp -> s.ptr = p -> s.ptr;
     }

     if (p + p -> s.sz == bp) {
          p -> s.sz += bp -> s.sz;
          p -> s.ptr = bp -> s.ptr;
     } else {
          p -> s.ptr = bp;
     }

     free_p = p;
}
