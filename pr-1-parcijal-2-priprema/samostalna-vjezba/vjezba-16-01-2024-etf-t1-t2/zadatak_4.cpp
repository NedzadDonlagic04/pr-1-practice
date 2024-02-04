#include<iostream>
#include<limits>
#include<optional>

void clearBuffer();
void enterNum(int &, const char * const, const std::optional<int>, const std::optional<int>);

int main() {
    int num {};

    enterNum(num, "Unesite prirodan broj u intervalu [0, 9]: ", 0, 9);

    std::cout<<"*****\n";
    std::cout<<"*****\n";
    std::cout<<"* "<<num<<" *\n";
    std::cout<<"*****\n";
    std::cout<<"*****\n";

    return 0;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterNum(int &num, const char * const outputText, const std::optional<int> min, const std::optional<int> max) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>num;

        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
            repeatLoop = true;
        } else if (min && num < min.value()) {
            std::cout<<"Uneseni broj treba biti veci od "<<min.value()<<std::endl;
            clearBuffer();
            repeatLoop = true;
        } else if (max && num > max.value()) {
            std::cout<<"Uneseni broj treba biti manji od "<<max.value()<<std::endl;
            clearBuffer();
            repeatLoop = true;
        }
    } while(repeatLoop);
}