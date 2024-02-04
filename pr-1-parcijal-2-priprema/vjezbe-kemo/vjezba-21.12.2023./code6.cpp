#include<iostream>

int main() {
    // Primjer ovaj koristen da pokaze kako input bafer spasava unos
    // '111 222 333'
    /*
        int broj1 {}, broj2 {}, broj3 {};

        std::cout<<"Unesite broj 1: ";
        std::cin>>broj1;

        std::cout<<"Unesite broj 2: ";
        std::cin>>broj2;

        std::cout<<"Unesite broj 3: ";
        std::cin>>broj3;

        std::cout<<"Broj 1: "<<broj1<<std::endl;
        std::cout<<"Broj 2: "<<broj2<<std::endl;
        std::cout<<"Broj 3: "<<broj3<<std::endl;
    */

    /*
        Navedeni niz ima sljedeci izgled:
        Index:  0 - Vrijednost: '\0' [prvi element; njegova adresa se cuva u 'tekst'] [0xAAEE110022]
        Index:  1 - Vrijednost: (junk) 
        Index:  2 - Vrijednost: (junk) 
        .
        .
        .
        Index: 19 - Vrijednost: (junk) [ovo je zadnji element i oznaca kraj niza]
    */
    /*
        Kako se unose nizovi karaktera preko konzole?
        Postoje 3 metode:
        1. objekt 'cin'
        2. funkcija cin.get
        3. cin.getline

        1. objekt 'cin'
            Neka je primjer sljedeci:

            int broj {};
            std::cin>>broj; // 123 125 101
            Kod unosa '123 125 101' samo se 123 pohranjuje kao broj u varijablu
            'broj', dok '125 101' ide u input bafer.

            Sta je to input bafer?
            To je privremena memorija koja se koristi za pohranu podataka sa konzolnog
            ulaza.

            int broj2 {};
            std::cin>>broj2;
            Ovdje cin uzima sljedecu slobodnu stakvu input bafera i pohranjuje u varijablu 'broj2'
            (dakle 125) a 101 i dalje ostaje u input baferu.

            Tek kada je input bafer prazan, tada se korisnika pita za unos.
            'cin' objekat ucitava sve simbole sa ulaza do prvog pojavljivanja znaka razmak ' '
            
            Naredni primjer:
            char niz[30];
            std::cin>>niz;  // grand theft auto 6
            rijec 'grand' ide u 'niz' a rijeci 'theft auto 6' ide u input bafer

            Upravo zbog ovoga, necemo koristiti 'cin' objekt za unos tekstova.
            'cin' je dobar za pojedinacne brojeve, ali nije dobar za tekstove.
        
        2.  'cin.get' je funkcija koja preuzima pojedinacne simbole iz input bafera
            i koristi se u kombinaciji sa 'while' petljom.
        
        3. 'cin.getline' je funkcija koja preuzima cijelu liniju iz input bafera.
            Linija predstavlja sve simbole/karaktere prije simbola za novi red ('\n')
    */

    // deklaracija statickog niza karaktera [sa inicijalizacijom]
    char tekst[20] { "" };

    std::cin.getline(tekst, std::size(tekst));  // ili umjesto std::size(tekst) moze i 20

    std::cout<<tekst<<std::endl;    
    
    return 0;
}