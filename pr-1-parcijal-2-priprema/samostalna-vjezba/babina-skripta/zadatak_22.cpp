#include<iostream>
#include<limits>

void clearBuffer();
void printErrorMsg(const char * const);
void enterSize(std::size_t &, const char *);

void fillArray(unsigned int * const, std::size_t &, const std::size_t = 1);
void printArray(const unsigned int * const, const std::size_t, const std::size_t = 0);

int main() {
    std::size_t size {};

    enterSize(size, "Unesite duzinu niza: ");

    unsigned int *arr { new unsigned int[size] {} };

    fillArray(arr, size);
    printArray(arr, size);

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