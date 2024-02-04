#include<iostream>

/*
    Adresna aritmetika i nizovi :: 
    Obzirom da je niz sastavljen od pojedinacnih varijabli [istog tipa],
    udaljenosti u adresnom prostoru izmedu susjednih elemenata su UVIJEK 1.
    Npr.
        abs(&arr[5] - &arr[4]);  // rezultat je 1
        abs(&arr[5] - &arr[1]);  // rezultat je 4 

    
*/

int main() {
    int arr[5] {11, 22, 33, 44, 55};

    for (int i = 0; i < std::size(arr); i++) {
        std::cout<<"Indeks: "<<i<<' ';
        std::cout<<"Adresa: "<<&arr[i]<<' ';            // arr + i
        std::cout<<"Vrijednost: "<<arr[i]<<std::endl;   // *(arr + i)
    }

    // Koji je rezultat sljedeceg izraza?
    std::cout<<*(arr + 1)<<std::endl;

    // Koji je rezultat sljedeceg izraza?
    std::cout<<(arr + 1)[-1]<<std::endl;

    // Koji je rezultat sljedeceg izraza?
    std::cout<<(arr + 5)[-2]<<std::endl;

    // Koji je rezultat sljedeceg izraza?
    std::cout<<(arr - 2)[4]<<std::endl;

    // Koji je rezultat sljedeceg izraza?
    std::cout<<*(&arr[4] - 1)<<std::endl;

    // Koji je rezultat sljedeceg izraza?
    std::cout<<&(*(arr + 1))<<std::endl;

    return 0;
}