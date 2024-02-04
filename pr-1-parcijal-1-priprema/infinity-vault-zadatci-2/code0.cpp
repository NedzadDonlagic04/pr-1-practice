#include<iostream>

/*  Napisati program koji simulira bacanje 3 kockice (jedna 
    kockica ima 6 strana i na tim stranama su brojevi 1 - 6).
    Simuliranje bacanja svake kockice ostvariti funkcijom rand() % 6 + 1.
    Simulirati konstantno bacanje sve tri kockice dok se u dva uzastopna 
    bacanja ne desi da se dobiju isti brojevi na sve tri kockice 
    (npr. u šestom bacanju se dobiju brojevi 2, 2, 2, a u sedmom 4, 4, 4
    na sve tri kockice).

    Ispisati koliko je ukupno bilo bacanja dok se nije ispunio navedeni uslov.

    Nije potrebno tražiti bilo kakav unos od korisnika. */

short baciKocku();
int getBrojIteracijaDoUslova();

int main() {
    // srand(time(NULL));
    // Nije trazeno u zadatku ali je moguce randomizirati seed prilikom pokretanja programa
    
    std::cout<<"Nakon "<<getBrojIteracijaDoUslova()<<" bacanja dobili smo iste cifre 2 puta zaredom"<<std::endl;

    return 0;
} 

short baciKocku() {
    return rand() % 6 + 1;
}

int getBrojIteracijaDoUslova() {
    int brojPonavljanjaBacanja {0};
    short brojac {0}, jednoBacanje {}, drugoBacanje {}, treceBacanje {};

    while (brojac < 2) {
        jednoBacanje = baciKocku();
        drugoBacanje = baciKocku();
        treceBacanje = baciKocku();
        brojPonavljanjaBacanja++;

        if (jednoBacanje == drugoBacanje && drugoBacanje == treceBacanje)
            brojac++;
        else
            brojac = 0;
    }

    return brojPonavljanjaBacanja;
}