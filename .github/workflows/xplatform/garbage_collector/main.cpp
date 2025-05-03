#include <stdio.h>
#include <stdlib.h>

#define STACK_SZ 256
#define IGCT 8

typedef enum {
      INT,
      TWIN,
} object_t;

typedef struct s_obj {
      object_t type;
      unsigned char marked;

      struct s_obj* next;

      union {
            int val;

            struct {
                  struct s_obj* head;
                  struct s_obj* tail;
            };
      };
} object;

typedef struct {
      object* stack[STACK_SZ];
      int stack_sz;

      object* first_obj;

      int num_objs;
      int max_objs;
} VM;

void push(VM*, object*);
object* pop(VM*);

VM* new_VM();

void mark(object*);
void mark_all(VM*);
void mark_speep(VM*);
void gc(VM*);

object* new_obj(VM*, object_t);

void push_int(VM*, int);
object* push_pair(VM*);

void obj_print(object*);

void free_VM(VM*);

void f_test();
void s_test();
void t_test();
void a_test();

void performance();


int main() {
      f_test();
      s_test();
      t_test();
      a_test();

      performance();

      return 0;
}


void push(VM* vm, object* val) {
      vm -> stack[vm -> stack_sz++] = val;
}
object* pop(VM* vm) {
      return (vm -> stack[--vm -> stack_sz]);
}

VM* new_VM() {
      VM* vm = (VM*) malloc(sizeof(VM));

      vm -> stack_sz = 0;
      
      vm -> first_obj = NULL;

      vm -> num_objs = 0;
      vm -> max_objs = IGCT;

      return vm;
}

void mark(object* obj) {
      if (obj -> marked) {
            return;
      }

      obj -> marked = 1;

      if (obj -> type == TWIN) {
            mark(obj -> head);
            mark(obj -> tail);
      }
}
void mark_all(VM* vm) {
      for (int i = 0; i < vm -> stack_sz; i++) {
            mark(vm -> stack[i]);
      }
}
void mark_speep(VM* vm) {
      object** obj = &vm -> first_obj;

      while (*obj) {
            if (!(*obj) -> marked) {
                  object* unreach = *obj;

                  *obj = unreach -> next;
                  free(unreach);

                  vm -> num_objs--;
            } else {
                  (*obj) -> marked = 0;
                  obj = &(*obj) -> next;
            }
      }
}
void gc(VM* vm) {
      int num_objs = vm -> num_objs;

      mark_all(vm);
      mark_speep(vm);

      vm -> max_objs = vm -> num_objs * 2;

      printf("Collected %d objects, %d left.\n", num_objs - vm -> num_objs, vm -> num_objs);
}

object* new_obj(VM* vm, object_t type) {
      if (vm -> num_objs == vm -> max_objs) {
            gc(vm);
      }

      object* obj = (object*) malloc(sizeof(object));

      obj -> type = type;
      obj -> next = vm -> first_obj;

      vm -> first_obj = obj;

      obj -> marked = 0;

      vm -> num_objs++;

      return obj;
}

void push_int(VM* vm, int val) {
      object* obj = new_obj(vm, INT);

      obj -> val = val;

      push(vm, obj);
}
object* push_pair(VM* vm) {
      object* obj = new_obj(vm, TWIN);

      obj -> tail = pop(vm);
      obj -> head = pop(vm);

      push(vm, obj);
      return obj;
}

void obj_print(object* obj) {
      switch (obj -> type) {
      case INT:
            printf("%d", obj -> val);
            break;
      case TWIN:
            printf("(");
            obj_print(obj -> head);
            printf(", ");
            obj_print(obj -> tail);
            printf(")");
            break;
      }
}

void free_VM(VM* vm) {
      vm -> stack_sz = 0;

      gc(vm);
      free(vm);
}

void f_test() {
      printf("1: Objects on the stack are preserved.\n");

      VM* vm = new_VM();

      push_int(vm, 1);
      push_int(vm, 2);

      gc(vm);
      free_VM(vm);
}
void s_test() {
      printf("2: Unreached objects are collected.\n");

      VM* vm = new_VM();

      push_int(vm, 1);
      push_int(vm, 2);

      pop(vm);
      pop(vm);

      gc(vm);
      free_VM(vm);
}
void t_test() {
      printf("3: Reach the nested objects.\n");

      VM* vm = new_VM();

      push_int(vm, 1);
      push_int(vm, 2);

      push_pair(vm);

      push_int(vm, 3);
      push_int(vm, 4);

      push_pair(vm);
      push_pair(vm);

      gc(vm);
      free_VM(vm);
}
void a_test() {
      printf("4: Cycles.\n");

      VM* vm = new_VM();

      push_int(vm, 1);
      push_int(vm, 2);

      object* a = push_pair(vm);

      push_int(vm, 3);
      push_int(vm, 4);

      object* b = push_pair(vm);

      a -> tail = b;
      b -> tail = a;

      gc(vm);
      free_VM(vm);
}

void performance() {
      printf("Performance of GC.\n");

      VM* vm = new_VM();

      for (int i = 0; i < 1000; i++) {
            for (int j = 0; j < 20; j++) {
                  push_int(vm, i);
            }

            for (int k = 0; k < 20; k++) {
                  pop(vm);
            }
      }

      free_VM(vm);
}
