#include "Derived.h"
#include "template.h"


int main(){

    swapClass <int> intSwap;
    int a = 5, b = 10;
    std::cout << "Before swapping: a = " << a << ", b = " << b << std::endl;
    intSwap.swap(a, b);
    std::cout << "After swapping: a = " << a << ", b = " << b << std::endl;

}