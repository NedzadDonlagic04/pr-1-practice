#include<iostream>

/*
    Napisati program koji će omogućiti korisniku unos broja 
    n ( 10 <= n <= 1000). Zatim simulirati n bacanja kockice 
    (kockica ima 6 strana i na tim stranicama su brojevi 1-6).
    Simuliranje bacanja svake kockice ostvariti funkcijom rand() % 6 + 1.
    Izračunati statičke podatke u kojem procentu ukupnog bacanja 
    se dobiva svaki od mogućih brojeva 1-6. Obavezno koristiti switch 
    statement za zbrajanje rezultata bacanja kockice.

    Napomena: Po želji kreirati dodatne funkcije da se olakša rješavanje zadataka.
*/

void unos(int &);
int baciKocku();
void ispisiProcenatBacanja(const int);

int main() {
    int n {};

    unos(n);
    ispisiProcenatBacanja(n);

    return 0;
}

void unos(int &broj) {
    do {
        std::cout<<"Unesi broj bacanja (n): ";
        std::cin>>broj;

        if (broj < 10 || broj > 1000)
            std::cout<<"Unesi broj ne smije biti manji od 10 ili veci od 1000\n";
    } while(broj < 10 || broj > 1000);
}

int baciKocku() {
    return rand() % 6 + 1;
}

void ispisiStatistiku(const int broj, const int statistika) {
    std::cout<<"Broj "<<broj<<" se pojavio "<<statistika<<"%\n";
}

void ispisiProcenatBacanja(const int brojBacanja) {
    const int DUZINA_NIZA { 6 };
    int pojavljivanje[DUZINA_NIZA] {};

    for (int i = 0; i < brojBacanja; i++) 
        pojavljivanje[baciKocku() - 1]++;

    for (int i = 0; i < DUZINA_NIZA; i++) 
        ispisiStatistiku(i + 1, float(pojavljivanje[i]) / brojBacanja * 100);
}