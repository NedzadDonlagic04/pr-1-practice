#include<iostream>
#include<cstring>
#include<limits>
#include<iomanip>
#include<optional>
#include<random>

constexpr std::size_t BUFFER_SIZE { 256 };

struct Automobil {
    char *Naziv {}; // niz karaktera;
    char *Marka {}; // niz karaktera;
    char *Tip {}; // niz karaktera;
    int *godinaProizvodnje {};  // u rangu 2005 - 2022
    float *potrosnjaNaStoKm {};

    Automobil();
    ~Automobil();

    [[nodiscard]] char * getNaziv() const;
    [[nodiscard]] char * getMarka() const;
    [[nodiscard]] char * getTip() const;
    [[nodiscard]] int getGodinaProizvodnje() const;
    [[nodiscard]] float getPostrosnjaNaStoKm() const;
};

using WritableAutomobili = Automobil*;
using ReadOnlyAutomobili = const Automobil * const;
using WritableAutomobilFirme = WritableAutomobili*;
using ReadOnlyAutomobilFirme = ReadOnlyAutomobili * const;

void printBreakLine();
void clearBuffer();
void printErrorMsg(const char * const);
void enterSize(std::size_t &, const char *);

void enterNum(int &, const char * const, const std::optional<int> = std::nullopt, const std::optional<int> = std::nullopt);
void enterNum(float &, const char * const, const std::optional<int> = std::nullopt, const std::optional<int> = std::nullopt);
void enterText(char *, const std::size_t, const char * const);

void allocateAutomobilFirme(WritableAutomobilFirme&, const std::size_t, const std::size_t);
void deallocateAutomobilFirme(WritableAutomobilFirme&, const std::size_t);

void enterAutomobilInfo(Automobil * const);
void enterAutomobilFirme(WritableAutomobilFirme, const std::size_t, const std::size_t);

void printAutomobilInfo(const Automobil * const);
void printAutomobilFirme(ReadOnlyAutomobilFirme, const std::size_t, const std::size_t);

[[nodiscard]] float roundTo1Decimal(const float);
void generateAutomobilFirme(WritableAutomobilFirme, const std::size_t, const std::size_t);

[[nodiscard]] float getProsjekPotrosnjaNa100KmForFirm(ReadOnlyAutomobili, const std::size_t);
[[nodiscard]] std::size_t getIndexForFirmWithLowestAvgPotrosnjaNa100Km(ReadOnlyAutomobilFirme, const std::size_t, const std::size_t);

int main() {
    std::size_t rows {}, cols {};
    WritableAutomobilFirme automobilFirme {};

    enterSize(rows, "Unesite broj redova: ");
    enterSize(cols, "Unesite broj kolona: ");

    allocateAutomobilFirme(automobilFirme, rows, cols);

    // enterAutomobilFirme(automobilFirme, rows, cols);
    generateAutomobilFirme(automobilFirme, rows, cols);
    printAutomobilFirme(automobilFirme, rows, cols);

    const std::size_t lowestAvgIndex { getIndexForFirmWithLowestAvgPotrosnjaNa100Km(automobilFirme, rows, cols) };

    std::cout<<"Firma sa najmanjom potrosnjom goriva po 100km je firma u redu broj ";
    std::cout<<lowestAvgIndex + 1<<'\n';

    deallocateAutomobilFirme(automobilFirme, rows);

    return 0;
}

Automobil::Automobil() {
    this->Naziv = new char[BUFFER_SIZE] {};
    this->Marka = new char[BUFFER_SIZE] {};
    this->Tip = new char[BUFFER_SIZE] {};
    this->godinaProizvodnje = new int {};
    this->potrosnjaNaStoKm = new float {};
}

Automobil::~Automobil() {
    delete[] this->Naziv;
    delete[] this->Marka;
    delete[] this->Tip;
    delete this->godinaProizvodnje;
    delete this->potrosnjaNaStoKm;
}

char * Automobil::getNaziv() const {
    return this->Naziv;
}

char * Automobil::getMarka() const {
    return this->Marka;
}

char * Automobil::getTip() const {
    return this->Tip;
}

int Automobil::getGodinaProizvodnje() const {
    return *this->godinaProizvodnje;
}

float Automobil::getPostrosnjaNaStoKm() const {
    return *this->potrosnjaNaStoKm;
}


void printBreakLine() {
    std::cout<<"------------------------------------\n";
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Be warned this one uses ANSI escape codes
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
            printErrorMsg("Nevalidan unos\n");
            clearBuffer();
            repeatLoop = true;
        } else if (size < 2 || size > 1000) {
            printErrorMsg("Unos mora biti u intervalu [2, 1000]\n");
            clearBuffer();
            repeatLoop = true;
        }
    } while (repeatLoop);

    clearBuffer();
}

