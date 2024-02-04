#include<iostream>
#include<cmath>

/*
    2. Zadatak
    Napravite rekurzivnu funkciju 'sumOfSquares' za racunanje sume kvadrata od 1 do x
*/
// n: 15 -> 15 ^ 2 + 14 ^ 2 + 13^2 + ... + 1^2
int sumOfSquares(int n) {
    if (n == 1) {
        return 1;
    }
    return std::pow(n, 2) + sumOfSquares(n - 1);
}

int main() {
    int n {};
    
    do {
        std::cout<<"Unesite broj 'n': ";
        std::cin>>n;
    } while (n < 1);

    std::cout<<"Suma kvadrata od 1 do "<<n<<" je "<<sumOfSquares(n)<<'\n';

    return 0;
}