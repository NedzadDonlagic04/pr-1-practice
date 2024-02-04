#include<iostream>
#include<limits>
#include<iomanip>
#include<cstring>

constexpr std::size_t SENTENCE_SIZE { 200 };
constexpr std::size_t WORD_SIZE { 10 };

void clearBuffer();
void enterText(char *, const std::size_t, const char * const);

void cStrToLower(char *);

[[nodiscard]] char* replaceSingleWord(char * const, const char * const, const char * const);
[[nodiscard]] char* replaceEveryWordInSentence(char *, const char * const, const char * const);

int main() {
    char *recenica { new char[SENTENCE_SIZE] {} };
    char rijec[WORD_SIZE] {};
    char rijecZaZamjenu[] { "FIT" };

    enterText(recenica, SENTENCE_SIZE, "Unesite recenicu: ");    
    enterText(rijec, WORD_SIZE, "Unesite rijec: "); 

    std::cout<<"Nakon sto se zamjeni svaka instanca rijeci "<<std::quoted(rijec)<<" sa rijeci ";
    std::cout<<std::quoted(rijecZaZamjenu)<<" u recenici "<<std::quoted(recenica)<<std::endl;

    recenica = replaceEveryWordInSentence(recenica, rijec, rijecZaZamjenu);

    std::cout<<"Dobije se recenica: "<<std::quoted(recenica)<<std::endl;

    delete[] recenica;

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

void enterText(char *text, const std::size_t bufferSize, const char * const outputText) {
    do {
        if (std::cin.fail()) {
            printErrorMsg("Nevalidan unos\n");
            clearBuffer();
        }

        std::cout<<outputText;
        std::cin.getline(text, bufferSize);
    } while(std::cin.fail());
}

void cStrToLower(char *str) {
    for (std::size_t i = 0; str[i] != '\0'; i++) {
        str[i] = std::tolower(str[i]);
    }
}

char* replaceSingleWord(char * const sentence, const char * const wordToFind, const char * const wordToInsert) {
    std::size_t newStrSize { std::strlen(sentence) + 1 };

    const std::ptrdiff_t sizeDiff = std::strlen(wordToInsert) - std::strlen(wordToFind);

    if (sizeDiff > 0) {
        newStrSize += sizeDiff;
    }
    
    char *dest { new char[newStrSize] {} };
    char *temp {};

    std::strcpy(dest, sentence);

    if (!std::strlen(wordToFind) || !std::strlen(wordToInsert)) {
        return dest;
    }

    temp = std::strstr(dest, wordToFind);

    // Many debug lines below
    if (temp) {
        // std::cout<<temp<<std::endl;
        std::memmove(temp + std::strlen(wordToInsert), temp + std::strlen(wordToFind), std::strlen(temp + std::strlen(wordToFind)) + 1);
        // std::cout<<temp<<std::endl;
        std::strncpy(temp, wordToInsert, std::strlen(wordToInsert));
        // std::cout<<temp<<std::endl;
    }

    // std::cout<<dest<<std::endl<<std::endl;

    return dest;
}

char* replaceEveryWordInSentence(char *sentence, const char * const wordToFind, const char * const wordToInsert) {
    char *temp { nullptr }; 

    do {
        if (temp) {
            delete[] sentence;
            sentence = temp;
        }

        temp = replaceSingleWord(sentence, wordToFind, wordToInsert);
    } while(std::strcmp(sentence, temp) != 0);

    delete[] sentence; 

    return temp;
}
