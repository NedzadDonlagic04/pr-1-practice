#include<iostream>
#include<limits>
#include<cstring>
#include<optional>

constexpr std::size_t BUFFER_SIZE { 256 };

struct vozilo {
    char *markaVozila {};
    char *brojSasije {};
    char *tipVozila {};     // dozvoliti unos samo vrijednost "A", "B" ili "C"
    float *potrosnja_goriva_po_km {};

    vozilo();
    ~vozilo();

    [[nodiscard]] static bool isValidTipVozila(const char *);

    void printVoziloInfo() const;
    void freeFudbalerInfo();

    void setVoziloInfo(char * const, char * const, char * const, float *);

    [[nodiscard]] float getPotrosnjaGorivaPoKm() const;
    [[nodiscard]] const char *getTipVozila() const;
};

void clearBuffer();
void printBreakLine();
void enterSize(std::size_t &, const char *);

void printErrorMsg(const char * const);
void enterText(char *, const std::size_t, const char * const);
void enterNum(float &, const char * const, const std::optional<int> = std::nullopt, const std::optional<int> = std::nullopt);

using ReadOnlyVozila = const vozilo * const;
using WritableVozila = vozilo *;
using ReadOnlyFirme = ReadOnlyVozila * const;
using WritableFirme = WritableVozila *;

void allocateFirme(WritableFirme&, const std::size_t, const std::size_t);
void deallocateFirme(WritableFirme&, const std::size_t);

void printFirmeInfo(ReadOnlyFirme, const std::size_t, const std::size_t);

void enterFirmaInfo(ReadOnlyFirme, const std::size_t, const std::size_t);
void enterFirmeInfo(WritableFirme, const std::size_t, const std::size_t);

[[nodiscard]] float getSumOfAllPotrosnjaGorivaPoKmFromFirm(ReadOnlyVozila, const std::size_t);
[[nodiscard]] ReadOnlyVozila findBestOrWorstFirmByPotrosnjaGoriva(ReadOnlyFirme, const std::size_t, const std::size_t, const bool = false);
void printAveragePotrosnjaGorivaForTypeC(ReadOnlyFirme, const std::size_t, const std::size_t);

void printSpecificVozilaInfo(ReadOnlyVozila, const std::size_t, const char *);

int main() {
    std::size_t rows {}, cols {};

    enterSize(rows, "Unesi duzinu redova: ");
    enterSize(cols, "Unesi duzinu kolona: ");

    WritableFirme firme {};

    allocateFirme(firme, rows, cols);

    enterFirmeInfo(firme, rows, cols);
    printFirmeInfo(firme, rows, cols);

    ReadOnlyVozila mostUsedFuel { findBestOrWorstFirmByPotrosnjaGoriva(firme, rows, cols) };
    printSpecificVozilaInfo(mostUsedFuel, cols, "Najveca potrosnja goriva po km ide firmi:\n");

    printAveragePotrosnjaGorivaForTypeC(firme, rows, cols);

    deallocateFirme(firme, rows);

    return 0;
}

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

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printBreakLine() {
    std::cout<<"------------------------------------\n";
}

