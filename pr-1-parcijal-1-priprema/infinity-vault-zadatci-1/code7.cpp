#include <iostream>

/* 
    Omogučiti unos dva broja X i Y iz intervala od 10 do 5000. 
    Kreirati program koji će pronaći i ispisati sve brojeve od 
    X do Y (uključujući granične vrijednosti) za koje važi da je 
    obrnuti broj djeljiv sa njegovom sumom cifara. Za olakšanje 
    rješenja zadataka napraviri funkcije za obrtanje poretka cifara
    i za sumu cifara. Npr. Za broj 144 vrijedi da mu je suma cifara 
    9 i da je broj koji se dobije nakon što se njegove cifre obrnu 441, 
    djeljiv sa 9.

    Definišite vrijednosti intervala [X, Y]: 11 150 
    Brojevi koji ispunjuju dati uslov: 18 20 21 24 27
*/

void unosXY(int &, int &);
int getObrnutBroj(int);
int getSumaCifara(int);
void printBrojeveOdXDoYUzUslovZadatka(int, const int);

int main() {
    int X {}, Y {};
    
    unosXY(X, Y);
    printBrojeveOdXDoYUzUslovZadatka(X, Y);

    std::cin.get();
    return 0;
}

void unosXY(int &X, int &Y) {
    do {
        std::cout<<"Definišite vrijednosti intervala [X, Y]: ";
        std::cin>>X>>Y;     

        if (X < 10 || X > 5001 || Y < 10 || Y > 5001)
            std::cout<<"Brojevi uneseni trebaju biti u intervalu od 10 do 5000\n";
    } while(X < 10 || X > 5001 || Y < 10 || Y > 5001);
}


int getObrnutBroj(int broj) {
    int obrnutBroj {0};

    while (broj) {
        obrnutBroj = obrnutBroj * 10 + broj % 10;
        broj /= 10;
    }

    return obrnutBroj;
}

int getSumaCifara(int broj) {
    int suma {0};

    while (broj) {
        suma += broj % 10;
        broj /= 10;
    }

    return suma;
}

void printBrojeveOdXDoYUzUslovZadatka(int X, const int Y) {
    std::cout<<"Brojevi koji ispunjuju dati uslov: ";

    for (; X <= Y; X++)
        if (getObrnutBroj(X) % getSumaCifara(X) == 0)
            std::cout<<X<<' ';

    std::cout<<std::endl;
}