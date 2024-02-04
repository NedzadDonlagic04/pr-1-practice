#include"./../includes/utility.hpp"

#include<iostream>
#include<cmath>
#include<limits>

namespace utils {
    void createSpaces(const int spaceCount) {
        for (int i = 0; i < spaceCount; i++) {
            std::cout<<' ';
        }
    }

    void clearBuffer() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    bool enterNum(int &num) {
        std::cin>>num;

        if (std::cin.fail()) {
            clearBuffer();
            return false;
        } 
        return true;
    } 

    int countDigits(const int num) {
        bool isNegative { num < 0 };

        return std::log10(std::abs(num)) + 1 + isNegative;
    }

    int findLargestNumberDigitCount(const int (&matrix)[MATRIX_SIZE][MATRIX_SIZE], std::size_t size) {
        size = std::min(MATRIX_SIZE * MATRIX_SIZE, size);

        int digitCount {}, largestDigitCount {};

        for (std::size_t i = 0; i < size; i++) {
            digitCount = countDigits(matrix[i / MATRIX_SIZE][i % MATRIX_SIZE]);

            if (i == 0 || digitCount > largestDigitCount) {
                largestDigitCount = digitCount;
            }        
        }

        return largestDigitCount;
    }

    // ANSI code to clear the screen
    // https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
    void clearTerminal() {
        std::cout<<"\033[2J\033[H";
    }

    void printMatrix(const int (&matrix)[MATRIX_SIZE][MATRIX_SIZE]) {
        const int numberWidth { findLargestNumberDigitCount(matrix) };

        std::cout<<"Ispis matrice:\n";
        for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
            for (std::size_t ii = 0; ii < MATRIX_SIZE; ii++) {
                createSpaces(numberWidth + 1 - countDigits(matrix[i][ii]));
                std::cout<<matrix[i][ii];
            }
            std::cout<<std::endl;
        }
    }

    void printPartOfMatrix(const int (&matrix)[MATRIX_SIZE][MATRIX_SIZE], std::size_t size, const int numberWidth) {
        size = std::min(size, MATRIX_SIZE * MATRIX_SIZE);

        int currentNum {};

        for (std::size_t i = 0; i < size; i++) {
            currentNum = matrix[i / MATRIX_SIZE][i % MATRIX_SIZE]; 

            createSpaces(numberWidth + 1 - countDigits(currentNum));
            std::cout<<currentNum;

            if (i % MATRIX_SIZE == MATRIX_SIZE - 1) {
                std::cout<<std::endl;
            }
        }
    }

    void enterMatrix(int (&matrix)[MATRIX_SIZE][MATRIX_SIZE]) {
        int largestDigitCount {};
        bool inputSuccess {};

        std::cout<<"Enter matrix:\n";

        for (std::size_t i = 0; i < MATRIX_SIZE; i++) {
            for (std::size_t ii = 0; ii < MATRIX_SIZE; ii++) {
                std::cout<<' ';
                inputSuccess = enterNum(matrix[i][ii]);

                // If input isn't successful repeat input
                if (!inputSuccess) {
                    ii--;
                }
                
                largestDigitCount = findLargestNumberDigitCount(matrix, MATRIX_SIZE * i + ii + 1);

                clearTerminal();
                std::cout<<"Enter matrix:\n";
                printPartOfMatrix(matrix, MATRIX_SIZE * i + ii + 1, largestDigitCount);
            }
        }

        std::cout<<std::endl;
    }
}