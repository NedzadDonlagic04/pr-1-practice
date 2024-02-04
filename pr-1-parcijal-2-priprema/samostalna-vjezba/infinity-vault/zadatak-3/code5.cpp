/*
Napisati program koji će generisati Fibonacci niz i smjestiti 
ga u jednodimenzionalni niz od 20 elemenata. (Fibonaccijev 
niz je niz brojeva koji počinje brojevima 0 i 1, a svaki sljedeći 
broj u nizu dobije se zbrajanjem prethodna dva: F(0) = 0, F(1) = 1, 
F(n) = F(n-1) + F(n-2)). Zatim napraviti funkciju koja će sortirati 
niz uzlazno po srednjoj cifri. (Za brojeve sa parnim brojem koristiti 
aritmeticku sredinu srednje dvije cifre).

(Voditi računa o tipu podatka prilikom računanja srednje cifre.)
*/

#include<iostream>
#include<cstddef>
#include<cmath>

void fillArray(int * const, float * const, const std::size_t, const std::size_t = 2);
//                                                       ^ jer prvi clan ce biti od pocetka 2
void printArray(const int * const, const std::size_t, const std::size_t = 0);

int countDigits(const int);
float getMiddleDigit(int);

void sortAscending(int * const, float * const, const std::size_t);
void sortByMiddleDigitOuterLoop(int * const, float * const, std::size_t);
void sortByMiddleDigitInnerLoop(int * const, float * const, const std::size_t, bool &, std::size_t = 0);

int main() {
    constexpr std::size_t arrSize { 20 };

    int *arr { new int[arrSize] };
    float *midDigitArr { new float[arrSize] };

    fillArray(arr, midDigitArr, arrSize);
    printArray(arr, arrSize);

    sortAscending(arr, midDigitArr, arrSize);
    printArray(arr, arrSize);

    delete[] arr;
    delete[] midDigitArr;

    return 0;
}

void fillArray(int * const arr, float * const midDigitArr, const std::size_t size, const std::size_t i) {
    if (i == 2) {
        *arr = 0;
        *midDigitArr = 0;

        *(arr + 1) = 1;
        *(midDigitArr+ 1) = 1;
    }
    if (i == size) {
        return;
    }

    *(arr + i) = *(arr + i - 1) + *(arr + i - 2);
    *(midDigitArr + i) = getMiddleDigit(*(arr + i));

    fillArray(arr, midDigitArr, size, i + 1);
}

void printArray(const int * const arr, const std::size_t size, const std::size_t i) {
    if (i == 0) {
        std::cout<<"Clanovi niza: ";
    } else if (i == size) {
        std::cout<<std::endl;
        return;
    }

    std::cout<<*(arr + i)<<' ';

    printArray(arr, size, i + 1);
}

int countDigits(const int num) {
    if (num == 0) {
        return 1;
    }

    return std::log10(std::abs(num)) + 1;
}

float getMiddleDigit(int num) {
    const int digitCount { countDigits(num) }; 
    const int digitsToRemove { digitCount / 2 - (digitCount % 2 == 0) };

    num /= std::pow(10, digitsToRemove);

    float middleDigit = num % 10;

    if (digitCount % 2 == 0) {
        middleDigit += num / 10 % 10;
        middleDigit /= 2;
    } 

    return middleDigit;
}

void sortAscending(int * const arr, float * const midDigitArr, const std::size_t size) {
    sortByMiddleDigitOuterLoop(arr, midDigitArr, size);
}

void sortByMiddleDigitOuterLoop(int * const arr, float * const midDigitArr, std::size_t size) {
    bool didSwapHappen { false };

    sortByMiddleDigitInnerLoop(arr, midDigitArr, size, didSwapHappen);
    
    if (didSwapHappen) {
        sortByMiddleDigitOuterLoop(arr, midDigitArr, size - 1);
    }
}

void sortByMiddleDigitInnerLoop(int * const arr, float * const midDigitArr, const std::size_t size, bool &didSwapHappen, std::size_t i) {
    if (i == size - 1) {
        return;
    }

    if (*(midDigitArr + i) > *(midDigitArr + i + 1)) {
        std::swap(*(arr + i), *(arr + i + 1));
        std::swap(*(midDigitArr+ i), *(midDigitArr + i + 1));
        didSwapHappen = true;
    }

    sortByMiddleDigitInnerLoop(arr, midDigitArr, size, didSwapHappen, i + 1);
}