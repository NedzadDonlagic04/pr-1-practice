#include<iostream>

/*
    1. Zadatak
    Napravite rekurzivnu funkciju "factorial" za racunanje faktorijela pozitivnog
    broja n.
*/

// n : 7        7 -> 1

// ovo je primjer 'tail' rekurzije
int factorial(int n) {
    // bazni slucaj
    if (n == 0 || n == 1) {
        return 1;
    }

    return n * factorial(n - 1);
}

int main() {
    int x {};

    do {
        std::cout<<"Unesite broj 'x': ";
        std::cin>>x;
    } while (x < 0);

    std::cout<<"Faktorijel broja "<<x<<" je "<<factorial(x)<<std::endl;

    return 0;
}