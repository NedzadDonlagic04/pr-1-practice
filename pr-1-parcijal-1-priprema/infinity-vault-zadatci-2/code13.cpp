#include<iostream>
#include<cmath>

/*
    Napišite program, u kojem ćete omogućiti unos 
    dva prirodna broja manja od 500 koji predstavljaju 
    granice intervala, te pronaći i ispisati kojom znamenkom 
    završava najveći prosti broj u zadanom intervalu ne 
    uključujući granične vrijednosti.
*/

void unos(int &, const char);
bool jesilProst(int);
int getNajveciProstBrojUIntervalu(int, const int);

int main() {
    int a {}, b {};

    unos(a, 'a');
    unos(b, 'b');

    int najveciProstBroj { getNajveciProstBrojUIntervalu(a, b) };

    std::cout<<"U intervalu ["<<a<<", "<<b<<"]";

    if (najveciProstBroj)
        std::cout<<" najveci prost broj je "<<najveciProstBroj<<std::endl;
    else 
        std::cout<<" nema prostih brojeva"<<std::endl;

    return 0;
}

void unos(int &broj, const char znakVarijable) {
    do {
        std::cout<<"Unesi broj ("<<znakVarijable<<"): ";
        std::cin>>broj;

        if (broj < 1 || broj > 500)
            std::cout<<"Uneseni broj treba biti veci od 1 a manji od 500\n";
    } while(broj < 1 || broj > 500);
}

bool jesilProst(int broj) {
    if (broj <= 1) return false;

    for (int i = 2; i * i <= broj; i++)
        if (broj % i == 0) 
            return false;

    return true;
}

int getNajveciProstBrojUIntervalu(int A, const int B) {
    int najveciProstBroj {0};

    for (; A <= B; A++)
        if (jesilProst(A))
            najveciProstBroj = std::max(A, najveciProstBroj);


    return najveciProstBroj;
}