#include <iostream>
#include <cmath>
#include <iomanip>

/* 
    Poštujući sve faze programiranja napisati 
    program koji omogućava unos prirodnog broja n
    preko tastature te izračunava sumu:

    (1/3)^2 + (1/5)^2 + ... + 1 / (2n + 1)^2
*/

void unos(int &);
float sumaDoN(const int);

int main() {
    int n {}; 

    unos(n);
    std::cout<<"Suma od [1, "<<n<<"] za datu formulu je ";
    std::cout<<std::setprecision(3)<<sumaDoN(n)<<std::endl;

    std::cin.get();
    return 0;
}

void unos(int &unos) {
    do {
        std::cout<<"Unesi prirodni broj (n): ";
        std::cin>>unos;
        
        if (unos < 1) {
            std::cout<<"Unos treba biti prirodan broj\n";
        }
    } while(unos < 1);
}

float sumaDoN(const int n) {
    float suma { 0.0f };

    for (int i = 1; i <= n; i++) 
        suma += 1 / std::pow(2 * i + 1, 2);

    return suma;
}