#include<iostream>
#include<limits>

using ULL = unsigned long long;

void clearBuffer();
void printErrorMsg(const char * const);
void enterSize(std::size_t &, const char *);

void fillArr(unsigned int * const, std::size_t &, const std::size_t = 2);
void printArr(const unsigned int * const, const std::size_t, const std::size_t = 0);

[[nodiscard]] int getRandomNum();
[[nodiscard]] ULL getSumOfArrElements(const unsigned int * const, const std::size_t, const std::size_t = 0);

int main() {
    std::srand(time(NULL));

    std::size_t size {};

    enterSize(size, "Unesi duzinu niza: ");

    unsigned *arr = new unsigned int[size] {};

    fillArr(arr, size);
    printArr(arr, size);

    std::cout<<"Suma clanova niza je "<<getSumOfArrElements(arr, size)<<std::endl;

    delete[] arr;

    return 0;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Be warned this one uses ANSI escape codes
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
            printErrorMsg("Nevalidan unos\n");
            clearBuffer();
            repeatLoop = true;
        } else if (size < 2 || size > 1000) {
            printErrorMsg("Unos mora biti u intervalu [2, 1000]\n");
            clearBuffer();
            repeatLoop = true;
        }
    } while (repeatLoop);

    clearBuffer();
}

void fillArr(unsigned int * const arr, std::size_t &size, const std::size_t i) {
    if (i == 2) {
        *arr = getRandomNum();
        *(arr + 1) = getRandomNum();
    }
    if (size == i) {
        return; 
    }

    *(arr + i) = getRandomNum();

    if (*(arr + i) == *(arr + i - 1) && *(arr + i) == *(arr + i - 2)) {
        size = i + 1;
        return;
    }

    fillArr(arr, size, i + 1);
}

void printArr(const unsigned int * const arr, const std::size_t size, const std::size_t i) {
    if (i == 0) {
        std::cout<<"Niz: ";
    } else if (i == size) {
        std::cout<<std::endl;
        return;
    }

    std::cout<<*(arr + i)<<' ';
    printArr(arr, size, i + 1);
}

int getRandomNum() {
    return rand() % 100 + 1;
}

ULL getSumOfArrElements(const unsigned int * const arr, const std::size_t size, const std::size_t i) {
    if (i == size) {
        return 0ull;
    }

    return *(arr + i) + getSumOfArrElements(arr, size, i + 1);
}