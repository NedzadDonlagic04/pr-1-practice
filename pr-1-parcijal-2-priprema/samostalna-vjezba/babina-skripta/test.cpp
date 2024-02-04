// Free file to test whatever I need while working

#include<iostream>
#include<memory>

struct Test {
    static int i;
    int myI {};

    Test() {
        this->myI = i;
        this->i++;
        std::cout<<"Created "<<this->myI<<std::endl;
    }
    ~Test() {
        std::cout<<"Destroyed "<<this->myI<<std::endl;
    }
};

int Test::i = 0;

std::unique_ptr<Test> doSomething() {
    std::cout<<"Inside doSomething\n";
    return std::unique_ptr<Test> { new Test {} };
}

void doSomethingElse(Test *) {
    std::cout<<"Inside doSomethingElse\n";
}

int main() {
    std::cout<<"Entered main a little bit ago...\n";

    std::unique_ptr<Test> idk { nullptr };

    for (std::size_t i = 0; i < 3; i++) {
        doSomethingElse(doSomething().get());
    }

    std::cout<<"Leaving main soon...\n";

    return 0;
}