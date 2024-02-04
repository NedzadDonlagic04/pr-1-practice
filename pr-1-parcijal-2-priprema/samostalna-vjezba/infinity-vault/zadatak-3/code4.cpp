/*
Napisati program koji će omogućiti korisniku da unese 
veličinu jednodimenzionalnog dinamičkog niza integer 
vrijednosti. Napisati rekurzivnu funkciju koja će taj niz 
popuniti random brojevima u opsegu od 1 do 100. Za generisanje 
random brojeva koristiti rand() % 100 + 1. Punjenje niza se 
prekida kada se popuni cijeli niz ili kada se tri puta uzastopno 
dobije isti random broj. U ovom zadatku je zabranjeno indeksirati 
elemente niza uglastim zagradama. Obavezno koristiti aritmetiku pokazivača.

(Obavezno sve riješiti jednom rekurzivnom funcijom.)
*/

#include<iostream>
#include<cstddef>
#include<limits>

void clearBuffer();
void enterArraySize(std::size_t &);
int getRandomNum();
void fillArray(int * const, std::size_t &, const std::size_t = 1, short = 0);
void printArray(int * const, const std::size_t, const std::size_t = 0);

int main() {
    std::size_t arrSize {};

    enterArraySize(arrSize);

    int *arr { new int[arrSize] };

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

int getRandomNum() {
    return rand() % 100 + 1;
}

void fillArray(int * const arr, std::size_t &size, const std::size_t i, short repeats) {
    if (i == 1) {
        *arr = getRandomNum();
    } else if (i == size) {
        return;
    } else if (repeats == 2) {
        size = i;
        return ;
    }

    *(arr + i) = getRandomNum();

    // If two adjacent elements are the same a repeat happened
    if (*(arr + i) == *(arr + i - 1)) {
        repeats++;
    } else {
        repeats = 0;
    }

    fillArray(arr, size, i + 1, repeats);
}

void printArray(int * const arr, const std::size_t size, const std::size_t i) {
    if (i == 0) {
        std::cout<<"Clanovi niza: ";
    } else if (i == size) {
        std::cout<<std::endl;
        return;
    }

    std::cout<<*(arr + i)<<' ';

    printArray(arr, size, i + 1);
}