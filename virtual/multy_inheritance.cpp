#include <iostream>

class Car {
    public:
        Car() {
            // std::cout << "Car is creating" << std::endl;
        }
        ~Car() {
            // std::cout << "Car is deleting" << std::endl;
        }

        void use() {
            std::cout << "I'm driving" << std::endl;
        }
};
class Airplane {
    public:
        Airplane() {
            // std::cout << "Airplane is creating" << std::endl;
        }
        ~Airplane() {
            // std::cout << "Airplane is deleting" << std::endl;k
        }

        void use() {
            std::cout << "I'm flying" << std::endl;
        }
};

class AirCar : public Car, public Airplane {
    public:
        AirCar() {
            // std::cout << "AirCar is creating" << std::endl;
        }
        ~AirCar() {
            // std::cout << "AirCar is deleting" << std::endl;
        }
};


int main() {
    AirCar ac;
    ac.Car::use();
    ac.Airplane::use();

    Car *cptr = &ac;
    Airplane *aptr = &ac;
    
    return 0;
}
