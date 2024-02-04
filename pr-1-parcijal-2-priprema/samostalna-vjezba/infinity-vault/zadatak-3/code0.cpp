/*
Napisati program koji će omogućiti korisniku da unese veličinu n 
jednodimenzionalnog dinamičkog niza integer vrijednosti (n > 2). 
Napisati rekurzivnu funkciju koja će taj niz puniti serijom brojeva 
tako da je svaki sljedeći broj jednak umnošku dva prethodna broja, 
a prva dva elementa su 1 i 3 (1, 3, 3, 9, 27, ...).

Zatim napraviti drugu rekurzivnu funkciju koja će izračunati zbir 
svih elemenata tog niza (voditi računa o tipu podatka zbog veličine broja).

(Obavezno koristiti aritmetiku pokazivača)
*/

#include<iostream>
#include<cstddef>
#include<limits>

// 64 because unsigned long long for me is 8 bytes
// which when converted to bits is 64
using int_64 = unsigned long long;

void clearBuffer();
void enterArraySize(std::size_t &);
void fillArray(unsigned int * const, const std::size_t, const std::size_t = 2);
//                                                                          ^ jer prva dva clana popunimo, tj. indekse 0 i 1
int_64 zbirElemenataNiza(unsigned int * const, const std::size_t, const std::size_t = 0);

int main() {
    std::size_t arrSize {};

    enterArraySize(arrSize);

    unsigned int *arr { new unsigned int[arrSize] };

    fillArray(arr, arrSize);

    int_64 sumaClanovaNiza { zbirElemenataNiza(arr, arrSize) };

    std::cout<<"Suma clanova niza duzine "<<arrSize<<" je "<<sumaClanovaNiza<<std::endl;

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
        } else if (arrSize <= 2) {
            std::cout<<"Duzina niza ne smije biti broj manji ili jednak 2\n";
            repeat = true;
        } else if (arrSize > 10000) {
            std::cout<<"Duzina niza ne smije biti broj veci od 10 000\n";
            repeat = true;
        }
    } while(repeat);
}

void fillArray(unsigned int * const arr, const std::size_t size, const std::size_t i) {
    if (i == 2) {
        // Posto smo garantovani da imamo arrSize > 2
        // ovo je ok za uraditi
        *arr = 1;
        *(arr + 1) = 3;    
    } else if (i == size) {
        return;
    }

    *(arr + i) = *(arr + i - 1) * *(arr + i - 2);

    fillArray(arr, size, i + 1);
}

int_64 zbirElemenataNiza(unsigned int * const arr, const std::size_t size, const std::size_t i) {
    if (i == size) {
        return 0;
    }

    return *(arr + i) + zbirElemenataNiza(arr, size, i + 1);
}