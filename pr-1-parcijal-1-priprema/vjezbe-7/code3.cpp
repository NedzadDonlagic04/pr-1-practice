#include<iostream>
#include<cmath>

bool isValid(int);
int binaryToDecimal(int);
void unosN(int &);
void unosBinarnogBroja(int &, const int);

int main() {
    int n {}, b {}, maxB { -1 };

    unosN(n);
    for (int i = 1; i <= n; i++) {
        unosBinarnogBroja(b, i);
        maxB = std::max(maxB, b);
    }

    std::cout<<"Max binarni broj je: "<<maxB<<'\n';
    std::cout<<"Njegova decimalna reprezentacija je: "<<binaryToDecimal(maxB)<<std::endl;

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

int binaryToDecimal(int x) {
    int decimal {0}, counter {0};

    while (x) {
        decimal += (x % 10) * std::pow(2, counter);
        counter++;
        x /= 10;
    }
    
    return decimal;
}

void unosN(int &broj) {
    do {
        std::cout<<"Unesite 'n':\n";
        std::cin>>broj;

        if (broj <= 1)
            std::cout<<"Unos treba biti broj strogo veci od 1\n";
    } while(broj <= 1);
}

void unosBinarnogBroja(int &broj, const int index) {
    do {
        std::cout<<"Unesite 'b' ["<<index<<"]:\n";
        std::cin>>broj;

        if (!isValid(broj))
            std::cout<<"Nepravilan unos, broj treba biti binarni\n";
    } while(!isValid(broj));
}