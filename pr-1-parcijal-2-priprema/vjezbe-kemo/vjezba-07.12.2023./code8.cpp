#include<iostream>
#include<cmath>

/*
    8. Zadatak
    Napravite rekurzivnu funkciju 'printTextInReverse'
    koja korisniku omogucava da unosi pojedinacne znakove.
    Unos se ponavlja sve dokle god korisnik ne unese tacku
    (.). Nakon unosa, program treba obrnuti redoslijedom
    ispisati sve unesene znakove (izuzev tacke).

    Unos:
    F
    I
    T
    .

    Ispis:
    TIF
*/

// head rekurzija
void printTextInReverse() {
    char sign {};

    std::cout<<"Unesi karakter: ";
    std::cin>>sign;

    if (sign != '.') {
        printTextInReverse();
        std::cout<<sign;
    }
}

int main() {
    printTextInReverse();
    std::cout<<std::endl;

    return 0;
}
