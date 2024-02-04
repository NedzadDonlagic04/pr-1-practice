#include<iostream>
#include<cstddef>
#include<iomanip>
#include<limits>
#include<cmath>

constexpr std::size_t MATRIX_SIZE { 10 };

void clearBuffer();

void handleMatrixInput(int &, const std::size_t, const std::size_t);
void enterMatrix(int (&)[MATRIX_SIZE][MATRIX_SIZE]);

void printMatrix(int (&)[MATRIX_SIZE][MATRIX_SIZE], const char *);

void switchRowsAndCols(int (&)[MATRIX_SIZE][MATRIX_SIZE]);
float aritmeticka(int (&)[MATRIX_SIZE][MATRIX_SIZE]);
void ispisiSimpaticneBrojeveIznadDijagonale(int (&)[MATRIX_SIZE][MATRIX_SIZE]);

bool prost_broj(const int);
int sumaCifara(int);
bool jelBrojSimpatican(const int num);

int main() {
    int matrix[MATRIX_SIZE][MATRIX_SIZE] {};

    enterMatrix(matrix);
    printMatrix(matrix, "Matrica nakon popunjenja:\n");

    switchRowsAndCols(matrix);
    printMatrix(matrix, "Matrica nakon zamjene redova i kolona:\n");

    const float artimetickaSredinaIspodSporedneDijagonale { aritmeticka(matrix) };
    std::cout<<"Aritmeticka sredina prostih brojeva ispod sporedne dijagonale: ";
    std::cout<<artimetickaSredinaIspodSporedneDijagonale<<std::endl;

    ispisiSimpaticneBrojeveIznadDijagonale(matrix);

    return 0;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printMatrix(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE], const char *outputText) {
    std::cout<<outputText;
    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        for (std::size_t ii = 0; ii < MATRIX_SIZE; ii++) {
            std::cout<<std::setw(3)<<matrix[i][ii]<<' ';
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

void handleMatrixInput(int &num, const std::size_t row, const std::size_t col) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<"Unos vrijednosti u element ["<<row<<", "<<col<<"]: ";
        std::cin>>num;

        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
            repeatLoop = true;
        } else if (std::abs(num) < 10 || std::abs(num) > 99) {
            std::cout<<"Unos treba biti dvocifren broj\n";
            repeatLoop = true;
        }
    } while (repeatLoop);
}

void enterMatrix(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE]) {
    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        for (std::size_t ii = 0; ii < MATRIX_SIZE; ii++) {
            handleMatrixInput(matrix[i][ii], i, ii);
        }
    }
}

void switchRowsAndCols(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE]) {
    for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
        for (std::size_t ii = i + 1; ii < MATRIX_SIZE; ii++) {
            // Used for debugging 
            // std::cout<<"["<<i<<", "<<ii<<"] <==> ["<<ii<<", "<<i<<"]\n";
            std::swap(matrix[i][ii], matrix[ii][i]);
        }
    }
}

float aritmeticka(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE]) {
    float average { 0.0f };
    int counter { 0 };

    for (std::ptrdiff_t i = MATRIX_SIZE - 1; i >= 1; i--) {
        for (std::size_t ii = MATRIX_SIZE - i; ii < MATRIX_SIZE; ii++) {
            if (prost_broj(matrix[i][ii])) {
                average += matrix[i][ii];
                counter++;
            }
        }
    }

    return (counter)? average / counter : 0.0f;
}

void ispisiSimpaticneBrojeveIznadDijagonale(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE]) {
    int counter { 0 };
    std::size_t initialColumn { 1 };

    std::cout<<"Simpaticni brojevi iznad dijagonale su: ";

    for (std::size_t i = 0; i < MATRIX_SIZE - 1; i++) {
        for (std::size_t ii = initialColumn; ii < MATRIX_SIZE; ii++) {
            if (jelBrojSimpatican(matrix[i][ii])) {
                std::cout<<matrix[i][ii]<<" ";
                counter++;
            }
        }
        initialColumn++;
    }

    if (!counter) {
        std::cout<<"Nema simpaticni brojeva!";
    }

    std::cout<<std::endl;
}

bool prost_broj(const int num) {
    if (num == 2 || num == 3) {
        return true;
    } else if (num <= 1 || num % 2 == 0 || num % 3 == 0) {
        return false;
    } 

    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) {
            return false;
        }
    }

    return true;
}

int sumaCifara(int num) {
    int sum { 0 };

    while (num) {
        sum += (num % 10);
        num /= 10;
    }

    return sum;
}

bool jelBrojSimpatican(const int num) {
    return sumaCifara(num * num) == sumaCifara(num) * sumaCifara(num);
}