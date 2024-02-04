#include<iostream>
#include<limits>

void clearBuffer();
void enterNum(int &, const char * const);

void printBasicMathOperations(const int, const int);

int main() {
    int num {};

    enterNum(num, "Unesite cijeli broj: ");
    printBasicMathOperations((num / 10) % 10, num % 10);

    return 0;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterNum(int &num, const char * const outputText) {
    do {
        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
        }

        std::cout<<outputText;
        std::cin>>num;
    } while(std::cin.fail());
}

void printBasicMathOperations(const int a, const int b) {
    std::cout<<"Zbir zadnje dvije cifre ("<<a<<" i "<<b<<") je: ";
    std::cout<<a + b<<std::endl;

    std::cout<<"Razlika zadnje dvije cifre ("<<a<<" i "<<b<<") je: ";
    std::cout<<a - b<<std::endl;

    std::cout<<"Proizvod zadnje dvije cifre ("<<a<<" i "<<b<<") je: ";
    std::cout<<a * b<<std::endl;

    std::cout<<"Kolicnik zadnje dvije cifre ("<<a<<" i "<<b<<") je: ";
    if (b) {
        std::cout<<a / static_cast<float>(b)<<std::endl;
    } else {
        std::cout<<"Nemoguce!\n";
    }
}