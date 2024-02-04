#include<iostream>
#include<cmath>
#include<limits>
#include<memory>

struct Degrees {
    unsigned int degrees {};
    unsigned int minutes {};
    unsigned int seconds {}; 

    Degrees() = default;
    Degrees(const float);

    [[nodiscard]] std::unique_ptr<char[]> getFormattedDegrees() const;
};

[[nodiscard]] unsigned int countDigits(const int);
std::unique_ptr<char[]> intToCharPtr(int);

[[nodiscard]] float roundTo2Decimals(float);

void clearBuffer();
void enterNum(float &, const char * const);

int main() {
    float userDegrees {};

    enterNum(userDegrees, "Unesite stepene: ");

    Degrees degrees(userDegrees);

    std::cout<<userDegrees<<" = "<<degrees.getFormattedDegrees().get()<<std::endl;

    return 0;
}

Degrees::Degrees(float degrees) {
    this->degrees = degrees;

    degrees -= this->degrees;
    degrees = roundTo2Decimals(degrees * 60);

    std::cout<<degrees<<std::endl;

    this->minutes = degrees; 

    degrees -= this->minutes;
    degrees = roundTo2Decimals(degrees * 60);

    std::cout<<degrees<<std::endl;

    this->seconds = degrees;
}

std::unique_ptr<char[]> Degrees::getFormattedDegrees() const {
    std::unique_ptr<char[]> formattedDegrees { new char[100] };

    std::sprintf(formattedDegrees.get(), "%u^ %u' %u''", this->degrees, this->minutes, this->seconds);

    return formattedDegrees;
}

unsigned int countDigits(const int num) {
    if (num < 0) {
        return 1;
    }

    const bool isNeg { num < 0 };

    return std::log10(std::abs(num)) + 1 + isNeg;
}

float roundTo2Decimals(float num) {
    num = static_cast<int>(num * 100);

    if ((static_cast<int>(num) % 10) >= 5) {
        num++;
    }

    num /= 100;

    return num;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterNum(float &num, const char * const outputText) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>num;

        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
            repeatLoop = true;
        } else if (num < 0) {
            std::cout<<"Unos ne moze biti broj manji od 0\n";
            clearBuffer();
            repeatLoop = true;
        }
    } while(repeatLoop);
}