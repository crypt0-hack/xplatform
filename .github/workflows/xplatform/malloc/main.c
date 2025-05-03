#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#define u8 uint8_t
#define u16 uint16_t
#define STACK_SZ 32
#define HEAP_SZ (STACK_SZ * 4)
#define HEADER 4

static u16 IN_USE;
typedef struct virtual_mem {
     u8 stack[STACK_SZ];
     char** unmapped;
     u8 heap[HEAP_SZ];

     struct {
          char** data;
          char** bss;
          char* text;
     } data_t;
} virtual_mem_t;

typedef struct entity {
     u8* ptr;
     u16 sz;
} entity_t;
entity_t LIST[40];

entity_t* new_entity(size_t sz);

void LOG();

void* h_malloc(size_t);
void h_free(void*);

void test();


int main() {
     test();

     return 0;
}

entity_t* new_entity(size_t sz) {
     if (LIST[0].ptr == NULL && LIST[0].sz == 0) {
          static virtual_mem_t vm;
          LIST[0].ptr = vm.heap;
          LIST[0].sz = HEAP_SZ;
          IN_USE++;
     }

     entity_t* best = LIST;
     for (unsigned i = 0; i < IN_USE; i++) {
          if (LIST[i].sz >= sz && LIST[i].sz < best -> sz) {
               best = &LIST[i];
          }
     }

     return best;
}

void LOG() {
     printf("OUR LIST\n");
     for (unsigned i = 0; i < IN_USE; i++) {
          printf("Data + HEADER. [%p]. Memory of out heap free: [%u]\n", LIST[i].ptr, LIST[i].sz);
     }
     printf("Entities in use: [%d]\n", (sizeof(LIST) / sizeof(LIST[0]) - IN_USE));
}

void* h_malloc(size_t sz) {
     assert(sz <= HEAP_SZ);

     sz += HEADER;
     
     entity_t* ent = new_entity(sz);
     
     u8* start = ent -> ptr;
     u8* user_ptr = start + HEADER;

     *start = sz;

     ent -> ptr += sz;
     ent -> sz -= sz;
     assert(ent -> sz >= 0);

     LOG();
     return user_ptr;
}
void h_free(void* ptr) {
     u8* start = (u8*)ptr - HEADER;

     LIST[IN_USE].ptr = &(*start);
     LIST[IN_USE].sz = (u8)*((u8*)ptr - HEADER);
     IN_USE++;

     LOG();
}
void test() {
     typedef struct foo {
          int a;
          int b;
     } foo_t;

     foo_t* foo;
     int* bazz;
     char* bar;

     foo = h_malloc(sizeof(foo_t));
     bazz = h_malloc(sizeof(int));
     bar = h_malloc(5);

     foo -> a = 5;
     foo -> b = 10;

     memcpy(bazz, &foo -> a, sizeof(int));

     strcpy(bar, "bar");

     printf("Address: [%p], data: [%d] [%d]\n", foo, foo -> a, foo -> b);
     printf("Address: [%p], data: [%s]\n", bar, bar);
     printf("Address: [%p], data: [%d]\n", bazz, *bazz);

     h_free(foo);
     h_free(bar);

     char* other = h_malloc(96);
     strcpy(other, "other");
     printf("Address: [%p], data: [%s]\n", other, other);
}
