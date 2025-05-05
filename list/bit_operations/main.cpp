#include <iostream>

bool is_set_bit(int, int);
int set_bit(int, int);
int reverse_bit(int, int);
int reset_bit(int, int);

int get_row(int);
int get_col(int);

bool is_set_bit(int *, int);
void set_bit(int *, int);
void reset_bit(int *, int);

int alek_hash(std::string);


int main() {
    #if 0
        int nums[2000];
        for (int i = 0; i < 2000; i++) {
            if (i % 8 == 0) std::cout << std::endl;
            nums[i] = rand() % 2000 + 1;
            std::cout << nums [i] << ", ";
        }
        std::cout << std::endl;
        int bit_vector[250] = {0};

        for (int i = 0; i < 2000; i++) {
            if (is_set_bit(bit_vector, nums[i] - 1)) {
                std::cout << "Duplicate:  " << nums[i] << ", position:  " << i << std::endl;
            } else {
                set_bit(bit_vector, nums[i] - 1);
            }
        }
    #endif
    #if 0
        std::cout << alek_hash("name") << std::endl;
        std::cout << alek_hash("amen") << std::endl;
        std::cout << alek_hash("main") << std::endl;
        std::cout << alek_hash("amin") << std::endl;
    #endif

    std::cout << set_bit(10, 0) << std::endl;

    return 0;
}


bool is_set_bit(int num, int ind) {
    return (num & (1 << ind)) != 0;
}
int set_bit(int num, int ind) {
    return (num | (1 << ind));
}
int reverse_bit(int num, int ind) {
    return (num ^ (1 << ind));
}
int reset_bit(int num, int ind) {
    return (num & ~(1 << ind));
}


int get_row(int bit) {
    return (bit >> 4);
}
int get_col(int bit) {
    return bit % 16;
}
bool is_set_bit(int *bits, int ind) {
    int r_ind = get_row(ind);
    int c_ind = get_col(ind);

    return ((bits[r_ind] & (1 << c_ind)) != 0);
}
void set_bit(int *bits, int ind) {
    int r_ind = get_row(ind);
    int c_ind = get_col(ind);

    bits[r_ind] |= 1 << c_ind;
}
void reset_bit(int *bits, int ind) {
    int r_ind = get_row(ind);
    int c_ind = get_col(ind);

    bits[r_ind] &= ~(1 << c_ind);
}

int alek_hash(std::string key) {
    int hash = 0;
    for (int i = 0; i < key.size(); i++) {
        hash = ((hash << 5) - hash) + (int)key[i];
    }

    return ((hash < 0) ? -hash : hash);  // index
}
