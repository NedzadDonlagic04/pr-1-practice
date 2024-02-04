#include<iostream>
#include<cstddef>
#include<iomanip>

/*
    Pokazivaci i dinamicki nizovi
    Dinamicki nizovi su nizovi cija se velicina moze odrediti u run-time-u [vremenu izvodenja]
    [za razliku od statickih nizova cija je velicina poznata u compile-time-u {vremenu kompajliranja}]

    new int[vel];   
    
    Ova komanda obavlja dvije funkcionalnosti
    1. Kreiranje dinamickog niza velicine 'vel'
    2. Vracanje adrese prvog elementa [0xAA00112233]
    
    Adresa se obicno cuva u lokalnom pokazivacu.
    int *p = new int[40];
    Ovo je inicijalizacija statickog pokazivaca 'p' na adresu prvog elementa nogokreiranog dinamickog niza
    velicine 40.

    Za brisanje dinamickog niza, potrebno je koristiti komandu 'delete[]'

    delete[] -> brise dinamicki niz koji pocinje sa adresom koja mu je proslijedena
*/

int getRandomValue(const int from, const int to) {
    return rand() % (to - from + 1) + from;
}

int main() {
    // Primjer pogresne dealokacije
    /*
    int broj {34};

    delete[] &broj;     // sintaksicki ispravno ali logicki neispravno koristenje komande
    */

   std::srand(time(NULL));

    std::size_t sizeOfArr {};

    do {
        std::cout<<"Unesite velicinu niza: ";
        std::cin>>sizeOfArr;
    } while(sizeOfArr < 1);

    int *p { new int[sizeOfArr] };

    // inicijalizacija elemenata niza na random vrijednosti
    for (std::size_t i = 0; i < sizeOfArr; i++) {
        *(p + i) = getRandomValue(6, 10);    // p[i] = getRandomValue(6, 10);
    }

    for (std::size_t i = 0; i < sizeOfArr; i++) {
        std::cout<<std::setw(3)<<*(p + i);
    }

    std::cout<<std::endl;

    delete[] p;         // 1. brisanje niza 2. inicijalizacija 'p' na junk hex vrijednost
    p = nullptr;        // setovanje vrijednosti pokazivaca na adresu 0x00000000
    // nulta adresa je dobra kao defaultna vrijednost (jer se ne moze raditi sa njom)

    return 0;
}