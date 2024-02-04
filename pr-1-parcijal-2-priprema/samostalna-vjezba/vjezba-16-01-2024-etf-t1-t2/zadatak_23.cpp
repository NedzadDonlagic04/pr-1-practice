/*
    Sorta useful sites for this one
    https://www.wolframalpha.com/input?i=Intersection+of+%5B%2F%2Fmath%3Ay%3D3.1x%2B5.2%2F%2F%5D+and+%5B%2F%2Fmath%3Ay%3D2.0x%2B1.0%2F%2F%5D
    https://www.desmos.com/calculator
*/

#include<iostream>
#include<limits>
#include<optional>

void clearBuffer();
void enterPoints(float &, float &, float &, float &, const char * const);
void printTypeOfLines(const float, const float, const float, const float);

[[nodiscard]] float roundTo1Decimal(const float);
[[nodiscard]] float getXIntersectSpot(const float, const float, const float, const float);
[[nodiscard]] float getYIntersectSpot(const float, const float, const float);

int main() {
    float a1 {}, a2 {}, b1 {}, b2 {};

    enterPoints(a1, b1, a2, b2, "Unesite a1, b1, a2, b2: ");
    printTypeOfLines(a1, b1, a2, b2);

    return 0;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterPoints(float &a1, float &b1, float &a2, float &b2, const char * const outputText) {
    do {
        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
        }

        std::cout<<outputText;
        std::cin>>a1>>b1>>a2>>b2;
    } while(std::cin.fail());
}

void printTypeOfLines(const float a1, const float b1, const float a2, const float b2) {
    if (a1 == a2 && b1 == b2) {
        std::cout<<"Poklapaju se\n";
    } else if (a1 == a2) {
        std::cout<<"Paralelne su\n";
    } else {
        const float x { roundTo1Decimal(getXIntersectSpot(a1, b1, a2, b2)) };

        const float y { roundTo1Decimal(getYIntersectSpot(a1, b1, x)) };

        std::cout<<"Prave se sijeku u tacci ("<<x<<", "<<y<<")\n";
    }
}

float roundTo1Decimal(const float num) {
    return static_cast<int>(num * 10) / 10.0f;
}

float getXIntersectSpot(const float a1, const float b1, const float a2, const float b2) {
    return (-(b1 - b2)) / (a1 - a2);
}

float getYIntersectSpot(const float a1, const float b1, const float x) {
    return a1 * x + b1;
}