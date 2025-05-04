#include <iostream>
#include <fstream>
#include <unistd.h>

#define MAX 2
#define DB "./db/db.txt"
#define ADM "./db/adm.txt"
#define TMP "./db/tmp.txt"

struct Request {
    std::string add_bit;

    std::string ind;
    std::string new_sum;
    std::string cn;
    std::string pin;


    Request() {
        add_bit = "0";

        ind = "0";
        new_sum = "0";
        cn = "";
        pin = "";
    }
};
int get(char c);
int to_integer_translate(std::string n);
void get_requests(struct Request *que);


int main() {
    Request que[MAX];
    get_requests(que);
    
    for (int i = 0; i < 2; i++) {
        std::cout << "Add bit:  " << que[i].add_bit << std::endl << std::endl;
        std::cout << "Index:  " << que[i].ind << std::endl;
        std::cout << "New sum:  " << que[i].new_sum << std::endl;
        std::cout << "Card Num:  " << que[i].cn << std::endl;
        std::cout << "Pin-code:  " << que[i].pin << std::endl << std::endl << std::endl;
    }
    #if 1
       Request que[MAX];

        for (int i = 0; i < MAX; i++) {
            if (que[i].add_bit == "1") {
                std::fstream old(DB);
                std::ofstream new_db(TMP);

                std::string tmp;
                for (; getline(old, tmp);) {
                    new_db << tmp << std::endl;
                }
                new_db << que[i].cn << std::endl;
                new_db << que[i].pin << std::endl;
                new_db << que[i].new_sum << std::endl;

                old.close();
                new_db.close();
                std::remove(DB);
                std::rename(TMP, DB);
            } else {
                std::fstream old(DB);
                std::ofstream new_db(TMP);

                std::string tmp;
                for (int id = 0; getline(old, tmp); id++) {
                    new_db << tmp << std::endl;

                    if (std::to_string(id) == que[i].ind) {
                        getline(old, tmp);
                        new_db << tmp << std::endl;
                        getline(old, tmp);

                        new_db << que[i].new_sum << std::endl;
                    }
                }

                old.close();
                new_db.close();
                std::remove(DB);
                std::rename(TMP, DB);
            }
        }
    #endif

    return 0;
}


void get_requests(struct Request *que) {
    std::ifstream requests("Requests.txt");
    std::string tmp;

    for (int i = 0; getline(requests, tmp); i++) {
        que[i].add_bit = tmp;
        getline(requests, tmp);
        que[i].ind = tmp;
        getline(requests, tmp);
        que[i].new_sum = tmp;
        getline(requests, tmp);

        que[i].cn = tmp;
        getline(requests, tmp);
        que[i].pin = tmp;
    }

    requests.clear();
    requests.close();
    std::remove("Requests.txt");
    std::ofstream reqs("Requests.txt");
    reqs.close();
}
int to_integer_translate(std::string n) {
    int *a = (int *) malloc(n.size());

    for (int i = 0; i < n.size(); i++) {
        a[i] = get(n[i]);
    }

    int num = 0;
    for (int i = n.size() - 1, j = 1; i >= 0; i++, j *= 10) {
        num += (a[i] * j);
    }

    return num;
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
