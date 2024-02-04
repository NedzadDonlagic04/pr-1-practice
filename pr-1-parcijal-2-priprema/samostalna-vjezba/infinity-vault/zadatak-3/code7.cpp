/*
Napisati program koji učitava prirodan broj n.
Program treba ispisati najmanji prirodni broj m ,
veći ili jednak n , koji je potencija nekog prirodnog 
broja, tj. m=k^l, gdje su k i l≥2 prirodni brojevi. U 
ovom zadatku je zabranjeno koristiti pow funkciju za 
računanje potencije.Potenciju računati koristeći rekurzivnu 
funkciju kojoj se proslijeđuje k i l i u kojoj je dozvoljena 
samo operacija množenja.

Za olakšanje rješenja, možete odabrati prototip funkcija 
po želji.
*/

#include<iostream>
#include<limits>
#include<cmath>

void clearBuffer();
void enterNumber(int &);
double customPow(const double, const int);

void getSmallestPotency(const int);
void smallestPotencyOuterLoop(const int, int &, const int = 2);
int smallestPotencyInnerLoop(const int, int &, const int, const int = 2);

int main() {
    int n {};

    enterNumber(n); 
    getSmallestPotency(n);

    return 0;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterNumber(int &num) {
    bool repeatInput {};

    do {
        repeatInput = false;

        std::cout<<"Unesi prirodni broj: ";
        std::cin>>num;

        if (std::cin.fail()) {;
            std::cout<<"Nevalidan unos\n";
            clearBuffer();

            repeatInput = true;
        } else if (num < 1) {
            std::cout<<"Greska, unos treba biti prirodan broj\n";

            repeatInput = true;
        }
    } while(repeatInput);
}

double customPow(const double base, const int exponent) {
    if (exponent <= 0) {
        return 1;
    }

    double result { 1 };

    for (int i = 0; i < exponent; i++) {
        result *= base;
    }

    return result;
}

void getSmallestPotency(const int num) {
    if (num == 1) {
        std::cout<<"Nije moguce predstaviti broj 1 zbog uslova da eksponent treba biti >= 2\n";
        return;
    }

    int smallestPotency {};

    smallestPotencyOuterLoop(num, smallestPotency);

    std::cout<<"Najmanji prirodni broj veci ili jednak unesenom broju: "<<smallestPotency<<std::endl;
}

void smallestPotencyOuterLoop(const int broj, int &smallestPotency, const int k) {
    int temp { smallestPotencyInnerLoop(broj, smallestPotency, k) };
    smallestPotency = (k == 2)? temp : std::min(temp, smallestPotency);

    if (k * k > broj || smallestPotency == broj) {
        return;
    }

    smallestPotencyOuterLoop(broj, smallestPotency, k + 1);
}

int smallestPotencyInnerLoop(const int broj, int &smallestPotency, const int k, const int l) {
    int tempPotency = customPow(k, l);

    if (tempPotency >= broj) {
        return tempPotency;
    }

    return smallestPotencyInnerLoop(broj, smallestPotency, k, l + 1);
}