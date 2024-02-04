#include <iostream>
#include <cmath>
#include <iomanip>

/* 
    Napisati program koji korisniku omogućava unos cijelog broja N,
    te izračunava geometrijsku sredinu svih neparnih 
    brojeva u intervalu [1, N] koji nisu djeljivi sa brojem 5. 
    Rezultat trebi biti zaokružen na dvije decimale.

    Geometrijska sredina n brojeva se računa po formuli:

    (a1 * a2 * ... an) ^ (1/n)

*/

void unosKrajaIntervala(int &);
double nadiGeometrijskuSredinuDoN(const int);

int main() {
    int N {};

    unosKrajaIntervala(N);

    double geometrijskaSredina { nadiGeometrijskuSredinuDoN(N) };

    std::cout<<"Geometrijska sredina svih neparnih brojeva koji nisu djeljivi sa 5 u intervalu [1, ";
    std::cout<<N<<"] je "<<std::setprecision(3)<<geometrijskaSredina<<std::endl;

    std::cin.get();
    return 0;
}

void unosKrajaIntervala(int &unos) {
    std::cout<<"Unesi kraj intervala (N): ";
    std::cin>>unos;
}

double nadiGeometrijskuSredinuDoN(const int N) {
    double suma {1.0};  
    // ^ bez double ili long double preciznost opada, npr. unos 100 nece biti ispravan
    // test tacnosti se moze raditi preko stranice kao sto je 
    // http://www.alcula.com/calculators/statistics/geometric-mean/

    int brojac {0};

    for (int i = 1; i <= N; i += 2) {
        if (i % 5 != 0) {
            suma *= i;
            brojac++;
        }
    }

    return std::pow(suma, 1.0 / brojac);
}