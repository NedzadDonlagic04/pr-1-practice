#include<iostream>
#include<limits>
#include<optional>
#include<cstring>
#include<memory>
#include<iomanip>

constexpr std::size_t IME_I_PREZIME_SIZE { 200 };
constexpr std::size_t POZICIJA_SIZE { 2 };
constexpr std::size_t BUFFER_SIZE { 4096 };

constexpr char VALIDNE_POZICIJE[][POZICIJA_SIZE] {
    "N",
    "O",
    "V"
};

struct fudbaler {
    int ID {};
    char *ime_i_prezime {};
    char *pozicija {}; 
    // prihvatiti samo slova N, O i V (napad, vezni i odbrana)
    int *broj_golova{};

    fudbaler();
    ~fudbaler();

    void enterInfo();
    void printInfo() const;

    [[nodiscard]] const char * getPozicija() const;
    [[nodiscard]] int getBrojGolova() const;

    [[nodiscard]] static const char * getFullNameOfPozicija(const char * const);
    [[nodiscard]] static bool isValidPozicija(const char * const);
    static void printValidPozicije();
};

struct Average {
    int counter {};
    int sum {};

    Average();
    void addToSum(const int);
    [[nodiscard]] float getAverage() const;
};

using WritableFudbaleri = fudbaler*;
using WritableKlubovi = WritableFudbaleri*;

using ReadOnlyFudbaleri = const fudbaler * const;
using ReadOnlyKlubovi = ReadOnlyFudbaleri * const;

void clearBuffer();
void printBreakLine();
void printErrorMsg(const char * const);
void enterSize(std::size_t &, const char * const);

void enterNum(int &, const char * const, const std::optional<int> = std::nullopt, const std::optional<int> = std::nullopt);
void enterText(char *, const std::size_t, const char * const);
void enterPozicija(char *, const char * const);

void allocateFudbaleri(WritableFudbaleri &, const std::size_t);
void allocateKlubovi(WritableKlubovi &, const std::size_t, const std::size_t);

void deallocateFudbaleri(WritableFudbaleri);
void deallocateKlubovi(WritableKlubovi &, const std::size_t);

void enterFudbaleriArray(WritableFudbaleri, const std::size_t);
void enterKluboviMatrix(WritableKlubovi, const std::size_t, const std::size_t);

void enterFudbaleriArray(WritableFudbaleri, const std::size_t);
void enterKluboviMatrix(WritableKlubovi, const std::size_t, const std::size_t);

void printFudbaleriArray(ReadOnlyFudbaleri, const std::size_t);
void printKluboviMatrix(ReadOnlyKlubovi, const std::size_t, const std::size_t);

void printAveragePerPosition4EachKlub(ReadOnlyKlubovi, const std::size_t, const std::size_t);

[[nodiscard]] float getAverage4FudbaleriByPosition(ReadOnlyFudbaleri, const std::size_t, const char *);
[[nodiscard]] std::size_t getKluboviWithBestPositionAverage(ReadOnlyKlubovi, const std::size_t, const std::size_t, const char *);

int main() {
    std::size_t rows {}, cols {};
    WritableKlubovi klubovi {};

    enterSize(rows, "Unesi duzine redova: ");
    enterSize(cols, "Unesi duzine kolona: ");

    allocateKlubovi(klubovi, rows, cols);

    enterKluboviMatrix(klubovi, rows, cols);
    printKluboviMatrix(klubovi, rows, cols);
    printAveragePerPosition4EachKlub(klubovi, rows, cols);

    const std::unique_ptr<char[]> pozicija { new char[POZICIJA_SIZE] };

    clearBuffer();
    enterPozicija(pozicija.get(), "Unesi poziciju za provjeru: ");

    std::size_t bestKlubForEnteredType { getKluboviWithBestPositionAverage(klubovi, rows, cols, pozicija.get()) };

    std::cout<<"Klubovi sa najboljim prosjekom plate za fudbalera pozicije ";
    std::cout<<std::quoted(fudbaler::getFullNameOfPozicija(pozicija.get()));
    std::cout<<" je klub u redu broj "<<bestKlubForEnteredType + 1<<'\n';

    deallocateKlubovi(klubovi, rows);

    return 0;
}


