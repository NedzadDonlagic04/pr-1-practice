#include<iostream>
#include<cmath>

const int KAPREKAROVA_KONSTANTA { 6174 };

void unos(int &);
bool jelMakar1CifraRazlicita(int);
int sortirajBroj(int);
int getCifreBroja(int);
int obrniBroj(int);
void ispisiSveDoKaprekaroveKonstante(int);

int main() {
    int A {};

    unos(A);
    ispisiSveDoKaprekaroveKonstante(A);

    std::cin.get();
    return 0;
}

bool jelMakar1CifraRazlicita(int broj) {
    const int zadnjaCifra { broj % 10 };

    broj /= 10;

    while(broj) {
        if (zadnjaCifra != (broj % 10))
            return true;

        broj /= 10;
    }

    return false;
}

void unos(int &unos) {
    do {
        std::cout<<"Unesi cetverocifreni broj: ";
        std::cin>>unos;

        if (unos < 1000 || unos > 9999)
            std::cout<<"Unos nije cetverocifreni broj\n";
        else if (!jelMakar1CifraRazlicita(unos))
            std::cout<<"Unos mora biti broj sa makar 2 razlicite cifre u sebi\n";
    } while(unos < 1000 || unos > 9999 || !jelMakar1CifraRazlicita(unos));
}

int getCifreBroja(int broj) {
    int brojac { 0 };

    while(broj) {   // broj > 0 // broj != 0
        broj /= 10;
        brojac++;
    }

    return brojac;
}

int sortirajBroj(int broj) {
    int brojac { 0 };
    int brojCifara { getCifreBroja(broj) };

    bool nastaviSortirati {};

    do {
        nastaviSortirati = false;

        for (int j = 0; j < brojCifara - 1; j++) {
            int a { (int)(broj / std::pow(10, j)) % 10 };
            int b { (int)(broj / std::pow(10, j + 1)) % 10 };

            if (a > b) {
                broj -= (std::pow(10, j) * a + std::pow(10, j + 1) * b);
                broj += (std::pow(10, j + 1) * a + std::pow(10, j) * b);
                nastaviSortirati = true;
            }
        }        

        brojCifara--;
    } while(nastaviSortirati);

    return broj;
}

int obrniBroj(int broj) {
    int obrnutBroj {0};

    while (broj) {
        obrnutBroj = obrnutBroj * 10 + broj % 10;
        broj /= 10;
    }

    return obrnutBroj;
}

void ispisiSveDoKaprekaroveKonstante(int broj) {
    int i = 0;

    do {
        int najveci { sortirajBroj(broj) };

        if (najveci < 1000) 
            najveci *= std::pow(10, 4 - getCifreBroja(najveci));

        int najmanji { obrniBroj(najveci) };

        broj = najveci - najmanji;

        std::cout<<"Iteracija "<<++i<<": "<<najveci<<" - "<<najmanji<<" = "<<broj<<'\n';
    } while(broj != KAPREKAROVA_KONSTANTA);
}