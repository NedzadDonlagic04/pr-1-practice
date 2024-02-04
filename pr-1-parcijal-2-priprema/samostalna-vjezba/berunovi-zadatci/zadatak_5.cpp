#include<iostream>
#include<limits>
#include<optional>

constexpr std::size_t BUFFER_SIZE { 4096 };

[[nodiscard]] std::size_t getIndex(const std::size_t, const std::size_t, const unsigned int);
void rotateArray(int **, int, int);

void clearBuffer();
void enterSize(std::size_t &, const char * const);
void enterNum(int &, const char * const, const std::optional<int> = std::nullopt, const std::optional<int> = std::nullopt);

void allocateArray(int **&, const std::size_t);
void deallocateArray(int **&, const std::size_t);

void enterArray(int **, const std::size_t);
void printArray(const int * const * const, const std::size_t, const char * const);

int main() {
    std::size_t size {};
    int **parray {};
    int rotateWindow {};

    enterSize(size, "Unesite velicinu dinamickog niza pokazivaca: ");

    allocateArray(parray, size);

    enterArray(parray, size);
    printArray(parray, size, "Ispis elemenata niza [PRIJE ROTACIJE]:\n");

    enterNum(rotateWindow, "Unesite velicinu rotacijskog prozora (broj skokova ulijevo): ", 1, size - 1);

    rotateArray(parray, size, rotateWindow);
    printArray(parray, size, "Ispis elemenata niza [POSLIJE ROTACIJE]:\n");

    deallocateArray(parray, size);

    return 0;
}

std::size_t getIndex(const std::size_t currentIndex, const std::size_t size, const unsigned int decrement) {
    std::ptrdiff_t index = currentIndex - decrement;

    if (index < 0) {
        index = size + index;
    }

    return index;
}

void rotateArray(int **parray, int size, int rotateWindow) {
    std::size_t currentIndex {};
    std::size_t sizeCopy = size;
    std::size_t finalIndex = (rotateWindow != 1 && size % rotateWindow == 0)? (size / rotateWindow) + 1 : size - 1;
    int temp {};

    for (std::size_t i = 0; i != size; ) {
        sizeCopy--;
        currentIndex = sizeCopy;
        temp = *parray[currentIndex];

        // Debug
        // std::cout<<"currentIndex = "<<currentIndex<<std::endl;

        do {
            currentIndex = getIndex(currentIndex, size, rotateWindow);
            // Debug
            // std::cout<<"currentIndex = "<<currentIndex<<std::endl;
            std::swap(temp, *parray[currentIndex]);
            i++;
        } while(currentIndex != sizeCopy);
    }
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterSize(std::size_t &size, const char * const outputText) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>size;

        if (std::cin.fail()) {
            std::cout<<"Invalid input\n";
            clearBuffer();
            repeatLoop = true;
        } else if (size < 2 || size > 1000) {
            std::cout<<"Unos treba biti u intervalu [2, 1000]\n";
            clearBuffer();
            repeatLoop = true;
        }
    } while(repeatLoop);
}

void enterNum(int &num, const char * const outputText, const std::optional<int> min, const std::optional<int> max) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>num;

        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            repeatLoop = true;
            clearBuffer();
        } else if (min && num < min.value()) {
            std::cout<<"Unos ne smije biti manji od "<<min.value()<<std::endl;
            repeatLoop = true;
            clearBuffer();
        } else if (max && num > max.value()) {
            std::cout<<"Unos ne smije biti veci od "<<max.value()<<std::endl;
            repeatLoop = true;
            clearBuffer();
        }
    } while(repeatLoop);
}

void allocateArray(int **&parray, const std::size_t rows) {
    parray = new int*[rows];

    for (std::size_t i = 0; i < rows; i++) {
        parray[i] = new int {};
    }
}

void deallocateArray(int **&parray, const std::size_t rows) {
    for (std::size_t i = 0; i < rows; i++) {
        delete parray[i];
    }

    delete[] parray;
}

void enterArray(int **parray, const std::size_t size) {
    char outputText[BUFFER_SIZE] {}; 

    for (std::size_t i = 0; i < size; i++) {
        std::sprintf(outputText, "Unesite element na lokaciju %lu: ", i);

        enterNum(*parray[i], outputText);
    }
}

void printArray(const int * const * const parray, const std::size_t size, const char * const outputText) {
    std::cout<<outputText;
    for (std::size_t i = 0; i < size; i++) {
        std::cout<<*parray[i]<<' ';
    }
    std::cout<<std::endl;
}