#include<iostream>

/*  
    Napisati program koji će omogućiti unos prirodnog broja A 
    (A > 100000), te kreirati i ispisati broj B koji će se 
    sastojati od cifara broja A u obrnutom redoslijedu gdje je
    svaka parna cifra uklonjena.

    Npr. ako se unese 45362792, funkcija treba vratiti 9735
    Ispisati razliku brojava A i B

    (Obavezno koristiti bar jednu korisnički definisanu funkciju) 
*/

void unos(unsigned long long &);
unsigned long long obrniBrojIzostaviParneCifre(unsigned long long);

int main() {
    unsigned long long A {};
    
    unos(A);

    std::cout<<"Broj "<<A<<" obrnut bez parnih cifara je "<<obrniBrojIzostaviParneCifre(A)<<std::endl;

    return 0;
}

void unos(unsigned long long &broj) {
    do {
        std::cout<<"Unesi broj (A): ";
        std::cin>>broj;

        if (broj < 100000)
            std::cout<<"Unesen broj treba biti veci od 100000\n";
    } while(broj < 100000);
}

unsigned long long obrniBrojIzostaviParneCifre(unsigned long long broj) {
    unsigned long long obrnutBroj {0};
    short zadnjaCifra {};

    while (broj) {
        zadnjaCifra = broj % 10;

        if (zadnjaCifra % 2 != 0)
            obrnutBroj = obrnutBroj * 10 + zadnjaCifra;

        broj /= 10;
    }

    return obrnutBroj;
}