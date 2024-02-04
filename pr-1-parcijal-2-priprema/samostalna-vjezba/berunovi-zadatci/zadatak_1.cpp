#include<iostream>
#include<cstring>
#include<limits>

constexpr std::size_t SENTENCE_SIZE { 4096 };
constexpr std::size_t WORD_SIZE { 50 };

int count(char **, int, const char *);
bool isSingleWord(const char *);

void clearBuffer();
void enterSize(std::size_t &);

void allocateSentences(char **&, const std::size_t);
void deallocateSentences(char **&, const std::size_t);

void allocateWord(char *&);
void deallocateWord(char *&);

void enterSentence(char *, const std::size_t);
void enterSentences(char **, const std::size_t);

void removeTekstPadding(char *&);
void enterWord(char *&);

void printSentences(const char * const * const, const std::size_t);

int main() {
    std::size_t size {};
    char **sentences {};
    char *word {};

    enterSize(size);
    allocateSentences(sentences, size);
    allocateWord(word);

    enterSentences(sentences, size);

    printSentences(sentences, size);

    enterWord(word);

    std::cout<<"Broj tekstova u kojima mozemo pronaci rijec je "<<count(sentences, size, word)<<std::endl;

    deallocateWord(word);
    deallocateSentences(sentences, size);

    return 0;
}

int count(char **tekstovi, int brojTekstova, const char *rijec) {
    int counter { 0 };

    for (std::size_t i = 0; i < brojTekstova; i++) {
        if (std::strstr(tekstovi[i], rijec) != nullptr) {
            counter++;
        }
    }

    return counter;
}

bool isSingleWord(const char *tekst) {
    for (std::size_t i = 0; tekst[i] != '\0'; i++) {
        if (tekst[i] == ' ') {
            return false;
        }    
    }

    return true;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterSize(std::size_t &size) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<"Unesite broj tekstova: ";
        std::cin>>size;

        if (std::cin.fail()) {
            std::cout<<"Unos nije validan\n";
            clearBuffer();
            repeatLoop = true;
        } else if (size < 2 || size > 1000) {
            std::cout<<"Unos treba biti u intervalu [2, 1000]\n";
            clearBuffer();
            repeatLoop = true;
        }
    } while(repeatLoop);
}

void allocateSentences(char **&sentences, const std::size_t size) {
    sentences = new char* [size] {};

    for (std::size_t i = 0; i < size; i++) {
        sentences[i] = new char[SENTENCE_SIZE] {};
    }
}

void deallocateSentences(char **&sentences, const std::size_t size) {
    for (std::size_t i = 0; i < size; i++) {
        delete[] sentences[i];
    }

    delete[] sentences;
    sentences = nullptr;
}

void allocateWord(char *&word) {
    word = new char[WORD_SIZE];
}

void deallocateWord(char *&word) {
    delete[] word;
}

void enterSentence(char *sentence, const std::size_t index) {
    do {
        if (std::cin.fail()) {
            clearBuffer();
        }

        std::cout<<"Unesite tekst na indeksu "<<index<<": ";
        std::cin.getline(sentence, SENTENCE_SIZE);
    } while(std::cin.fail());
}

void enterSentences(char **sentences, const std::size_t size) {
    clearBuffer();

    for (std::size_t i = 0; i < size; i++) {
        enterSentence(sentences[i], i);
    }
}

void removeTekstPadding(char *&word) {
    std::size_t frontIndex { 0 };
    std::size_t endIndex { std::strlen(word) - 1 };
    std::size_t lenToReduceBy { 0 };

    while (word[frontIndex++] == ' ') {
        lenToReduceBy++;
    }
    std::cout<<std::endl;

    while (word[endIndex--] == ' ') {
        lenToReduceBy++;
    }

    std::size_t newSize { std::strlen(word) - lenToReduceBy };

    if (!newSize) {
        newSize = 1;
    }

    char *temp { new char[newSize + 1] };

    for (std::size_t i = 0; i < newSize; i++) {
        temp[i] = word[i + frontIndex - 1];
    }

    temp[newSize] = '\0';

    delete[] word;

    word = temp;
}

void enterWord(char *&word) {
    do {
        std::cout<<"Unesite jednu rijec: ";
        std::cin.getline(word, WORD_SIZE);
        
        removeTekstPadding(word);

        if (std::cin.fail()) {
            clearBuffer();
        }
    } while(!isSingleWord(word));
}

void printSentences(const char * const * const sentences, const std::size_t size) {
    for (std::size_t i = 0; i < size; i++) {
        std::cout<<"Tekst "<<i<<": "<<sentences[i]<<'\n';
    }
}