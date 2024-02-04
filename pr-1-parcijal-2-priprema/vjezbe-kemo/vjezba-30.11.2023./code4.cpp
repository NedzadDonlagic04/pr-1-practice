#include<iostream>
#include<algorithm>

/*
    Zadatak 4:
    Napisati program koji pronalazi najucestaliji element u 1D nizu.
    Hint: Za pronalazenje najucestalijeg elementa, veoma je povezno da se isti sortira.
    Za sortiranje mozete implementirati sopstvenu funkciju, a isto tako mozete koristiti
    gotovu funkciju 'sort' iz biblioteke 'algorithm'
    Za ovaj primjer, ukljucite biblioteku 'algorithm' i koristite funckiju 'sort'
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

int getMostFrequentElement(int arr[], const int size) {
    // 2 2 4 3 1 1 3 3 4

    std::sort(arr, arr + size);

    // 1 1 2 2 3 3 3 4 4

    int mostFrequentElement {arr[0]}, mostFrequentCounter {1};
    int currentCounter {1};

    std::cout<<std::endl;

    // 1 1 2 2 3 3 3 4 4 4 4 4 4 4 4 4 4
    for (int i = 1; i < size; i++) {
        if (arr[i - 1] != arr[i]) {
            if (currentCounter > mostFrequentCounter) {
                mostFrequentCounter = currentCounter;
                mostFrequentElement = arr[i - 1];
            }
            currentCounter = 0; 
        }
        currentCounter++;
    }

    return (currentCounter > mostFrequentCounter)? arr[size - 1] : mostFrequentElement;
}

int main() {
    int arr[9] {};

    enterArray(arr, std::size(arr));
    printArray(arr, std::size(arr));

    std::cout<<"Element koji se najcesce pojavljuje je: "<<getMostFrequentElement(arr, std::size(arr))<<std::endl;

    return 0;
}