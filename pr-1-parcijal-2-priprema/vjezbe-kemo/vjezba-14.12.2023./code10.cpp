#include<iostream>

/*
    Pokazivaci i funkcije [vracanje vrijednosti{adrese}]
*/

// funkcija koja vraca adresu
int* func() {
    int a {55};

    std::cout<<"Adresa 'a': "<<&a<<std::endl;
    std::cout<<"Vrijednost 'a': "<<a<<std::endl;
    std::cout<<"------------------------------\n";

    return &a;  // vracanje adrese od lokalne varijable 'a'
}

// funkcija koja vraca CIJELI pokazivac
int*& func1() {
    int a {55};
    int *p {&a};
    return p;   // vracanje adrese od lokalne varijable 'a'
}

int main() {
    int *p {func()};     
    // lokalni pokazivac 'p' se inicijalizira na adresu koju vraca funkcija 'func'
    std::cout<<"Adresa 'p': "<<&p<<std::endl;
    std::cout<<"Vrijednost 'p': "<<p<<std::endl;

    return 0;
}