#include<iostream>
#include<iomanip>
#include"./includes/utility.hpp"

#include<vector>
#include<algorithm>

int main() {
    int num {}, iterations {0};

    std::vector<int> kaprekarResults {};

    util::handleInput(num);

    auto repetitionIndex { std::find(kaprekarResults.begin(), kaprekarResults.end(), num) };
    const int originalNum { num };
    const int originalNumSize { util::getNumberOfDigits(num) };

    while (1) {
        num = util::sortNumberDesc(num);

        util::addTrailing0s(num, originalNumSize);

        num -= util::reverseNum(num);

        repetitionIndex = std::find(kaprekarResults.begin(), kaprekarResults.end(), num); 

        if (repetitionIndex != kaprekarResults.end())
            break;

        kaprekarResults.push_back(num);

        iterations++;
    }

    util::formattedOutput(originalNumSize, originalNum, num);

    for (const auto &k : kaprekarResults)
        util::formattedOutput(originalNumSize, k, num);

    std::cout<<"Number of iterationss needed to reach kaprekar's constant / routine / cycle: "<<iterations - 1<<std::endl;

    return 0;
}