#include<iostream>
#include<cmath>

/*
    Pokazivaci i funkcije [vracanje vrijednosti{adrese}]
*/
// funkcija za unos elemenata u niz
// moci ce se koristiti i za staticke i za dinamicke nizove
void enterArray(int *p, const int size) {
    // lokalna pokazivacka varijabla 'p' dohvaca adresu prvog elementa u nizu
    // potreban nam je dodatna varijabla 'size' koja oznacava velicinu niza
    // prije smo koristili 'int arr []'
    // 'int arr[]' je syntax sugar (pogodniji nacin da se nesto zapise)
    // 'int arr[]' je u pozadini zapravo 'int * arr'
    // 'int p[]' ili 'int *p'

    for (int i = 0; i < size; i++) {
        std::cout<<"Unesi element na lokaciji "<<i<<": ";
        std::cin>>p[i];
        // moglo isto ici *(p + i)
    }
}

void printArray(int *p, const int size) {
    for (int i = 0; i < size; i++) {
        std::cout<<"Element na indeksu "<<i<<" je "<<p[i]<<'\n';
    }
}

int max(int *p, const int size) {
    int maxEl {p[0]};

    for (int i = 1; i < size; i++) {
        maxEl = std::max(maxEl, p[i]);
    }

    return maxEl;
}

int main() {
    int arr[5] {};

    enterArray(arr, std::size(arr));
    printArray(arr, std::size(arr));
    std::cout<<"Najveci element u nizu je "<<max(arr, std::size(arr))<<std::endl;

    return 0;
}