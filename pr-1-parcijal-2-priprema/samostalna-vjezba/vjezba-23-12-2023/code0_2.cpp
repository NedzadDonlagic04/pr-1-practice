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

// Sub Task 2

#include<iostream>
#include<cstddef>

void fillOutArray(int *, const std::ptrdiff_t, const std::ptrdiff_t = 0);
void printArray(const int *, const std::ptrdiff_t, const std::ptrdiff_t = 0);

int main() {
    constexpr std::size_t ARR_SIZE { 100 };
    int niz[ARR_SIZE] {};

    fillOutArray(niz, std::size(niz));
    printArray(niz, std::size(niz));

    return 0;
}

void fillOutArray(int *niz, const std::ptrdiff_t size, const std::ptrdiff_t i) {
    if (i == size) {
        return;
    }

    *(niz + i) = (i % 2 == 0)? -i : i;

    fillOutArray(niz, size, i + 1); 
}

void printArray(const int *niz, const std::ptrdiff_t size, const std::ptrdiff_t i) {
    if (i == 0) {
        std::cout<<"Niz: ";
    } else if (i == size) {
        std::cout<<std::endl;
        return;
    }

    std::cout<<*(niz + i)<<' ';

    printArray(niz, size, i + 1); 
}