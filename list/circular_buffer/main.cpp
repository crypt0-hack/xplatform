#include <iostream>
#define BUF_SZ 10

template<typename T> class circular_buffer {
    T buf[BUF_SZ];
    int _write;
    int _read;

    void buf_init() {
        for (int i = 0; i < BUF_SZ; i++) {
            buf[i] = T();
        }
    }
    bool is_full() {
        if (_write == BUF_SZ - 1 && _read < _write) {
            return true;
        }
        return false;
    }
    bool is_empty() {
        if (_write == _read) {
            return true;
        }
        return false;
    }


    public:
        circular_buffer(int write = 0, int read = 0) {
            buf_init();
            this -> _write = write;
            this -> _read = read;
        }

    public:
        void write(T data) {
            if (!is_full()) {
                buf[_write] = data;
                _write = (_write + 1) % BUF_SZ;
            } else {
                std::cout << "Buffer is full" << std::endl;
            }
        }
        T read() {
            if (!is_empty()) {
                T read_bt = buf[_read];
                _read = (_read + 1) % BUF_SZ;

                return read_bt;
            } else {
                std::cout << "Buffer is empty" << std::endl;
                return T();
            }
        }
};
