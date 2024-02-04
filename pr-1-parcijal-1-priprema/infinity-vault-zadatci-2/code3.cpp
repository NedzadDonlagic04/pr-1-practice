#include<iostream>

/* 
    Svaki paran broj se može prikazati kao suma dva prosta 
    broja (tkz. Goldbachovo pravilo). Napisati program koji 
    će najprije učitati dva prirodna broja n1 i n2 (n2 > n1).

    Zatim prikazati sve parne brojeve u intervalu od n1 do n2 
    kao sumu dva prosta broja.

    (U glavnom programu samo unijeti navedena dva prirodna broja 
    i pozvati funkciju koja obavlja zadani posao.)
*/

int cachedProstiBroj = 3;

void unos(int &, const int, const int);
void ispisiSveParneOdADoB(int, const int);
bool jesilProst(int);
void goldbach(const int);

int main() {
    int n1 {}, n2 {};

    unos(n1, 1, 0);
    unos(n2, 2, n1);

    ispisiSveParneOdADoB(n1, n2);

    return 0;
}

void unos(int &broj, const int kojiN, const int min) {
    do {
        std::cout<<"Unesi prirodni broj (n"<<kojiN<<"): ";
        std::cin>>broj;

        if (broj <= min)
            std::cout<<"Uneseni broj treba biti veci od "<<min<<'\n';
    } while(broj <= min);
}

void ispisiSveParneOdADoB(int A, const int B) {
    for(A = A + (A % 2 != 0); A <= B; A += 2)
        goldbach(A);
}

bool jesilProst(const int broj) {
    if (broj <= 1) return false;

    for (int i = 2; i * i <= broj; i++)
        if (broj % i == 0) 
            return false;

    return true;
}

void goldbach(const int broj) {
    if (broj == 4) {
        std::cout<<"4 = 2 + 2\n";
    } else if (jesilProst(cachedProstiBroj) && jesilProst(broj - cachedProstiBroj)) {
        std::cout<<broj<<" = "<<cachedProstiBroj<<" + "<<broj - cachedProstiBroj<<'\n';
        cachedProstiBroj += 2;
    } else {
        for (int i = 3; i <= broj - i; i += 2) {
            if (jesilProst(i) && jesilProst(broj - i)) {
                std::cout<<broj<<" = "<<i<<" + "<<broj - i<<'\n';
                cachedProstiBroj = i + 2;
                break;
            }
        }
    }
}