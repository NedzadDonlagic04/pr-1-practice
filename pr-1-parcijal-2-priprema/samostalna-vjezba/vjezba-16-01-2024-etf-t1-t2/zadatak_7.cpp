#include<iostream>
#include<cmath>
#include<limits>

void clearBuffer();
void enterABC(double &, double &, double &, const char * const);
double calcKoeficijent(const double, const double, const double);

int main() {
    double a {}, b {}, c {};

    enterABC(a, b, c, "Unesite koeficijente a, b i c: ");
    
    try {
        const double koeficient { calcKoeficijent(a, b, c) };

        std::cout<<"Iznos za koeficijente "<<a<<", "<<b<<" i "<<c<<" je: ";
        std::cout<<koeficient<<std::endl;
    } catch(const char * const errorMsg) {
        std::cout<<errorMsg<<std::endl;
    }

    return 0;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterABC(double &a, double &b, double &c, const char * const outputText) {
    do {
        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
        }

        std::cout<<outputText;
        std::cin>>a>>b>>c;
    } while(std::cin.fail());
}

double calcKoeficijent(const double a, const double b, const double c) {
    const double toSqrt { std::pow(b, 2) - 4 * a * c };

    if (toSqrt < 0) {
        throw "Korijen negativnog broja nema realnih rjesenja!";
    }

    return std::sqrt(toSqrt);
}