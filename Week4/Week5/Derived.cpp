#include "base.h"

class Derived : public Base {
public:
    void sayByefunc() override {
        std::cout << "Goodbye from Derived!" << std::endl;
    }
    Derived() {
        std::cout << "Derived constructor called!" << std::endl;
    }
    ~Derived() {
        std::cout << "Derived destructor called!" << std::endl;
    }
};