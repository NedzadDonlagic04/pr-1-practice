/*
Kreirati niz duzine 100, nakon cega je potrebno izvrsiti 
unos podataka u niz na nacin da svaki parni index spasi 
negativni verziju sebe, dok svaki neparni index spasi 
pozitivni verziju sebe. Primjer ispod
niz[0] ima vrijednost 0
niz[1] ima vrijednost 1
niz[2] ima vrijednost -2
niz[3] ima vrijednost 3
niz[4] ima vrijednost -4
...
Nakon cega se ovaj niz treba ispisati.

Sub task 0: Uraditi ovo bez ijedne funkcije, cisto unutar main funkcije
Sub task 1: Uraditi ovo uz pomoc 2 funkcije, fillOutArray i printArray
Sub task 2: Gore navedene funkcije napisati rekurzivno
*/

// Sub Task 1 

#include<iostream>
#include<cstddef>

constexpr std::size_t ARR_SIZE { 100 };

void fillOutArray(int (&)[ARR_SIZE]);
void printArray(const int (&)[ARR_SIZE]);

int main() {
    int niz[ARR_SIZE] {};

    fillOutArray(niz);
    printArray(niz);

    return 0;
}

void fillOutArray(int (&niz)[ARR_SIZE]) {
    for (std::ptrdiff_t i = 0; i < ARR_SIZE; i++) {
        niz[i] = (i % 2 == 0)? -i : i;
    }
}

void printArray(const int (&niz)[ARR_SIZE]) {
    std::cout<<"Niz: ";
    for (const auto broj : niz) {
        std::cout<<broj<<' ';
    }
    std::cout<<std::endl;
}