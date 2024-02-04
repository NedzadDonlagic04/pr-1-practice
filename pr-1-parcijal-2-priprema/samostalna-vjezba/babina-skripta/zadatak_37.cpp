#include<iostream>
#include<limits>
#include<optional>
#include<cmath>

void clearBuffer();
void printErrorMsg(const char * const);
void enterNums(int &, int &, const char * const);

[[nodiscard]] unsigned int countDigits(const int);
[[nodiscard]] float getMiddleDigit(int);

int main() {
    int m {}, n {};
    float lastMiddleDigit { -1.0f }, middleDigit {};

    do {
        enterNums(m, n, "unesi m i n: ");
        std::cout<<std::endl;

        middleDigit = getMiddleDigit(m * n);

        std::cout<<"srednja cifra/sredina proizvoda brojeva "<<m<<" i ";
        std::cout<<n<<" ("<<m<<"*"<<n<<"="<<m*n<<") je: ";

        if (lastMiddleDigit == -1.0f || middleDigit > lastMiddleDigit) {
            std::cout<<middleDigit<<"\n\n";
            lastMiddleDigit = middleDigit;
        } else {
            std::cout<<"ne ispisuje se\n\n";
        }
    } while(n != 0 && middleDigit != 9);

    if (n == 0) {
        std::cout<<"forsirani prekid...\n";
    } else {
        std::cout<<"Dosegnuta najveca srednja cifra "<<middleDigit<<std::endl;
    }

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

void enterNums(int &m, int &n, const char * const outputText) {
    bool repeatLoop {};

    do {
        repeatLoop = false; 

        std::cout<<outputText;
        std::cin>>m;
        std::cin.get();
        std::cin>>n;

        if (std::cin.fail()) {
            printErrorMsg("Nevalidan unos\n");
            clearBuffer();
            repeatLoop = true;
        } else if (m < 1 || m > 50) {
            printErrorMsg("m treba biti u intervalu [1, 50]\n");
            clearBuffer();
            repeatLoop = true;
        } else if (n < 0 || n > 500) {
            printErrorMsg("n treba biti u intervalu [1, 500]\n");
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