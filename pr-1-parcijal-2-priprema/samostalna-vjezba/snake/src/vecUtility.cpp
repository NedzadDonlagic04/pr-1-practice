#include"./../includes/vecUtility.hpp"
#include<iostream>

namespace vecUtil {
    void arrPush(int **&matrix, int &size, int &capacity, const int *point) {
        if (size == capacity) {
            arrResize(matrix, size, capacity);
        }

        matrix[size] = new int[2];
        matrix[size][0] = point[0];
        matrix[size][1] = point[1];
        size++;
    }

    void arrPop(int &size) {
        size--;
    }

    void arrUnshift(int **&matrix, int &size, int &capacity, const int *point) {
        if (size == capacity) {
            arrResize(matrix, size, capacity);
        }

        moveArrElRightBy1(matrix, size);

        matrix[0] = new int[2];
        matrix[0][0] = point[0];
        matrix[0][1] = point[1];
        size++;
    }

    void moveArrElRightBy1(int **matrix, int &size) {
        matrix[size] = new int[2];
        for (int i = size; i > 0; i--) {
            matrix[i][0] = matrix[i - 1][0];
            matrix[i][1] = matrix[i - 1][1];
        }
    }

    void arrResize(int **&matrix, int &size, int &capacity) {
        capacity = capacity + (capacity >> 1);

        int **temp { new int*[capacity] };

        for (int i = 0; i < size; i++) {
            temp[i] = new int[2];
            temp[i][0] = matrix[i][0];
            temp[i][1] = matrix[i][1];
        }

        arrUninitialize(matrix, size);

        matrix = temp;
    }

    void arrUninitialize(int **matrix, const int size) {
        for (int i = 0; i < size; i++) {
            delete[] matrix[i];
        }

        delete[] matrix;
    }
}