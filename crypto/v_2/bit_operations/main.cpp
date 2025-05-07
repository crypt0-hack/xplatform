#include <iostream>

bool is_set(int num, int ind);
int set_bit(int num, int ind);
int inverse_bit(int num, int ind);
int reset_bit(int num, int ind);


int main() {
    

    return 0;
}


bool is_set(int num, int ind) {
    return (num & (1 << ind));
}
int set_bit(int num, int ind) {
    return (num | (1 << ind));
}
int inverse_bit(int num, int ind) {
    return (num ^ (1 << ind));
}
int reset_bit(int num, int ind) {
    return (num & ~(1 << ind));
}
