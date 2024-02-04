#include<iostream>
#include<cstddef>
#include<limits>
#include<string.h>
#include<cmath>

constexpr std::size_t MAX_BUFFER_SIZE { 256 };

constexpr char VALIDNI_TIPOVI_PADAVINA[][MAX_BUFFER_SIZE] = {
    "kisa",
    "snijeg",
};

struct vremenska_prognoza {
    char *padavine {};              // dozvoliti unos rijeci npr. "kisa" ili "snijeg"
    float *temperatura {}; 
    float *vlaznost_vazduha {};

    vremenska_prognoza();
    ~vremenska_prognoza();

    static bool isValidPadavina(const char *);
    static void printValidPadavine();

    void printVremenskaPrognozaInfo() const;
    void freeVremenskaPrognozaInfo();

    void setPrognozaInfo(char * const, float * const, float * const);

    float getTemperatura() const;
};

vremenska_prognoza::vremenska_prognoza() {}

vremenska_prognoza::~vremenska_prognoza() {
    this->freeVremenskaPrognozaInfo();
}

bool vremenska_prognoza::isValidPadavina(const char *padavina) {
    for (const auto VALIDAN_TIP_PADAVINE : VALIDNI_TIPOVI_PADAVINA) {
        if (strcmp(padavina, VALIDAN_TIP_PADAVINE) == 0) {
            return true;
        } 
    }

    return false;
}

void vremenska_prognoza::printValidPadavine() {
    std::size_t size { std::size(VALIDNI_TIPOVI_PADAVINA) };

    for (std::size_t i = 0; i < size; i++) {
        std::cout<<"\""<<VALIDNI_TIPOVI_PADAVINA[i]<<"\"";
        if (i + 1 != size) {
            std::cout<<", ";
        }
    }
}

void vremenska_prognoza::printVremenskaPrognozaInfo() const {
    std::cout<<"Padavine: "<<this->padavine<<'\n';
    std::cout<<"Temperatura: "<<*this->temperatura<<'\n';
    std::cout<<"Vlaznost vazduha: "<<*this->vlaznost_vazduha<<'\n';
}

void vremenska_prognoza::freeVremenskaPrognozaInfo() {
    delete this->padavine;
    delete this->temperatura;
    delete this->vlaznost_vazduha;

    this->padavine = nullptr;
    this->temperatura = nullptr;
    this->vlaznost_vazduha = nullptr;
}

void vremenska_prognoza::setPrognozaInfo(char * const padavine, float * const temperatura, float * const vlaznost_vazduha) {
    this->padavine = padavine;
    this->temperatura = temperatura;
    this->vlaznost_vazduha = vlaznost_vazduha;
}

float vremenska_prognoza::getTemperatura() const {
    return *this->temperatura;
}

void printBreakLine();
void clearBuffer();
void enterSize(std::size_t &, const char *);

void handleCStringInput(char *, const std::size_t, const char *);
void handleNumberInput(float *, const char *, const int);
void handleNumberInput(float *, const char *);

// Types intended to be used only for reading
using ReadOnlyVremenskePrognoze = const vremenska_prognoza * const; 
using ReadOnlyMeterolozi = ReadOnlyVremenskePrognoze * const;

// Types intended to be used only for writing
using WritableVremenskePrognoze = vremenska_prognoza *;
using WritableMeterolozi = WritableVremenskePrognoze*;

void allocateVremenskePrognoze(WritableVremenskePrognoze &, const std::size_t);
void deallocateVremenskePrognoze(WritableVremenskePrognoze &);

void allocateMeterolozi(WritableMeterolozi &, const std::size_t, const std::size_t);
void deallocateMeterolozi(WritableMeterolozi &, const std::size_t);

void printVremenskePrognoze(ReadOnlyVremenskePrognoze, const std::size_t);
void printMeteorolozi(ReadOnlyMeterolozi, const std::size_t, const std::size_t);

void enterVremenskePrognoze(WritableVremenskePrognoze, const std::size_t);
void enterMeteorolozi(WritableMeterolozi, const std::size_t, const std::size_t);

float calcPrognozaPrecision(ReadOnlyVremenskePrognoze, ReadOnlyVremenskePrognoze, const std::size_t);
std::size_t findMostAccurateMeteolog(ReadOnlyMeterolozi, ReadOnlyVremenskePrognoze, const std::size_t, const std::size_t);

int main() {
    std::size_t rows {}, cols {};

    enterSize(rows, "Unesi duzinu redova: ");
    enterSize(cols, "Unesi duzinu kolona: ");

    WritableMeterolozi meteorolozi {};
    WritableVremenskePrognoze stvarneVremenskePrognoze {};

    allocateMeterolozi(meteorolozi, rows, cols);
    allocateVremenskePrognoze(stvarneVremenskePrognoze, cols);

    enterMeteorolozi(meteorolozi, rows, cols);
    std::cout<<"Unos stvarni vremenski prognoza\n";
    enterVremenskePrognoze(stvarneVremenskePrognoze, cols);

    printMeteorolozi(meteorolozi, rows, cols);

    printBreakLine();
    std::cout<<"Ispis stvarnih prognoza:\n";
    printVremenskePrognoze(stvarneVremenskePrognoze, cols);
    printBreakLine();

    std::size_t najpreciznijaPrognozaIndex { findMostAccurateMeteolog(meteorolozi, stvarneVremenskePrognoze, rows, cols) };

    printBreakLine();
    std::cout<<"Najpreciznija prognoza:\n";
    printVremenskePrognoze(*(meteorolozi + najpreciznijaPrognozaIndex), cols);
    printBreakLine();
    
    deallocateMeterolozi(meteorolozi, rows);
    deallocateVremenskePrognoze(stvarneVremenskePrognoze);

    return 0;
}

