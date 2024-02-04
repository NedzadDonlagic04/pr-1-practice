#include<iostream>

/*
    Pokazivaci i funkcije [poziv po vrijednosti]
*/

// Poziv funkcije po vrijednosti pokazivaca
void func(int *q) {
    // U ovoj funkciji, kreira se NOVA pokazivacka varijabla 'q'
    // u koju se pohranjuje vrijednost koja dode iz main funkcije
    // Imamo dva pokazivaca 'p' i 'q' koji cuvaju istu vrijednost
    // npr. 0xAABBCCDD0011

    *q *= 3;
    // *q += 3;    // uvecavanje varijable 'a' za 3
    // q += 3;     // uvecavanje adrese u pokazivacu 'q' za 3 memorijska prostora
    std::cout<<"Adresa 'q': "<<&q<<std::endl;
    std::cout<<"Adresa na koju pokazuje 'q': "<<q<<std::endl;
    std::cout<<"------------------------------------\n";
}

int main() {
    int a {555};
    int *p {&a};    // npr. 0xAABBCCDD0011

    func(p);        // salje se samo VRIJEDNOST pokazivaca [adresa]

    std::cout<<"Adresa 'p': "<<&p<<std::endl;
    std::cout<<"Adresa na koju pokazuje 'p': "<<p<<std::endl;
    std::cout<<"------------------------------------\n";

    std::cout<<"Adresa 'a': "<<&a<<std::endl;
    std::cout<<"Vrijednost 'a': "<<a<<std::endl;
    std::cout<<"------------------------------------\n";

    return 0;
}