#include<iostream>
#include<concepts>


template <typename T>
 class  swapClass{

    public:
    swapClass(){}
    void swap(T &a, T &b){
        T temp = a;
        a = b;
        b = temp;
    }

    void myMax(T a, T b){
        if(a > b){
            std::cout << "Max is: " << a << std::endl;
        } else {
            std::cout << "Max is: " << b << std::endl;
        }
    }

    
};

template <typename T>
void printValue(T value){
    std::cout << "Value: " << value << std::endl;
}

template <typename T>
concept HasSize = requires(T a) {
    { a.size() } -> std::convertible_to<std::size_t>;
};

template <HasSize T>
void printSize(const T& container){
    std::cout << "Size: " << container.size() << std::endl;
}


