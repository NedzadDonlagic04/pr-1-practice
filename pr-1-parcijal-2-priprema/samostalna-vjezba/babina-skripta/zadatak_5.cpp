#include<iostream>
#include<limits>
#include<optional>
#include<cmath>

constexpr std::size_t BUFFER_SIZE { 4096 };

void clearBuffer();
void printErrorMsg(const char * const); 
void enterNum(int &, const char * const, const std::optional<int> = std::nullopt, const std::optional<int> = std::nullopt);

[[nodiscard]] unsigned int countDigits(const int);
[[nodiscard]] float getMiddleDigit(int);
void printMiddleDigitsInRangeAB(const int, const int);

int main() {
    int n {}, m {};

    enterNum(m, "Unesi broj (m): ", 100, 498);
    enterNum(n, "Unesi broj (m): ", m + 1, 499);

    printMiddleDigitsInRangeAB(m, n);

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

unsigned int countDigits(const int num) {
    if (!num) {
        return 1;
    }

    return std::log10(std::abs(num)) + 1;
}

float getMiddleDigit(int num) {
    const unsigned int digitCount { countDigits(num) };
    const bool isEven { digitCount % 2 == 0 };
    num = num / std::pow(10, digitCount / 2 - isEven);

    if (digitCount % 2 == 0) {
        return ((num % 10) + ((num / 10) % 10)) / 2.0f;
    }

    return num % 10;
}

void printMiddleDigitsInRangeAB(const int m, const int n) {
    float sum { 0.0f };
    float biggestMiddleDigit { 0 };

    std::cout<<"Srednje cifre u intervalu ["<<m<<", "<<n<<"]: ";

    for (int i = m; i <= n; i++) {
        float middleDigit { getMiddleDigit(i) };

        std::cout<<middleDigit<<' ';

        biggestMiddleDigit = std::max(biggestMiddleDigit, middleDigit);
        sum += middleDigit;
    }

    sum /= (n - m + 1);

    std::cout<<"Aritmeticka sredina svih srednjih cifara u intervalu [";
    std::cout<<m<<", "<<n<<"] je "<<sum<<std::endl;
    std::cout<<"Najveca srednja cifra u intervalu je "<<biggestMiddleDigit<<std::endl;
}