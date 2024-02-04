#include<iostream>
#include<iomanip>
#include"./includes/utility.hpp"

int main() {
    int num {}, iterations {0};

    int usedSize {0}, fullSize {1};
    int *kaprekarRepetitions { new int[fullSize]{} };
    int repetitionIndex { -1 };

    util::handleInput(num);

    const int originalNum { num };
    const int originalNumSize { util::getNumberOfDigits(num) };

    while (repetitionIndex == -1) {
        num = util::sortNumberDesc(num);

        util::addTrailing0s(num, originalNumSize);

        num -= util::reverseNum(num);

        repetitionIndex = util::findValueInArr(kaprekarRepetitions, usedSize, num);

        util::pushBack(kaprekarRepetitions, usedSize, fullSize, num);

        iterations++;
    }

    util::formattedOutput(originalNumSize, originalNum, num);

    for (int i = 0; i < usedSize - 1; i++)
        util::formattedOutput(originalNumSize, kaprekarRepetitions[i], num);

    std::cout<<"Number of iterationss needed to reach kaprekar's constant / routine / cycle: "<<iterations - 1<<std::endl;

    delete[] kaprekarRepetitions;

    return 0;
}