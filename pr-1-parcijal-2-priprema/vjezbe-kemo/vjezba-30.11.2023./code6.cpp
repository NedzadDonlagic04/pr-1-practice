#include<iostream>
#include<iomanip>

/*
    Iomanip je skracenica od input/output manipulation.
*/

/*
    Matrica :: pojam

    2D niz (dvodimenzionalni niz) - matrica

    3D, 4D i vise dimenzionalni nizovi - tenzori
    (Cesto se koriste u fizici, neuralnim mrezama etc)

    Podaci su grupisani u redove i kolone.
    Svaki red je 1D niz (elementi su jedan do drugog).

*/

int main() {
    // deklaracija 2D niza (3x4)
    int matrica[3][4] {};   // naziv 'matrica' oznacava adresu elementa na lokaciji [0 x 0]

    matrica[0][0];          // dvostruko dereferenciranje
    
    // deklaracija i inicijalizacija 1D niza
    int arr[5] = {1, 0, -1, 22, 4};

    // deklaracija i inicijalizacija 2D niza
    int m[3][4] = {
        {1, 2, 3, 4},
        {3, 3, 5, 31},
        {2, -3, 53, 3}
    };

    for (int i = 0; i < std::size(m); i++) {
        // size(m) --> vraca broj redova
        // size(m[i]) --> vraca broj kolona u redu 'i'
        // Sparse matrice --> matrice gdje razliciti redovi imaju drugaciji broj kolona
        for (int ii = 0; ii < std::size(m[i]); ii++) {
            // setw (set width) --> setuje sirinu okvira gdje se ispisuju brojevi
            // setw(3) --> sirina okvira je 3 (3 cifre)
            std::cout<<std::setw(3)<<m[i][ii]<<' ';
        }
        std::cout<<std::endl;
    }

    return 0;
}