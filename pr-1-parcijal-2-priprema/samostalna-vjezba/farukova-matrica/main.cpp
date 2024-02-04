// g++ main.cpp ./src/utility.cpp -o run
#include<iostream>

#include"./includes/utility.hpp"

int main() {
    int matrix[utils::MATRIX_SIZE][utils::MATRIX_SIZE] {};    

    utils::enterMatrix(matrix);
    utils::printMatrix(matrix);

    return 0;
}