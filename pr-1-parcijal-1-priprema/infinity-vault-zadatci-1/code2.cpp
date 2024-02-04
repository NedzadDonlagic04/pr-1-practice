#include <iostream>

/* 
    Napisati program u kojem je potrebno unijeti odabrani broj cifara 
    počevši od cifre najveće težinske vrijednosti, pa od njih sastaviti 
    i napisati prirodni broj. Unos cifara se prekida kada se unese broj 
    manji od 0, ukoliko korisnik unese cifru veću od 9, ispisati poruku 
    da cifra nije validna, ali se unos ne prekida.

    (Obavezno koristiti barem jednu korisnički definisanu funkciju)

    Ispis neka bude oblika:

    Upisi cifru: 2

    Upisi cifru: 8

    Upisi cifru: 72

    Cifra nije validna

    Upisi cifru: -1

    Broj sastavljen od zadanih cifara je 28.
*/

void unosCifaraPrirodnogBroja(unsigned long long &);

int main() {
    unsigned long long prirodniBroj { 0ull };

    unosCifaraPrirodnogBroja(prirodniBroj);

    std::cout<<"Broj sastavljen od zadanih cifara je "<<prirodniBroj<<"."<<std::endl;

    std::cin.get();
    return 0;
}

void unosCifaraPrirodnogBroja(unsigned long long &prirodniBroj) {
    int unos {};

    do {
        std::cout<<"Upisi cifru: ";
        std::cin>>unos;

        if (unos > 9)
            std::cout<<"\nCifra nije validna\n";
        else if (unos >= 0)
            prirodniBroj = prirodniBroj * 10 + unos;
        std::cout<<'\n';
    } while (unos >= 0);
}