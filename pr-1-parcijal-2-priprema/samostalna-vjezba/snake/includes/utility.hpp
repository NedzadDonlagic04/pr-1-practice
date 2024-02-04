#pragma once

#ifndef UTILITY
#define UTILITY

namespace utils {
    void clearTerminal();
    void waitForEnter();
    void sleep100ms();

    bool isKeyPressed();
    char getPressedKey();

    int generateRandomNum(const int, const int);
}

#endif