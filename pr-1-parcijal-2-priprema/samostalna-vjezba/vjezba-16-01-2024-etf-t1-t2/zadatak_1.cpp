#include<iostream>
#include<cmath>
#include<iomanip>
#include<limits>
#include<optional>

[[nodiscard]] double sqrtSqrt(const double);

void clearBuffer();
void enterNum(double &, const char * const);

int main() {
    double num {};

    enterNum(num, "Unesite broj: ");

    std::cout<<"4. korijen iz "<<num<<" je ";
    std::cout<<std::setprecision(12)<<std::fixed<<sqrtSqrt(num)<<std::endl;

    return 0;
}

double sqrtSqrt(const double num) {
    return std::sqrt(std::sqrt(num));
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterNum(double &num, const char * const outputText) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>num;

        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
            repeatLoop = true;
        } else if (num < 0) {
            std::cout<<"Unos treba biti pozitivan broj\n";
            clearBuffer();
            repeatLoop = true;
        }
    } while(repeatLoop);
}