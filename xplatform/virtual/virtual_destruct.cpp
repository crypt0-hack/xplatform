#include <iostream>

class A {
    public:
        A() {}

        virtual ~A() = 0;
};
A::~A() {}

class B : public A {
    public:
        B() {}

        ~B() override {}
};


int main() {
    A *bptr = new B;

    delete bptr;

    return 0;
}