void printBreakLine() {
    std::cout<<"-----------------------------------------------\n";
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterSize(std::size_t &size, const char *outputText) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>size;

        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
            repeatLoop = true;
        } else if (size < 2 || size > 1000) {
            std::cout<<"Unos mora biti u intervalu [2, 1000]\n";
            repeatLoop = true;
        }
    } while (repeatLoop);

    clearBuffer();
}

void handleCStringInput(char *input, const std::size_t bufferSize, const char *outputText) {
    std::cout<<outputText;
    std::cin.getline(input, bufferSize);
}

void handleNumberInput(float *input, const char *outputText, const int min) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>*input;

        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
            repeatLoop = true;
        } else if (*input <= min) {
            std::cout<<"Unos treba biti veci od "<<min<<'\n';
            repeatLoop = true;
        }
    } while(repeatLoop);

    clearBuffer();
}

void handleNumberInput(float *input, const char *outputText) {
    do {
        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
        }

        std::cout<<outputText;
        std::cin>>*input;
    } while(std::cin.fail());

    clearBuffer();
}

void allocateVremenskePrognoze(WritableVremenskePrognoze &vremenskePrognoze, const std::size_t size) {
    vremenskePrognoze = new vremenska_prognoza[size] {};
}

void deallocateVremenskePrognoze(WritableVremenskePrognoze &vremenskePrognoze) {
    delete[] vremenskePrognoze;

    vremenskePrognoze = nullptr;
}

void allocateMeterolozi(WritableMeterolozi &meteorolozi, const std::size_t rows, const std::size_t cols) {
    meteorolozi = new vremenska_prognoza*[rows] {};

    for (std::size_t i = 0; i < rows; i++) {
        allocateVremenskePrognoze(*(meteorolozi + i), cols);
    }
}

void deallocateMeterolozi(WritableMeterolozi &meteorolozi, const std::size_t rows) {
    for (std::size_t i = 0; i < rows; i++) {
        deallocateVremenskePrognoze(*(meteorolozi + i));
    }

    delete[] meteorolozi;

    meteorolozi = nullptr;
}

void printVremenskePrognoze(ReadOnlyVremenskePrognoze vremenskePrognoze, const std::size_t size) {
    for (std::size_t i = 0; i < size; i++) {
        std::cout<<"Prognoza za "<<i + 1<<". dan\n";
        (vremenskePrognoze + i)->printVremenskaPrognozaInfo();
        if (i + 1 != size) {
            std::cout<<std::endl;
        }
    }

}

void printMeteorolozi(ReadOnlyMeterolozi meteorolozi, const std::size_t rows, const std::size_t cols) {
    printBreakLine();
    for (std::size_t i = 0; i < rows; i++) {
        std::cout<<"Ispis prognoza "<<i + 1<<". meterologa\n";
        printVremenskePrognoze(*(meteorolozi + i), cols);
        if (i + 1 != rows) {
            std::cout<<"\n\n";
        }
    } 
    printBreakLine();
}

void enterVremenskePrognoze(WritableVremenskePrognoze vremenskePrognoze, const std::size_t size) {            
    for (std::size_t i = 0; i < size; i++) {
        char *padavine { new char[MAX_BUFFER_SIZE] {} };
        float *temperatura { new float {} };
        float *vlaznost_vazduha { new float {} };
        
        std::cout<<"Unesi podatke za prognozu "<<i + 1<<". dana\n";
            
        do {
            handleCStringInput(padavine, MAX_BUFFER_SIZE, "Unesi padavinu: ");

            if (!vremenska_prognoza::isValidPadavina(padavine)) {
                std::cout<<"Padavina moze samo biti: ";
                vremenska_prognoza::printValidPadavine();
                std::cout<<std::endl;
            } 
        } while(!vremenska_prognoza::isValidPadavina(padavine));

        handleNumberInput(temperatura, "Unesi temperaturu: ");
        handleNumberInput(vlaznost_vazduha, "Unesi vlaznost vazduha: ", 0);

        (vremenskePrognoze + i)->setPrognozaInfo(padavine, temperatura, vlaznost_vazduha);
    }
}

void enterMeteorolozi(WritableMeterolozi meteorolozi, const std::size_t rows, const std::size_t cols) {
    for (std::size_t i = 0; i < rows; i++) {
        std::cout<<"Unos podataka "<<i + 1<<". meterologa\n";
        enterVremenskePrognoze(*(meteorolozi + i), cols); 
        std::cout<<std::endl;
    } 
}

float calcPrognozaPrecision(ReadOnlyVremenskePrognoze prognoza1, ReadOnlyVremenskePrognoze prognoza2, const std::size_t size) {
    float result { 0.0f }, diff {};

    for (std::size_t i = 0; i < size; i++) {
        diff = std::abs((prognoza1 + i)->getTemperatura() - (prognoza2 + i)->getTemperatura()); 
        result += diff;
    }

    return result;
}

std::size_t findMostAccurateMeteolog(ReadOnlyMeterolozi meteorolozi, ReadOnlyVremenskePrognoze stvarnaPrognoza, const std::size_t rows, const std::size_t cols) {
    std::size_t mostAccurateIndex { 0 };
    float mostAccuratePrognoza { calcPrognozaPrecision(*meteorolozi, stvarnaPrognoza, cols) };
    float tempPrognoza {};

    for (std::size_t i = 1; i < rows; i++) {
        tempPrognoza = calcPrognozaPrecision(*(meteorolozi + i), stvarnaPrognoza, cols);

        if (tempPrognoza < mostAccuratePrognoza) {
            mostAccuratePrognoza = tempPrognoza;
            mostAccurateIndex = i;
        }

        if (mostAccuratePrognoza == 0) {
            break;
        }
    }

    return mostAccurateIndex;
}