#include<iostream>
#include<cstring>
#include<limits>

constexpr std::size_t BUFFER_SIZE { 4096 };

void clearBuffer();
void enterSize(std::size_t &);

void allocateText(char *&);
void deallocateText(char *&);

void enterText(char * const);

[[nodiscard]] char* findBiggestWordInText(const char * const);

int main() {
    char *text{};
    char *longestWord {};

    allocateText(text);
    enterText(text);

    longestWord = findBiggestWordInText(text);

    std::cout<<"Najveca duzina je: "<<std::strlen(longestWord)<<std::endl;
    std::cout<<"Najveca rijec je: "<<longestWord<<std::endl;

    deallocateText(text);
    deallocateText(longestWord);

    return 0;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void allocateText(char *&text) {
    text = new char[BUFFER_SIZE];
}

void deallocateText(char *&text) {
    delete[] text;
}

void enterText(char * const text) {
    do {
        if (std::cin.fail()) {
            clearBuffer();
        }

        std::cout<<"Unesite tekst: ";
        std::cin.getline(text, BUFFER_SIZE);
    } while(std::cin.fail());
}

char* findBiggestWordInText(const char * const text) {
    std::size_t longestCount { 0 };
    std::size_t longestStart { 0 };
    std::size_t temp { 0 };

    for (std::size_t i = 0; i <= std::strlen(text); i++) {
        if (std::isalpha(text[i])) {
            temp++;
        } else {
            if (temp > longestCount) {
                longestCount = temp;
                longestStart = i - temp;
            }
            temp = 0;
        }

        // Used for debuggin
/*         std::cout<<"temp = "<<temp<<std::endl;
        std::cout<<"longestCount = "<<longestCount<<std::endl;
        std::cout<<"longestStart = "<<longestStart<<std::endl; */
    }

    char *longestText { new char[longestCount + 1] };

    for (std::size_t i = 0; i < longestCount; i++) {
        // Also used for debuggin
/*         std::cout<<text[i + longestStart]<<' '; */
        longestText[i] = text[i + longestStart];
    }

    longestText[longestCount] = '\0';

    return longestText;
}