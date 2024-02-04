#include<iostream>

/*
    Adresna aritmetika :: pojam

    Aritmetika: +, *, -, /

    Adresna aritmetika u C++ omogucava manipulaciju memorijskim
    adresama kako bi se izvrsile odredene operacije, kao sto je pristupanje
    elementima niza ili manipulacija podacima u memoriji.

    Memorijska adresa [C++] predstavlja jedinstvenu memorijsku lokaciju.
    Memorijska lokacija je niz bita (ali se zbog citljivosti prikazuje UVIJEK u
    heksadecimalnom formatu)

    1011
    Kako znati kojoj bazi pripada ovaj broj?
    Ovaj broj je vlaidan i u bazi 2, 3, 4, 5, ..., 10, ..., 16, ...
    Da bi se izbjegla konfuzija, koriste se prefiksi.
    Kada NEMA prefiksa, to automatski znaci da je broj u dekadskom sistemu.

    Za pisanje binarnih brojeva (baza 2) imamo sljedeci prefiks:
    bx10101010101
    bx1011
    bx110101

    Za pisanje heksadecimalnih brojeva (baza 16) imamo sljedeci prefiks:
    0x0011a112233ff
    0xaa00
    0x00001101

    U kontektsu koristenja objektnog programiranja u C++, postoje dva tipa
    -> stack (stek) memorija - velicine 1 MB [koristi se po defaultu]
    -> heap memorija (dinamicka memorija) - u teoriji beskonacna [zahtijeva koristenje pokazivaca]

    Na adrese se mogu upisivati vrijednosti i bez postojanja varijabli.
    Nulta adresa - prva adresa u memorijskom prostoru, generalno se koristi od strane OS-a.
    Nulta adresa je rezervirana od strane OS-a.

    U adresnoj aritmetici dozvoljene su operacije tipa:
    -> adresa + broj = nova adresa
        Interpretacija: Dobija se adresa koja je za 'broj' korara iza proslijedene adrese
            Npr. ako je broj = 5, "nova adresa" se nalazi za 5 mjesta iza "adrese"
    -> adresa - broj = nova adresa
        Interpretacija: Dobija se adresa koja je za 'broj' koraka ispred proslijedene adrese.
    -> abs(adresa1 - adresa2)
        Interpretacija: Mjerenje udaljenosti izmedu dvije adrese
*/

int main() {
    // Dodaje 5 na heksadecimalnu vrijednost, ispisuje rezultat.
    std::cout<<0x7fff5fbff700 + 5<<std::endl;
    
    // Oduzima 1 od heksadecimalne vrijednosti.
    std::cout<<0x7fff5fbff700 - 1<<std::endl;

    // Izracunava absolutnu razliku izmedu dvije heksadecimalne vrijednosti, ispisuje rezultat.
    std::cout<<std::abs(0x7fff5fbff700 - 0x7fff5fbff703)<<std::endl;

    // Na isti nacin se odvija adresna aritmetika

    return 0;
}