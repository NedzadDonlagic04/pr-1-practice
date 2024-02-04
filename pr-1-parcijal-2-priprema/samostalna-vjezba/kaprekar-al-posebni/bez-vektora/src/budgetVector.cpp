#include"./../includes/utility.hpp"

namespace util {
    void allocateNewArr(int *&arr, int &usedSize, int &fullSize) {
        if (fullSize == 1) fullSize = 2;
        else fullSize = fullSize + (fullSize >> 1);

        int *temp = new int[fullSize];

        for (int i = 0; i < usedSize; i++) {
            temp[i] = arr[i];
        }

        delete[] arr;

        arr = temp;
    }

    void pushBack(int *&arr, int &usedSize, int &fullSize, const int val) {
        if (usedSize + 1 >= fullSize) {
            allocateNewArr(arr, usedSize, fullSize);     
        }
        
        arr[usedSize] = val;

        usedSize++;
    }

    int findValueInArr(int *p, const int size, const int val) {
        for (int i = 0; i < size; i++) {
            if (p[i] == val) {
                return i;
            }
        }

        return -1;
    }
}