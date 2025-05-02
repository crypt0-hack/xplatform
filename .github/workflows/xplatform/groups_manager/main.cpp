#include <iostream>
#include <fstream>

std::fstream bs("base.bin", std::ios::binary | std::ios::in | std::ios::out);

struct Group {
    static const int BUFFER_SIZE = 20;
    double precision = 0.02;
    unsigned int id;
    char name[BUFFER_SIZE];
    double averageScore;
    unsigned int amountOfStudents; 
};
std::istream& operator >> (std::istream& in, Group& grp) {
    in >> grp.id >> grp.name >> grp.averageScore >> grp.amountOfStudents;
    return in;
}
void init(char* g) {
    for (int i = 0; i < sizeof(Group); i++) {
        g[i] = ' ';
    }
}
void update(Group *grps, int sz) {
    bs.seekp(0);
    bs.write((char*)grps, sizeof(Group)*sz);
}
int work();

void add_group(Group* grps) {
    Group cls;
    std::cin >> cls;

    bs.write((char*)&cls, sizeof(Group));
    delete[] grps;
    work();
}
void print(Group &grp) {
    std::cout << grp.id << "\t |" <<
        grp.averageScore << "\t |" <<
        grp.amountOfStudents << std::endl;
}
void print_all(Group*& grps, int sz) {
    for (int i = 0; i < sz; i++) {
        std::cout << grps[i].id << "\t |" << grps[i].name << "\t |"
            << grps[i].averageScore << "\t |"
            << grps[i].amountOfStudents << std::endl;
    }
    std::cout << std::endl;
}
void edit(Group*& grps, const int& id, const int& sz) {
    int i = 0;
    for (; grps[i].id != id; i++);

    std::cout << "Что вы хотите изменить?\n\t1 - имя группы;\n\t2 - средний балл;\n\t3 - количество студентов;\n" << std::endl;
    int chng;
    std::cin >> chng;

    if (chng == 1) {
        std::cin.getline(grps[i].name, grps->BUFFER_SIZE);
    }
    switch (chng) {
    case 2:
        double score;
        std::cin >> score;
        grps[i].averageScore = score;
        break;

    case 3:
        unsigned int amount;
        std::cin >> amount;
        grps[i].amountOfStudents = amount;
        break;
    }

    update(grps, sz);
}
void swap(Group* lhs, Group* rhs) {
    Group tmp = *lhs;
    *lhs = *rhs;
    *rhs = tmp;
}
void sort(Group*& grps, const int& sz, const int sort_to) {
    if (sort_to == 0) {
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz - i - 1; j++) {
                if (grps[j].id > grps[j + 1].id) {
                    swap(&grps[j], &grps[j + 1]);
                }
            }
        }
    }
    else {
        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < sz - i - 1; j++) {
                if (grps[j].averageScore > grps[j + 1].averageScore) {
                    swap(&grps[j], &grps[j + 1]);
                }
            }
        }
    }
}
int search(Group*& grps, const double& score, const int& sz) {
    int low = 0, high = sz - 1;
    
    while (low <= high) {
        int mid = (low + high) / 2;

        if (std::abs(grps[mid].averageScore - score) <= grps->averageScore) {
            return mid;
        }
        if (grps[mid].averageScore > score) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    return -1;
}


int work() {
    Group* grps;
    bs.seekg(0, std::ios::end);
    int sz = (bs.tellg() / sizeof(Group));
    bs.seekg(0);
    if (sz == 0) {
        grps = new Group[2];
    }
    else {
        grps = new Group[sz];
        for (int i = 0; i < sz; i++) {
            bs.read((char*)&grps[i], sizeof(Group));
        }
    }

    std::cout << "Что вы хотите сделать?\t\n"
        << "1 - добавить группу\t\n"
        << "2 - просмотреть список\t\n"
        << "3 - редактировать группу\t\n"
        << "4 - сортировать список\t\n"
        << "5 - найти группу\t\n"
        << "6 - выход\t\n"
        << std::endl;
    int chng;
    std::cin >> chng;
    switch (chng) {
    case 1:
        add_group(grps);
        break;
    case 2:
        print_all(grps, sz);
        break;
    case 3:
        int id;
        std::cout << "Введите номер группы для редактирования:  ";
        std::cin >> id;
        edit(grps, id, sz);
        break;
    case 4:
        int sort_to;
        std::cout << "1 - сортировка по номеру\t\n2 - сортировка по среднему баллу\n";
        std::cin >> sort_to;
        sort(grps, sz, sort_to);
        break;
    case 6:
        std::cout << "Завершение работы" << std::endl;
        update(grps, sz);
        delete[] grps;
        return 0;
    }
    if (chng == 5) {
        double score;
        std::cout << "Введите средний балл для поиска:  ";
        std::cin >> score;
        int pos = search(grps, score, sz);
        if (pos >= 0) {
            std::cout << "Группа найдена с id:  " << grps[pos].id << std::endl;
        }
        else {
            std::cout << "Соответствующая группа не найдена" << std::endl;
        }
    }

    return 1;
}


int main() {
    setlocale(LC_ALL, "rus");

    int ind = 1;
    do {
        ind = work();
    } while (ind);

    return 0;
}
