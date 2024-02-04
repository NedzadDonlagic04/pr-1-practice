#include<iostream>
#include<iomanip>

// globalna konstanta koja odreduje max broj redova za matricu
const int MAX_ROWS { 100 };

// globalna konstanta koja odreduje max broj kolona za matricu
const int MAX_COLUMNS { 100 };

void enterMatrix(int matrica[][MAX_COLUMNS], const int rows, const int cols) {
    if (rows > MAX_ROWS || cols > MAX_COLUMNS) {
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
    if (rows > MAX_ROWS || cols > MAX_COLUMNS) {
        return;
    }

    for (int i = 0; i < rows; i++) {
        for (int ii = 0; ii < cols; ii++) {
            std::cout<<std::setw(3)<<matrica[i][ii]<<' ';
        }
        std::cout<<std::endl;
    }
}

/*
    Demo:
    Simulacija kreiranja matrice sa proizvoljnim brojevim redova i kolona:
    Potrebne su nam dvije globalne konstante:
    --> MAX_ROWS
    --> MAX_COLUMNS
*/

int main() {
/*     int r {};
    std::cin>>r; */
    // Nije dozvoljeno da vrijednost varijable predtsavlja broj redova / kolona
    // matrice, buduci da je stack memorija ogranicena
    // Teoretski je moguce da korisnik unese 'r' = 1000, 'c' = 1000
    // I pritom mozda izazove stack overflow
    // Dimenzije statickih nizova i matrica moraju biti konstantne vrijednosti

    int r {}, c {};
    
    do {
        std::cout<<"Unesite broj redova: ";
        std::cin>>r;

        std::cout<<"Unesite broj kolona: ";
        std::cin>>c;
    } while(r < 0 || r > MAX_ROWS || c < 0 || c > MAX_COLUMNS);

    int matrica[MAX_ROWS][MAX_COLUMNS] {};

    enterMatrix(matrica, r, c);
    printMatrix(matrica, r, c);

    return 0;
}