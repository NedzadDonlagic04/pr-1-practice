#include <iostream>

/* 
    Napisati program koji će omogućiti unos prirodnog broja A (A > 100000), 
    te kreirati i ispisati broj B koji će se sastojati od cifara broja A u 
    obrnutom redoslijedu u kojem je svaka parna uklonjena. (npr. ako se 
    unese 45362792 funkcija će vratiti 9735). Ispisati razliku brojeva A i B.

    (Obavezno koristiti bar jednu korisnički definiranu funkciju.)
*/

void unosBrojA(unsigned long long &);
unsigned long long kreirajBrojB(unsigned long long);

int main() {
    unsigned long long A {}, B {};

    unosBrojA(A);

    B = kreirajBrojB(A);

    std::cout<<"Broj A: "<<A<<'\n';
    std::cout<<"Broj B: "<<B<<'\n';
    std::cout<<"Razlika: "<<A - B<<std::endl;

    std::cin.get();
    return 0;
}

void unosBrojA(unsigned long long &A) {
    do {
        std::cout<<"Unesi prirdno broj (A): ";
        std::cin>>A;
    } while(A <= 100000);
}

unsigned long long kreirajBrojB(unsigned long long A) {
    unsigned long long B {0ull};
    int zadnjaCifra {};

    while (A) {
        zadnjaCifra = A % 10;

        if (zadnjaCifra % 2 != 0)
            B = B * 10 + zadnjaCifra % 10;

        A /= 10;
    }

    return B;
}