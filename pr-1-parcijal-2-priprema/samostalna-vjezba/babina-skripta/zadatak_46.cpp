#include<iostream>
#include<limits>
#include<optional>

constexpr std::size_t BUFFER_SIZE { 256 };

void clearBuffer();
void printErrorMsg(const char * const);
void enterNum(int &, const char * const, const std::optional<int> = std::nullopt, const std::optional<int> = std::nullopt);

[[nodiscard]] bool isPrime(const int);
[[nodiscard]] bool isNumAscending(int);

void printNumsUpToNThatArePrimeAndAscending(const int);

int main() {
    int n {};

    enterNum(n, "Unesi broj (n): ", 10, 1000);
    printNumsUpToNThatArePrimeAndAscending(n);

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

bool isNumAscending(int num) {
    num = std::abs(num);
    unsigned int currentDigit = num % 10;
    num /= 10;

    while (num) {
        if (currentDigit < (num % 10)) {
            return false;
        }

        currentDigit = num % 10;
        num /= 10;
    }

    return true;
}

void printNumsUpToNThatArePrimeAndAscending(const int num) {
    std::cout<<"Svi prosti brojevi koji su rastuci u intervalu ";
    std::cout<<"[0, "<<num<<"] su: ";
    for (int i = 0; i <= num; i++) {
        if (isPrime(i) && isNumAscending(i)) {
            std::cout<<i<<' ';
        }
    }
    std::cout<<std::endl;
}