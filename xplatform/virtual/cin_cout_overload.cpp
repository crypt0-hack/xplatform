#include <iostream>
#include <fstream>

class point {
    int x;
    int y;
    int z;

    public:
        point() {
            x = y = z = 0;
        }
        point(int x, int y, int z) {
            this -> x = x;
            this -> y = y;
            this -> z = z;
        }


    friend std::ostream& operator<< (std::ostream &os, const point &point);
    friend std::istream& operator>> (std::istream &is, point &point);
};
std::ostream& operator<< (std::ostream &os, const point &point);
std::istream& operator>> (std::istream &is, point &point);


int main() {
    point p(34, 453, 23);
    std::cout << p << std::endl;

    return 0;
}


std::ostream& operator<< (std::ostream &os, const point &point) {
    os << point.x << " " << point.y << " " << point.z;

    return os;
}
std::istream& operator>> (std::istream &is, point &point) {
    is >> point.x >> point.y >> point.z;

    return is;
}
