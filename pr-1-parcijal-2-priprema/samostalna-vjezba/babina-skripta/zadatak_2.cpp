#include<iostream>
#include<cmath>
#include<limits>

void clearBuffer();
void printOptions();
void printErrorMsg(const char * const);

void enterNum(int &, const char * const);
void enterNum(float &, const char * const);
[[nodiscard]] bool isValidOption(const char);
void enterOption(char &, const char * const);

[[nodiscard]] float doTheMath(const float, const int, const char);
[[nodiscard]] float getNextSum(const float, const int, const char);

int main() {
    float x {};
    int m {};
    char option {};

    enterNum(x, "Unesi realan broj (x): ");
    enterNum(m, "Unesi cijeli broj (m): ");
    enterOption(option, "Unesi opciju: ");

    std::cout<<"Za realni broj "<<x<<" i cijeli broj "<<m<<"\n";
    std::cout<<"Unesena je opcija '"<<option<<"' koja daje rezultat "<<doTheMath(x, m, option)<<std::endl;

    return 0;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printErrorMsg(const char * const errorMsg) {
    std::cout<<"\033[m";
    std::cout<<errorMsg;
    std::cout<<"\033[39m";
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

void enterNum(float &num, const char * const outputText) {
    do {
        if (std::cin.fail()) {
            printErrorMsg("Nevalidan unos\n");
            clearBuffer();
        }

        std::cout<<outputText;
        std::cin>>num;
    } while(std::cin.fail());
}

void printOptions() {
    std::cout<<"Moguce opcije:\n";
    std::cout<<"s - sin\n";
    std::cout<<"c - cos\n";
    std::cout<<"q - sqrt\n";
    std::cout<<"p - pow\n";
}

bool isValidOption(const char option) {
    return option == 's' || option == 'c' || option == 'q' || option == 'p';
}

void enterOption(char &option, const char * const outputText) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        printOptions();
        std::cout<<outputText;
        std::cin>>option;

        if (std::cin.fail()) {
            printErrorMsg("Nevalidan unos\n");
            clearBuffer();
            repeatLoop = true;
        } else if (!isValidOption(option)) {
            printErrorMsg("Opcija nije validna\n");
            clearBuffer();
            repeatLoop = true;
        }
    } while(repeatLoop);
}

float getNextSum(const float x, const int m, const char option) {
    switch (option) {
        case 's':
            return m / (std::sin(x / m) + x);
        case 'c':
            return m / (std::cos(x / m) + x);
        case 'q':
            return m / (std::sqrt(x / m) + x);
        default:
            return m / (std::pow(x / m, 2) + x);
    }
}

float doTheMath(const float x, const int m, const char option) {
    float sum { 1.0f };

    for (int i = 1; i <= m; i++) {
        sum += getNextSum(x, i, option);
    } 

    return sum;
}