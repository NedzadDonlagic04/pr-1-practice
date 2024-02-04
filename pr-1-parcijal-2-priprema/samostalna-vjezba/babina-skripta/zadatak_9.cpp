#include<iostream>
#include<limits>
#include<optional>
#include<cmath>

constexpr std::size_t BUFFER_SIZE { 4096 };

int counter { 0 };

void clearBuffer();
void printErrorMsg(const char * const); 
void enterNum(int &, const char * const, const std::optional<int> = std::nullopt, const std::optional<int> = std::nullopt);

[[nodiscard]] bool isPrime(int);

void printNumAsSumOfPrimes(const int);
void printAllEvensAsSumOfPrimes(int, const int);

int main() {
    int n1 {}, n2 {};

    enterNum(n1, "Unesi pocetak intervala (n1): ", 1);
    enterNum(n2, "Unesi kraj intervala (n2): ", n1 + 1);

    printAllEvensAsSumOfPrimes(n1, n2);

    std::cout<<"Funkcija isPrime se pozvala ovoliko puta: "<<counter<<std::endl;

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
    // Counter counts the amount of calls to isPrime
    // to check optimization and such
    counter++;

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

void printNumAsSumOfPrimes(const int num) {
    if (isPrime(num - 2)) {
        std::cout<<num<<" = 2 + "<<num - 2<<std::endl; 
    } else if (isPrime(num - 3)) {
        std::cout<<num<<" = 3 + "<<num - 3<<std::endl; 
    } else {
        for (int i = 5; i <= num - i; i += 6) {
            if (isPrime(num - i)) {
                std::cout<<num<<" = "<<i<<" + "<<num - i<<std::endl; 
                return;
            } else if (isPrime(num - (i + 2))) {
                std::cout<<num<<" = "<<i + 2<<" + "<<num - (i + 2)<<std::endl; 
                return;
            }
        }
    }
}

void printAllEvensAsSumOfPrimes(int a, const int b) {
    for (a = a + (a % 2); a <= b; a += 2) {
        printNumAsSumOfPrimes(a);
    }
}