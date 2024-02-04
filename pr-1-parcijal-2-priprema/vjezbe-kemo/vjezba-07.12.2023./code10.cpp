#include<iostream>
#include<cmath>

/*
    Napisite program koji ce omoguciti 1D niza proizvoljne velicine
    te uz pomoc rekurzivnih funkcija omoguciti:
    --> unos elemenata
    --> ispis elemenata
    --> izracunati sumu svih elemenata niza
    --> sumu pozitivnih elemenata niza
    --> sumu elemenata niza s parnim indeksom
*/

/*
    1D niza proizvoljne velicine
    --> staticki niz [globalna konstanta]
    --> dinamicki niz [pokazivaci]
*/

const int MAX_ARR_SIZE {500};

/*
    ideja je da se iterator 'i' uvecava do vrijednosti size
    adresa 'arr' je fiksna
    size je fiksna vrijednost takodjer
*/
void enterArray(int arr[], int i, const int size) {
    if (i == size) {
        return;
    }

    std::cout<<"Unesite vrijednost na index poziciju "<<i<<": ";
    std::cin>>arr[i];

    enterArray(arr, i + 1, size);
}

void printArray(int arr[], int i, const int size) {
    if (i == size) {
        return;
    }

    std::cout<<arr[i]<<' ';
    printArray(arr, i + 1, size);
}

void printArrayReversed(int arr[], int i, const int size) {
    if (i == size) {
        return;
    }

    printArrayReversed(arr, i + 1, size);
    std::cout<<arr[i]<<' ';
}

int sumOfArrayElements(int arr[], int i, const int size) {
    if (i + 1 == size) {
        return arr[i];
    }

    return arr[i] + sumOfArrayElements(arr, i + 1, size);
}

int sumOfPositiveArrayElements(int arr[], int i, const int size) {
    if (i == size) {
        return 0;
    }

    return std::max(0, arr[i]) + sumOfPositiveArrayElements(arr, i + 1, size);
}

int sumOfEvenIndexes(int arr[], int i, const int size) {
    if (i + 2 >= size) {
        return arr[i];
    }

    return arr[i] + sumOfEvenIndexes(arr, i + 2, size);
}

int main() {
    int arr[MAX_ARR_SIZE] {};
    int size {};

    do {
        std::cout<<"Unesite velicinu niza: ";
        std::cin>>size;

        if (size > MAX_ARR_SIZE) {
            std::cout<<"Duzina niza mora biti manja od 500\n";
        } else if (size < 0) {
            std::cout<<"Duzina niza mora biti veca od 0\n";
        }
    } while (size < 0 || size > MAX_ARR_SIZE);

    enterArray(arr, 0, size);

    std::cout<<"Clanovi niza: ";
    printArray(arr, 0, size);
    std::cout<<std::endl;

    std::cout<<"Clanovi niza unazad ispisani: ";
    printArrayReversed(arr, 0, size);
    std::cout<<std::endl;

    std::cout<<"Suma clanova niza je: "<<sumOfArrayElements(arr, 0, size)<<'\n';
    std::cout<<"Suma pozitivnih clanova niza je: "<<sumOfPositiveArrayElements(arr, 0, size)<<'\n';
    std::cout<<"Suma parnih index clanova niza je: "<<sumOfEvenIndexes(arr, 0, size)<<'\n';

    return 0;
}