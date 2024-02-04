#include<iostream>
#include<limits>
#include<optional>
#include<cmath>

constexpr std::size_t BUFFER_SIZE { 4096 };

void clearBuffer();
void printErrorMsg(const char * const); 
void enterNum(int &, const char * const, const std::optional<int> = std::nullopt, const std::optional<int> = std::nullopt);
void printPrimeAndPalindromNumsInRange(const int, const int);

[[nodiscard]] bool isPrime(const int);
[[nodiscard]] bool isPalindrome(int);
[[nodiscard]] unsigned int countDigits(const int);

int main() {
    int a {}, b {};

    enterNum(a, "Unesi pocetak intervala (a): ", 10, 100);
    enterNum(b, "Unesi kraj intervala (b): ", 1000, 2000);
    printPrimeAndPalindromNumsInRange(a, b);

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

void printPrimeAndPalindromNumsInRange(int a, const int b) {
    std::cout<<"Brojevi koji su prosti i palindromi u intervalu ";
    std::cout<<"["<<a<<", "<<b<<"] su: ";

    for (; a <= b; a++) {
        if (isPrime(a) && isPalindrome(a)) {
            std::cout<<a<<' ';
        }
    }

    std::cout<<std::endl;
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

bool isPalindrome(int num) {
    const unsigned int digitCount { countDigits(num) };
    int reverseNum { 0 };

    for (unsigned int i = 0; i < digitCount / 2; i++) {
        reverseNum = reverseNum * 10 + num % 10;
        num /= 10;
    }

    if (digitCount % 2 != 0) {
        num /= 10;
    }

    return num == reverseNum;
}

unsigned int countDigits(const int num) {
    if (!num) {
        return 1;
    }

    return std::log10(std::abs(num)) + 1;
}