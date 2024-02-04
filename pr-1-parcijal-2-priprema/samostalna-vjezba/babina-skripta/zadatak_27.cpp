#include<iostream>
#include<limits>
#include<optional>

constexpr std::size_t BUFFER_SIZE { 256 };

void clearBuffer();
void printErrorMsg(const char * const);
void enterNum(int &, const char * const, const std::optional<int> = std::nullopt, const std::optional<int> = std::nullopt);

[[nodiscard]] int getReversedNum(int);
[[nodiscard]] int getDigitSum(int);

void printAllNumsInRangeWhoseReverseIsDivisibleByDigitSum(int, const int);

int main() {
    int X {}, Y {};

    enterNum(X, "Unesi pocetak intervala (X): ", 10, 5000);
    enterNum(Y, "Unesi kraj intervala (Y): ", 10, 5000);

    printAllNumsInRangeWhoseReverseIsDivisibleByDigitSum(X, Y);

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

void printAllNumsInRangeWhoseReverseIsDivisibleByDigitSum(int X, const int Y) {
    int reverseX {};

    std::cout<<"U intervalu ["<<X<<", "<<Y<<"] brojevi koji kada se obrne su ";
    std::cout<<"djeljivi sa sumom svoji cifara su: ";
    for (; X <= Y; X++) {
        reverseX = getReversedNum(X);

        if (reverseX % getDigitSum(X) == 0) {
            std::cout<<X<<' ';
        } 
    }
    std::cout<<std::endl;
}

int getReversedNum(int num) {
    const bool isNeg { num < 0 };
    num = std::abs(num);

    int reverseNum { 0u };

    while (num) {
        reverseNum = reverseNum * 10 + num % 10;
        num /= 10;
    }

    return reverseNum * ((isNeg)? -1 : 1);
}

int getDigitSum(int num) {
    num = std::abs(num);

    int sum { 0 };

    while (num) {
        sum += (num % 10);
        num /= 10;
    }

    return sum;
}