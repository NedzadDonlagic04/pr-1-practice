#include<iostream>
#include<cmath>

int takeEvenDigits(int);
void unos(int &, const char);
bool imasLiParnuCifruSemNule(int);
void ispisiBrojeveUIntervalu(int, const int);

int main() {
    int m {}, n {};

    do {
        unos(m, 'm');
        unos(n, 'n'); 
    } while(m > n);

    ispisiBrojeveUIntervalu(m, n);

    return 0;
}

int takeEvenDigits(int number) {
    int evenNumber {0}, counter {0};

    while (number) {
        if (number % 10 % 2 == 0) {
            evenNumber += (number % 10 * std::pow(10, counter));
            counter++;
        }

        number /= 10;
    }

    return evenNumber;
}

void unos(int &broj, const char varZnak) {
    do {
        std::cout<<"Unesi pozitivan broj '"<<varZnak<<"': ";
        std::cin>>broj;
    } while(broj < 0);
}

bool imasLiParnuCifruSemNule(int broj) {
    while (broj) {
        if (broj % 10 % 2 == 0 && broj % 10)
            return true;

        broj /= 10;
    }

    return false;
}

void ispisiBrojeveUIntervalu(int m, const int n) {
    int parneCifre {};

    for (; m < n; m++) {
        parneCifre = takeEvenDigits(m);

        if (imasLiParnuCifruSemNule(parneCifre)) 
            std::cout<<m<<" -> "<<parneCifre<<'\n'; 
    }
    
    std::cout<<std::endl;
}