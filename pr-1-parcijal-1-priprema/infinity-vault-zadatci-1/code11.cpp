#include<iostream>
#include<cmath>
#include<iomanip>

/* 
    Napisati program koji korisniku omogućava unos cijelog broja n,
    te izračunava:

    S = [1/(n + 1)] - [2/((n - 1) + 2!)] + [3/((n - 2) + 3!)] - 
    [4/((n - 3) + 4!)] + ... + (-1)^(n - 1) * [n/(1 + n!)]
*/

void unos(int &);
float sumaFormuleZadatkaDoN(const int);
unsigned long long faktorijal(int);

int main() {
    int n {};

    unos(n);

    std::cout<<"Suma formule u intervalu [1, "<<n<<"] je ";
    std::cout<<std::setprecision(3)<<sumaFormuleZadatkaDoN(n)<<std::endl;

    std::cin.get();
    return 0;
}

void unos(int &unos) {
    std::cout<<"Unesi cijeli broj (n): ";
    std::cin>>unos;
}

unsigned long long faktorijal(int broj) {
    unsigned long long faktorijal {1ull};

    for (; broj >= 2; broj--)
        faktorijal *= broj;

    return faktorijal;
}

float sumaFormuleZadatkaDoN(const int n) {
    float suma {0.0f};

    for (int i = 1; i <= n; i++)
        suma += std::pow(-1, i - 1) * i / (1 + faktorijal(i));

    return suma;
}