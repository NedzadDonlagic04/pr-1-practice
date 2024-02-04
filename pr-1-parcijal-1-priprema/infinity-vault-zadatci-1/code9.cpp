#include<iostream>
#include<iomanip>
#include<cmath>

/* 
    Poštujući sve faze procesa programiranja, napišite program,
    koji za uneseni prirodni broj n i realni broj x izračunava:

    S = cos(x) + cos(x^2) + cos(x^3) + ... + cos(x^n)
*/

void unosN(int &);
void unosX(float &);
float sumaZadatkaDoN(const int, const float);

int main() {
    int n {};
    float x {};

    unosN(n);
    unosX(x);

    std::cout<<"Suma date formule u intervalu [1, "<<n<<"] je ";
    std::cout<<std::setprecision(3)<<sumaZadatkaDoN(n, x)<<std::endl;

    std::cin.get();
    return 0;
}

void unosN(int &unos) {
    std::cout<<"Unesi prirodni broj (n): ";
    std::cin>>unos;
}

void unosX(float &unos) {
    std::cout<<"Unesi realni broj (x): ";
    std::cin>>unos;
}

float sumaZadatkaDoN(const int n, const float x) {
    float suma {0.0f};

    for (int i = 1; i <= n; i++)
        suma += std::cos(std::pow(x, i));

    return suma;
}