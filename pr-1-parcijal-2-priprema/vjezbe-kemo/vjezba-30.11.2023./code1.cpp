#include<iostream>
#include<cmath>

/*
    Koristenje nizova u funkcijama

    Pitanje 1:  Da li se nizovi salju po vrijednosti?
                Tj. da li se nizovi salju u cjelini? [Odgovor: NE]
    Pitanje 2:  Da li se nizovi salju po referenci?
                Tj. da li se za niz napravi 'alias' [drugo ime za vec postojecu varijablu]
                [Odgovor: Da i Ne]
                Zasto DA? Zbog toga sto je u pitanju jedan srodan pojam koji nije referenca
                Zasto NE? Zato sto se ne proslijeduje niz po referensi 

                Kako se salju nizovi?
                Odgovor: Salju se iskljucivo dva podatka:
                1. Adresa prvog elementa ['arr'] (adresa elementa sa indeksom 0)
                2. Dimenzije niza (broj elemenata)

    ADRESA != REFERENSA
    Na osnovu adrese prvog elementa i operatora '[]' prisupa se svima ostalim elementima.
*/

void enterArray(int arr[], const int size) {
    // arr[] --> ovo nije deklaracija niza, niti je primanje niza, niti se odnosi na prihvatanje niza
    // u cjelini
    // arr[] --> "syntax sugar" koji oznacava POKAZIVAC 
    // "int arr[]" je isto sto i "int *arr"
    // Upravo zbog toga sto je 'arr' pokazivac a NE NIZ, ne mozemo koristiti ovdje funkciju 'size'
    // 'size' (size funkcija radi samo nad nizovima)

    for (int i = 0; i < size; i++) {
        std::cout<<"Unesite element na lokaciji "<<i<<": ";
        std::cin>>arr[i];       
    }
}

void printArray(int arr[], const int size) {
    std::cout<<"Velicina niza: "<<size<<std::endl;

    for (int i = 0; i < size; i++) {
        std::cout<<arr[i]<<' ';
    }

    std::cout<<std::endl;
}

int max(int arr[], const int size) {    // custom funkcija 'max'
    int temp { arr[0] };

    for (int i = 1; i < size; i++) {
        temp = std::max(temp, arr[i]);  // ugradena funkcija 'max'
    }

    return temp;
}

int min(int arr[], const int size) {
    int temp { arr[0] };

    for (int i = 1; i < size; i++) {
        temp = std::min(temp, arr[i]);  // ugradena funkcija 'min'
    }

    return temp;
}

// Funkcija treba da vrati element najslicniji vrijednosti 'val'
int getMostSimilar(int arr[], const int size, const int val) {
    // Trazimo element u nizu koji minimizira udaljenost izmjedju sebe i 'val'
    int mostSimilarId { 0 };
    int distance = std::abs(val - arr[mostSimilarId]);
    int currentDistance {};

    for (int i = 1; i < size; i++) {
        currentDistance = std::abs(val - arr[i]);
        if (distance > currentDistance) {
            mostSimilarId = i;
            distance = currentDistance;
        }
    }

    return arr[mostSimilarId];
} 

int main() {
    int arr[5] {};

    enterArray(arr, std::size(arr));
    printArray(arr, std::size(arr));

    std::cout<<"Najveci element je: "<<max(arr, std::size(arr))<<std::endl;
    std::cout<<"Najmanji element je: "<<min(arr, std::size(arr))<<std::endl;

    int val {};

    std::cout<<"Unesite neku vrijednost: ";
    std::cin>>val;

    std::cout<<"Najslicniji element je: "<<getMostSimilar(arr, std::size(arr), val)<<std::endl;

    return 0;
}