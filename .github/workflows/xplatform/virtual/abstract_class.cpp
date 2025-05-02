#include <iostream>

class Weapon {
    public:
        virtual void use() = 0;
};

class Knife : public Weapon {
    public:
        void use() override {
            std::cout << "Vzukh-vzukh" << std::endl;
        }
};
class Firearm : public Weapon {};
class Gun : public Firearm {
    public:
        void use() override {
            std::cout << "Bduh" << std::endl;
        }
};
class MachineGun : public Firearm {
    public:
        void use() override {
            std::cout << "Bduh Bduh Bduh" << std::endl;
        }
};
class Bazooka : public Firearm {
    public:
        void use() override {
            std::cout << "Badabah" << std::endl;
        }
};


class Player {
    public:
        void atack(Weapon *weapon) {
            weapon -> use();
        }
};


int main() {
    Knife k;
    Gun g;
    MachineGun mg;
    Bazooka b;

    Player p;
    p.atack(&k);

    return 0;
}
