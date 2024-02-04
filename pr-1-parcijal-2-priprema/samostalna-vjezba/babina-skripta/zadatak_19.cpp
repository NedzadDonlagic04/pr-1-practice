#include<iostream>

[[nodiscard]] int throwDyce();

int main() {
    std::srand(time(NULL));

    int dyce1 {}, dyce2 {}, dyce3 {};
    unsigned int dyceThrownCount { 0u };

    do {
        dyce1 = throwDyce();
        dyce2 = throwDyce();
        dyce3 = throwDyce();

        std::cout<<dyce1<<' '<<dyce2<<' '<<dyce3<<std::endl;

        dyceThrownCount++;
    } while(dyce1 != dyce2 || dyce1 != dyce3); 
    dyceThrownCount--;

    std::cout<<"Broj puta koji su se bacile kocke "<<3 * dyceThrownCount<<std::endl;

    return 0;
}

int throwDyce() {
    return std::rand() % 6 + 1;
}