#include<iostream>
#include<limits>
#include<cmath>
#include<iomanip>

constexpr std::size_t ARR_SIZE { 10 };

void clearBuffer();
bool enterNum(int &);
void enterArray(int (&)[ARR_SIZE], const char * const);
void printTaskFormattedArray(int (&)[ARR_SIZE]);

int main() {
    int arr[ARR_SIZE] {};

    enterArray(arr, "Unesite 10 prirodnih brojeva: ");
    printTaskFormattedArray(arr);

    return 0;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool enterNum(int &num) {
    std::cin>>num;

    if (std::cin.fail()) {
        std::cout<<"Nevalidan unos\n";
        clearBuffer();
        return false;
    }
    return true;    
}

void enterArray(int (&arr)[ARR_SIZE], const char * const outputText) {
    std::cout<<outputText;

    for (std::ptrdiff_t i = 0; i < std::size(arr); i++) {
        if (!enterNum(arr[i])) {
            i = -1;
            std::cout<<outputText;
        }
    }
}

void printTaskFormattedArray(int (&arr)[ARR_SIZE]) {
    for (const auto num : arr) {
        std::cout<<std::setw(15)<<std::left<<std::setfill(' ');

        if (num % 2 == 0) {
            std::cout<<std::right<<std::setfill('0');
        }

        std::cout<<num;
        std::cout<<std::endl;
    }
}