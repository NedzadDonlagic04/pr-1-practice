#include<iostream>
#include<memory>
#include<cmath>

unsigned int countDigits(const int num) {
    if (num == 0) {
        return 1;
    }

    const bool isNeg { num < 0 };

    return std::log10(std::abs(num)) + 1 + isNeg;
}

std::unique_ptr<char[]> intToCharPtr(int num) {
    std::size_t strLen { countDigits(num) };

    std::unique_ptr<char[]> str { new char[strLen + 1] };
    str[strLen--] = '\0';
    str[strLen] = '0';

    if (num < 0) {
        str[0] = '-';
        num = std::abs(num);
    }

    while (num) {
        str[strLen--] = (num % 10) + '0';
        num /= 10;
    }

    return str;
}

float roundTo2Decimals(float num) {
    num = static_cast<int>(num * 100);

    if ((static_cast<int>(num) % 10) >= 5) {
        num++;
    }

    num /= 100;

    return num;
}

int main() {
    float num { 26.09999 };

    std::cout<<roundTo2Decimals(num)<<std::endl;

    return 0;
}