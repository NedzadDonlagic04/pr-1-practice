#include<iostream>
#include<cmath>
#include<iomanip>

/* 
    Napisati program koji korisniku omogućava unos realnog broja x, 
    cijelog broja m i odabir funkcije za proračun datog izraza.
    Korisnik bira funkciju unosom sljedećih karaktera 's' (sin),
    'c' (cos), 'q' (sqrt), 'p' (pow). U slučaju da korisnik unese 
    karakter koji ne odgovara niti jednoj od predefinisanih vrijednosti 
    ispisati odgovarajuću poruku i ponoviti odabir. Funkciji pow 
    postavite broj 2 za drugi parametar.

    Za odabranu funkciju izraz je:

    1 / [ sin((x / 1) + x) ] + 2 / [ sin((x / 2) + x) ] + ... + m / [ sin(x / m) + x ]
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

    std::cout<<"Suma formule za unesenu funkciju i brojeve je ";
    std::cout<<std::setprecision(3)<<pronadiSumuZaIzbor(x, m, izbor)<<std::endl;

    std::cin.get();
    return 0;
}

void unosX(float &unos) {
    std::cout<<"Unesi realan broj (x): ";
    std::cin>>unos;
}

void unosM(int &unos) {
    std::cout<<"Unesi prirodan broj (m): ";
    std::cin>>unos;
}

void unosIzbora(char &unos) {
    do {
        std::cout<<"Lista izbora: \n\t'c' = cos\n\t's' = sin\n\t'q' = sqrt\n\t'p' = pow\n";
        std::cout<<"Unesite jedan od izbora iznad: ";
        std::cin>>unos;

        if (unos != 'c' && unos != 's' && unos != 'q' && unos != 'p')
            std::cout<<"Nevazeci unos opcije!\n";
    } while(unos != 'c' && unos != 's' && unos != 'q' && unos != 'p');
}

float pronadiSumuZaIzbor(const float x, const int m, const char izbor) {
    float suma {0.0f};

    for (int i = 1; i <= m; i++) {
        switch(izbor) {
            case 'c':
                suma += i / (std::cos(x / i) + x);
                break;
            case 's':
                suma += i / (std::sin(x / i) + x);
                break;
            case 'q':
                suma += i / (std::sqrt(x / i) + x);
                break;
            default:
                suma += i / (std::pow(x / i, 2) + x);
        }
    }

    return suma;
}