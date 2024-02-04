#include<iostream>
#include<iomanip>
#include<cstring>

constexpr std::size_t SENTENCE_SIZE { 200 };
constexpr std::size_t WORD_SIZE { 5 };

void cStrToLower(char *);
[[nodiscard]] unsigned int getWordInstanceInSentence(const char *, char *);

int main() {
    char recenica[SENTENCE_SIZE] { "Most u Mostaru je Stari most a pored njega je jos jedan most." };
    char rijec[WORD_SIZE] { "most" };

    std::cout<<"Broj ponavljanja rijeci "<<std::quoted(rijec)<<" u recenici "<<std::quoted(recenica);

    unsigned counter { getWordInstanceInSentence(rijec, recenica) };

    std::cout<<" je "<<counter<<std::endl;

    return 0;
}

void cStrToLower(char *str) {
    for (std::size_t i = 0; str[i] != '\0'; i++) {
        str[i] = std::tolower(str[i]);
    }
}

unsigned int getWordInstanceInSentence(const char * word, char * sentence) {
    char tempBuffer[SENTENCE_SIZE] {};

    const char * token = std::strtok(sentence, " ");
    
    unsigned int counter { 0 };

    while (token) {
        std::strcpy(tempBuffer, token);
        cStrToLower(tempBuffer);
        if (std::strstr(tempBuffer, word)) {
            // Debuggin
            // std::cout<<token<<std::endl;
            counter++;
        }

        // Debuggin
        // std::cout<<std::quoted(token)<<std::endl;
        token = std::strtok(nullptr, " ");
    }

    return counter;
}