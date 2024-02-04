#include <iostream>
#include <cmath>

/* 
    a) Omogućiti korisniku unos prirodnog broja i nakon toga napraviti funkciju koja će prebrojati koliko taj broj ima cifara

    b) Za taj broj pronaći i ispisati prvu, srednju i zadnju cifu (koristiti zasebne funkcije)

    c) Obrnuti cifre tom broju (npr. ako je broj bio 12345 treba biti 54321)    
*/

void unosPrirodnogBroja(int &);

int getBrojCifaraBroja(const int);

int getPrvuCifruBroja(const int);
int getSrednjuCifruBroja(int);
int getZadnjuCifruBroja(const int);

int getObrnutBroj(int);

int main() {
    int prirodniBroj {};

    unosPrirodnogBroja(prirodniBroj);

    std::cout<<"Broj cifara broja "<<prirodniBroj<<" je "<<getBrojCifaraBroja(prirodniBroj)<<'\n';
    std::cout<<"Prva cifra ovog broja je "<<getPrvuCifruBroja(prirodniBroj)<<'\n';
    std::cout<<"Srednja cifra ovog broja je "<<getSrednjuCifruBroja(prirodniBroj)<<'\n';
    std::cout<<"Zadnja cifra ovog broja je "<<getZadnjuCifruBroja(prirodniBroj)<<'\n';
    std::cout<<"Obrnut broj "<<prirodniBroj<<" je "<<getObrnutBroj(prirodniBroj)<<std::endl;

    std::cin.get();
    return 0;
}

void unosPrirodnogBroja(int &unos) {
    std::cout<<"Unesi prirodni broj: ";
    std::cin>>unos;
}

int getBrojCifaraBroja(const int broj) {
    return std::log10(broj) + 1;
}

int getPrvuCifruBroja(const int broj) {
    return getObrnutBroj(broj) % 10;
}

int getSrednjuCifruBroja(int broj) {
    int brojCifara { getBrojCifaraBroja(broj) / 2 };

    for (int i = 0; i < brojCifara; i++) 
        broj /= 10;

    return broj % 10;
}

int getZadnjuCifruBroja(const int broj) {
    return broj % 10;
}

int getObrnutBroj(int broj) {
    int obrnutBroj {0};

    while (broj) {
        obrnutBroj = obrnutBroj * 10 + broj % 10;
        broj /= 10;   
    }

    return obrnutBroj;
}