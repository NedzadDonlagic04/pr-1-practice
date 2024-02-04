#include<iostream>
#include<cstddef>
#include<limits>
#include<string.h>

constexpr std::size_t BUFFER_SIZE { 256 };

struct vozilo {
    char *markaVozila {};
    char *brojSasije {};
    char *tipVozila {};     // dozvoliti unos samo vrijednost "A", "B" ili "C"
    float *potrosnja_goriva_po_km {};

    vozilo();
    ~vozilo();

    static bool isValidTipVozila(const char *);

    void printVoziloInfo() const;
    void freeFudbalerInfo();

    void setVoziloInfo(char * const, char * const, char * const, float *);

    float getPotrosnjaGorivaPoKm() const;
    const char *getTipVozila() const;
};

vozilo::vozilo() : markaVozila(nullptr), brojSasije(nullptr), tipVozila(nullptr), potrosnja_goriva_po_km(nullptr) {}
vozilo::~vozilo() {
    this->freeFudbalerInfo();
}
    
void vozilo::printVoziloInfo() const {
    std::cout<<"Marka vozila: "<<this->markaVozila<<'\n';
    std::cout<<"Broj sasija "<<this->brojSasije<<'\n';
    std::cout<<"Tip vozila: "<<this->tipVozila<<'\n';
    std::cout<<"Potrosnja goriva po km: "<<*this->potrosnja_goriva_po_km<<'\n';
}

