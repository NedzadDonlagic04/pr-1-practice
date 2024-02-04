#include<iostream>
#include<limits>

constexpr std::size_t ARR_SIZE { 10 };

[[nodiscard]] int sumOfDigits(int);
[[nodiscard]] bool isFibNum(const int);

void placeNumAtFirstNonFibIndex(int (&)[ARR_SIZE], const std::size_t);
void ubaci(int (&)[ARR_SIZE]);
[[nodiscard]] std::size_t izbaci(int (&)[ARR_SIZE]);
void ispisiNiz(int (&)[ARR_SIZE], const char * const);

void clearBuffer();
bool enterNum(int &);
void enterArray(int (&)[ARR_SIZE], const char * const);

int main() {
    int arr[ARR_SIZE] {};

    enterArray(arr, "Unesite niz od 10 brojeva: ");

    const std::size_t newSize { izbaci(arr) };

    ubaci(arr);
    ispisiNiz(arr, "Niz: ");

    return 0;
}

int sumOfDigits(int num) {
    int sum { 0 };

    while (num) {
        sum += (num % 10);
        num /= 10;
    }

    return sum;
}

bool isFibNum(const int num) {
    int a { 0 };
    int b { 1 };

    while (num >= a) {
        if (num == a || num == b) {
            return true;
        }

        a += b;
        b += a;
    }

    return false;
}

void placeNumAtFirstNonFibIndex(int (&arr)[ARR_SIZE], const std::size_t currentIndex) {
    for (std::size_t i = 0; i < currentIndex; i++) {
        if (isFibNum(arr[i])) {
            arr[i] = arr[currentIndex]; 
            arr[currentIndex] = 1;
            break;
        }
    }
}

void ubaci(int (&arr)[ARR_SIZE]) {
    for (std::ptrdiff_t i = ARR_SIZE / 2 - 1; i >= 0; i--) {
        arr[i * 2] = arr[i];
    }
    for (std::size_t i = 1; i < ARR_SIZE; i += 2) {
        arr[i] = sumOfDigits(arr[i - 1]);
    }
}

std::size_t izbaci(int (&arr)[ARR_SIZE]) {
    std::size_t thrownOutNums { 0 };

    for (std::size_t i = 0; i < ARR_SIZE; i++) {
        if (!isFibNum(arr[i])) {
            placeNumAtFirstNonFibIndex(arr, i);
            thrownOutNums++;
        }
    }

    return ARR_SIZE - thrownOutNums;
}

void ispisiNiz(int (&arr)[ARR_SIZE], const char * const outputText) {
    std::cout<<outputText;

    for (std::size_t i = 0; i < ARR_SIZE; i++) {
        std::cout<<arr[i]<<' ';
    }

    std::cout<<std::endl;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool enterNum(int &num) {
    std::cin>>num;

    if (std::cin.fail()) {
        std::cout<<"Nevalidan unos\n";
        clearBuffer();
        return false;
    }
    return true;    
}

void enterArray(int (&arr)[ARR_SIZE], const char * const outputText) {
    std::cout<<outputText;

    for (std::ptrdiff_t i = 0; i < std::size(arr); i++) {
        if (!enterNum(arr[i])) {
            i = -1;
            std::cout<<outputText;
        }
    }
}