#include<iostream>

/*
    Pokazivaci i funkcije [poziv po referenci]
*/

void func(int *&q) {
    // kreira referenca 'q' na pokazivac 'p'
    // primamro orginalni pokazivac iz main funkcije 
    // (sa adresom i vrijednoscu)

    *q *= 3;
    std::cout<<"Adresa 'q': "<<&q<<std::endl;
    std::cout<<"Adresa na koju pokazuje 'q': "<<q<<std::endl;
    std::cout<<"------------------------------------\n";
}

int main() {
    int a {555};
    int *p {&a};    // npr. 0xAABBCCDD0011

    func(p);        // salje se CIJELA pokazivacka varijabla 

    std::cout<<"Adresa 'p': "<<&p<<std::endl;
    std::cout<<"Adresa na koju pokazuje 'p': "<<p<<std::endl;
    std::cout<<"------------------------------------\n";

    std::cout<<"Adresa 'a': "<<&a<<std::endl;
    std::cout<<"Vrijednost 'a': "<<a<<std::endl;
    std::cout<<"------------------------------------\n";

    return 0;
}