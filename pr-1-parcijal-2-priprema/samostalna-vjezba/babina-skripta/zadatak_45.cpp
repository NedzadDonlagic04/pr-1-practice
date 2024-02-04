#include<iostream>
#include<cmath>
#include<limits>
#include<optional>

constexpr std::size_t BUFFER_SIZE { 256 };

void clearBuffer();
void printErrorMsg(const char * const);
void enterNum(int &, const char * const, const std::optional<int> = std::nullopt, const std::optional<int> = std::nullopt);

[[nodiscard]] unsigned int getNearestPotential(const int);
void getNextBaseAndResult(int &, int &, const int, const int);

int main() {
    int num {};

    enterNum(num, "Unesi broj: ", 1);

    if (num == 1) {
        std::cout<<"Za broj 1 nije moguce izvrsiti ovu operaciju\n";
    } else {
        const unsigned int nearestPotential { getNearestPotential(num) };

        std::cout<<"Najbliza potencija je broj "<<nearestPotential<<std::endl;
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

unsigned int getNearestPotential(const int num) {
    if (num <= 1) {
        return 0u;
    }

    int previousResult {}, previousExponent {}, previousBase {};
    int result {}, exponent { 2 }, base { 2 }; 
    
    getNextBaseAndResult(base, result, num, exponent);

    do {
        previousExponent = exponent;
        previousResult = result;
        previousBase = base;

        exponent++;

        getNextBaseAndResult(base, result, num, exponent);
    } while(previousResult >= result);

    // Debugging
    // std::cout<<previousBase<<'^'<<previousExponent<<'='<<previousResult<<std::endl;

    return previousResult;
}

void getNextBaseAndResult(int &base, int &result, const int num, const int exponent) {
    base = std::ceil(std::pow(num, 1.0 / exponent));
    result = std::pow(base, exponent);
}