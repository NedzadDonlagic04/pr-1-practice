#include<iostream>

/*
    Adresna aritmetika i tekstovi
*/

int main() {
    // deklaracija statickog niza karaktera [sa inicijalizacijom]
    char tekst[30] { "Digimon" };
    // duzina teksta: 7
    // tekstualni sadrzaj okupira indekse od 0 do 6
    // lokacija '\0' je indeks [7]
    // indeksi 8 - 29 imaju "junk" vrijednosti

    // ispis sadrzaja od adrese prvog elementa sve do '\0' [kraja teksta]
    std::cout<<tekst<<std::endl;
    // ispis sadrzaja od adrese drugog elementa sve do '\0' [kraja teksta]
    std::cout<<tekst + 1<<std::endl;
    // ispis sadrzaja od adrese treceg elementa sve do '\0' [kraja teksta]
    std::cout<<tekst + 2<<std::endl;

    // ispis jednog simbola na indeksu 0
    std::cout<<*(tekst + 0)<<std::endl;     // isto kao - "*tekst; tekst[0];"
    // ispis jednog simbola na indeksu 1
    std::cout<<*(tekst + 1)<<std::endl;     // isto kao - "tekst[1];"
    // ispis jednog simbola na indeksu 2
    std::cout<<*(tekst + 2)<<std::endl;     // isto kao - "tekst[2];"

    *(tekst + 3) = 'K';                     // promjena vrijednosti jednog karaktera u nizu (na lokaciji 3)
    // tekst = "Liga prvaka";               // nevalidno koristenje

    return 0;
}