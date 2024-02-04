#include<iostream>
#include<limits>
#include<cstring>

constexpr std::size_t ARR_SIZE { 5 };

void clearBuffer();
void printErrorMsg(const char * const);

void enterCharOrNum(char &, const char * const);
void enterCharacters(char (&)[ARR_SIZE]);
void printCharacters(char (&)[ARR_SIZE]);

int main() {
    char characters[ARR_SIZE] {};
    
    enterCharacters(characters);
    printCharacters(characters);

    return 0;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printErrorMsg(const char * const errorMsg) {
    std::cout<<"\033[31m";
    std::cout<<errorMsg;
    std::cout<<"\033[39m";
}

void enterCharOrNum(char &alphaOrNum, const char * const outputText) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>alphaOrNum;

        if (std::cin.fail()) {
            printErrorMsg("Nevalidan unos\n");
            clearBuffer();
            repeatLoop = true;
        } else if (!std::isalnum(alphaOrNum)) {
            printErrorMsg("\nUnos mora biti slovo izmedu A i Z ili broj izmedu 0 i 9\n\n");
            clearBuffer();
            repeatLoop = true;
        }     
    } while(repeatLoop);
}

void enterCharacters(char (&characters)[ARR_SIZE]) {
    char previousNum { '0' - 1 };
    char previousChar { 'A' - 1 };

    std::size_t i { 0 };

    const char outpuText[] { "Unesite veliko slovo ili broj: " };

    while(i < ARR_SIZE) {
        enterCharOrNum(characters[i], outpuText);
        std::cout<<"\033[1F\033["<<std::strlen(outpuText) + 2<<"C";

        if (std::isdigit(characters[i]) && characters[i] > previousNum) {
            previousNum = characters[i];
            i++;
        } else if (std::isalpha(characters[i]) && characters[i] > previousChar)  {
            previousChar = characters[i];
            i++;
        } else {
            std::cout<<"(unos se ignorise)";
        }

        std::cout<<"\n\n";
    }
}

void printCharacters(char (&characters)[ARR_SIZE]) {
    std::cout<<"\n\nElementi niza: ";
    for (std::size_t i = 0; i < ARR_SIZE; i++) {
        std::cout<<characters[i]<<' ';
    }
    std::cout<<std::endl;
}