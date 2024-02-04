/*
Napisati program koji će omogućiti korisniku da 
unese veličinu jednodimenzionalnog dinamičkog niza 
integer vrijednosti. Napisati funkciju koja će taj 
niz popuniti serijom Fibonacci brojeva počevši od 
broja 1. Za pronalazenje elemenata Fibonacci serije 
obavezno koristiti rekurzivnu funkciju. Punjenje niza 
se prekida kada se popuni cijeli niz ili kada se desi 
overflow na integer varijabli.

(U ovom zadatku je zabranjeno indeksirati niz uglastim 
zagradama. Obavezno koristiti aritmetiku pokazivača.)
*/

#include<iostream>
#include<cstddef>
#include<limits>

void enterArraySize(std::size_t &);
void fillArray(unsigned int * const, std::size_t &, const std::size_t = 2);
//                                                       ^ jer prvi clan ce biti od pocetka 2
bool isValueInArray(unsigned int * const, const std::ptrdiff_t, const std::ptrdiff_t, const int);
void clearBuffer();
void enterValueToFind(int &);

int main() {
    std::size_t arrSize {};

    enterArraySize(arrSize);

    unsigned int *arr { new unsigned int[arrSize] };

    fillArray(arr, arrSize);

    int numToFind {};

    enterValueToFind(numToFind);

    if (isValueInArray(arr, 0, arrSize - 1, numToFind)) {
        std::cout<<"Vrijednost "<<numToFind<<" se nalazi u nizu\n";
    } else {
        std::cout<<"Vrijednost "<<numToFind<<" se ne nalazi u nizu\n";
    }

    delete[] arr;

    return 0;
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
        } else if (arrSize <= 2) {
            std::cout<<"Duzina niza ne smije biti broj manji ili jednak 2\n";
            repeat = true;
        } else if (arrSize > 10000) {
            std::cout<<"Duzina niza ne smije biti broj veci od 10 000\n";
            repeat = true;
        }
    } while(repeat);
}

void fillArray(unsigned int * const arr, std::size_t &size, const std::size_t i) {
    if (i == 2) {
        *arr = 1;
        *(arr + 1) = 1;
    }
    if (i == size) {
        return;
    }

    *(arr + i) = *(arr + i - 1) + *(arr + i - 2);

    // In case of overflow in last fill
    // Stop recursion and make i the size of the array
    if (*(arr + i) < *(arr + i - 1)) {
        size = i;
        return;
    }

    fillArray(arr, size, i + 1);
}

// Function below implements the binary search algorithm
// It works because we fill the array with values that are sorted
bool isValueInArray(unsigned int * const arr, const std::ptrdiff_t start, const std::ptrdiff_t end, const int numToFind) {
    if (start > end) {
        return false;
    }

    const std::ptrdiff_t middle { (end - start) / 2 + start };

    if (arr[middle] == numToFind) {
        return true;
    } else if (arr[middle] > numToFind) {
        return isValueInArray(arr, start, middle - 1, numToFind);
    } else {
        return isValueInArray(arr, middle + 1, end, numToFind);
    }
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterValueToFind(int &num) {
    do {
        if (std::cin.fail()) {
            std::cout<<"Greska, unos nije validan\n";
            clearBuffer(); 
        }

        std::cout<<"Unesi broj za pronaci: ";
        std::cin>>num;
    } while(std::cin.fail());
}