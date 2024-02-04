/*
Napisati program koji od korisnika trazi prvo unos 
prirodnog broja (duzina niza), nakon cega je potrebno 
napraviti 2 niza te duzine (tipa float ili koji god 
decimalni tip podatka podrzava jezik) i upisati vrijednosti 
s tastature (od korisnika) u njih.
Nakon cega je potrebno napraviti novi niz na osnovu prva 2 
niza. Novi niz sadrzi najvece elemente na odgovarajucim 
indeksima za oba niza.

Sub task 0: Uraditi ovaj zadatak kada imamo 1 unos za duzinu niza

Primjeri:

niz1 = {0.0, 2.3, -3.2}
niz2 = {1.0, 1.5, -2.5}
niz3 = {1.0, 2.3, -2.5}

Sub task 1: Uraditi ovaj zadatak kada imamo 2 unosa za duzinu niza (nizovi mogu biti razlicite duzine)

Primjeri:

niz1 = {0.0, 2.3, -3.2, 5.7, 8.9}
niz2 = {1.0, 1.5, -2.5, 4.7}
niz3 = {1.0, 2.3, -2.5, 5.7, 8.9}
*/

// Sub task 1 

#include<iostream>
#include<cstddef>
#include<cmath>
#include<limits>

void clearBuffer();

void enterArrSize(std::size_t &, const char *);
void enterArrElement(float &, const std::size_t);
void enterArrElements(float *, const std::size_t, const char *);

void printArr(const float *, const std::size_t, const char *);

float* getMaxValuesFromArrays(const float *, const float *, const std::size_t, const std::size_t, const std::size_t);

int main() {
    std::size_t arr1Size {};
    std::size_t arr2Size {};

    enterArrSize(arr1Size, "Unesi duzinu 1. niza: ");
    enterArrSize(arr2Size, "Unesi duzinu 2. niza: ");

    std::size_t arr3Size = std::max(arr1Size, arr2Size);

    float *arr1 { new float[arr1Size] };
    float *arr2 { new float[arr2Size] };
    float *arr3 {};

    enterArrElements(arr1, arr1Size, "Unos u 1. niz\n");
    enterArrElements(arr2, arr2Size, "Unos u 2. niz\n");
    arr3 = getMaxValuesFromArrays(arr1, arr2, arr1Size, arr2Size, arr3Size);

    printArr(arr1, arr1Size, "Ispis 1. niza: ");
    printArr(arr2, arr2Size, "Ispis 2. niza: ");
    printArr(arr3, arr3Size, "Ispis 3. niza: ");

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;

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
            std::cout<<"Unos nije valid\n";
            clearBuffer();
            repeatLoop = true;
        } else if (arrSize < 2 || arrSize > 10000) {
            std::cout<<"Duzina mora biti u intervalu [2, 10 000]\n";
            repeatLoop = true;
        }
    } while(repeatLoop);
}

void enterArrElement(float &num, const std::size_t index) {
    do {
        if (std::cin.fail()) {
            std::cout<<"Unos nije valid\n";
            clearBuffer();
        } 

        std::cout<<"Unesi broj na index "<<index<<": ";
        std::cin>>num;
    } while(std::cin.fail());
}

void enterArrElements(float *arr, const std::size_t arrSize, const char *outputText) {
    std::cout<<outputText;
    for (std::size_t i = 0; i < arrSize; i++) {
        enterArrElement(arr[i], i);
    }
}

void printArr(const float *arr, const std::size_t arrSize, const char *outputText) {
    std::cout<<outputText<<'\t';
    for (std::size_t i = 0; i < arrSize; i++) {
        std::cout<<arr[i]<<" \t";
    }
    std::cout<<std::endl;
}

float* getMaxValuesFromArrays(const float *arr1, const float *arr2, const std::size_t arr1Size, const std::size_t arr2Size, const std::size_t newArrSize) {
    float *newArr { new float[newArrSize] };

    for (std::size_t i = 0; i < newArrSize; i++) {
        if (i < arr1Size && i < arr2Size) {
            newArr[i] = std::max(arr1[i], arr2[i]);
        } else if (i < arr1Size) {
            newArr[i] = arr1[i];
        } else {
            newArr[i] = arr2[i];
        }
    }

    return newArr;
}