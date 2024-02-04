#include<iostream>
#include<limits>

void clearBuffer();
void enterNum(int &, const char * const);

[[nodiscard]] const char* getCorrectObjectForm(const int);

int main() {
    int age {};

    enterNum(age, "Unesite godine: ");
    std::cout<<"Imate "<<age<<' '<<getCorrectObjectForm(age)<<std::endl;

    return 0;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterNum(int &num, const char * const outputText) {
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