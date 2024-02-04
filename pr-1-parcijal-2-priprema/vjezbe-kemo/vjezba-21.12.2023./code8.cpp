#include<iostream>
#include<cstddef>
#include<string.h>

/*
    Nizovi karaktera i funkcije
*/

void enterText(char *text, const std::size_t size) {
    // "char *text" je deklaracija statickog pokazivaca u kojeg se ucitava vrijednost (adresa)
    // pristigla iz druge funkcije (cesto main funkcije)
    // ovo je poziv funkcije po vrijednosti
    // imate i poziv funkcije po referenci "char *& tekst"

    std::cout<<"Unesite tekst: ";
    std::cin.getline(text, size);
    // ovdje necemo koristiti 'const char *' jer moramo biti u mogucnosti da mijenjamo sadrzaj
}

void printText(const char *text = "") {
    // ovdje mozemo koristiti "const char *" tip, jer ne trebamo mijenjati sadrzaj teksta
    std::cout<<text<<std::endl;
}

int main() {
    char tekst1[100] {}, tekst2[70] {};

    // unos prvog i drugog teksta
    enterText(tekst1, std::size(tekst1));
    enterText(tekst2, std::size(tekst2));
    // ispis prvog i drugog teksta
    printText(tekst1);
    printText(tekst2);

    // string compare [vraca 0 ako su isti, u suprotnom vraca druge vrijednosti]
    (strcmp(tekst1, tekst2) == 0)? 
        std::cout<<"Tekstovi su isti" :
        std::cout<<"Tekstovi nisu isti";
    
    std::cout<<std::endl;

    return 0;
}