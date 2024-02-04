#include<iostream>
#include<cmath>

void doSomething(const char, const int);
void doSomething(const int, const int);
void doSomething(const double, const int);

void handleGenericInput(const char *, int&);
void handleGenericInput(const char *, double&);
void handleGenericInput(const char *, char&);

void handleOptionInput(short &);

void printOptions();

void option1Handler();
void option2Handler();
void option3Handler();

int main() {
    short option {};

    do {
        handleOptionInput(option);
        std::cout<<"\n\n";

        if (option == 1) {
            option1Handler();
        } else if (option == 2) {
            option2Handler();
        } else if (option == 3) {
            option3Handler();
        }
    } while(option != 4);

    std::cout<<"Kraj programa\n";

    return 0;
}

void doSomething(const char sign, const int numOfRepeats) {
    for (int i = 0; i < numOfRepeats; i++) {
        std::cout<<sign;
    }
}

void doSomething(const int base, const int exponent) {
    std::cout<<std::pow(base, exponent);
}

void doSomething(const double multiplier, const int exponent) {
    std::cout<<multiplier * std::pow(10, exponent);
}

void handleGenericInput(const char *textToPrint, int &num) {
    std::cout<<textToPrint;
    std::cin>>num;
}

void handleGenericInput(const char *textToPrint, double &num) {
    std::cout<<textToPrint;
    std::cin>>num;
}

void handleGenericInput(const char *textToPrint, char &sign) {
    std::cout<<textToPrint;
    std::cin>>sign;
}

void handleOptionInput(short &option) {
    do {
        printOptions();
        std::cout<<"Unesi jednu od gore navedenih opcija: ";
        std::cin>>option;

        if (option < 1 || option > 4) {
            std::cout<<"Nevalidna opcija\n\n";
        }
    } while(option < 1 || option > 4);
}

void printOptions() {
    std::cout<<"Opcija 1: Ponavljanja karakter x broj y puta\n";
    std::cout<<"Opcija 2: Racunanje formule a^b\n";
    std::cout<<"Opcija 3: Racunanje formule n * 10^m\n";
    std::cout<<"Opcija 4: Kraj izvrsavanja programa\n";
}

void option1Handler() {
    char sign {};
    int numOfRepeats {};

    handleGenericInput("Unesi karakter za ponavljati: ", sign);
    handleGenericInput("Unesi broj ponavljanja: ", numOfRepeats);

    doSomething(sign, numOfRepeats);
    std::cout<<"\n\n";
}

void option2Handler() {
    int base {}, exponent {};

    handleGenericInput("Unesi bazu: ", base);
    handleGenericInput("Unesi eksponent: ", exponent);

    doSomething(base, exponent);
    std::cout<<"\n\n";
}

void option3Handler() {
    double multiplier {};
    int exponent {};

    handleGenericInput("Unesi mnozilac: ", multiplier);
    handleGenericInput("Unesi eksponent broja 10: ", exponent);

    doSomething(multiplier, exponent);
    std::cout<<"\n\n";
}