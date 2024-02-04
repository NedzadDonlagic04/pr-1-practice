#include<iostream>
#include<cmath>
#include<limits>
#include<iomanip>

void clearBuffer();
void enterNum(double &, const char * const);

void print10ExponentsForNum(const double);

int main() {
    double num {};

    enterNum(num, "Unesite broj: ");
    print10ExponentsForNum(num);

    return 0;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterNum(double &num, const char * const outputText) {
    do {
        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
        }

        std::cout<<outputText;
        std::cin>>num;
    } while(std::cin.fail());
}

void print10ExponentsForNum(const double num) {
    for (int i = 1; i <= 10; i++) {
        std::cout<<"^"<<std::setw(2)<<std::right<<i<<": ";

        if (i <= 5) {
            std::cout<<std::right;
        } else {
            std::cout<<std::left;
        }

        std::cout<<std::setw(20)<<std::fixed<<std::setprecision(5);
        std::cout<<std::pow(num, i)<<std::endl;
    }
}