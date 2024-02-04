/*
Napisati program koji će omogućiti korisniku da 
unese veličinu jednodimenzionalnog dinamičkog niza 
integer vrijednosti. Napisati rekurzivnu funkciju koja 
će taj niz popuniti faktorijelom rednog broja člana 
niza (1!, 2!, 3!, 4!...). Rekurzija se prekida kada se 
popuni cijeli niz ili kada se desi overflow na integer 
varijabli. U ovom zadatku je zabranjeno indeksirati elemente 
niza uglastim zagradama.

(Obavezno koristiti aritmetiku pokazivača. Obavezno sve 
riješiti jednom rekurzivnom funkcijom.)
*/

#include<iostream>
#include<cstddef>
#include<limits>

void clearBuffer();
void enterArraySize(std::size_t &);
unsigned int getFactorial(const int);
void fillArray(unsigned int * const, std::size_t &, const std::size_t = 1);
void printArray(unsigned int * const, const std::size_t, const std::size_t = 0);

int main() {
    std::size_t arrSize {};

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

unsigned int getFactorial(const int num) {
    if (num <= 1) {
        return 1;
    }

    return num * getFactorial(num - 1);
}

void fillArray(unsigned int * const arr, std::size_t &size, const std::size_t i) {
    if (i == 1) {
        *arr = getFactorial(1);
    } else if (i == size) {
        return;
    }

    *(arr + i) = getFactorial(i + 1);

    // In case of overflow in last fill
    // Stop recursion and make i the size of the array
    if (*(arr + i) < *(arr + i - 1)) {
        size = i;
        return;
    
    }

    fillArray(arr, size, i + 1);
}

void printArray(unsigned int * const arr, const std::size_t size, const std::size_t i) {
    if (i == 0) {
        std::cout<<"Clanovi niza: ";
    } else if (i == size) {
        std::cout<<std::endl;
        return;
    }

    std::cout<<*(arr + i)<<' ';

    printArray(arr, size, i + 1);
}