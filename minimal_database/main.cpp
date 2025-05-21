#include <iostream>
#include <fstream>

class User {
    int ID;
    std::string name;
    int age;

    public:
        User(int ID = 0, std::string name = "", int age = 0) {
            this -> ID = ID;
            this -> name = name;
            this -> age = age;
        }
        ~User() {

        }


    public:
        std::string skip() {
            std::string s = "";

            for (int i = 0; i < 20; i++) {
                s += '-';
            }

            return s;
        }

        void set_id(int ID) {
            this -> ID = ID;
        }
        void set_name(std::string name) {
            this -> name = name;
        }
        void set_age(int age) {
            this -> age = age;
        }

        int get_id() {
            return ID;
        }
        std::string get_name() {
            return name;
        }
        int get_age() {
            return age;
        }


    public:
        void print() {
            std::cout << "ID:  " << ID << "\nName:  " << name << "\nAge:  " << age << std::endl << skip() << std::endl;
        }
};
void serialize(User &usr);
void deserialize(User *usrs);

std::string skip();
int to_int(std::string str);
int get(char c);



int main() {
    srand(time(NULL));
    User usrs[10];

    for (int i = 0; i < 10; i++) {
        usrs[i].set_id(i + 1);
        
        std::string name;
        std::cout << "Enter name:  ";
        std::cin >> name;
        usrs[i].set_name(name);
        usrs[i].set_age((rand() % 100) + 1);


        serialize(usrs[i]);
    }

    User d_usrs[10];
    std::cout << std::endl << std::endl;
    deserialize(d_usrs);
    for (int i = 0; i < 10; i++) {
        d_usrs[i].print();
    }

    return 0;
}


void serialize(User &usr) {
    std::ofstream file("peoples.bin", std::ios::app);

    file << usr.get_id() << '\n' << usr.get_name() << '\n' << usr.get_age() << std::endl << skip() << std::endl;
    file.close();
}
void deserialize(User *usrs) {
    User tmp;
    std::string str;

    std::ifstream db("peoples.bin");

    for (int i = 0; i < 10; i++) {
        getline(db, str);
        if (str[0] == '-') {
            getline(db, str);
        }

        int id = to_int(str);
        getline(db, str);
        std::string name = str;
        getline(db, str);
        int age = to_int(str);

        usrs[i].set_id(id);
        usrs[i].set_name(name);
        usrs[i].set_age(age);
    }
}

std::string skip() {
    std::string s = "";

    for (int i = 0; i < 20; i++) {
        s += '-';
    }

    return s;
}
int to_int(std::string str) {
    int *tmp = (int *) malloc(str.size());

    for (int i = 0; i < str.size(); i++) {
        tmp[i] = get(str[i]);
    }

    int n = 0;
    for (int i = str.size() - 1, j = 1; i < str.size(); i--, j *= 10) {
        n += (tmp[i] * j);
    }

    return n;
}
int get(char c) {
    switch (c) {
        case '0':
            return 0;
            break;

        case '1':
            return 1;
            break;

        case '2':
            return 2;
            break;

        case '3':
            return 3;
            break;

        case '4':
            return 4;
            break;

        case '5':
            return 5;
            break;

        case '6':
            return 6;
            break;

        case '7':
            return 7;
            break;

        case '8':
            return 8;
            break;

        case '9':
            return 9;
            break;
    }

    return -1;
}
