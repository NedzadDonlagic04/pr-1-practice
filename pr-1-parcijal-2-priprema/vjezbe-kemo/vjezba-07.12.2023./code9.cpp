#include<iostream>

/* 
    Zadatak 10
    Napravite rekurzivnu funkciju 'printLettersBetween'
    koja treba da ispise sva velika slova koja se nalaze izmedu 
    dva proslijedena velika slova
*/

void printLettersBetween(char s1, char s2) {
    if (s1 <= s2) {
        if (s1 >= 'A' && s1 <= 'Z') {
            std::cout<<s1<<' ';
        }
        printLettersBetween(s1 + 1, s2);
    }
}

void printLettersBetweenInReverse(char s1, char s2) {
    if (s1 <= s2) {
        if (s2 >= 'A' && s2 <= 'Z') {
            std::cout<<s2<<' ';
        }
        printLettersBetweenInReverse(s1, s2 - 1);
    }
}

int main() {
    char slovo1 {}, slovo2 {};

    do {
        do {
            std::cout<<"Unesite prvo slovo: "<<std::endl;
            std::cin>>slovo1;
        } while (!isupper(slovo1));

        do {
            std::cout<<"Unesite drugo slovo: "<<std::endl;
            std::cin>>slovo2;
        } while(!isupper(slovo2));
    } while(slovo1 > slovo2);

    std::cout<<"Ispis slova izmedu dva unesena ["<<slovo1<<", "<<slovo2<<"]: ";
    printLettersBetween(slovo1, slovo2); 
    std::cout<<std::endl;

    std::cout<<"Ispis slova izmedu dva unesena u obrnutom redoslijedu ["<<slovo1<<", "<<slovo2<<"]: ";
    printLettersBetweenInReverse(slovo1, slovo2); 
    std::cout<<std::endl;

    return 0;
}