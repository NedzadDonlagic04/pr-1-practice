/*
Napisati program koji od korisnika trazi prvo unos 
prirodnog broja (duzina niza), nakon cega je potrebno 
napraviti 2 niza te duzine (tipa float ili koji god 
decimalni tip podatka podrzava jezik) i upisati vrijednosti 
s tastature (od korisnika) u njih.
Nakon cega je potrebno napraviti novi niz na osnovu prva 2 
niza. Novi niz sadrzi najvece elemente na odgovarajucim 
indeksima za oba niza.

Napomena, u zadatku je obavezno da se napravi struktura koja ce
sadrzati niz i duzinu niza, i da se ona primarno koristi za rad sa
ova 3 niza.

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

// Sub Task 0

#include<iostream>
#include<cstddef>
#include<cmath>
#include<limits>

struct Array {
    const std::size_t size {};
    float *array {};

    Array(const std::size_t);
    ~Array();
};

Array::Array(const std::size_t size) : size(size), array(new float[size]) {}

Array::~Array() {
    delete[] this->array;
}

void clearBuffer();

void enterArrSize(std::size_t &);
void enterArrElement(float &, const std::size_t);
void enterArrElements(Array &, const char *);

void printArr(const Array &, const char *);

void getMaxValuesFromArrays(const Array &, const Array &, Array &);

int main() {
    std::size_t arrSize {};

    enterArrSize(arrSize);

    Array arr1(arrSize);
    Array arr2(arrSize);
    Array arr3(arrSize);

    enterArrElements(arr1, "Unos u 1. niz\n");
    enterArrElements(arr2, "Unos u 2. niz\n");
    getMaxValuesFromArrays(arr1, arr2, arr3);

    printArr(arr1, "Ispis 1. niza: ");
    printArr(arr2, "Ispis 2. niza: ");
    printArr(arr3, "Ispis 3. niza: ");

    return 0;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterArrSize(std::size_t &arrSize) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<"Unesi duzinu niza: ";
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

void enterArrElements(Array &arr, const char *outputText) {
    std::cout<<outputText;
    for (std::size_t i = 0; i < arr.size; i++) {
        enterArrElement(arr.array[i], i);
    }
}

void printArr(const Array &arr, const char *outputText) {
    std::cout<<outputText<<'\t';
    for (std::size_t i = 0; i < arr.size; i++) {
        std::cout<<arr.array[i]<<" \t";
    }
    std::cout<<std::endl;
}

void getMaxValuesFromArrays(const Array &arr1, const Array &arr2, Array &arr3) {
    for (std::size_t i = 0; i < arr3.size; i++) {
        arr3.array[i] = std::max(arr1.array[i], arr2.array[i]);
    }
}
