#include<iostream>
#include<string.h>

/*
    Nizovi karaktera i pokazivaca
*/

int main() {
    // staticki niz karaktera
    char arr[20] { "" };
    
    std::cout<<"Unesite tekst: ";
    std::cin.getline(arr, std::size(arr));  // unos "Star Trek"

    // deklaracija statickog pokazivaca i inicijalizacija istog na NULTU adresu
    char *c { nullptr };    // isto se moze pisati char *c { NULL };
    // Nulta adresa se cesto koristi kao defaultna vrijednost pokazivaca (bez obzira na njegov tip)

    // Postavljanje adrese 'arr' kao vrijednost pokazivaca c
    c = arr;

    // ispis teksta preko pokazivaca (ispis pocinje od adrese prvog elementa)
    std::cout<<c<<std::endl;
    // ispis teksta preko pokazivaca (ispis pocinje od adrese drugog elementa)
    std::cout<<c + 1<<std::endl;
    // ispis teksta preko pokazivaca (ispis pocinje od adrese treceg elementa)
    std::cout<<c + 2<<std::endl;
    // ispis karaktera na lokaciji 2
    std::cout<<*(c + 2)<<std::endl; // alternativno "std::cout<<c[2]<<std::endl;"

    // staticki pokazivac na staticki konstantni niz karaktera
    const char *arr2 { "Dune (2023)" };
    // elementi ovog niza ne mogu mijenjati vrijednosti
    // npr. ne mozemo reci 
    // *(arr2 + 2) = 'A';   arr2[2] = 'A';

    /*
        Kako se mjeri duzina?
        Za mjerenje duzine sadrzaja koristi se funkcija 'strlen' [string length]

        'strlen' funkcija prima parametar 'Str' koji je tipa 'const char *'

        'const char *' je pogodan jer obezbjeduje nepromjenjivost / konstantnost niza
        Sta to znaci?
        Ulazni parametar je pokazivac na konstantni niz karaktera, sto znaci da se vrijednosti
        niza ne mogu [i nece] mijenjati unutar implementacije funkcije 'strlen', sto i ima smisla
        jer je njen zadatak samo da izmjeri duzinu.

        Glavna pouka:
        Dosta cesto se koristi pokazivac tip "const char *" za rad sa nizovima karaktera u funkcijama.
    */

    std::cout<<strlen(arr2)<<std::endl;     // ispisuje duzinu teksta

    return 0;
}