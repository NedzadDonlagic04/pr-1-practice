#include<iostream>
#include<limits>
#include<optional>

void allocatePointerArray(int **, std::size_t);
void deallocatePointerArray(int **, std::size_t);

void clearBuffer();
void enterNum(int &, const char *, const std::optional<std::size_t> = std::nullopt);

void enterArray(int **, int, int);
void printArray(int **, int, int);

int sumArray(int **, int, int);
int findElement(int **, int, int, int);

int main() {
    constexpr std::size_t ARR_SIZE { 10 };
    int *parray[ARR_SIZE] {};
    int target {};

    allocatePointerArray(parray, ARR_SIZE);

    enterArray(parray, 0, ARR_SIZE);
    printArray(parray, 0, ARR_SIZE);

    std::cout<<"Suma elemenata: "<<sumArray(parray, 0, ARR_SIZE)<<std::endl;

    enterNum(target, "Unesite element za pretragu: ");

    int indexOfElement { findElement(parray, 0, ARR_SIZE, target) };

    std::cout<<"Element "<<target;
    if (indexOfElement == -1) {
        std::cout<<" nije pronadjen";
    } else {
        std::cout<<" pronadjen na indeksu "<<indexOfElement;
    }
    std::cout<<std::endl;

    deallocatePointerArray(parray, ARR_SIZE);

    return 0;
}

void allocatePointerArray(int **parray, std::size_t size) {
    for (std::size_t i = 0; i < size; i++) {
        parray[i] = new int {};
    }
}

void deallocatePointerArray(int **parray, std::size_t size) {
    for (std::size_t i = 0; i < size; i++) {
        delete[] parray[i];
        parray[i] = nullptr;
    }
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterNum(int &num, const char *outputText, const std::optional<std::size_t> index) {
    do {
        if (std::cin.fail()) {
            std::cout<<"Invalid input\n";
            clearBuffer();
        }
        std::cout<<outputText;
        if (index) {
            std::cout<<index.value();
        }
        std::cout<<": ";
        std::cin>>num;

    } while(std::cin.fail());
}

void enterArray(int **parray, int i, int max) {
    if (i == max) {
        return;
    }

    enterNum(*parray[i], "Unesite element na lokaciji ", i);

    enterArray(parray, i + 1, max);
}

void printArray(int **parray, int i, int max) {
    if (i == 0) {
        std::cout<<"Ispis: ";
    } else if (i == max) {
        std::cout<<std::endl;
        return;
    }

    std::cout<<*parray[i]<<' ';

    printArray(parray, i + 1, max);
}

int sumArray(int **parray, int i, int max) {
    if (i == max) {
        return 0;
    }

    return *parray[i] + sumArray(parray, i + 1, max);
}

int findElement(int **parray, int i, int max, int target) {
    if (i == max) {
        return -1;
    } else if (*parray[i] == target) {
        return i;
    }

    return findElement(parray, i + 1, max, target);
}