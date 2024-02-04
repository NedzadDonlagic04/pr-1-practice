#include<iostream>
#include<cmath>

bool isValid(int);
int sumOfDigits(int);
int decimalToBinary(int);
void unosN(int &);
void unosDecimalniBroj(int &, const int);
int getNajmanjiOdNUnosaN(const int);

int main() {
    int n {};

    unosN(n);

    const int najmanjiBroj { getNajmanjiOdNUnosaN(n) };
    const int najmanjiUBinarnom { decimalToBinary(najmanjiBroj) }; 

    std::cout<<"Najmanji broj u binarnom obliku: "<<najmanjiUBinarnom<<std::endl;
    std::cout<<"Suma znamenki binarnog broja: "<<sumOfDigits(najmanjiUBinarnom)<<std::endl;

    return 0;
}

bool isValid(int x) {
    while (x) {
        if (x % 10 > 1)
            return false;

        x /= 10;
    }

    return true;
}

int sumOfDigits(int x) {
    int sum {0};

    while (x) {
        sum += x % 10;
        x /= 10;
    }

    return sum;
}

int decimalToBinary(int x) {
    int binary {0}, counter {0};

    while (x) {
        binary += ((x % 2) * std::pow(10, counter));
        counter++;
        x /= 2;
    } 

    return binary;
}

void unosN(int &broj) {
    do {
        std::cout<<"Unesite broj decimalnih brojeva 'n': ";
        std::cin>>broj;

        if (broj < 1)
            std::cout<<"Unos treba biti pozitivan\n";
    } while(broj < 1);
}

void unosDecimalniBroj(int &broj, const int index) {
    std::cout<<"Unesite decimalni broj ["<<index<<"]: ";
    std::cin>>broj;
}

int getNajmanjiOdNUnosaN(const int n) {
    int temp {}, najmanjiBroj {};

    for (int i = 1; i <= n; i++) {
        unosDecimalniBroj(temp, i);

        if (i == 1)
            najmanjiBroj = temp;
        else
            najmanjiBroj = std::min(temp, najmanjiBroj);
    }

    return najmanjiBroj;
}