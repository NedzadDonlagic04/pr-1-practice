#include<iostream>
#include<limits>

void clearBuffer();
void enterOption(char &);
void enterArraySize(std::size_t &);

void fillArray(unsigned int * const, std::size_t &, const char, const std::size_t = 2, unsigned int = 0, unsigned int = 1);
void printArray(const unsigned int * const, const std::size_t, const std::size_t = 0);

int main() {
    char option {};
    std::size_t size {};

    enterOption(option);
    enterArraySize(size);

    unsigned int * const arr { new unsigned int[size] };

    fillArray(arr, size, option);
    printArray(arr, size);

    delete[] arr;

    return 0;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterOption(char &option) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<"Enter option: ";
        std::cin>>option; 

        if (std::cin.fail()) {
            std::cout<<"Invalid input\n";
            clearBuffer();
            repeatLoop = true;
        } else if (option != 'p' && option != 's') {
            std::cout<<"Unos treba biti jedna od validni opcija 'p' ili 's'\n";
            clearBuffer();
            repeatLoop = true;
        }
    } while(repeatLoop);
}

void enterArraySize(std::size_t &size) {
    bool repeatLoop {};

    do {
        std::cout<<"Enter size: ";
        std::cin>>size; 

        if (std::cin.fail()) {
            std::cout<<"Invalid input\n";
            clearBuffer();
            repeatLoop = true;
        } else if (size < 2 || size > 1000) {
            std::cout<<"Unos treba biti u intervalu [2, 1000]\n";
            clearBuffer();
            repeatLoop = true;
        }
    } while(repeatLoop);
}

void fillArray(unsigned int * const arr, std::size_t &size, const char option, const std::size_t i, unsigned int a, unsigned int b) {
    if (i == 2 && a + b < 2) {
        if (option == 'p') {
            a = 1;
            b = 1;
        }

        *arr = a;
        *(arr + 1) = b;
    } 
    if (i == size) {
        return;
    }

    b += a;
    a = b - a;

    if (b < a) {
        size = i;
        return;
    }

    // Debugging
    // std::cout<<i<<" = "<<b<<std::endl;
    *(arr + i) = b;

    if (option == 'p' && b % 2 == 0) {
        fillArray(arr, size, option, i, a, b);        
    } else {
        fillArray(arr, size, option, i + 1, a, b);        
    }
}

void printArray(const unsigned int * const arr, const std::size_t size, const std::size_t i) {
    if (i == 0) {
        std::cout<<"Niz: ";
    } else if (i == size) {
        std::cout<<std::endl;
        return;
    }

    std::cout<<*(arr + i)<<' ';

    printArray(arr, size, i + 1);
}