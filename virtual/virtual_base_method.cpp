#include <iostream>

class Msg {
    std::string msg;

    public:
        Msg(std::string msg) {
            this -> msg = msg;
        }

        virtual std::string get_msg() {
            return msg;
        }
};

class Brakets_msg : public Msg{
    public:
        Brakets_msg(std::string msg) : Msg(msg) {}

        std::string get_msg() override {
            return '[' + ::Msg::get_msg() + ']';
        }
};

class Printer {
    public:
        void print(Msg *msg) {
            std::cout << msg -> get_msg() << std::endl;
        }
};


int main() {
    Msg msg("fha");
    Brakets_msg bmsg("asa");
    
    Printer p;
    p.print(&msg);
    p.print(&bmsg);

    return 0;
}
