#include<iostream>
#include<cmath>

/*
    3. Zadatak
    Napraviti rekurzivnu funkciju 'sumOfSquaresBetween' za racunanje sume kvadrata od m do n
*/

/*
    m: 5
    n: 10

    Dva su pristupa:
    1. uvecavanje m do n [5-->10]   [n je fiksno]
    2. smanjivanje n do m [10-->5]  [m je fiksno]
*/

int sumOfSquaresBetween(int m, int n) {
    if (m == n) {
        return m * m;   // m * n, n * n
    }
    return std::pow(m, 2) + sumOfSquaresBetween(m + 1, n);
    // return std::pow(n, 2) + sumOfSquaresBetween(m, n - 1);
}

int main() {
    int m {}, n {};

    do {
        std::cout<<"Unesite 'm': ";
        std::cin>>m;

        std::cout<<"Unesite 'n': ";
        std::cin>>n;
    } while (m > n);

    std::cout<<"Suma kvadrata od "<<m<<" do "<<n<<" je "<<sumOfSquaresBetween(m, n)<<std::endl;

    return 0;
}