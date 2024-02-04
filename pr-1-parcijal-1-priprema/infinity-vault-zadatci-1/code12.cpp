#include<iostream>
#include<cmath>
#include<iomanip>

/* 
    Napisati program koji omogućava unos realnog broja x,
    cijelog broja m (m > 0) i odabir funkcije za proračun 
    datog izraza. Korisnik bira funkciju unosom jednog od 
    sljedećih karaktera: 's' (sabiranje), 'o' (oduzimanje),
    'm' (množenje), 'd' (dijeljenje). U slučaju da korisnik 
    unese karakter koji ne odgovara niti jednoj od predefinisanih 
    vrijednosti ispisati odgovarajuću poruku i ponoviti odabir.

    Za odabir funkcije s izraz je: f(x, m) = (x - 1) * 1 + (x - 2) * 2 + ... + (x - m) * m

    Za odabir funkcije o izraz je: f(x, m) = (x - 1) * 1 - (x - 2) * 2 - ... - (x - m) * m itd.

    Broj faktora u izrazu odgovara unesenom broju m. U rješenju obavezno iskoristiti switch iskaz.
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
    do {
        std::cout<<"Unesi cijeli broj (m): ";
        std::cin>>unos;

        if (unos <= 0)
            std::cout<<"Cijeli broj mora biti strogo veci od 0\n";
    } while (unos <= 0);
}

void unosIzbora(char &unos) {
    do {
        std::cout<<"Lista izbora: \n\t's' = sabiranje\n\t'o' = oduzimanje\n\t'm' = mnozenje\n\t'd' = dijeljenje\n";
        std::cout<<"Unesite jedan od izbora iznad: ";
        std::cin>>unos;

        if (unos != 's' && unos != 'o' && unos != 'm' && unos != 'd')
            std::cout<<"Nevazeci unos opcije!\n";
    } while(unos != 's' && unos != 'o' && unos != 'm' && unos != 'd');
}

float pronadiSumuZaIzbor(const float x, const int m, const char izbor) {
    float suma { (izbor == 's' || izbor == 'o')? 0.0f : 1.0f };

    for (int i = 1; i <= m; i++) {
        switch(izbor) {
            case 's':
                suma += (x - i) * i;
                break;
            case 'o':
                suma -= (x - i) * i;
                break;
            case 'm':
                suma *= (x - i) * i;
                break;
            default:
                suma /= (x - i) * i;
        }
    }

    return suma;
}