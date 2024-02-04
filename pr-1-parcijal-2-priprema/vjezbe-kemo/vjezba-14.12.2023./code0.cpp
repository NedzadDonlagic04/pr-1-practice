#include<iostream>
#include<iomanip>

/*
    "Foreach" petlja :: pojam

    Koristi se za iteriranje (prolazenje) kroz elemente kontejnera
    (engl. container)
    Kontejner je podatkovna struktura za pohranu podataka (uglavnom)
    istog tipa.
    Primjer su vektori, liste, nizovi (staticki), stekovi, redovi, ...

    Kod foreach petlje NE POSTOJI iterator (varijabla 'i')
    vec se ISKLJUCIVO koriste privremene reference.

    Manipuliranje elementima niza se upravo odvija preko manipulacije
    tim privremenim referencama.

    One se ne mogu koristiti za dinamicke nizove (pokazivace).
*/

const int MAX_SIZE {15};

int getRandomValue(const int from, const int to) {
    return std::rand() % (to - from + 1) + from;
}

int main() {
    std::srand(694);

    int arr[MAX_SIZE] {0};  // kreiranje statickog niza na stek (statickoj) memoriji

    for (int &el : arr) {
        // 'el' je privremena referenca za svaki pojedini element 
        // referenca nam ovdje sluzi za dohvacanje originalne varijable koja je dio niza

        el = getRandomValue(6, 10);
    } 

    for (const int el : arr) {
        std::cout<<std::setw(3)<<el<<" ";
    }

    std::cout<<std::endl;

    return 0;
}