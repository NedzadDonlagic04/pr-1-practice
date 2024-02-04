/*
Kreirati jednodim dinam niz n velicine i napuniti 
ga serijom kubova svakog proslog broja pocevsi od 2. 
Prekida se kada se deesi overflow, napuni niz.
Ispisati niz rekurzivno!

Koristiti aritmetiku pointera!
*/

#include<iostream>
#include<cstddef>
#include<cmath>
#include<limits>

void clearBuffer();
void enterArraySize(std::size_t &);
void fillArray(unsigned int * const, std::size_t &, const std::size_t = 1);
//                                                                      ^ jer prvi clan ce biti od pocetka 2
void printArray(const unsigned int * const, const std::size_t, const std::size_t = 0);

int main() {
    std::size_t arrSize { };

    enterArraySize(arrSize);

    unsigned int *arr { new unsigned int[arrSize] };

    fillArray(arr, arrSize);
    printArray(arr, arrSize);

    delete[] arr;

    return 0;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterArraySize(std::size_t &arrSize) {
    bool repeat {};

    do {
        repeat = false;

        std::cout<<"Unesi duzinu niza: ";
        std::cin>>arrSize;

        if (std::cin.fail()) {
            std::cout<<"Greska, unos nije validan\n";
            clearBuffer(); 
            repeat = true;
        } else if (arrSize < 2) {
            std::cout<<"Duzina niza ne smije biti broj manji 2\n";
            repeat = true;
        } else if (arrSize > 10000) {
            std::cout<<"Duzina niza ne smije biti broj veci od 10 000\n";
            repeat = true;
        }
    } while(repeat);
}

void fillArray(unsigned int * const arr, std::size_t &size, const std::size_t i) {
    if (i == 1) {
        *arr = 2;
    } else if (i == size) {
        return;
    }

    *(arr + i) = std::pow(*(arr + i - 1), 3);

    // In case of overflow in last fill
    // Stop recursion and make i the size of the array
    if (*(arr + i) < *(arr + i - 1)) {
        size = i;
        return;
    }

    fillArray(arr, size, i + 1);
}

void printArray(const unsigned int * const arr, const std::size_t size, const std::size_t i) {
    if (i == 0) {
        std::cout<<"Clanovi niza: ";
    } else if (i == size) {
        std::cout<<std::endl;
        return;
    }

    std::cout<<*(arr + i)<<' ';

    printArray(arr, size, i + 1);
}