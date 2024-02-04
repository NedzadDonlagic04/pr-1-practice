#include<iostream>
#include<cmath>
#include<iomanip>

/* 
    Napisatprogram kojkorisniku omogućava unos 
    realnog broja x, cijelog broja m odabir funkcije 
    za proračun datog izraza. Korisnik bira funkciju unosom 
    sljedećih karaktera 's' (sin), 'c' (cos), 'q' (sqrt), 'p' (pow).
    U slučaju da korisnik unese karakter kojne odgovara nitjednoj 
    od predefinisanih vrijednostispisatodgovarajuću poruku 
    ponovitodabir.Za funkciju pow() drugparametar treba bit3.

    Za odabranu funkciju izraz je:
    sin(x) + 1 + sin(x) + 2 + sin(x) + 3 + ... + sin(x) + m
*/

void unosX(float &);
void unosM(int &);
void unosIzbora(char &);
float pronadiSumuZaIzbor(const float, const int, const char);

int main() {
    float x {};
    int m {};
    char izbor {};

    unosX(x);
    unosM(m);
    unosIzbora(izbor);

    std::cout<<"Suma formule za unesenu funkciju brojeve je ";
    std::cout<<std::setprecision(3)<<pronadiSumuZaIzbor(x, m, izbor)<<std::endl;

    std::cin.get();
    return 0;
}

void unosX(float &unos) {
    std::cout<<"Unes realan broj (x): ";
    std::cin>>unos;
}

void unosM(int &unos) {
    std::cout<<"Unes prirodan broj (m): ";
    std::cin>>unos;
}

void unosIzbora(char &unos) {
    do {
        std::cout<<"Lista izbora: \n\t'c' = cos\n\t's' = sin\n\t'q' = sqrt\n\t'p' = pow\n";
        std::cout<<"Unesite jedan od izbora iznad: ";
        std::cin>>unos;

        if (unos != 'c' && unos != 's' && unos != 'q' && unos != 'p')
            std::cout<<"Nevazecunos opcije!\n";
    } while(unos != 'c' && unos != 's' && unos != 'q' && unos != 'p');
}

float pronadiSumuZaIzbor(const float x, const int m, const char izbor) {
    float suma {0.0f};

    for (int i = 1; i <= m; i++) {
        switch(izbor) {
            case 'c':
                suma += std::cos(x) + i;
                break;
            case 's':
                suma += std::sin(x) + i;
                break;
            case 'q':
                suma += std::sqrt(x) + i;
                break;
            default:
                suma += std::pow(x, 3) + i;
        }
    }

    return suma;
}