void vozilo::freeFudbalerInfo() {
    delete this->markaVozila;
    delete this->brojSasije;
    delete this->tipVozila;
    delete this->potrosnja_goriva_po_km;

    this->markaVozila = nullptr;
    this->brojSasije = nullptr;
    this->tipVozila = nullptr;
    this->potrosnja_goriva_po_km = nullptr;
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

void vozilo::setVoziloInfo(char * const markaVozila, char * const brojSasije, char * const tipVozila, float *potrosnja_goriva_po_km) {
    this->markaVozila = markaVozila;
    this->brojSasije = brojSasije;
    this->tipVozila = tipVozila;
    this->potrosnja_goriva_po_km = potrosnja_goriva_po_km;
}
    
float vozilo::getPotrosnjaGorivaPoKm() const {
    return *this->potrosnja_goriva_po_km;
}

const char * vozilo::getTipVozila() const {
    return this->tipVozila;
}

void clearBuffer();
void enterSize(std::size_t &, const char *);

void handleCStringInput(char *, const std::size_t, const char *);
void handleNumberInput(float *, const char *, const int);

using Firma = const vozilo * const;

void allocateVozila(vozilo **&, const std::size_t, const std::size_t);
void deallocateVozila(vozilo **, const std::size_t);

void printVoziloInfo(Firma* const, const std::size_t, const std::size_t);
void enterVozilaInfo(vozilo **, const std::size_t, const std::size_t);

Firma findBestOrWorstFirmByPotrosnjaGoriva(Firma * const, const std::size_t, const std::size_t, const bool = false);
void printAveragePotrosnjaGorivaForTypeC(Firma* const, const std::size_t, const std::size_t);

void printSpecificFirmaInfo(Firma, const std::size_t, const char *);

int main() {
    std::size_t rows {}, cols {};

    enterSize(rows, "Unesi duzinu redova: ");
    enterSize(cols, "Unesi duzinu kolona: ");

    vozilo **vozila {};

    allocateVozila(vozila, rows, cols);

    enterVozilaInfo(vozila, rows, cols);
    printVoziloInfo(vozila, rows, cols);

    Firma mostUsedFuel { findBestOrWorstFirmByPotrosnjaGoriva(vozila, rows, cols) };
    printSpecificFirmaInfo(mostUsedFuel, cols, "Najveca potrosnja goriva po km ide firmi:\n");

    printAveragePotrosnjaGorivaForTypeC(vozila, rows, cols);

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
    float *potrosnja_goriva_po_km {};

    for (std::size_t i = 0; i < rows; i++) {
        std::cout<<"Unos podataka firme "<<i + 1<<'\n';
        for (std::size_t ii = 0; ii < cols; ii++) {
            std::cout<<"Unesi podatke za "<<ii + 1<<". vozilo\n";

            markaVozila = new char[MAX_BUFFER_SIZE] {};
            brojSasije = new char[MAX_BUFFER_SIZE] {};
            tipVozila = new char[MAX_BUFFER_SIZE] {};
            potrosnja_goriva_po_km = new float {};

            handleCStringInput(markaVozila, MAX_BUFFER_SIZE, "Unesi marku vozila: ");
            handleCStringInput(brojSasije, MAX_BUFFER_SIZE, "Unesi broj sasije: ");
            
            do {
                handleCStringInput(tipVozila, MAX_BUFFER_SIZE, "Unesi tip vozila: ");

                if (!vozilo::isValidTipVozila(tipVozila)) {
                    std::cout<<"Tip vozila moze biti samo 'A', 'B' ili 'C'!\n";
                }
            } while(!vozilo::isValidTipVozila(tipVozila));

            handleNumberInput(potrosnja_goriva_po_km, "Unesi potrosnju goriva po km: ", 0);

            (*(vozila + i) + ii)->setVoziloInfo(markaVozila, brojSasije, tipVozila, potrosnja_goriva_po_km);
        }
        std::cout<<std::endl;
    } 
}

Firma findBestOrWorstFirmByPotrosnjaGoriva(Firma* const vozila, const std::size_t rows, const std::size_t cols, const bool findWorst) {
    std::size_t firmaIndex {};
    float potrosnjaGorivaPoKm {}, tempPotrosnjaGorivaPoKm {}; 
    
    for (std::size_t i = 0; i < rows; i++) {
        tempPotrosnjaGorivaPoKm = 0;

        for (std::size_t ii = 0; ii < cols; ii++) {
            tempPotrosnjaGorivaPoKm += (*(vozila + i) + ii)->getPotrosnjaGorivaPoKm();
        }

        if (i == 0) {
            firmaIndex = i;
            potrosnjaGorivaPoKm = tempPotrosnjaGorivaPoKm;
        } else if (findWorst && potrosnjaGorivaPoKm > tempPotrosnjaGorivaPoKm) {
            firmaIndex = i;
            potrosnjaGorivaPoKm = tempPotrosnjaGorivaPoKm;
        } else if (!findWorst && potrosnjaGorivaPoKm < tempPotrosnjaGorivaPoKm) {
            firmaIndex = i;
            potrosnjaGorivaPoKm = tempPotrosnjaGorivaPoKm;
        }
    }

    return *(vozila + firmaIndex);
}

void printAveragePotrosnjaGorivaForTypeC(Firma* const vozila, const std::size_t rows, const std::size_t cols) {
    float potrosnjaGorivaPoKmC { 0.0f }; 
    int potrosnjaGorivaCountC { 0 };
    
    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t ii = 0; ii < cols; ii++) {
            if (strcmp((*(vozila + i) + ii)->getTipVozila(), "C") == 0) {
                potrosnjaGorivaPoKmC += (*(vozila + i) + ii)->getPotrosnjaGorivaPoKm();  
                potrosnjaGorivaCountC++;
            } 
                
        }
    }

    if (potrosnjaGorivaCountC) {
        std::cout<<potrosnjaGorivaPoKmC<<std::endl;
        potrosnjaGorivaPoKmC /= potrosnjaGorivaCountC;
    }

    std::cout<<"Prosjek potrosnje goriva za tip vozila 'C': "<<potrosnjaGorivaPoKmC<<std::endl;
}

void printSpecificFirmaInfo(Firma vozila, const std::size_t size, const char *outputText) {
    std::cout<<outputText;
    for (std::size_t i = 0; i < size; i++) {
        (vozila + i)->printVoziloInfo();
        std::cout<<std::endl;
    }
}