void enterNum(int &num, const char * const outputText, const std::optional<int> min, const std::optional<int> max) {
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

void allocateAutomobilFirme(WritableAutomobilFirme& automobilFirme, const std::size_t rows, const std::size_t cols) {
    automobilFirme = new WritableAutomobili[rows] {};

    for (std::size_t i = 0; i < rows; i++) {
        *(automobilFirme + i) = new Automobil[cols] {};
    }
}

void deallocateAutomobilFirme(WritableAutomobilFirme& automobilFirme, const std::size_t rows) {
    for (std::size_t i = 0; i < rows; i++) {
        delete[] *(automobilFirme + i);
    }

    delete[] automobilFirme;
    automobilFirme = nullptr;
}

void enterAutomobilInfo(Automobil * const automobil) {
    enterText(automobil->Naziv, BUFFER_SIZE, "Unesi naziv automobila: ");
    enterText(automobil->Marka, BUFFER_SIZE, "Unesi makru automobila: ");
    enterText(automobil->Tip, BUFFER_SIZE, "Unesi tip automobila: ");
    enterNum(*automobil->godinaProizvodnje, "Unesi godinu proizvodnje: ", 0);
    enterNum(*automobil->potrosnjaNaStoKm, "Unesi potrosnju na 100km: ", 0);
    clearBuffer();
}

void enterAutomobilFirme(WritableAutomobilFirme automobilFirme, const std::size_t rows, const std::size_t cols) {
    for (std::size_t i = 0; i < rows; i++) {
        printBreakLine();
        std::cout<<"Unos podataka za "<<i + 1<<". firmu automobila\n"; 
        for (std::size_t ii = 0; ii < cols; ii++) {
            std::cout<<"Unos podataka za "<<ii + 1<<". automobil\n";

            enterAutomobilInfo(*(automobilFirme + i) + ii);

            if (ii + 1 != cols) {
                std::cout<<std::endl;
            }
        }
        printBreakLine();
    }
}

void printAutomobilInfo(const Automobil * const automobil) {
    std::cout<<"Naziv: "<<std::quoted(automobil->getNaziv())<<'\n';
    std::cout<<"Marka: "<<std::quoted(automobil->getMarka())<<'\n';
    std::cout<<"Tip: "<<std::quoted(automobil->getTip())<<'\n';
    std::cout<<"Godina proizvodnje: "<<automobil->getGodinaProizvodnje()<<'\n';
    std::cout<<"Potrosnja na 100km: "<<automobil->getPostrosnjaNaStoKm()<<'\n';
}

void printAutomobilFirme(ReadOnlyAutomobilFirme automobilFirme, const std::size_t rows, const std::size_t cols) {
    for (std::size_t i = 0; i < rows; i++) {
        printBreakLine();
        std::cout<<"Ispis podataka za "<<i + 1<<". firmu automobila\n"; 
        for (std::size_t ii = 0; ii < cols; ii++) {
            std::cout<<"Ispis podatak za "<<ii + 1<<". automobil\n";

            printAutomobilInfo(*(automobilFirme + i) + ii);

            if (ii + 1 != cols) {
                std::cout<<std::endl;
            }
        }
        printBreakLine();
    }
}

float roundTo1Decimal(const float num) {
    return std::round(num * 10) / 10;
}

void generateAutomobilFirme(WritableAutomobilFirme automobilFirme, const std::size_t rows, const std::size_t cols) {
    constexpr const char RAND_NAZIVI[][BUFFER_SIZE] {
        "Opel",
        "BMW",
        "Volkswagen",
        "Ford",
        "Toyota",
    };

    constexpr const char RAND_MARKE[][BUFFER_SIZE] {
        "Astra",
        "E46",
        "Passat",
        "F150",
        "RAV4",
    };

    constexpr const char RAND_TIPOVI[][BUFFER_SIZE] {
        "Hatchback",
        "Limousine",
        "Caravan",
        "Truck",
        "SUV",
    };

    std::random_device dev {};
    std::mt19937 rng { dev() };
    std::uniform_int_distribution<std::mt19937::result_type> nazivMarkaTipDist { 0, 4 };
    std::uniform_int_distribution<std::mt19937::result_type> godinaProizvodnjeDist { 2005, 2022 };
    // Source for the below distribution range: my roommate
    std::uniform_real_distribution<> potrosnjaNa100KmDist { 3.5, 20.0 };

    std::size_t randIndexNazivMarkaTip {};        
    
    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t ii = 0; ii < cols; ii++) {
            randIndexNazivMarkaTip = nazivMarkaTipDist(rng);

            std::strcpy((*(automobilFirme + i) + ii)->Naziv, RAND_NAZIVI[randIndexNazivMarkaTip]);
            std::strcpy((*(automobilFirme + i) + ii)->Marka, RAND_MARKE[randIndexNazivMarkaTip]);
            std::strcpy((*(automobilFirme + i) + ii)->Tip, RAND_TIPOVI[randIndexNazivMarkaTip]);
            *(*(automobilFirme + i) + ii)->godinaProizvodnje = godinaProizvodnjeDist(rng);
            *(*(automobilFirme + i) + ii)->potrosnjaNaStoKm = roundTo1Decimal(potrosnjaNa100KmDist(rng));
        }
    }
}

float getProsjekPotrosnjaNa100KmForFirm(ReadOnlyAutomobili automobili, const std::size_t size) {
    float sum { 0.0f };

    for (std::size_t i = 0; i < size; i++) {
        sum += automobili->getPostrosnjaNaStoKm();
    }

    return (sum)? sum / size : 0.0f;
}

std::size_t getIndexForFirmWithLowestAvgPotrosnjaNa100Km(ReadOnlyAutomobilFirme automobilFirme, const std::size_t rows, const std::size_t cols) {
    std::size_t lowestAvgIndex { 0 };
    float lowestAvg { getProsjekPotrosnjaNa100KmForFirm(*(automobilFirme + lowestAvgIndex), cols) };
    float tempAvg {};

    for (std::size_t i = 1; i < rows; i++) {
        tempAvg = getProsjekPotrosnjaNa100KmForFirm(*(automobilFirme + i), cols);

        if (tempAvg < lowestAvg) {
            lowestAvgIndex = i;
            lowestAvg = tempAvg;
        }

        if (lowestAvg == 0) {
            break;
        }
    }
    
    return lowestAvgIndex;
}