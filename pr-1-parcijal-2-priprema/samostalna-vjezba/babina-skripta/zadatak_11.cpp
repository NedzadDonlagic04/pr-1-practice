#include<iostream>
#include<cmath>
#include<limits>
#include<iomanip>

void clearBuffer();
void printErrorMsg(const char * const);

void enterValid4DigitKaprekarNum(int &, const char * const);
[[nodiscard]] bool hasAtLeastOneUniqueDigit(int);

unsigned int printStepsToKaprekarsConstant(const int);
[[nodiscard]] unsigned int countDigits(const int);
[[nodiscard]] int sortDigitsDescending(int);
[[nodiscard]] int reverseNum(int);
[[nodiscard]] int add0PaddingOnRightOfNum(const int, const unsigned int);

int main() {
    int num {};

    enterValid4DigitKaprekarNum(num, "Unesi broj: ");
    const unsigned int kaprekarStepsCount { printStepsToKaprekarsConstant(num) };

    std::cout<<"Dobivena je Kaprekar konstanta u "<<kaprekarStepsCount;
    std::cout<<" iteracije\n";

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

void enterValid4DigitKaprekarNum(int &num, const char * const outputText) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>num;

        if (std::cin.fail()) {
            printErrorMsg("Nevalidan unos\n");
            clearBuffer();
            repeatLoop = true;
        } else if (num < 1000 || num > 9999) {
            printErrorMsg("Broj treba biti u intervalu [1000, 9999]\n");
            clearBuffer();
            repeatLoop = true;
        } else if (!hasAtLeastOneUniqueDigit(num)) {
            printErrorMsg("Uneseni broj ne smije imati 4 iste cifre\n");
            clearBuffer();
            repeatLoop = true;
        }
    } while(repeatLoop);
}

bool hasAtLeastOneUniqueDigit(int num) {
    num = std::abs(num);

    unsigned int lastDigit = num % 10;
    num /= 10;

    while (num) {
        if (lastDigit != (num % 10)) {
            return true;
        }

        lastDigit = num % 10;
        num /= 10;
    }

    return false;
}

unsigned int printStepsToKaprekarsConstant(const int num) {
    unsigned int counter { 0u };

    unsigned int result = num, previousResult { 0 };
    const unsigned int originalDigitCount { countDigits(result) };

    while(1) {
        counter++;

        const unsigned int biggerNum = sortDigitsDescending(result);
        const unsigned int smallerNum = reverseNum(biggerNum);
        result = biggerNum - smallerNum;        

        std::cout<<std::setw(4)<<biggerNum<<" - ";
        std::cout<<std::setw(4)<<smallerNum<<" = ";
        std::cout<<std::setw(4)<<result<<std::endl;

        if (previousResult && result == previousResult) {
            break;
        }
        previousResult = result;
        result = add0PaddingOnRightOfNum(result, originalDigitCount);
    }

    std::cout<<"Kaprekar konstanta za cetverocifreni broj iznosi: "<<result<<std::endl;

    return counter;
}

int sortDigitsDescending(int num) {
    const bool isNeg { num < 0 };
    num = std::abs(num);

    constexpr std::size_t ARR_SIZE { 10 };
    unsigned int digitsCount[ARR_SIZE] { 0 };

    while (num) {
        digitsCount[num % 10]++;
        num /= 10;
    }

    for (std::ptrdiff_t i = ARR_SIZE - 1; i >= 0; i--) {
        for (int ii = 0; ii < digitsCount[i]; ii++) {
            num = num * 10 + i;
        }
    }

    return num;
}

int reverseNum(int num) {
    int reverseNum { 0 };

    while (num) {
        reverseNum = reverseNum * 10 + (num % 10);
        num /= 10;
    }

    return reverseNum;
}

int add0PaddingOnRightOfNum(const int num, const unsigned int originalDigitCount) {
    const unsigned int currentDigitCount { countDigits(num) };

    if (originalDigitCount - currentDigitCount != 0) {
        return num * std::pow(10, originalDigitCount - currentDigitCount);
    }

    return num;
}

unsigned int countDigits(const int num) {
    if (!num) {
        return 1;
    }

    return std::log10(std::abs(num)) + 1;
}