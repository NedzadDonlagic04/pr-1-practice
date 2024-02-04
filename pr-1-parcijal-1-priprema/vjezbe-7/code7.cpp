#include<iostream>
#include<cmath>

void unos(int &);
int toDecimal(int, const int);
int maxNumberWithDigits(int, const int);
void ispisiNajveciBrojZaBazu(const int, const int);
void ispisiNajveciBrojZaSvakuBazu(const int);

int main() {
    int d {};

    unos(d);
    ispisiNajveciBrojZaSvakuBazu(d);

    return 0;
}

void unos(int &broj) {
    do {
        std::cout<<"Unesite broj cifara: ";
        std::cin>>broj;

        if (broj < 0)
            std::cout<<"Broj treba biti pozitivan\n";
    } while (broj < 0);
}

int toDecimal(int number, const int base) {
    int decimal {0}, eksponent {0};

    while (number) {
        decimal += ((int)std::pow(base, eksponent) * (number % 10));
        eksponent++;
        number /= 10;
    }

    return decimal;
}

int maxNumberWithDigits(int base, const int digits) {
    int maxNum {0};
    base--;

    for (int i = 0; i < digits; i++)
        maxNum = maxNum * 10 + base;

    return maxNum;
}

void ispisiNajveciBrojZaBazu(const int baza, const int brojCifara) {
    int maxNum { maxNumberWithDigits(baza, brojCifara) };

    std::cout<<"Baza: "<<baza<<" Najveci broj : "<<maxNum<<' ';
    std::cout<<"Odgovarajuci broj u dekadskom sistemu je: "<<toDecimal(maxNum, baza)<<'\n';
}

void ispisiNajveciBrojZaSvakuBazu(const int brojCifara) {
    for (int i = 2; i <= 10; i++) 
        ispisiNajveciBrojZaBazu(i, brojCifara);
}