#include<iostream>
#include<cmath>
#include<limits>

constexpr std::size_t ARR_SIZE { 5 };
constexpr std::size_t BUFFER_SIZE { 256 };

void clearBuffer();
// Be warned this one uses ANSI escape codes
void printErrorMsg(const char * const);
void enterNum(int &, const char * const);

[[nodiscard]] unsigned int countDigits(const int);

void enterArray(int (&)[ARR_SIZE]);
void printArray(int *, const std::size_t, const char * const);
std::size_t removeNumsDivisibleBy6(int (&)[ARR_SIZE]);

int main() {
    int arr[ARR_SIZE] {};

    enterArray(arr);
    printArray(arr, ARR_SIZE, "Niz: ");

    const std::size_t newSize { removeNumsDivisibleBy6(arr) };

    printArray(arr, newSize, "Niz nakon izbacivanja brojeva djeljivih sa 6: ");

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

void enterNum(int &num, const char * const outputText) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>num;

        if (std::cin.fail()) {
            printErrorMsg("Nevalidan unos\n");
            clearBuffer();
            repeatLoop = true;
        } else if (num % 2 != 0 || countDigits(num) % 2 == 0) {
            printErrorMsg("Unos treba biti paran broj sa neparnim brojem cifara\n");
            clearBuffer();
            repeatLoop = true;
        }
    } while(repeatLoop);
}

unsigned int countDigits(const int num) {
    if (!num) {
        return 1;
    }

    return std::log10(std::abs(num)) + 1;
}

void enterArray(int (&arr)[ARR_SIZE]) {
    char outputText[BUFFER_SIZE] {};

    for (std::size_t i = 0; i < ARR_SIZE; i++) {
        std::sprintf(outputText, "Unesi broj na index poziciju %lu: ", i);
        enterNum(arr[i], outputText);
    }

}

void printArray(int *arr, const std::size_t size, const char * const outputText) {
    std::cout<<outputText;
    for (std::size_t i = 0; i < size; i++) {
        std::cout<<arr[i]<<' ';
    }
    std::cout<<std::endl;
}

std::size_t removeNumsDivisibleBy6(int (&arr)[ARR_SIZE]) {
    std::size_t newSize { 0 };

    for (std::size_t i = 0; i < ARR_SIZE; i++) {
        if (arr[i] % 6 != 0) {
            arr[newSize] = arr[i];
            newSize++;
        } 
    }

    return newSize;
}