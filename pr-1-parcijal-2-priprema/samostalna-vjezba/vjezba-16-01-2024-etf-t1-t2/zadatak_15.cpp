#include<iostream>
#include<limits>

[[nodiscard]] bool isIntervalA(const int); 
[[nodiscard]] bool isIntervalB(const int);
[[nodiscard]] bool isIntervalC(const int);

void clearBuffer();
void enterNum(int &, const char * const);

int main() {
    int num {};

    enterNum(num, "Unesi cijeli broj: ");

    if (isIntervalA(num) || isIntervalB(num) || isIntervalC(num)) {
        std::cout<<"Nalazi\n";
    } else {
        std::cout<<"Ne nalazi\n";
    }

    return 0;
}

bool isIntervalA(const int num) {
    return (num >= -3 && num < 11) || (num > 5 && num < 15) 
            || (num > 17 && num <= 31) || (num > 19 && num < 33);
}

bool isIntervalB(const int num) {
    return (num > -1 && num <= 1) || (num >= 2 && num <= 12) 
            || (num >= 5 && num <= 56) || (num >= 9 && num < 10);
}

bool isIntervalC(const int num) {
    return (num > -11 && num < -6) || (num > 15 && num <= 16) 
            || (num >= 6 && num <= 9);
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterNum(int &num, const char * const outputText) {
    do {
        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
        } 

        std::cout<<outputText;
        std::cin>>num;
    } while(std::cin.fail());
}