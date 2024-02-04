#include<iostream>

void printFirmInfo(const char, const double);
[[nodiscard]] const char* getCorrectObjectForm(const int);

int main() {
    double firmA { 10000000 }, firmB { 7000000 }, firmC { 5000000 };
    double rastPrihodaA { 2.05 / 100.0 }, rastPrihodaB { 2.8 / 100.0 }, rastPrihodaC { 4.3 / 100.0 };
    unsigned int counter { 0 };

    do {
        firmA += (firmA * rastPrihodaA);
        firmB += (firmB * rastPrihodaB);
        firmC += (firmC * rastPrihodaC);
        counter++;
        
        // Debuggin
/*         printFirmInfo('A', firmA);
        printFirmInfo('B', firmB);
        printFirmInfo('C', firmC); */
    } while(firmB <= firmA && firmC <= firmA);

    if (firmB > firmA && firmC > firmA) {
        std::cout<<"Obe firme su prevazisle firmu A u isto vrijeme\n";
    } else if (firmB > firmA) {
        std::cout<<"Firma B je prestigla firmu A prva\n";
    } else {
        std::cout<<"Firma C je prestigla firmu A prva\n";
    }
    std::cout<<"Za to je trebalo "<<counter<<" "<<getCorrectObjectForm(counter)<<'\n';

    printFirmInfo('A', firmA);
    printFirmInfo('B', firmB);
    printFirmInfo('C', firmC);

    return 0;
}

void printFirmInfo(const char firm, const double money) {
    std::cout<<"Firma "<<firm<<" prihodi: "<<static_cast<unsigned long long>(money)<<std::endl;
}

const char* getCorrectObjectForm(const int age) {
    if (age >= 10 && age <= 19) {
        return "godina";
    }

    const int lastDigit { age % 10 };

    if (lastDigit == 1) {
        return "godinu";
    } else if (lastDigit >= 2 && lastDigit <= 4) {
        return "godine";
    }

    return "godina";
}