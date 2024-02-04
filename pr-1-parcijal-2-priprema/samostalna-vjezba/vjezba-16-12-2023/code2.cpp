#include<iostream>

int i { 0 };

struct Example {
    const int instanceNum {};

    Example();
    ~Example();
};

Example::Example() : instanceNum(i) {
    std::cout<<"Example created with instanceNum: "<<i<<std::endl;
    i++;
}

Example::~Example() {
    std::cout<<"Example destroyed with instanceNum: "<<this->instanceNum<<std::endl;
}

int main() {
    Example examples[10] {};
    std::cout<<std::endl;

    return 0;
}