fudbaler::fudbaler() {
    this->ime_i_prezime = new char[IME_I_PREZIME_SIZE] {};
    this->pozicija = new char[POZICIJA_SIZE] {};
    this->broj_golova = new int {};
}

fudbaler::~fudbaler() {
    delete[] this->ime_i_prezime;
    delete[] this->pozicija;
    delete this->broj_golova;
}

void fudbaler::enterInfo() {
    enterNum(this->ID, "Unesite ID fudbalera: ");
    clearBuffer();

    enterText(this->ime_i_prezime, IME_I_PREZIME_SIZE, "Unesite ime i prezime fudbalera: ");
    enterPozicija(this->pozicija, "Unesite poziciju fudbalera: ");

    enterNum(*this->broj_golova, "Unesite broj golova fudbalera: ", 0);
}

void fudbaler::printInfo() const {
    std::cout<<"ID: "<<this->ID<<'\n';
    std::cout<<"Ime i prezime: "<<this->ime_i_prezime<<'\n';
    std::cout<<"Pozicija: "<<this->getFullNameOfPozicija(this->pozicija)<<'\n';
    std::cout<<"Broj golova: "<<*this->broj_golova<<'\n';
}

const char * fudbaler::getPozicija() const {
    return this->pozicija;
}

int fudbaler::getBrojGolova() const {
    return *this->broj_golova;
}

const char * fudbaler::getFullNameOfPozicija(const char * const pozicija){
    if (std::strcmp(pozicija, "N") == 0) {
        return "Napad";
    } else if (std::strcmp(pozicija, "O") == 0) {
        return "Odbrana";
    } else if (std::strcmp(pozicija, "V") == 0) {
        return "Vezni";
    }
    return "";
}

bool fudbaler::isValidPozicija(const char * const pozicija) {
    for (const auto VALIDNA_POZICIJA : VALIDNE_POZICIJE) {
        if (std::strcmp(pozicija, VALIDNA_POZICIJA) == 0) {
            return true;
        }
    }

    return false;
}

void fudbaler::printValidPozicije() {
    std::cout<<"Validne pozicije su: ";
    for (std::size_t i = 0; i < std::size(VALIDNE_POZICIJE); i++) {
        std::cout<<VALIDNE_POZICIJE[i];

        if (i + 1 != std::size(VALIDNE_POZICIJE)) {
            std::cout<<", ";
        }
    }
    std::cout<<std::endl;
}


Average::Average() : sum(0), counter(0) {}

void Average::addToSum(const int num) {
    this->sum += num;
    this->counter++;
}

float Average::getAverage() const {
    if (!this->sum) {
        return 0;
    }

    return static_cast<float>(this->sum) / this->counter;
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

void enterSize(std::size_t &size, const char * const outputText) {
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
            printErrorMsg("Duzina treba biti u intervalu [2, 1000]\n");
            clearBuffer();
            repeatLoop = true;
        }
         
    } while(repeatLoop);
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

void enterPozicija(char *pozicija, const char * const outputText) {
    do {
        fudbaler::printValidPozicije();
        enterText(pozicija, POZICIJA_SIZE, outputText);

        if (!fudbaler::isValidPozicija(pozicija)) {
            printErrorMsg("Nevalidan pozicija fudbalera\n");
        }
    } while(!fudbaler::isValidPozicija(pozicija));
}

void allocateFudbaleri(WritableFudbaleri &fudbalerTemp, const std::size_t cols) {
    fudbalerTemp = new fudbaler[cols];
}

void allocateKlubovi(WritableKlubovi &klubovi, const std::size_t rows, const std::size_t cols) {
    klubovi = new fudbaler*[rows];

    for (std::size_t i = 0; i < rows; i++) {
        allocateFudbaleri(*(klubovi + i), cols);
    }
}

void deallocateFudbaleri(WritableFudbaleri fudbalerTemp) {
    delete[] fudbalerTemp;
}

void deallocateKlubovi(WritableKlubovi &klubovi, const std::size_t rows) {
    for (std::size_t i = 0; i < rows; i++) {
        deallocateFudbaleri(*(klubovi + i));
    }

    delete[] klubovi;
    klubovi = nullptr;
}

