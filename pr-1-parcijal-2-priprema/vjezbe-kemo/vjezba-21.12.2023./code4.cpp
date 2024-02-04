#include<iostream>

int main() {
    // deklaracija statickog niza karaktera [sa inicijalizacijom]
    char arr[20] { "Pokemon" };
    // velicina niza: 20
    // duzina sadrzaja: 7  

    /*
        'arr' je ovdje adresa slova 'P'
        Null-terminirajuci karakter se smjesta na kraj sadrzaja tj. na slobodno
        mjesto iza zadnjeg slova 'n'

        Navedeni niz ima sljedeci izgled:
        Index:  0 - Vrijednost: 'P' [prvi element; njegova adresa se cuva u 'arr'] [0xAAEE110022]
        Index:  1 - Vrijednost: 'o' 
        Index:  2 - Vrijednost: 'k' 
        Index:  3 - Vrijednost: 'e' 
        Index:  4 - Vrijednost: 'm' 
        Index:  5 - Vrijednost: 'o' 
        Index:  6 - Vrijednost: 'n' 
        Index:  7 - Vrijednost: '\0' (null-terminirajuci karakter)
        Index:  8 - Vrijednost: (junk) 
        Index:  9 - Vrijednost: (junk) 
        Index: 10 - Vrijednost: (junk) 
        Index: 11 - Vrijednost: (junk) 
        .
        .
        .
        Index: 19 - Vrijednost: (junk) [ovo je zadnji element i oznaca kraj niza]
    */

    std::cout<<arr<<std::endl;

    /*
        Ispisuje sve karaktere od adrese '[0xAAEE110022]' [adresa prvog elementa u nizu] sve do '\0'
    */

    return 0;
}