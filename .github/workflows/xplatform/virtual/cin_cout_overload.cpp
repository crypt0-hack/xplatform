#include <iostream>
#include <fstream>

class Point {
    int x;
    int y;
    int z;

    public:
        Point() {
            x = y = z = 0;
        }
        Point(int x, int y, int z) {
            this -> x = x;
            this -> y = y;
            this -> z = z;
        }


    friend std::ostream& operator<< (std::ostream &os, const Point &point);
    friend std::istream& operator>> (std::istream &is, Point &point);
};
std::ostream& operator<< (std::ostream &os, const Point &point);
std::istream& operator>> (std::istream &is, Point &point);


int main() {
    Point p(34, 453, 23);
    std::cout << p << std::endl;

    return 0;
}


std::ostream& operator<< (std::ostream &os, const Point &point) {
    os << point.x << " " << point.y << " " << point.z;

    return os;
}
std::istream& operator>> (std::istream &is, Point &point) {
    is >> point.x >> point.y >> point.z;

    return is;
}
