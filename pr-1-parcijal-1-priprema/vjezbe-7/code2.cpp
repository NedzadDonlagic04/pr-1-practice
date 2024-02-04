#include<iostream>
#include<cmath>

int countDigits(int);
bool isValid(int);
void unos(int &, const int);
bool ekvivalecija(const int, const int);
int operation(int, int);

int main() {
    int b1 {}, b2 {};

    do {
        unos(b1, 1);
        unos(b2, 2);
    } while(!isValid(b1) || !isValid(b2) || countDigits(b1) != countDigits(b2));

    std::cout<<"Rezultat je: "<<operation(b1, b2)<<std::endl;

    return 0;
}

int countDigits(int x) {
    int brojac {0};

    while (x) {
        brojac++;
        x /= 10;
    }

    return brojac;
}

bool isValid(int b) {
    while (b) {
        if (b % 10 > 1)
            return false;

        b /= 10;
    }

    return true;
}

bool ekvivalecija(const int b1, const int b2) {
    return (!b1 || b2) && (!b2 || b1);
}

int operation(int b1, int b2) {
    const int numCount { countDigits(b1) };
    int result {0};

    for (int i = 0; i < numCount; i++) {
        result += (ekvivalecija(b1 % 10, b2 % 10) * std::pow(10, i));

        b1 /= 10;
        b2 /= 10;
    }

    return result;
}

void unos(int &broj, const int brVar) {
    std::cout<<"Unesite 'b"<<brVar<<"':\n";
    std::cin>>broj;
}