#include <iostream>

using namespace std;

class Base{
public:
    virtual void sayByefunc() = 0;
    virtual ~Base() = default;
    void sayHi() {
        std::cout << "Hi from base!" << std::endl;
    }

};