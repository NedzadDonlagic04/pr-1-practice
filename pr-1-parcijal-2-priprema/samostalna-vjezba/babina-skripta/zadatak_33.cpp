#include<iostream>
#include<limits>
#include<optional>
#include<cmath>
#include<iomanip>

constexpr std::size_t BUFFER_SIZE { 256 };

void clearBuffer();
void printErrorMsg(const char * const);
void enterNum(int &, const char * const, const std::optional<int> = std::nullopt, const std::optional<int> = std::nullopt);

[[nodiscard]] bool isEqual(const double, const double, const double = 0.01);

[[nodiscard]] unsigned int countDigits(const int);
[[nodiscard]] float getMiddleDigit(int);

int main() {
    int num {};

    enterNum(num, "Unesi neki broj: ");

    const float middleDigit { getMiddleDigit(num) };
    float smallestMultiplier { std::ceil(num / middleDigit) };
    
    if (isEqual(num, middleDigit * smallestMultiplier)) {
        smallestMultiplier = smallestMultiplier + ((num < 0)? -1 : 1);
        //                                         ^ in case num is negative
        //                                          we have to subtract -1
    }

    const auto currentPrecision { std::cout.precision() + 2 };
    std::cout<<std::setprecision(currentPrecision);

    std::cout<<"Srednja cifra broja "<<num<<" je broj "<<middleDigit<<std::endl;
    std::cout<<"Najmanji cijeli broj s kojim se treba pomnoziti broj "<<middleDigit;
    std::cout<<" da se dobije broj veci od "<<num<<" je "<<smallestMultiplier<<std::endl;
    std::cout<<"Jer je "<<smallestMultiplier * middleDigit<<" > "<<num<<std::endl;

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

bool isEqual(const double f1, const double f2, const double epsilon) {
    return std::abs(f1 - f2) <= epsilon;
}

unsigned int countDigits(const int num) {
    if (!num) {
        return 1;
    }

    return std::log10(std::abs(num)) + 1;
}

float getMiddleDigit(int num) {
    num = std::abs(num);

    const unsigned int digitCount { countDigits(num) };
    const bool isEven { digitCount % 2 == 0 };
    num = num / std::pow(10, digitCount / 2 - isEven);

    if (digitCount % 2 == 0) {
        return ((num % 10) + ((num / 10) % 10)) / 2.0f;
    }

    return num % 10;
}