#include<iostream>
#include<limits>

void clearBuffer();
void printErrorMsg(const char * const);
void enterSize(std::size_t &, const char *);
void enterNum(int &, const char * const);

void fillArray(unsigned int * const, std::size_t &, const std::size_t = 1);
void printArray(const unsigned int * const, const std::size_t, const std::size_t = 0);

std::ptrdiff_t findElInArray(const unsigned int * const, const unsigned int, std::ptrdiff_t, std::ptrdiff_t = 0);

int main() {
    std::size_t size {};

    enterSize(size, "Unesite duzinu niza: ");

    unsigned int *arr { new unsigned int[size] {} };

    fillArray(arr, size);
    printArray(arr, size);

    int numToFind {};
    enterNum(numToFind, "Unesite broj za pronaci: ");

    const std::ptrdiff_t numToFindIndex { findElInArray(arr, numToFind, size - 1) };

    if (numToFindIndex != -1) {
        std::cout<<"Broj postoji u nizu\n";
    } else {
        std::cout<<"Broj ne postoji u nizu\n";
    }

    delete[] arr;

    return 0;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printErrorMsg(const char * const errorMsg) {
    std::cout<<"\033[31m";
    std::cout<<errorMsg;
    std::cout<<"\033[39m";
}

void enterSize(std::size_t &size, const char *outputText) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>size;

        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
            repeatLoop = true;
        } else if (size < 2 || size > 1000) {
            std::cout<<"Unos mora biti u intervalu [2, 1000]\n";
            repeatLoop = true;
        }
    } while (repeatLoop);

    clearBuffer();
}

void enterNum(int &num, const char * const outputText) {
    do {
        if (std::cin.fail()) {
            printErrorMsg("Nevalidan unos\n");
            clearBuffer();
        }

        std::cout<<outputText;
        std::cin>>num;
    } while(std::cin.fail());
}

void fillArray(unsigned int * const arr, std::size_t &size, const std::size_t i) {
    if (i == size) {
        return;
    } else if (i == 1) {
        *arr = 2;
    }

    *(arr + i) = *(arr + i - 1) * 2;

    if (*(arr + i) < *(arr + i - 1)) {
        size = i;
        return;
    }

    fillArray(arr, size, i + 1);
}

void printArray(const unsigned int * const arr, const std::size_t size, const std::size_t i) {
    if (i == size) {
        std::cout<<std::endl; 
        return;
    } else if (i == 0) {
        std::cout<<"Niz: ";
    }

    std::cout<<*(arr + i)<<' '; 

    printArray(arr, size, i + 1);
}

std::ptrdiff_t findElInArray(const unsigned int * const arr, const unsigned int numToFind, std::ptrdiff_t end, std::ptrdiff_t start) {
    if (start > end) {
        return -1;
    }

    const std::ptrdiff_t middle { start + (end - start) / 2 };

    if (*(arr + middle) == numToFind) {
        return middle;
    } else if (*(arr + middle) < numToFind) {
        return findElInArray(arr, numToFind, end, middle + 1);
    }
    
    return findElInArray(arr, numToFind, middle - 1, start);
}

/* 
0 1 2 3 4 5 6 7 8 9

6 - 0 = 6 / 2 = 3
6 - 4 = 2 / 2 = 1

9 - 

*/