void enterFudbaleriArray(WritableFudbaleri fudbaleri, const std::size_t size) {
    for (std::size_t i = 0; i < size; i++) {
        std::cout<<"Unos podataka fudbalera "<<i + 1<<'\n';
        (fudbaleri + i)->enterInfo();

        if (i + 1 != size) {
            std::cout<<std::endl;
        }
    }
}

void enterKluboviMatrix(WritableKlubovi klubovi, const std::size_t rows, const std::size_t cols) {
    for (std::size_t i = 0; i < rows; i++) {
        printBreakLine();
        std::cout<<"Unesi podatke "<<i + 1<<". kluba:\n";
        enterFudbaleriArray(*(klubovi + i), cols);
        printBreakLine();
    }
}

void printFudbaleriArray(ReadOnlyFudbaleri fudbaleri, const std::size_t size) {
    for (std::size_t i = 0; i < size; i++) {
        std::cout<<"Ispis podataka fudbalera "<<i + 1<<'\n';
        (fudbaleri + i)->printInfo();

        if (i + 1 != size) {
            std::cout<<std::endl;
        }
    }
}

void printKluboviMatrix(ReadOnlyKlubovi klubovi, const std::size_t rows, const std::size_t cols) {
    for (std::size_t i = 0; i < rows; i++) {
        printBreakLine();
        std::cout<<"Ispis podataka "<<i + 1<<". kluba:\n";
        printFudbaleriArray(*(klubovi + i), cols);
        printBreakLine();
    }
}

void printAveragePerPosition4EachKlub(ReadOnlyKlubovi klubovi, const std::size_t rows, const std::size_t cols) {
    for (std::size_t i = 0; i < rows; i++) {
        Average avgN {};
        Average avgO {};
        Average avgV {};

        for (std::size_t ii = 0; ii < cols; ii++) {
            const char* pozicija { (*(klubovi + i) + ii)->getPozicija() };
            const int plata { (*(klubovi + i) + ii)->getBrojGolova() };

            if (std::strcmp(pozicija, "N") == 0) {
                avgN.addToSum(plata);
            } else if (std::strcmp(pozicija, "O") == 0) {
                avgO.addToSum(plata);
            } else if (std::strcmp(pozicija, "V") == 0) {
                avgV.addToSum(plata);
            }
        }

        printBreakLine();
        std::cout<<"Za klubove "<<i + 1<<". prosjecni golovi po poziciju su:\n";
        std::cout<<fudbaler::getFullNameOfPozicija("N")<<" - "<<avgN.getAverage()<<std::endl;
        std::cout<<fudbaler::getFullNameOfPozicija("O")<<" - "<<avgO.getAverage()<<std::endl;
        std::cout<<fudbaler::getFullNameOfPozicija("V")<<" - "<<avgV.getAverage()<<std::endl;
        printBreakLine();
    }
}

float getAverage4FudbaleriByPosition(ReadOnlyFudbaleri fudbaleri, const std::size_t size, const char *wantedPozicija) {
    Average avg {};

    for (std::size_t i = 0; i < size; i++) {
        const char* pozicija { (fudbaleri + i)->getPozicija() };
        const int plata { (fudbaleri + i)->getBrojGolova() };

        if (std::strcmp(pozicija, wantedPozicija) == 0) {
            avg.addToSum(plata);
        }
    }

    return avg.getAverage();
}

std::size_t getKluboviWithBestPositionAverage(ReadOnlyKlubovi klubovi, const std::size_t rows, const std::size_t cols, const char *pozicija) {
    std::size_t bestKlubIndex { 0 };
    float bestKlubAvg { getAverage4FudbaleriByPosition(*(klubovi + bestKlubIndex), cols, pozicija) };
    float tempAvg {};

    for (std::size_t i = 1; i < rows; i++) {
        tempAvg = getAverage4FudbaleriByPosition(*(klubovi + i), cols, pozicija);

        if (bestKlubAvg < tempAvg) {
            bestKlubIndex = i;
            bestKlubAvg = tempAvg;
        }
    }

    return bestKlubIndex;
}