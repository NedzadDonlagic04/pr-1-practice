#include<iostream>
#include<cstddef>
#include<limits>
#include<string.h>

constexpr std::size_t BUFFER_SIZE { 256 };

struct vozilo {
    char *markaVozila {};
    char *brojSasije {};
    char *tipVozila {};     // dozvoliti unos samo vrijednost "A", "B" ili "C"
    int *kubnihCM {};

    vozilo();
    ~vozilo();

    static bool isValidTipVozila(const char *);

    void printVoziloInfo() const;
    void freeFudbalerInfo();

    void setVoziloInfo(char * const, char * const, char * const, int *);

    int getKubnihCM() const;
    const char *getTipVozila() const;
};

vozilo::vozilo() : markaVozila(nullptr), brojSasije(nullptr), tipVozila(nullptr), kubnihCM(nullptr) {}
vozilo::~vozilo() {
    this->freeFudbalerInfo();
}
    
void vozilo::printVoziloInfo() const {
    std::cout<<"Marka vozila: "<<this->markaVozila<<'\n';
    std::cout<<"Broj sasija "<<this->brojSasije<<'\n';
    std::cout<<"Tip vozila: "<<this->tipVozila<<'\n';
    std::cout<<"Kubnih CM: "<<*this->kubnihCM<<'\n';
}

void vozilo::freeFudbalerInfo() {
    delete this->markaVozila;
    delete this->brojSasije;
    delete this->tipVozila;
    delete this->kubnihCM;

    this->markaVozila = nullptr;
    this->brojSasije = nullptr;
    this->tipVozila = nullptr;
    this->kubnihCM = nullptr;
}

bool vozilo::isValidTipVozila(const char *tipVozila) {
    constexpr char VALIDNI_TIPOVI_VOZILA[][2] = {
        "A",
        "B",
        "C" 
    };

    for (const auto VALIDAN_TIP_VOZILA : VALIDNI_TIPOVI_VOZILA) {
        if (strcmp(tipVozila, VALIDAN_TIP_VOZILA) == 0) {
            return true;
        } 
    }

    return false;
}

void vozilo::setVoziloInfo(char * const markaVozila, char * const brojSasije, char * const tipVozila, int *kubnihCM) {
    this->markaVozila = markaVozila;
    this->brojSasije = brojSasije;
    this->tipVozila = tipVozila;
    this->kubnihCM = kubnihCM;
}
    
int vozilo::getKubnihCM() const {
    return *this->kubnihCM;
}

const char * vozilo::getTipVozila() const {
    return this->tipVozila;
}

void clearBuffer();
void enterSize(std::size_t &, const char *);

void handleCStringInput(char *, const std::size_t, const char *);
void handleNumberInput(int *, const char *, const int);

using Firma = const vozilo * const;

void allocateVozila(vozilo **&, const std::size_t, const std::size_t);
void deallocateVozila(vozilo **, const std::size_t);

void printVoziloInfo(Firma* const, const std::size_t, const std::size_t);
void enterVozilaInfo(vozilo **, const std::size_t, const std::size_t);

Firma findBestOrWorstFirmByKubnihCM(Firma * const, const std::size_t, const std::size_t, const bool = false);
void printAverageKubnihCMForCarTypeAB(Firma* const, const std::size_t, const std::size_t);

void printSpecificFirmaInfo(Firma, const std::size_t, const char *);

