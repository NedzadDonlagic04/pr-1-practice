#include<iostream>

/*
    4. Zadatak
    Napisati rekurzivnu funkciju 'sumOdd' koja izracunava sumu neparnih brojeva izmedu m i n

*/

bool isEven(int x) {
    return x % 2 == 0;
}

bool isOdd(int x) {
    return !isEven(x);
}

// uvecavamo 'm' do vrijednosti 'n' ['n' je fiksna vrijednost]
// na sumu dodajemo 'm' samo ako je neparan broj
int sumOdd(int m, int n) {
    if (m > n) {
        return 0;
    }
    return ((isOdd(m))? m : 0) + sumOdd(m + 1, n);
    // return ((isOdd(n))? n : 0) + sumOdd(m, n - 1);   // alternativni nacin
}

int main() {
    int m {}, n {};

    do {
        std::cout<<"Unesite 'm': ";
        std::cin>>m;

        std::cout<<"Unesite 'n': ";
        std::cin>>n;
    } while (m > n);

    std::cout<<"Suma neparnih brojeva od "<<m<<" do "<<n<<" je "<<sumOdd(m, n)<<std::endl;

    /*
        m: 5, n: 10 => 5 + 7 + 9 = 21
    */

    return 0;
}