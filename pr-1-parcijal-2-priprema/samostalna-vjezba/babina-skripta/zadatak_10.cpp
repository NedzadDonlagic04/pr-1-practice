#include<iostream>
#include<limits>
#include<optional>
#include<cmath>

constexpr std::size_t BUFFER_SIZE { 4096 };

void clearBuffer();
void printErrorMsg(const char * const); 
void enterNum(int &, const char * const, const std::optional<int> = std::nullopt, const std::optional<int> = std::nullopt);

[[nodiscard]] int getReversedNum(int);
[[nodiscard]] bool isPalindrome(int);
[[nodiscard]] int getNextPalindrome(int);

void printNumAsSumOfPalindromes(const int);
void printAllEvensAsSumOfPalindromes(int, const int);

int main() {
    int a {}, b {};

    enterNum(a, "Unesi pocetak intervala (a): ", 201);
    enterNum(b, "Unesi kraj intervala (b): ", a + 101);

    printAllEvensAsSumOfPalindromes(a, b);

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

int getReversedNum(int num) {
    const bool isNeg { num < 0 };
    num = std::abs(num);

    int reverseNum { 0 };

    while (num) {
        reverseNum = reverseNum * 10 + num % 10;
        num /= 10;
    }

    return reverseNum * ((isNeg)? -1 : 1);
}

bool isPalindrome(int num) {
    if (num < 0) {
        return false;
    }

    return num == getReversedNum(num);
}

int getNextPalindrome(int num) {
    do {
        num++;
    } while(!isPalindrome(num));

    return num;
}

void printNumAsSumOfPalindromes(const int num) {
    for (int i = 1; i <= num - i; i = getNextPalindrome(i)) {
        if (isPalindrome(num - i)) {
            std::cout<<num<<" = "<<i<<" + "<<num - i<<std::endl; 
            return;
        }
    }
}

void printAllEvensAsSumOfPalindromes(int a, const int b) {
    for (a = a + (a % 2); a <= b; a += 2) {
        printNumAsSumOfPalindromes(a);
    }
}