int main() {
    std::size_t rows {}, cols {};

    enterSize(rows, "Unesi duzinu redova: ");
    enterSize(cols, "Unesi duzinu kolona: ");

    vozilo **vozila {};

    allocateVozila(vozila, rows, cols);

    enterVozilaInfo(vozila, rows, cols);
    printVoziloInfo(vozila, rows, cols);

    Firma bestFirmaByKubnihCM { findBestOrWorstFirmByKubnihCM(vozila, rows, cols) };
    printSpecificFirmaInfo(bestFirmaByKubnihCM, cols, "Najbolja firma po kubnih cm je:\n");

    printAverageKubnihCMForCarTypeAB(vozila, rows, cols);

    deallocateVozila(vozila, rows);

    return 0;
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

void handleNumberInput(int *input, const char *outputText, const int min) {
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

void allocateVozila(vozilo **&vozila, const std::size_t rows, const std::size_t cols) {
    vozila = new vozilo*[rows];

    for (std::size_t i = 0; i < rows; i++) {
        *(vozila + i) = new vozilo[cols];
    }
}

void deallocateVozila(vozilo **vozila, const std::size_t rows) {
    for (std::size_t i = 0; i < rows; i++) {
        delete[] *(vozila + i);
    }

    delete[] vozila;
}

void printVoziloInfo(Firma* const vozila, const std::size_t rows, const std::size_t cols) {
    for (std::size_t i = 0; i < rows; i++) {
        std::cout<<"Ispis podataka "<<i + 1<<". firme\n";
        for (std::size_t ii = 0; ii < cols; ii++) {
            (*(vozila + i) + ii)->printVoziloInfo();
            std::cout<<std::endl;
        }
        std::cout<<std::endl;
    } 
}

void enterVozilaInfo(vozilo **vozila, const std::size_t rows, const std::size_t cols) {
    constexpr std::size_t MAX_BUFFER_SIZE { 256 };

    char *markaVozila {};
    char *brojSasije {};
    char *tipVozila {};     
    int *kubnihCM {};

    for (std::size_t i = 0; i < rows; i++) {
        std::cout<<"Unos podataka firme "<<i + 1<<'\n';
        for (std::size_t ii = 0; ii < cols; ii++) {
            std::cout<<"Unesi podatke za "<<ii + 1<<". vozilo\n";

            markaVozila = new char[MAX_BUFFER_SIZE] {};
            brojSasije = new char[MAX_BUFFER_SIZE] {};
            tipVozila = new char[MAX_BUFFER_SIZE] {};
            kubnihCM = new int {};

            handleCStringInput(markaVozila, MAX_BUFFER_SIZE, "Unesi marku vozila: ");
            handleCStringInput(brojSasije, MAX_BUFFER_SIZE, "Unesi broj sasije: ");
            
            do {
                handleCStringInput(tipVozila, MAX_BUFFER_SIZE, "Unesi tip vozila: ");

                if (!vozilo::isValidTipVozila(tipVozila)) {
                    std::cout<<"Tip vozila moze biti samo 'A', 'B' ili 'C'!\n";
                }
            } while(!vozilo::isValidTipVozila(tipVozila));

            handleNumberInput(kubnihCM, "Unesi kubne CM: ", 0);

            (*(vozila + i) + ii)->setVoziloInfo(markaVozila, brojSasije, tipVozila, kubnihCM);
        }
        std::cout<<std::endl;
    } 
}

Firma findBestOrWorstFirmByKubnihCM(Firma* const vozila, const std::size_t rows, const std::size_t cols, const bool findWorst) {
    std::size_t firmaIndex {};
    float prosjekKubihCM {}, tempProsjekKubihCM {}; 
    
    for (std::size_t i = 0; i < rows; i++) {
        tempProsjekKubihCM = 0;

        for (std::size_t ii = 0; ii < cols; ii++) {
            tempProsjekKubihCM += (*(vozila + i) + ii)->getKubnihCM();
        }

        tempProsjekKubihCM /= cols;

        if (i == 0) {
            firmaIndex = i;
            prosjekKubihCM = tempProsjekKubihCM;
        } else if (findWorst && prosjekKubihCM > tempProsjekKubihCM) {
            firmaIndex = i;
            prosjekKubihCM = tempProsjekKubihCM;
        } else if (!findWorst && prosjekKubihCM < tempProsjekKubihCM) {
            firmaIndex = i;
            prosjekKubihCM = tempProsjekKubihCM;
        }
    }

    return *(vozila + firmaIndex);
}

void printAverageKubnihCMForCarTypeAB(Firma* const vozila, const std::size_t rows, const std::size_t cols) {
    float prosjekKubihCMA { 0.0f }, prosjekKubihCMB { 0.0f }; 
    int kubikCMCountA { 0 }, kubikCMCountB { 0 };
    
    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t ii = 0; ii < cols; ii++) {
            if (strcmp((*(vozila + i) + ii)->getTipVozila(), "A") == 0) {
                prosjekKubihCMA += (*(vozila + i) + ii)->getKubnihCM();
                kubikCMCountA++;
            } else if (strcmp((*(vozila + i) + ii)->getTipVozila(), "B") == 0) {
                prosjekKubihCMB += (*(vozila + i) + ii)->getKubnihCM();
                kubikCMCountB++;
            }
        }
    }

    if (kubikCMCountA) {
        prosjekKubihCMA /= kubikCMCountA;
    }

    if (kubikCMCountB) {
        prosjekKubihCMB /= kubikCMCountB;
    }

    std::cout<<"Prosjek po kubiku cm za tip vozila 'A': "<<prosjekKubihCMA<<std::endl;
    std::cout<<"Prosjek po kubiku cm za tip vozila 'B': "<<prosjekKubihCMB<<std::endl;
}

void printSpecificFirmaInfo(Firma vozila, const std::size_t size, const char *outputText) {
    std::cout<<outputText;
    for (std::size_t i = 0; i < size; i++) {
        (vozila + i)->printVoziloInfo();
    }
    std::cout<<std::endl;
}