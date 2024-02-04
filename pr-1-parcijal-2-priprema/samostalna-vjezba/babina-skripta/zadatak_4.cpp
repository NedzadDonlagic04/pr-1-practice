#include<iostream>
#include<limits>
#include<optional>
#include<cmath>

constexpr std::size_t BUFFER_SIZE { 4096 };

void clearBuffer();
void printErrorMsg(const char * const); 
void enterNum(int &, const char * const, const std::optional<int> = std::nullopt, const std::optional<int> = std::nullopt);

[[nodiscard]] unsigned int getSmallestDigitInNum(int);
[[nodiscard]] unsigned int getSmallestDigitInNum(int);
[[nodiscard]] unsigned int countDigits(const int);
[[nodiscard]] int replaceDigitsWithDigit(int, unsigned int);

int main() {
    int num {};

    enterNum(num, "Unesi pozitivan broj: ", 1);

    const int numAfterReplacement { replaceDigitsWithDigit(num, getSmallestDigitInNum(num)) };

    std::cout<<"Broj "<<num<<" nakon zamjenjivanja najmnanje cifre sa 3 je "<<numAfterReplacement<<'\n';
    std::cout<<"Razlika izmedu ova dva broja je "<<num - numAfterReplacement<<std::endl;

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

void enterNum(int &num, const char * const outputText, const std::optional<int> min, const std::optional<int> max) {
    bool repeatLoop {};
    char errorMsg[BUFFER_SIZE];

    do {
        repeatLoop = false; 

        std::cout<<outputText;
        std::cin>>num;

        if (std::cin.fail()) {
            printErrorMsg("Nevalidan unos\n");
            clearBuffer();
            repeatLoop = true;
        } else if (min && num < min.value()) {
            std::sprintf(errorMsg, "Unos ne moze biti manji od %d\n", min.value());
            printErrorMsg(errorMsg);
            clearBuffer();
            repeatLoop = true;
        } else if (max && num > max.value()) {
            std::sprintf(errorMsg, "Unos ne moze biti veci od %d\n", max.value());
            printErrorMsg(errorMsg);
            clearBuffer();
            repeatLoop = true;
        }
    } while(repeatLoop);
}

unsigned int getSmallestDigitInNum(int num) {
    num = std::abs(num);

    unsigned int smallestDigit = num % 10;
    unsigned int temp {};
    num /= 10;

    while (num) {
        temp = num % 10;

        if (temp < smallestDigit) {
            smallestDigit = temp;
        }
        if (smallestDigit == 1) {
            break;
        }

        num /= 10;
    }

    return smallestDigit;
}

unsigned int countDigits(const int num) {
    if (!num) {
        return 1;
    }

    return std::log10(std::abs(num)) + 1;
}

int replaceDigitsWithDigit(int num, unsigned int digit) {
    for (int i = 1; i < num; i *= 10) {
        unsigned int currentDigit = (num / i) % 10;

        if (currentDigit == digit) {
            currentDigit *= i;
            num -= currentDigit;
            num += 3 * i;
        }
    }    

    return num;
}