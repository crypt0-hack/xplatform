#include <iostream>
#include <fstream>

class String {
    char *s;
    int sz;

    int size(char *s) { 
        int i = 0;  
        for (; s[i] != '\0'; i++);
        return ++i;
    }
    int size(const char *s) { 
        int i = 0;  
        for (; s[i] != '\0'; i++);
        return ++i;
    }

    void copy(char *s) {
        sz = size(s);
        this->s = new char[sz];
        
        for (int i = 0; i < sz; i++) {
            this->s[i] = s[i];
        }

        this->s[sz] = '\0';
    }
    void copy(const char *s) {
        sz = size(s);
        this->s = new char[sz];

        for (int i = 0; i < sz; i++) {
            this->s[i] = s[i];
        }

        this->s[sz] = '\0';
    }


    public:
        String() : String("") {
            
        }
        String(char *s) {
            copy(s);
        }
        String(const char *s) {
            copy(s);
        }
        String(const String &other) {
            copy(other.s);
        }
        String(String &&other) {
            this -> sz = other.sz;
            this -> s = other.s;

            other.s = nullptr;
        }
        ~String() {
            delete[] s;
        }

        String& operator= (const String &other) {
            if (s != nullptr) {
                delete[] s;
            }

            copy(other.s);

            return *this;
        }
        String operator+ (const String &other) {
            String new_str;

            new_str.sz = (size(this->s) + size(other.s)) - 1;
            new_str.s = new char[new_str.sz];

            int i = 0;
            for (; i < size(this->s); i++) {
                new_str.s[i] = this->s[i];
            }
            for (int j = 0; j < size(other.s); j++, i++) {
                new_str.s[i] = other.s[j];
            }

            new_str.s[new_str.sz] = '\0';
            return new_str;
        }
        bool operator== (const String &other) {
            if (this -> sz == other.sz) {
                for (int i = 0; i < this -> sz; i++) {
                    if (this -> s[i] != other.s[i]) {
                        return false;
                    }
                }

                return true;
            }

            return false;
        }
        bool operator!= (const String &other) {
            return !(this -> operator==(other));
        }
        char& operator[] (int i) {
            return s[i];
        }


    public:
        void print() {
            for (int i = 0; i < sz; i++) {
                std::cout << s[i];
            }

            std::cout << std::endl;
        }

        int size() { 
            return sz;
        }


        friend std::ostream& operator<< (std::ostream &os, const String &s);
        friend std::istream& operator>> (std::istream &is, String &s);
};

std::ostream& operator<< (std::ostream &os, const String &s);
std::istream& operator>> (std::istream &is, String &s);


int main() {
    String str("hello a");
    // std::cin >> str;
    std::cout << std::endl << str;

    return 0;
}


std::ostream& operator<< (std::ostream &os, const String &s) {
    os << s.s << std::endl;

    return os;
}
std::istream& operator>> (std::istream &is, String &s) {
    is >> s.s;

    return is;
}
