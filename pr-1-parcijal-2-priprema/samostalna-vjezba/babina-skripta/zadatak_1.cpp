#include<iostream>
#include<limits>

using ULL = unsigned long long;

void clearBuffer();
void enterNum(int &, const char * const);
[[nodiscard]] ULL enterTaskNum();

// Be warned this one uses ANSI escape codes
void printErrorMsg(const char * const);

[[nodiscard]] unsigned int getSumOfNumDivisors(const int);
[[nodiscard]] bool isPerfectNum(const int);

int main() {
    ULL num { enterTaskNum() };

    std::cout<<"Broj sastavljen od zadanih znamenaka je "<<num<<".\n";

    if (isPerfectNum(num)) {
        std::cout<<"Broj je savrsen.\n";
    }

    return 0;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterNum(int &num, const char * const outputText) {
    do {
        if (std::cin.fail()) {
            printErrorMsg("Nevalidan unos\n");
            clearBuffer();
        }

        std::cout<<outputText;
        std::cin>>num;
    } while(std::cin.fail());
}

ULL enterTaskNum() {
    ULL totalNum { 0 };
    int numToAppend {};

    do {
        enterNum(numToAppend, "Upisi znamenku: ");

        if (numToAppend >= 0 && numToAppend <= 9) {
            totalNum = totalNum * 10 + numToAppend;
        }

    } while(numToAppend >= 0 && numToAppend <= 9);

    return totalNum;
}

// Be warned this one uses ANSI escape codes
void printErrorMsg(const char * const errorMsg) {
    std::cout<<"\033[31m";
    std::cout<<errorMsg;
    std::cout<<"\033[39m";
}

unsigned int getSumOfNumDivisors(const int num) {
    unsigned int sum { 1 };

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            sum += i;

            if (i != (num / i)) {
                sum += (num / i);
            }
        }
    }

    // Debuggin
    // std::cout<<sum<<std::endl;

    return sum;
}

bool isPerfectNum(const int num) {
    if (num <= 1) {
        return false;
    }

    return num == getSumOfNumDivisors(num);
}