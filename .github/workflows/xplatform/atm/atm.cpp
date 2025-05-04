#include "atm.h"

#define DB "./db/db.txt"
#define ADM "./db/adm.txt"
#define TMP "./db/tmp.txt"

static int m = 0;
class guard {
    public:
        guard() {
            if (m == 0) {
                m = 1;
            } else {
                for (;m != 0;);
                guard();
            }
        }
        ~guard() {
            m = 0;
        }
};

bool check_num(std::string cn, std::string pin) {
    std::fstream file;
    file.open(DB);

    std::string tmp;
    while (getline(file, tmp)) {
        if (tmp == cn) {
            getline(file, tmp);
            if (tmp == pin) {
                return true;
            }
        }
    }

    file.close();
    return false;
}
bool check(std::string un, std::string pwd) {
    std::fstream f;
    f.open(ADM);

    std::string tmp;
    while (getline(f, tmp)) {
        if (un == tmp) {
            getline(f, tmp);
            if (pwd == tmp) {
                return true;
            }
        }
    }

    return false;
}
bool is_digit(char c) {
    if (c >= '0' && c <= '9') {
        return true;
    }

    return false;
}

int get(int *i, std::string cn) {
    std::fstream file;
    file.open(DB);
    int *a;

    std::string tmp;
    for (*i = 0; getline(file, tmp); (*i)++) {
        if (tmp == cn) {
            getline(file, tmp);
            getline(file, tmp);
            break;
        }
    }

    a = (int*) malloc(tmp.size());
    for (int j = 0; j < tmp.size(); j++) {
        a[j] = get(tmp[j]);
    }
    int n = 0;
    for (int j = tmp.size() - 1, k = 1; j >= 0; j--, k *= 10) {
        n += (a[j] * k);
    }

    file.close();

    return n;
}
int get(std::string cn) {
    std::fstream file;
    file.open(DB);
    int *a;

    std::string tmp;
    for (; getline(file, tmp);) {
        if (tmp == cn) {
            getline(file, tmp);
            getline(file, tmp);
            break;
        }
    }

    a = (int*) malloc(tmp.size());
    for (int j = 0; j < tmp.size(); j++) {
        a[j] = get(tmp[j]);
    }
    int n = 0;
    for (int j = tmp.size() - 1, k = 1; j >= 0; j--, k *= 10) {
        n += (a[j] * k);
    }

    file.close();

    return n;
}
int get(char c) {
    switch (c) {
        case '0':
            return 0;

        case '1':
            return 1;

        case '2':
            return 2;

        case '3':
            return 3;

        case '4':
            return 4;

        case '5':
            return 5;

        case '6':
            return 6;

        case '7':
            return 7;

        case '8':
            return 8;

        case '9':
            return 9;
    }

    return -1;
}

std::string intro() {
    std::string s;

    for (int i = 0; i < 20; i++) {
        s += '-';
    }
    
    return s;
}

void start() {
    std::string cn, pin;


    for (;;) {
        welcome();

        std::cout << "Enter card number:  ";
        std::cin >> cn;
        std::cout << "Enter PIN-code:  ";
        std::cin >> pin;

        login(cn, pin);

        if ((cn.size() == 16) && (pin.size() == 4) && (check_num(cn, pin))) {
            work(cn, pin);
            std::cout << std::endl << std::endl << std::endl;
        }
    }
}
void welcome() {
    std::cout << '<' << intro() << " ATM SYSTEM " << intro() << '>' << std::endl;
    std::cout << "\t    Written by hackst0n3 with C++" << std::endl;
    std::cout << "\t\t\tWelcome!" << std::endl;
}
void withdraw(std::string cn) {
    int sum;
    int index;

    int n = get(&index, cn);
    std::cout << "Curent sum:  " << n << std::endl;

    std::cout << "Enter withdraw amount:  ";
    std::cin >> sum;
    if ((n - sum) < 0) {
        std::cout << "Warning! Not enough funds. Try again." << std::endl;
        withdraw(cn);
    } else if ((n - sum) == 0) {
        std::cout << "Caution! You have zero balance." << std::endl;
    }

    std::cout << "New sum:  " << (n - sum) << std::endl;
    update(index, (n - sum));
    bye();
}
void replenish(std::string cn) {
    int sum;

    int index;
    int n = get(&index, cn);
    std::cout << "Current sum:  " << n << std::endl;
    std::cout << "Enter the amount to replinsh:  ";
    std::cin >> sum;

    std::cout << "New sum:  " << (n + sum) << std::endl;
    update(index, (n + sum));
    bye();
}
void check(std::string cn) {
    int n = get(cn);

    std::cout << "Current sum:  " << n << std::endl;
    bye();
}
void update(int index, int new_sum) {
    guard();

    std::fstream old;
    old.open(DB);
    std::ofstream d;
    d.open(TMP);

    std::string tmp;
    for (int i = 0; getline(old, tmp); i++) {
        d << tmp << '\n';

        if (i == index) {
            getline(old, tmp);
            d << tmp << '\n';

            getline(old, tmp);
            d << new_sum << '\n';
        }
    }

    old.close();
    d.close();

    std::remove(DB);
    std::rename(TMP, DB);
}
void update(std::string cn, std::string pin) {
    guard();

    std::fstream old;
    old.open(DB);
    std::ofstream d;
    d.open(TMP);

    std::string tmp;
    for (; getline(old, tmp);) {
        d << tmp << '\n';
    }
    d << cn << '\n';
    d << pin << '\n';
    d << 0 << '\n';

    d.close();

    std::remove(DB);
    std::rename("./db/tmp.txt", DB);
}
void add() {
    std::string cn, pin;
    std::cout << "\tEnter new card num:  ";
    std::cin >> cn;
    std::cout << "\tEnter new pin-code:  ";
    std::cin >> pin;

    update(cn, pin);
    std::cout << std::endl << std::endl;
}
void login(std::string cn, std::string pin) {
    if (check(cn, pin)) {
        add();
    }
}
int cin() {
    std::string s;

    std::cout << "1 - withdraw money.\n2 - Replenish the account.\n3 - Check account.\n4 - exit\nEnter choice:  ";
    std::cin >> s;

    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '1' || s[i] == '2' || s[i] == '3' || s[i] == '4') {
            switch (s[i]) {
                case '1':
                    return 1;

                case '2':
                    return 2;

                case '3':
                    return 3;

                case '4':
                    return 4;
            }
        }
    }

    std::cout << std::endl;
    return cin();
}
void work(std::string cn, std::string pin) {
    if (check_num(cn, pin)) {
        int n = cin();

        switch (n) {

            case 1:
                withdraw(cn);
                break;

            case 2:
                replenish(cn);
                break;

            case 3:
                check(cn);
                break;

            case 4:
                std::cout << "\x1B[2J\x1B[H\n\n";
                std::cout << "Goodbye!" << std::endl;
                start();
                break;

            default:
                work(cn, pin);
        }
    } else {
        std::cout << "Wrong input!" << std::endl << std::endl;
    }
}
void bye() {
    std::cout << "Goodbye! And see you later!" << std::endl;
    sleep(5);
    std::cout << "\x1B[2J\x1B[H\n\n";
}
