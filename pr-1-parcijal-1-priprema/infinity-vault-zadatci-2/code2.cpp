#include<iostream>
#include<cmath>

/* 
    Napisati program koji omogućava unos pozitivnog broja 
    n te pronalazi njegove parne cifre i formira novi broj 
    u kojem su parne cifre zamijenjene cifrom '5'.

    Dodatno program treba ispisati razliku unesenog i broja 
    koji se dobije nakon zamjene.
*/

void unos(int &);
int transformisiBroj(int);

int main() {
    int n{};

    unos(n);

    int transformisaniBroj { transformisiBroj(n) };

    std::cout<<"Broj "<<n<<" nakon transformacije "<<transformisaniBroj<<'\n';
    std::cout<<"Razlika izmedu ta 2 broja je "<<n - transformisaniBroj<<std::endl;

    return 0;
}

void unos(int &broj) {
    do {
        std::cout<<"Unesi pozitivan broj (n): ";
        std::cin>>broj;

        if (broj < 1)
            std::cout<<"Uneseni broj mora biti pozitivan\n";
    } while(broj < 1);
}

int transformisiBroj(int broj) {
    int noviBroj {0};
    short zadnjaCifra {};

    for (int i = 0; broj; i++) {
        zadnjaCifra = broj % 10;

        if (zadnjaCifra % 2 == 0)
            zadnjaCifra = 5;

        noviBroj += std::pow(10, i) * zadnjaCifra;

        broj /= 10;
    }

    return noviBroj;
}