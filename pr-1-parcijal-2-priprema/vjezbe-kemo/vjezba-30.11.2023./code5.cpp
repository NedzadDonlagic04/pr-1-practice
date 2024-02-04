#include<iostream>

/*
    Zadatak 5:
    Napisati program koji provjerava da li je uneseni niz (velicine 5) - aritmeticki niz
    Primjer aritmetickih nizova:

    Aritmeticki niz je niz gdje je udaljenost izmedju susjednih elemenata ISTA.
    1, 2, 3, 4, 5, ...          udaljenost: 1
    1, 3, 5, 7, 9, ...          udaljenost: 2
    10, 20, 30, 40, 50, ...     udaljenost: 10
    11, 22, 33, 44, 55, ...     udaljenost: 11

    a(n) = d + a(n-1)
*/

void enterArray(int arr[], const int size) {
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

bool isArithmetic(int arr[], const int size) {
    int razlika { arr[1] - arr[0] };
    /*
        arr[0] - arr[-1]    nevalidno
        arr[1] - arr[0]
        arr[2] - arr[1]
        arr[3] - arr[2]
        arr[4] - arr[3]
    */

    for (int i = 2; i < size; i++) { 
        if (razlika != arr[i] - arr[i - 1]) {
            return false;
        }   
    }

    return true;
}

int main() {
    int arr[5] {};

    enterArray(arr, std::size(arr));
    printArray(arr, std::size(arr));

    if (isArithmetic(arr, std::size(arr))) {
        std::cout<<"Niz je aritmeticki."<<std::endl;
    } else {
        std::cout<<"Niz nije aritmeticki."<<std::endl;
    }

    return 0;
}