#include"./../includes/utility.hpp"

#include<iostream>
#include<cmath>
#include<iomanip>

namespace util {
    void handleInput(int &num) {
        do {
            std::cout<<"Enter a number: ";
            std::cin>>num;

            if (num < 0) {
                std::cout<<"Invalid input\nNumber has to be equal to or bigger than 0\n\n";
            }
        } while(num < 0);
    }

    int getNumberOfDigits(const int num) {
        return std::log10(num) + 1;
    }

    int sortNumberDesc(int num) {
        const int ARR_SIZE { 10 };
        int digits[ARR_SIZE] {};

        while (num) {
            digits[num % 10]++;
            num /= 10;
        }

        for (int i = ARR_SIZE - 1; i >= 0; i--) {
            for (int ii = 0; ii < digits[i]; ii++) {
                num = num * 10 + i;
            }
        }
        
        return num;
    }

    int reverseNum(int num) {
        int reversedNum {0};

        while (num) {
            reversedNum = reversedNum * 10 + num % 10;
            num /= 10;
        }

        return reversedNum;
    }

    void addTrailing0s(int &num, const int intendedSize) {
        const int currentSize { getNumberOfDigits(num) };

        if (currentSize < intendedSize) {
            num *= std::pow(10, intendedSize - currentSize);
        }
    }

    void formattedOutput(const int originalNumSize, int num, const int startOfCycle) {
        num = sortNumberDesc(num);
        addTrailing0s(num, originalNumSize);
        const int reversedNum { reverseNum(num) };
        const int result { num - reversedNum };

        std::cout<<std::setw(originalNumSize)<<num;
        std::cout<<" - ";
        std::cout<<std::setw(originalNumSize)<<reversedNum<<" = ";
        
        // Turn the text red
        if (result == startOfCycle) {
            std::cout<<"\033[31m";
        }

        std::cout<<std::setw(originalNumSize)<<result<<'\n';
        // Reset to black text
        std::cout<<"\033[39m";
    }
}