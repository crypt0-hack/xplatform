#include <iostream>


class PC {
    public:
        enum PC_state {
            OFF,
            ON,
            SLEEP
        };

        void set_state(PC_state state) {
            this -> state = state;
        }
        PC_state get_state() {
            return state;
        }

    private:
        PC_state state;
};


int main() {
    PC p;
    p.set_state(PC::PC_state::SLEEP);
    std::cout << p.get_state() << std::endl;

    return 0;
}
