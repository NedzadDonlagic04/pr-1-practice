#ifndef UTILS_HPP
#define UTILS_HPP

#include"./memory.hpp"
#include"./constants.hpp"

#include<cmath>
#include<optional>
#include<memory>

namespace utils {
    std::size_t getDigitCount(const int); 
    std::size_t getDigitCount(const unsigned int);

    void repeatCharacter(const char, const int);

    void drawLineBorder(const int);

    void printFormatedMemoryLine(const char * const, const char * const, const int);
    void printFormatedMemoryLine(const memory::AddressType, const int, const int);

    void clearBuffer();
    void clearTerminalANSI();

    void handleSizeInput(std::size_t &);

    void handleNumInput(int &, const char * const, const std::optional<int> = std::nullopt);
    void handleNumInput(memory::AddressType &, const char * const, const std::optional<int> = std::nullopt);

    void handleMemoryLinesInput(memory::Memory &);

    [[nodiscard]] std::unique_ptr<char[]> substr(const char * const, const std::size_t, const std::size_t);

    [[nodiscard]] constexpr std::size_t strlen(const char * const str) {
        std::size_t i = 0;

        while (str[i] != '\0') {
            i++;
        }

        return i;
    }

    [[nodiscard]] constexpr std::size_t getShortestInstructionLen(const char (*strings)[constants::BUFFER_SIZE], const std::size_t size) {
        std::size_t shortestStrLen { 0 };

        for (std::size_t i = 1; i < size; i++) {
            shortestStrLen = std::min(shortestStrLen, strlen(strings[i])); 
        }

        return shortestStrLen;
    }
}

#endif