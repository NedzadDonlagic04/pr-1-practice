#include<iostream>

/*
    Poštujući sve faze procesa programiranja napraviti program 
    koji pronalazi i ispisuje sve složene brojeve brojeve iz 
    intervala m-n (10 < m < 100, 500 < n < 2000, m < n; ukoliko 
    unesene vrijednosti nisu ispravne, učitavanje treba ponavljati), 
    te pronalazi i ispisuje njihovu aritmetičku sredinu. Napraviti 
    sljedeće funkcije:

    bool slozeni – koja će ispitivati da li je broj složeni 
    ispis – koja koja će ispisivati sve složene brojeve i vratiti main funkciji 
    njihovu aritmetičku sredinu.

    U glavnom programu je potrebno ispisati aritmetičku sredinu.

    Složeni broj je svaki broj koji nije prosti, odnosno koji ima bar 
    jednog djelioca osim broja 1 i samog sebe.
*/

void unos(int &, const char, const int, const int);
bool slozeni(int);
float ispisi(int, const int);

int main() {
    int m {}, n {};

    unos(m, 'm', 10, 100);
    unos(n, 'n', 500, 2000);

    const float aritmetickaSredina { ispisi(m, n) };

    std::cout<<"Aritmeticka sredina slozenih brojeva je "<<aritmetickaSredina<<std::endl;

    return 0;
}

void unos(int &broj, const char znakVarijable, const int min, const int max) {
    do {
        std::cout<<"Unesi broj ("<<znakVarijable<<"): ";
        std::cin>>broj;

        if (broj <= min)
            std::cout<<"Uneseni broj mora biti veci od "<<min<<'\n';
        else if (broj >= max)
            std::cout<<"Uneseni broj mora biti manji od "<<max<<'\n';
    } while(broj <= min || broj >= max);
}

bool slozeni(int broj) {
    if (broj <= 1) return true;

    for (int i = 2; i * i <= broj; i++) 
        if (broj % i == 0)
            return true;

    return false;
}

float ispisi(int m, const int n) {
    int brojac {0}, suma {0};

    for (; m <= n; m++) {
        if (slozeni(m)) {
            brojac++;
            suma += m;
            std::cout<<m<<' ';
        }
    }
    std::cout<<std::endl;

    return (brojac)? (float)suma / brojac : suma;
    //      ^ u slucaju da brojac je 0, tj. nema slozeni brojeva u intervalu
    // moramo napraviti uslov da izbjegnemo potencijalno dijeljenje sa 0
    // u nasem slucaju se to nece desiti jer je unos to ogranicio al da funkcija
    // bude sto vise fleksibilna dodano je ovdje
}