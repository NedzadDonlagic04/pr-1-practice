#include<iostream>
#include<limits>
#include<cstring>
#include<memory>
#include<iomanip>

constexpr std::size_t SENTENCE_SIZE { 200 };
constexpr std::size_t MAX_WORD_SIZE { 5 };

void clearBuffer();
void printBreakLine();
void printErrorMsg(const char * const);

void enterText(char *, const std::size_t, const char * const);

[[nodiscard]] std::size_t getSentenceSizeAfterRemoval(const char *, const std::size_t);
[[nodiscard]] std::unique_ptr<char[]> getCStringWithRemovedWordsLongerThan(const char *, const std::size_t);

int main() {
    char sentence[SENTENCE_SIZE] {};

    enterText(sentence, SENTENCE_SIZE, "Unesite recenicu: ");

    std::unique_ptr<char[]> newSentence { getCStringWithRemovedWordsLongerThan(sentence, MAX_WORD_SIZE) };

    std::cout<<"Stara recenica: "<<std::quoted(sentence)<<std::endl;
    std::cout<<"Nova recenica:  "<<std::quoted(newSentence.get())<<std::endl;

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

std::size_t getSentenceSizeAfterRemoval(const char * sentence, const std::size_t maxSizeToRemove) {
    std::size_t counter { 0 }, newSize { 0 };

    // Due to for loop condition the new size will
    // take into account the \0 character
    for (std::size_t i = 0; i < std::strlen(sentence) + 1; i++) {
        counter++;
        if (sentence[i] == ' ' || sentence[i] == '\0') {
            // std::cout<<counter<<std::endl;
            if (counter - 1 <= maxSizeToRemove) {
                newSize += counter;
            }
            counter = 0;
        }
    }

    return newSize;
}

std::unique_ptr<char[]> getCStringWithRemovedWordsLongerThan(const char * strToCut, const std::size_t maxSizeToRemove) {
    const std::size_t newSize { getSentenceSizeAfterRemoval(strToCut, maxSizeToRemove) };
    std::unique_ptr<char[]> newSentence { new char[newSize] {} };

    std::size_t counter { 0 }, newSentenceIt { 0 };

    for (std::size_t i = 0; i < std::strlen(strToCut) + 1; i++) {
        counter++;
        if (strToCut[i] == ' ' || strToCut[i] == '\0') {
            // std::cout<<counter<<std::endl;
            if (counter - 1 <= maxSizeToRemove) {
                std::memmove(newSentence.get() + newSentenceIt, strToCut + i - counter + 1, counter);
                newSentenceIt += counter;
            }
            counter = 0;
        }
    }

    return newSentence;
}