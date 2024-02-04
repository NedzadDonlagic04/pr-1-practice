#include<iostream>

/*
    5. Zadatak
    Napisati rekurzivnu funkciju 'sumSpec' koja izracunava sumu brojeva izmedu m i n
    koji su djeljivi sa 3 i nedjeljivi sa 7

*/

// uvecavamo 'm' do vrijednosti 'n' ['n' je fiksna vrijednost]
// na sumu dodajemo 'm' samo ako je neparan broj
int sumSpec(int m, int n) {
    if (m > n) {
        return 0;
    }
    return ((m % 3 == 0 && m % 7 != 0)? m : 0) + sumSpec(m + 1, n);
    // return ((n % 3 == 0 && n % 7 != 0)? n : 0) + sumSpec(m, n - 1);  // alternativni nacin
}

int main() {
    int m {}, n {};

    do {
        std::cout<<"Unesite 'm': ";
        std::cin>>m;

        std::cout<<"Unesite 'n': ";
        std::cin>>n;
    } while (m > n);

    std::cout<<"Suma brojeva djeljivi sa 3 i nedjeljivi sa 7 od "<<m<<" do "<<n<<" je "<<sumSpec(m, n)<<std::endl;

    return 0;
}