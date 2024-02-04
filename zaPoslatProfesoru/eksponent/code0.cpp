#include<iostream>
#include<cmath>

int brojac {0};

void doTheFormula(int &, int &, const int, const int);
void outputNearestPotential(const int);
void unos(int &);

int main() {
    int n {};

    unos(n);
    outputNearestPotential(n);

    std::cout<<"Broj iteracija "<<brojac<<'\n';

    return 0;
}

void doTheFormula(int &base, int &result, const int num, const int exponent) {
    base = std::ceil(std::pow(num, 1.0 / exponent));
    result = std::pow(base, exponent);
}

void outputNearestPotential(const int num) {
    if (num == 1) {
        std::cout<<"Nije moguce predstaviti broj 1 zbog uslova da eksponent treba biti >= 2\n";
        return;
    }

    int previousResult {}, previousExponent {}, previousBase {};
    int result {}, exponent {2}, base {2}; 

    doTheFormula(base, result, num, exponent);
    brojac++;

    do {
        brojac++;

        previousExponent = exponent;
        previousResult = result;
        previousBase = base;

        exponent++;

        doTheFormula(base, result, num, exponent);
    } while(previousResult >= result);

    std::cout<<previousBase<<'^'<<previousExponent<<'='<<previousResult<<std::endl;
}

void unos(int &broj) {
    do {
        std::cout<<"Unesi neki prirodni broj: ";
        std::cin>>broj;

        if (broj < 1)
            std::cout<<"Uneseni broj treba biti prirodni\n";
    } while(broj < 1);
}