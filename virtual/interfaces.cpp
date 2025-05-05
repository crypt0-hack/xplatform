#include <iostream>

class IBicycle {
    public:
        void virtual twist_wheel() = 0;
        void virtual ride() = 0;

        
};
class Bicycle : public IBicycle {
    public:
        void twist_wheel() override {
            std::cout << "twist the wheel   bicycle" << std::endl;
        }
        void ride() override {
            std::cout << "Ride    bicycle" << std::endl;
        }
};
class Bmx : public IBicycle {
    public:
        void twist_wheel() override {
            std::cout << "twist the wheel   bmx" << std::endl;
        }
        void ride() override {
            std::cout << "Ride    bmx" << std::endl;
        }
};
class Human {
    public:
        void ride_on(IBicycle &bicycle) {
            std::cout << "twist the wheel" << std::endl;
            bicycle.twist_wheel();
            std::cout << "Let's ride" << std::endl;
            bicycle.ride();
        }
};


int main() {
    Bicycle b;
    Bmx bm;

    Human h;
    h.ride_on(b);
    std::cout << std::endl;
    h.ride_on(bm);

    return 0;
}
