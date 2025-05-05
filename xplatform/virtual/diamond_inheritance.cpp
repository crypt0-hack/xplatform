#include <iostream>

// class Component {
//     public:
//         std::string name;

//         Component(std::string name) {
//             std::cout << "Detail constructor" << std::endl;
//             this -> name = name;
//         }
// };
// class Memory : public Component {
//     public:
//         Memory(std::string name) : Component(name) {
//             std::cout << "Memory construct" << std::endl;
//         }
// };
// class GPU : public Memory, public Component {
//     public:
//     GPU(std::string name, std::string mem_name) : Memory(mem_name), Component(name) {
//         std::cout << "GPU construct" << std::endl;
//     }
// };


class Character {
    public:
        int hp;

        Character() {
            std::cout << "Character" << std::endl;
        }
};
class Orc : public virtual Character {
    public:
        Orc() {
            std::cout << "Orc" << std::endl;
        }
};
class Warrior : public virtual Character {
    public:
        Warrior() {
            std::cout << "Warrior" << std::endl;
        }
};
class Orc_warrior : public Orc, public Warrior {
    public:
        Orc_warrior() {
            std::cout << "Orc warrior" << std::endl;
        }
};


int main() {
    // GPU gpu("Intel", "Kingstone");
    Orc_warrior ow;

    return 0;
}
