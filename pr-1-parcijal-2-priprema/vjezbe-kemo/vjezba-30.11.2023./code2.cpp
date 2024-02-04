#include<iostream>

/*
    Zadatak 2:
    Napisati program koji provjerava da li je 1D niz rastuci.
    Velicina niza je 5
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

bool isAscending(int arr[], const int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) { 
            return false;
        }
    }
    return true;
}

int main() {
    int arr[5] {};

    enterArray(arr, std::size(arr));
    printArray(arr, std::size(arr));

    if (isAscending(arr, std::size(arr))) {
        std::cout<<"Niz je rastuci."<<std::endl;
    } else {
        std::cout<<"Niz nije rastuci."<<std::endl;
    }

    return 0;
}