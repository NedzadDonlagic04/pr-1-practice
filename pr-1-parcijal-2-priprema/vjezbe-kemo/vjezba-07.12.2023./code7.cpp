#include<iostream>
#include<cmath>

/*
    7. Zadatak
    Napravite rekurzivnu funkciju 'maxNumber' koja ce zahtjevati unos pozitivnih
    brojva od korisnika sve dok korisnik ne unese negativan broj ili broj 0.
    Povratna vrijednost iz funkcije treba da najveci uneseni broj.
*/

int maxNumber() {
    int x {};

    std::cout<<"Unesi broj: ";
    std::cin>>x;

    if (x <= 0) {
        return 0;
    }

    return std::max(x, maxNumber());     // tail rekurzija
}

int main() {
    int maxNumFromUserInput { maxNumber() };

    std::cout<<"Max number nakon unosa je "<<maxNumFromUserInput<<std::endl;

    return 0;
}