void printErrorMsg(const char * const errorMsg) {
    std::cout<<"\033[31m";
    std::cout<<errorMsg;
    std::cout<<"\033[39m";
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

void enterNum(float &num, const char * const outputText, const std::optional<int> min, const std::optional<int> max) {
    bool repeatLoop {};
    char errorMsg[BUFFER_SIZE];

    do {
        repeatLoop = false; 

        std::cout<<outputText;
        std::cin>>num;

        if (std::cin.fail()) {
            printErrorMsg("Nevalidan unos\n");
            clearBuffer();
            repeatLoop = true;
        } else if (min && num < min.value()) {
            std::sprintf(errorMsg, "Unos ne moze biti manji od %d\n", min.value());
            printErrorMsg(errorMsg);
            clearBuffer();
            repeatLoop = true;
        } else if (max && num > max.value()) {
            std::sprintf(errorMsg, "Unos ne moze biti veci od %d\n", max.value());
            printErrorMsg(errorMsg);
            clearBuffer();
            repeatLoop = true;
        }
    } while(repeatLoop);

    clearBuffer();
}

void allocateFirme(WritableFirme &firme, const std::size_t rows, const std::size_t cols) {
    firme = new WritableVozila[rows];

    for (std::size_t i = 0; i < rows; i++) {
        *(firme + i) = new vozilo[cols];
    }
}

void deallocateFirme(WritableFirme &firme, const std::size_t rows) {
    for (std::size_t i = 0; i < rows; i++) {
        delete[] *(firme + i);
    }

    delete[] firme;
    firme = nullptr;
}

void printFirmeInfo(ReadOnlyFirme firme, const std::size_t rows, const std::size_t cols) {
    for (std::size_t i = 0; i < rows; i++) {
        printBreakLine();
        std::cout<<"Ispis podataka "<<i + 1<<". firme\n";
        for (std::size_t ii = 0; ii < cols; ii++) {
            (*(firme + i) + ii)->printVoziloInfo();
            
            if (ii + 1 != cols) {
                std::cout<<std::endl;
            }
        }
        printBreakLine();
    } 
}

void enterFirmaInfo(WritableVozila vozila, const std::size_t size) {
    constexpr std::size_t MAX_BUFFER_SIZE { 256 };

    char *markaVozila {};
    char *brojSasije {};
    char *tipVozila {};     
    float *potrosnja_goriva_po_km {};

    for (std::size_t i = 0; i < size; i++) {
        std::cout<<"Unesi podatke za "<<i + 1<<". vozilo\n";

        markaVozila = new char[MAX_BUFFER_SIZE] {};
        brojSasije = new char[MAX_BUFFER_SIZE] {};
        tipVozila = new char[MAX_BUFFER_SIZE] {};
        potrosnja_goriva_po_km = new float {};

        enterText(markaVozila, MAX_BUFFER_SIZE, "Unesi marku vozila: ");
        enterText(brojSasije, MAX_BUFFER_SIZE, "Unesi broj sasije: ");
            
        do {
            enterText(tipVozila, MAX_BUFFER_SIZE, "Unesi tip vozila: ");

            if (!vozilo::isValidTipVozila(tipVozila)) {
                std::cout<<"Tip vozila moze biti samo 'A', 'B' ili 'C'!\n";
            }
        } while(!vozilo::isValidTipVozila(tipVozila));

        enterNum(*potrosnja_goriva_po_km, "Unesi potrosnju goriva po km: ", 0);

        (vozila + i)->setVoziloInfo(markaVozila, brojSasije, tipVozila, potrosnja_goriva_po_km);
            
        if (i + 1 != size) {
            std::cout<<std::endl;
        }
    }
}

void enterFirmeInfo(WritableFirme firme, const std::size_t rows, const std::size_t cols) {
    constexpr std::size_t MAX_BUFFER_SIZE { 256 };

    char *markaVozila {};
    char *brojSasije {};
    char *tipVozila {};     
    float *potrosnja_goriva_po_km {};

    for (std::size_t i = 0; i < rows; i++) {
        printBreakLine();
        
        std::cout<<"Unos podataka firme "<<i + 1<<'\n';
        enterFirmaInfo(*(firme + i), cols);

        printBreakLine();
    } 

    std::cout<<"\n\n";
}

float getSumOfAllPotrosnjaGorivaPoKmFromFirm(ReadOnlyVozila vozila, const std::size_t size) {
    float sum { 0.0f };

    for (std::size_t i = 0; i < size; i++) {
        sum += (vozila + i)->getPotrosnjaGorivaPoKm();
    }

    return sum;
}

ReadOnlyVozila findBestOrWorstFirmByPotrosnjaGoriva(ReadOnlyFirme firme, const std::size_t rows, const std::size_t cols, const bool findWorst) {
    std::size_t firmaIndex {};
    float potrosnjaGorivaPoKm { getSumOfAllPotrosnjaGorivaPoKmFromFirm(*(firme + firmaIndex), cols) }; 
    float tempPotrosnjaGorivaPoKm {}; 
    
    for (std::size_t i = 1; i < rows; i++) {
        tempPotrosnjaGorivaPoKm = getSumOfAllPotrosnjaGorivaPoKmFromFirm(*(firme + i), cols);

        if (findWorst && potrosnjaGorivaPoKm > tempPotrosnjaGorivaPoKm) {
            firmaIndex = i;
            potrosnjaGorivaPoKm = tempPotrosnjaGorivaPoKm;
        } else if (!findWorst && potrosnjaGorivaPoKm < tempPotrosnjaGorivaPoKm) {
            firmaIndex = i;
            potrosnjaGorivaPoKm = tempPotrosnjaGorivaPoKm;
        }
    }

    return *(firme + firmaIndex);
}

void printAveragePotrosnjaGorivaForTypeC(ReadOnlyFirme firme, const std::size_t rows, const std::size_t cols) {
    float potrosnjaGorivaPoKmC { 0.0f }; 
    int potrosnjaGorivaCountC { 0 };
    
    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t ii = 0; ii < cols; ii++) {
            if (strcmp((*(firme + i) + ii)->getTipVozila(), "C") == 0) {
                potrosnjaGorivaPoKmC += (*(firme + i) + ii)->getPotrosnjaGorivaPoKm();  
                potrosnjaGorivaCountC++;
            } 
                
        }
    }

    if (potrosnjaGorivaCountC) {
        potrosnjaGorivaPoKmC /= potrosnjaGorivaCountC;
    }

    std::cout<<"Prosjek potrosnje goriva za tip vozila 'C': "<<potrosnjaGorivaPoKmC<<std::endl;
}

void printSpecificVozilaInfo(ReadOnlyVozila vozila, const std::size_t size, const char *outputText) {
    printBreakLine();
    std::cout<<outputText;
    for (std::size_t i = 0; i < size; i++) {
        (vozila + i)->printVoziloInfo();
        std::cout<<std::endl;
    }
    printBreakLine();
}