#include<iostream>

/*
    Zadatak 3:
    Napisati program koji provjerava da li je 1D niz palindrom.
    Palindrom je rijec ili niz ili sekvenca koja se isto cita i sa lijeve i sa desne strane.
    [Main funkcija] Kreirati dva niza od koji ce jedan biti dimenzija 5, a drugi 6.
    Testirati funkciju za provjeru palindroma na oba niza.
    
    --> Neparni palindrom (neparan broj elemenata u nizu)
    1 2 1
    1 1 1
    4 2 4
    1 3 5 3 1
    2 4 2 4 2

    --> Parni palindrom (paran broj elemenata u nizu)
    1 3 3 1
    1 2 2 1
    4 4 4 4
    4 3 3 4
    5 1 1 5

    Testirati funkciju za provjeru palindroma na oba niza
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

bool isArrPalindrom(int arr[], const int size) {
    /*
        velicina: 5
        indeksi: 0 1 2 3 4
        moraju biti jednaki:
        --> arr[0] = arr[4]
        --> arr[1] = arr[3]
        --> arr[2] --> njega ne poredimo
    */

    /*
        velicina: 6 
        indeksi: 0 1 2 3 4 5
        moraju biti jednaki:
        --> arr[0] = arr[5]
        --> arr[1] = arr[4]
        --> arr[2] = arr[3]
    */

    for (int i = 0; i < size / 2; i++) {
        if (arr[i] != arr[size - i - 1]) {
            return false;
        }
    }

    return true;
}

int main() {
    int arr1[5] {};
    int arr2[6] {};

    enterArray(arr1, std::size(arr1));
    printArray(arr1, std::size(arr1));

    enterArray(arr2, std::size(arr2));
    printArray(arr2, std::size(arr2));

    if (isArrPalindrom(arr1, std::size(arr1))) {
        std::cout<<"Prvi niz je palindrom."<<std::endl;
    } else {
        std::cout<<"Prvi niz nije palindrom."<<std::endl;
    }

    if (isArrPalindrom(arr2, std::size(arr2))) {
        std::cout<<"Drugi niz je palindrom."<<std::endl;
    } else {
        std::cout<<"Drugi niz nije palindrom."<<std::endl;
    }

    return 0;
}