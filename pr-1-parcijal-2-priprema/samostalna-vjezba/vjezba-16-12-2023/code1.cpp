#include<iostream>

void enterArray(int *, const std::size_t, const std::size_t = 0);
void printArray(int *, const std::size_t, const std::size_t = 0);

void enterElementToFind(int &);

int* findArrayElement(int *, const std::size_t, const int);

int main() {
    constexpr std::size_t ARR_SIZE {5};
    int arr[ARR_SIZE] {};
    int elToFind {};

    enterArray(arr, ARR_SIZE);
    printArray(arr, ARR_SIZE);

    enterElementToFind(elToFind);

    auto foundEl { findArrayElement(arr, ARR_SIZE, elToFind) };

    if (foundEl) {
        std::cout<<"Element "<<*foundEl<<" found\n";
    } else {
        std::cout<<"Element not found\n";
    }

    return 0;
}

void enterArray(int *arr, const std::size_t size, const std::size_t i) {
    if (i == size) {
        return;
    }

    std::cout<<"Unjeti element na index poziciju "<<i<<": ";
    std::cin>>*(arr + i);

    enterArray(arr, size, i + 1);
}

void printArray(int *arr, const std::size_t size, const std::size_t i) {
    if (i == 0) {
        std::cout<<"Clanovi niza: ";
    } else if (i == size) {
        std::cout<<std::endl;
        return;
    }

    std::cout<<*(arr + i)<<' ';

    printArray(arr, size, i + 1);
}

void enterElementToFind(int &num) {
    std::cout<<"Enter the element to find from the array: ";
    std::cin>>num;
}

int* findArrayElement(int *arr, const std::size_t size, const int elToFind) {
    int *ptrToEl {nullptr};

    for (int i = 0; i < size; i++) {
        if (*(arr + i) == elToFind) {
            ptrToEl = arr + i;
            break;
        }
    }

    return ptrToEl;
}