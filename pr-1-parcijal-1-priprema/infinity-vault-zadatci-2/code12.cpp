#include<iostream>

/*
    Napišite program u kojem ćete omogućiti unos 
    dva prirodna broja manja od 500 koji predstavljaju 
    granice intervala, te pronaći i ispisati kojom cifrom/znamenkom
    završava umnožak svih prostih brojeva u zadanom intervalu 
    uključujući granične vrijednosti.
*/

void unos(int &, const char);
bool jesilProst(int);
short getZadnjuCifruUmnoskaProstiBrojeveIntervalaADoB(int, const int);

int main() {
    int a {}, b {};

    unos(a, 'a');
    unos(b, 'b');

    std::cout<<"Kada se prosti brojevi u intervalu ["<<a<<", "<<b<<"] izmnoze zadnja cifra broja bude ";
    std::cout<<getZadnjuCifruUmnoskaProstiBrojeveIntervalaADoB(a, b)<<std::endl;

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

short getZadnjuCifruUmnoskaProstiBrojeveIntervalaADoB(int A, const int B) {
    unsigned long long proizvod { 1ull }; 

    for (; A <= B; A++)
        if (jesilProst(A))
            proizvod *= A;

    return proizvod % 10;
}