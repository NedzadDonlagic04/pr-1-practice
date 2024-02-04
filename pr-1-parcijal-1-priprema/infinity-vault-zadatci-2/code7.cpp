#include<iostream>

/* 
    Napisati program koji izračunava ukupan zbir faktorijela
    od svih prostih brojeva koji su članovi prvih 100 elemenata 
    Fibonacci niza (tzv. fibonacci prime).

    Napomena: Pazljivo pročitajte zadatak. Obavezno voditi računa 
    da se uradi tačno ono što je trazeno u zadatku i da zadatak 
    bude logicki ispravan. Obavezno koristiti bar jednu funkciju 
    kojoj ćete proslijediti parametar po referenci.
*/

/*
    Zbog velicine broja nakon sume toliko prosti brojeva, nece se moci kako treba
    ispisati, zbog cega sam interval stavio da ide do 25
*/

bool jesilProst(unsigned long long);
unsigned long long faktorijal(unsigned long long);

int main() {
    unsigned long long a {0}, b {1}, sumaFaktorijela {0};

    for (int i = 0; i < 25; i += 2) {
        if (jesilProst(a))
            sumaFaktorijela += faktorijal(a);
        a += b;

        std::cout<<sumaFaktorijela<<std::endl;

        if (jesilProst(b))        
            sumaFaktorijela += faktorijal(b);
        b += a;

        std::cout<<sumaFaktorijela<<std::endl;
    }

    std::cout<<"Suma prosti brojeva fibonacijevog niza u intervalu [0, 25] je "<<sumaFaktorijela<<std::endl;

    return 0;
}

bool jesilProst(unsigned long long broj) {
    if (broj <= 1) return false;

    for (unsigned long long i = 2; i * i <= broj; i++)
        if (broj % i == 0) 
            return false;

    return true;
}

unsigned long long faktorijal(unsigned long long broj) {
    unsigned long long proizvod {1};

    for (; broj >= 2; broj--) {
        proizvod *= broj;
    }

    return proizvod;
}