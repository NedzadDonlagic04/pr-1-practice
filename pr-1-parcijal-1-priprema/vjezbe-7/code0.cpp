#include<iostream>

void unos(int &);
bool isPrime(int);
bool isSorted(int);
void ispisiSveProsteSaUslovomZadatka(const int);

int main() {
    int n {};

    unos(n);
    ispisiSveProsteSaUslovomZadatka(n);

    return 0;
}

void unos(int &broj) {
    do {
        std::cout<<"Unesite 'n':\n";
        std::cin>>broj;

        if (broj < 2 || broj > 1000)
            std::cout<<"Uneseni broj mora biti u intervalu [2, 1000]\n";
    } while (broj < 2 || broj > 1000);
}

bool isPrime(int x) {
    if (x == 2 || x == 3) return true;
    else if (x <= 1 || x % 2 == 0 || x % 3 == 0) return false;

    for (int i = 5; i * i <= x; i += 6)
        if (x % i == 0 || x % (i + 2) == 0)
            return false;

    return true;
}

bool isSorted(int x) {
    int zadnjaCifra {x % 10};
    x /= 10;

    while(x) {
        if (zadnjaCifra < x % 10)
            return false;
        
        zadnjaCifra = x % 10;
        x /= 10;
    }

    return true;
}

void ispisiSveProsteSaUslovomZadatka(const int max) {
    std::cout<<"Ispis brojeva\n"<<std::endl;

    if (max > 2)
        std::cout<<2<<' '; 
    if (max > 3)
        std::cout<<3<<' ';

    for (int i = 5; i <= max; i += 6) {
        if (isPrime(i) && isSorted(i))
            std::cout<<i<<' ';
        if (isPrime(i + 2) && isSorted(i + 2))
            std::cout<<i + 2<<' ';
    }

    std::cout<<std::endl;
}