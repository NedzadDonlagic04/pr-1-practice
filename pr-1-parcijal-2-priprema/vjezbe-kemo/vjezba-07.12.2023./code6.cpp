#include<iostream>

/*
    6. Zadatak
    Napisati rekurzivnu funkciju 'sumUserInputs' koja izracunava sumu brojeva koje
    je korisnik unio. Rekurzivna funkcija treba od korisnika zahtijevati unos brojeva
    sve dok korisnik ne unese negativan broj.
*/

int sumUserInputs() {
    int x {};

    std::cout<<"Unesi broj: ";
    std::cin>>x;

    if (x < 0) {
        return 0;
    }

    return x + sumUserInputs();     // tail rekurzija
}

int main() {
    int sumOfUserInputs{ sumUserInputs() };

    std::cout<<"Suma korisnickih unosa je "<<sumOfUserInputs<<std::endl;

    return 0;
}