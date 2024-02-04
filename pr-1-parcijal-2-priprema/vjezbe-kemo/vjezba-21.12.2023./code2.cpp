#include<iostream>
#include<cstddef>
#include<iomanip>

/*
    Dinamicki nizovi i funkcije
*/

// createArray [alokacija]
int* createArray(const std::size_t size) {
    // int arr[40] = {0};           // inicijalizacija svih varijabli na 0

    return new int[size] {0};       // 1. kreiranje niza, 2. inicijalizacija svih, 3. vracanje adrese prve varijable
}

// enterArray [za korisnicki unos] ili setRandomValues [za randomizaciju]
void enterArray(int *p, const std::size_t size) {
    for (std::size_t i = 0; i < size; i++) {
        std::cout<<"Unesite vrijednost na lokaciji "<<i<<": ";
        std::cin>>*(p + i);     // p[i];
    }
}

// printArray [ispis]
void printArray(int *p, const std::size_t size) {
    std::cout<<"Ispis niza\n";
    for (std::size_t i = 0; i < size; i++) {
        std::cout<<std::setw(4)<<*(p + i)<<' ';
    }
    std::cout<<std::endl;
}

// deleteArray ili destroyArray [dealokacija]
void deleteArray(int *p) {
    delete[] p;
    p = nullptr;        // ovdje je 'nullptr' suvisan zbog toga sto je 'p' lokalna varijabla
}

void deleteArray2(int *&p) {
    delete[] p;
    p = nullptr;        // ovdje je 'nullptr' pogodan zbog toga sto je 'p' referenca na drugu varijablu
}

int main() {
    std::size_t sizeOfArr {};

    do {
        std::cout<<"Unesite velicinu niza: ";
        std::cin>>sizeOfArr;
    } while(sizeOfArr < 1);

    int *p { createArray(sizeOfArr) };

    enterArray(p, sizeOfArr);       // ili eventualno setRandomValues
    printArray(p, sizeOfArr);       
    deleteArray2(p);                // proslijeduje se adresa kojom pocinje niz, i onda se niz obrise

    return 0;
}