#include<iostream>
#include<iomanip>

/*
    Matrice i funkcije...
    
    Da li se matrice salju po vrijednosti? Odgovor: NE
    Kako se salju matrice?
    Matrice se nikada ne salju u cjelini
        Prilikom slanja matrica potrebno je da se posalju tri parametra:
        * 'int matrica[][neka_vrijednost]' --> niz adresa sa kojim pocinju redovi
        * broj redova
        * broj kolona
*/

// globalna konstanta koja odreduje max broj kolona za matricu
const int MAX_COLUMNS { 100 };

void enterMatrix(int matrica[][MAX_COLUMNS], const int rows, const int cols) {
    if (cols > MAX_COLUMNS) {
        return;
    }

    for (int i = 0; i < rows; i++) {
        for (int ii = 0; ii < cols; ii++) {
            std::cout<<"Unesite element ["<<i<<", "<<ii<<"]: ";
            std::cin>>matrica[i][ii];   // dvostruko referenciranje 
            // (krecemo se po adresnom prostoru prvo redova pa onda kolona)
        }
    }
}

void printMatrix(int matrica[][MAX_COLUMNS], const int rows, const int cols) {
    if (cols > MAX_COLUMNS) {
        return;
    }

    for (int i = 0; i < rows; i++) {
        for (int ii = 0; ii < cols; ii++) {
            std::cout<<std::setw(3)<<matrica[i][ii]<<' ';
        }
        std::cout<<std::endl;
    }
}

int main() {
    const int r {3}, c {4};

    // deklaracija 2D niza cijelih brojeva dimenzija (r x MAX_COLUMNS)
    // napomena: necemo koristiti sve kolone, nego iskljucivo koristimo onoliko kolona
    // koliko nam je potrebno u ovom slucaju, koristimo tek 4 kolone (c = 4)
    int matrica[r][MAX_COLUMNS] {};

    enterMatrix(matrica, r, c);
    printMatrix(matrica, r, c);

    return 0;
}