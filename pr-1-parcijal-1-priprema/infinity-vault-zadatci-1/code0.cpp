#include <iostream>
#include <cmath>

/* 
    Poštujući sve faze programiranja, napisati program koji korisniku omogućava unos 
    realnog broja x i odabir funkcije za proračun datog izraza. KOrisnik bira funkciju 
    unosom jednog od sljedećih karaktera: 's'(sin), 'c'(cos). U slučaju da korisnik 
    unese karakter koji ne odgovara niti jednog od predefinisanih vrijednosti ispisati 
    odgovarajuću poruku i ponoviti odabir.

    Za odabranu funkciju sin izraz je:

    f(x) = 1 + 1 / [ sin(x) + x ] + 2 / [ sin(x / 2) + x ] +
    (...) + x / [ sin(x / x) + x ] 

*/

void unosIzbora(char &);
void unosRealnogBroja(float &);
float proracun(const char, const float);

int main() {
    char opcija {};
    float x {};

    unosRealnogBroja(x);
    unosIzbora(opcija);

    std::cout<<"Proracun za izabrani izraz je "<<proracun(opcija, x)<<std::endl;

    std::cin.get();
    return 0;
}

void unosIzbora(char &opcija) {
    do {
        std::cout<<"Unesi opciju ('s' = sin, 'c' = cos): ";
        std::cin>>opcija;
    } while(opcija != 'c' && opcija != 's');
}

void unosRealnogBroja(float &unos) {
    std::cout<<"Unesi realan broj (x): ";
    std::cin>>unos;
}

float proracun(const char opcija, const float x) {
    float suma {1.0f};

    for (int i = 1; i <= x; i++) {
        if (opcija == 'c')
            suma += i / (std::cos(x / i) + x);  
        else
            suma += i / (std::sin(x / i) + x);  
    }

    return suma;
}