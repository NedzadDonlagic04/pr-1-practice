#include<iostream>
#include<limits>
#include<optional>

constexpr std::size_t BUFFER_SIZE { 256 };

void clearBuffer();
void printErrorMsg(const char * const);
void enterNum(int &, const char * const, const std::optional<int> = std::nullopt, const std::optional<int> = std::nullopt);

[[nodiscard]] bool isPrime(const int);
[[nodiscard]] int getRandomNum();
float printNRandomNums(const int);

int main() {
    std::srand(time(NULL));

    int n {};

    enterNum(n, "Unesi broj (n): ", 10, 1000);
    const float percentOfPrimes { printNRandomNums(n) };

    std::cout<<"Out of "<<n<<" random nums "<<percentOfPrimes<<"%";
    std::cout<<" are primes\n";

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

int getRandomNum() {
    return std::rand() % 1000 + 1;
}

float printNRandomNums(const int n) {
    int randomNum {}, randomNumCounter {0};

    for (int i = 0; i < n; i++) {
        randomNum = getRandomNum();

        if (isPrime(randomNum)) {
            std::cout<<"\033[31m";
            randomNumCounter++;
        }

        std::cout<<randomNum;

        if (i + 1 != n) {
            std::cout<<", ";
        }
        
        std::cout<<"\033[39m";
    }
    std::cout<<std::endl;

    return randomNumCounter * 100.0f / n;
}