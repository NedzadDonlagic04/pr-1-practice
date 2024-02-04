/*
Napraviti funkciju intscmp (integers compare) koja ce uzeti 2 niza 
(mogu biti razlicite duzine) i vratiti 0 ako su oba niza jednaka, 
-1 ako je prvi niz veci od drugog, 1 ako je drugi niz veci od prvog. 

Cilj zadatka je pokazati funkcionalnost funkcije, hoce li se praviti
statican niz, dinamican, hard coded je nebitno.

Primjeri nizova i rezultata nakon sto se proslijede funkciji:

niz1 = {1, 2, 3, 4, 5}
niz2 = {1, 2, 3, 4, 5}
Ovdje je rezultat funkcije 0 jer su oba niza jednaka

niz1 = {1, 2, 1, 4, 5}
niz2 = {1, 2, 3, 4, 5}
Ovdje je rezultat funkcije 1 jer 3. clan u niz1 manji od 3. clana niz2

niz1 = {5, 2, 3, 4, 5}
niz2 = {1, 2, 3, 4, 5}
Ovdje je rezultat funkcije -1 jer 1. clan u niz1 je veci od 1. clana niz2

niz1 = {1, 2, 3, 4, 5, 6, 7}
niz2 = {1, 2, 3, 4, 5}
Ovdje je rezultat funkcije -1 jer 1. niz veci od 2.

niz1 = {1, 2, 3, 4, 5, 6, 7}
niz2 = {1, 2, 3, 4, 5, 6, 7, 8}
Ovdje je rezultat funkcije 1 jer 2. niz veci od 1.
*/

#include<iostream>
#include<cstddef>
#include<limits>

void clearBuffer();

void enterArrSize(std::size_t &, const char *);
void enterArrNum(int &, const std::size_t);
void enterArr(int *, const std::size_t, const char *);

void printArr(const int *, const std::size_t, const char *);

int intscmp(const int *, const std::size_t, const int *, const std::size_t);

int main() {
    std::size_t arr1Size {}, arr2Size {};
    int *arr1 {}, *arr2 {};

    enterArrSize(arr1Size, "Unesi duzinu niza 1: ");
    arr1 = new int[arr1Size];
    enterArr(arr1, arr1Size, "Unos vrijednosti u niz 1\n");

    enterArrSize(arr2Size, "Unesi duzinu niza 2: ");
    arr2 = new int[arr2Size];
    enterArr(arr2, arr2Size, "Unos vrijednosti u niz 2\n");

    printArr(arr1, arr1Size, "Niz 1: ");
    printArr(arr2, arr2Size, "Niz 2: ");

    const int arrCmp { intscmp(arr1, arr1Size, arr2, arr2Size) };

    if (arrCmp == -1) {
        std::cout<<"Prvi niz je veci od drugog niza\n";
    } else if (arrCmp == 0) {
        std::cout<<"Nizovi su jednaki\n";
    } else {
        std::cout<<"Drugi niz je veci od prvog niza\n";
    }

    delete[] arr1;
    delete[] arr2;

    return 0;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterArrSize(std::size_t &arrSize, const char *outputText) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>arrSize;

        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
            repeatLoop = true;
        } else if (arrSize < 2) {
            std::cout<<"Duzina niza ne moze biti manji od 2\n";
            repeatLoop = true;
        } else if (arrSize > 10000) {
            std::cout<<"Duzina niza ne moze biti veca od 10 000\n";
            repeatLoop = true;
        }
    } while(repeatLoop);
}

void enterArrNum(int &num, const std::size_t index) {
    do {
        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
        }

        std::cout<<"Unesi broj na index poziciju "<<index<<": ";
        std::cin>>num;
    } while(std::cin.fail());
}

void enterArr(int *arr, const std::size_t arrSize, const char *outputText) {
    std::cout<<outputText;
    for (std::size_t i = 0; i < arrSize; i++) {
        enterArrNum(arr[i], i);
    }
}

void printArr(const int *arr, const std::size_t arrSize, const char *outputText) {
    std::cout<<outputText;
    for (std::size_t i = 0; i < arrSize; i++) {
        std::cout<<arr[i]<<' ';
    }
    std::cout<<std::endl;
}

int intscmp(const int *arr1, const std::size_t arr1Size, const int *arr2, const std::size_t arr2Size) {
    if (arr1Size > arr2Size) {
        return -1;
    } else if (arr1Size < arr2Size) {
        return 1;
    }

    for (std::size_t i = 0; i < arr1Size; i++) {
        if (arr1[i] > arr2[i]) {
            return -1;
        } else if (arr1[i] < arr2[i]) {
            return 1;
        }
    }

    return 0;
}