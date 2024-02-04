#include<iostream>
#include<limits>
#include<optional>
#include<cmath>

constexpr std::size_t BUFFER_SIZE { 4096 };

void clearBuffer();
void printErrorMsg(const char * const);
void enterNum(int &, const char * const, const std::optional<int> = std::nullopt, const std::optional<int> = std::nullopt);

[[nodiscard]] bool isPrime(const int);
[[nodiscard]] unsigned int sumOfDigits(int);

void printAllDigitsSumThatArePrimeInRangeXY(int, const int);

int main() {
    int X {}, Y {};

    enterNum(X, "Unesi pocetak intervala (X): ", 10, 4900);
    enterNum(Y, "Unesi kraj intervala (Y): ", X + 100, 5000);

    printAllDigitsSumThatArePrimeInRangeXY(X, Y);

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

bool isPrime(const int num) {
    if (num == 2 || num == 3) {
        return true;
    } else if (num <= 1 || num % 2 == 0 || num % 3 == 0) {
        return false;
    }

    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) {
            return false;
        }
    }

    return true;
}

unsigned int sumOfDigits(int num) {
    num = std::abs(num);
    unsigned int sum { 0u };

    while (num) {
        sum += (num % 10);
        num /= 10;
    }

    return sum;
}

void printAllDigitsSumThatArePrimeInRangeXY(int X, const int Y) {
    std::cout<<"Ispis brojeva cija suma cifara je prost broj: ";
    for (; X <= Y; X++) {
        if (isPrime(sumOfDigits(X))) {
            std::cout<<X<<' ';
        }
    }
    std::cout<<std::endl;
}