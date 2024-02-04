#include<iostream>

/*
 *  Napisati program koji ostvaruje sljedece funkcionalnosti:
 *  - Deklarisati niz od 100 cjelobrojnih vrijednosti
 *  - Generirati elemente niza koristeci random rand()%100000 + 1 i popuniti niz
 *  minimalno trocifrenim vrijednostima uz uvjet da svaki element ima neparan
 *  broj cifara
 *  - Pronaci i ispisati u kojem procentu su se pojavili prosti brojevi u nizu.
 *  Ukoliko se nije pojavio niti jedan broj, ispisati odgovarajucu poruku
 *  
 *  Primjer ispisa:
 *  26501
 *  293
 *  21727
 *  19913
 *  24371
 *  18757
 *  26309
 *  19073
 *  13291
 *  18637
 *  13967
 *  U nizu se nalazi 11% prostih brojeva
 */

int generisiBroj();
bool validirajClanaNiza(const int);
int generisiClanaNiza();
bool jelBrojProst(const int);

int main() {
    int brojProsti {0}, clanNiza {};

    for (int i = 0; i < 100; i++) {
        clanNiza = generisiClanaNiza();
        std::cout<<clanNiza<<'\n';
        if (jelBrojProst(clanNiza))
            brojProsti++;
    }
    
    if (brojProsti) 
        std::cout<<"U nizu se nalazi "<<brojProsti<<"% prostih brojeva\n";
    else
        std::cout<<"U nizu se ne nalazi niti jedan prost broj\n";

    return 0;
}

int generisiBroj() {
    return rand() % 100000 + 1; 
}

bool validirajClanaNiza(const int broj) {
    return (broj >= 100 && broj <= 999) || (broj >= 10000  && broj <= 99999);
}

int generisiClanaNiza() {
    int clanNiza {};

    do {
        clanNiza = generisiBroj();
    } while(!validirajClanaNiza(clanNiza));

    return clanNiza;
}

bool jelBrojProst(const int broj) {
    // int brojac {0};

    if (broj == 2 || broj == 3) 
        return true;
    else if (broj <= 1 || broj % 2 == 0 || broj % 3 == 0)
        return false;
    
    for (int i = 5; i * i <= broj; i += 6/* , brojac++ */)
        if (broj % i == 0 || broj % (i + 2) == 0)
            return false;

    // std::cout<<"Za broj "<<broj<<" bilo je "<<brojac<<" prolaza\n";
    
    return true;
}