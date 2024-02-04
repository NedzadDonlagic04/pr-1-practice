#pragma once

#ifndef UTILITY
#define UTILITY

namespace util {
    void handleInput(int &);
    int getNumberOfDigits(const int);
    int sortNumberDesc(int);
    void addTrailing0s(int &, const int);
    int reverseNum(int);
    void formattedOutput(const int, int, const int);
}

#endif