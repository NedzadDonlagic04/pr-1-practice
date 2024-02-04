/*
    Nisam siguran koji su minimumi i ogranicenja kod unosa tezine i visine
*/

#include<iostream>
#include<optional>
#include<limits>

void clearBuffer();

void enterGender(char &, const char * const);
void enterNum(float &, const char * const, const std::optional<float> = std::nullopt, const std::optional<float> = std::nullopt);

[[nodiscard]] float convertCMtoInch(const float);
[[nodiscard]] float getIdealWeight(const char, const float);

[[nodiscard]] const char* getAdviceMessage(const float, const float);

int main() {
    char gender {};
    float currentHeight {}, currentWeight {};

    enterGender(gender, "Unesite trenutni spol: ");
    enterNum(currentHeight, "Unesite trenutnu visinu (u cm): ", 50);
    enterNum(currentWeight, "Unesite trenutnu tezinu (u kg): ", 3);

    const float idealWeight { getIdealWeight(gender, convertCMtoInch(currentHeight)) };

    std::cout<<getAdviceMessage(currentWeight, idealWeight)<<'\n';
    std::cout<<"Trenutna tezina: "<<currentWeight<<"kg\n";
    std::cout<<"Idealna tezina: "<<idealWeight<<"kg\n";

    return 0;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterGender(char &gender, const char * const outputText) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>gender;

        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
            repeatLoop = true;
        } else if (std::towlower(gender) != 'z' && std::tolower(gender) != 'm') {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
            repeatLoop = true;
        }
    } while(repeatLoop);
}

void enterNum(float &num, const char * const outputText, const std::optional<float> min, const std::optional<float> max) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>num;

        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
            repeatLoop = true;
        } else if (min && num < min.value()) {
            std::cout<<"Uneseni broj treba biti veci od "<<min.value()<<std::endl;
            clearBuffer();
            repeatLoop = true;
        } else if (max && num > max.value()) {
            std::cout<<"Uneseni broj treba biti manji od "<<max.value()<<std::endl;
            clearBuffer();
            repeatLoop = true;
        }
    } while(repeatLoop);
}

float convertCMtoInch(const float height) {
    return height / 2.54;
}

float getIdealWeight(const char gender, const float height) {
    const float partOfIdealWeight { 2.3f * (height - 60) };

    return std::abs(((gender == 'z')? 45.5 : 50) + partOfIdealWeight);
}

const char* getAdviceMessage(const float weight, const float idealWeight) {
    const float differenceInWeight { idealWeight - weight };

    if (differenceInWeight > 3) {
        return "Potrebno je udebljati se da ostvarite idealnu tezinu";
    } else if (differenceInWeight < -3) {
        return "Potrebno je smrsati da ostvarite idealnu tezinu";
    }

    return "Idealna kilaza ostvarena";
}