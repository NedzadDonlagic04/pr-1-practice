#include<iostream>
#include<limits>
#include<cstring>

constexpr std::size_t BUFFER_SIZE { 4096 };

void allocateTexts(char ** const, const std::size_t);
void deallocateText(char *&);
void deallocateTexts(char ** const, const std::size_t);

void clearBuffer();
void enterText(char *, const char * const);
void enterTexts(char ** const, const std::size_t);

char* concatTexts(const char * const * const, const std::size_t);
void kapitalizacijaTeksta(char *);

int main() {
    constexpr std::size_t SENTENCE_SIZE { 10 };
    char *tekstovi[SENTENCE_SIZE] {};

    allocateTexts(tekstovi, SENTENCE_SIZE);

    enterTexts(tekstovi, SENTENCE_SIZE);

    char *concatedTexts { concatTexts(tekstovi, SENTENCE_SIZE) };

    kapitalizacijaTeksta(concatedTexts);

    std::cout<<"Rezultat konkatenacije i kapitalizacije prvih slova svake rijece:\n";
    std::cout<<concatedTexts<<std::endl;

    deallocateText(concatedTexts);
    deallocateTexts(tekstovi, SENTENCE_SIZE);

    return 0;
}

void allocateTexts(char **texts, const std::size_t size) {
    for (std::size_t i = 0; i < size; i++) {
        texts[i] = new char[BUFFER_SIZE] {};
    }
}

void deallocateText(char *&text) {
    delete[] text;
    text = nullptr;
}

void deallocateTexts(char ** const texts, const std::size_t size) {
    for (std::size_t i = 0; i < size; i++) {
        delete[] texts[i];
        texts[i] = nullptr;
    }
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterText(char *text, const char * const outputText) {
    do {
        if (std::cin.fail()) {
            std::cout<<"Invalid input\n";
            clearBuffer();
        }

        std::cout<<outputText;
        std::cin.getline(text, BUFFER_SIZE);
    } while(std::cin.fail());
}

void enterTexts(char ** const texts, const std::size_t size) {
    char outputText[BUFFER_SIZE] {};

    for (std::size_t i = 0; i < size; i++) {
        std::sprintf(outputText, "Unesite tekst %lu: ", i + 1);

        enterText(texts[i], outputText);
    }
}

char* concatTexts(const char * const * const texts, const std::size_t size) {
    std::size_t newSize { 0 };

    for (std::size_t i = 0; i < size; i++) {
        newSize += std::strlen(texts[i]);
    } 

    newSize += size - 1;
    // Added spaces for in between every sentence

    char *newText { new char[newSize + 1] {} };
    std::size_t newTextIndex { 0 };

    for (std::size_t i = 0; i < size; i++) {
        for (std::size_t ii = 0; texts[i][ii] != '\0'; ii++) {
            newText[newTextIndex++] = texts[i][ii];
        }
        newText[newTextIndex++] = ' '; 
    }

    newText[newSize] = '\0';

    return newText;
}

void kapitalizacijaTeksta(char *text) {
    if (std::isalpha(text[0])) {
        text[0] = std::toupper(text[0]);
    }

    for (std::size_t i = 1; text[i] != '\0'; i++) {
        if (text[i - 1] == ' ' && std::isalpha(text[i])) {
            text[i] = std::toupper(text[i]);
        }
    }
}