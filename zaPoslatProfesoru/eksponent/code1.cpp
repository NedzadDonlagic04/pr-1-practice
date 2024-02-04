#include<iostream>
#include<cmath>

int brojac {0};

void najmanjaPotencija(const int);
void unos(int &);

int main() {
    int n {};

    unos(n);
    najmanjaPotencija(n);

    std::cout<<"Brojac: "<<brojac<<std::endl;

    return 0;
}

void unos(int &broj) {
    do {
        std::cout<<"Unesi neki prirodni broj: ";
        std::cin>>broj;

        if (broj < 1)
            std::cout<<"Uneseni broj treba biti prirodni\n";
    } while(broj < 1);
}

void najmanjaPotencija(const int broj) {
    if (broj == 1) {
        std::cout<<"Nije moguce predstaviti broj 1 zbog uslova da eksponent treba biti >= 2\n";
        return;
    }

    int result {}, baza {}, eksponent {};

    for (int k = 2; k < broj; k++) {
        for (int l = 2; std::pow(k, l - 1) < broj; l++) {
            baza = k; 
            eksponent = l;
            brojac++;
        }
        if (k == 2) result = std::pow(baza, eksponent);
        else result = std::min(result, (int)std::pow(baza, eksponent));
    }

    std::cout<<result<<std::endl;
}