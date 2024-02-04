#include<iostream>
#include<cstddef>
#include<limits>
#include<string.h>

constexpr std::size_t MAX_BUFFER_SIZE { 256 };

constexpr char VALIDNE_FUDBALER_POZICIJE[][2] = {
    "N",
    "O",
    "P",
};

struct fudbaler {
    int ID {};
    char *imePrezime {};
    char *pozicija {};      // prihvati samo slova N, O i V (napad, vezni i odbrana);
    int *broj_golova {};

    fudbaler() = default;
    ~fudbaler();

    [[nodiscard]] static bool isValidnaPozicija(const char *);
    static void printValidnePozicije();

    void freeFudbaler();
    void printFudbalerInfo() const;

    void setFudbalerInfo(const int, char * const, char * const, int * const);

    [[nodiscard]] const char* getPozicija() const;
    [[nodiscard]] int getBrojGolova() const;
    [[nodiscard]] bool arePozicijeSame(const char *) const;
};

fudbaler::~fudbaler() {
    this->freeFudbaler();
}

bool fudbaler::isValidnaPozicija(const char *pozicija) {
    for (const auto VALIDNA_POZICIJA : VALIDNE_FUDBALER_POZICIJE) {
        if (strcmp(pozicija, VALIDNA_POZICIJA) == 0) {
            return true;
        } 
    }

    return false;
}

void fudbaler::printValidnePozicije() {
    std::size_t size { std::size(VALIDNE_FUDBALER_POZICIJE) };

    for (std::size_t i = 0; i < size; i++) {
        std::cout<<"\""<<VALIDNE_FUDBALER_POZICIJE[i]<<"\"";
        if (i + 1 != size) {
            std::cout<<", ";
        }
    }
}

void fudbaler::freeFudbaler() {
    delete this->imePrezime;
    delete this->pozicija;
    delete this->broj_golova;

    this->imePrezime = nullptr;
    this->pozicija = nullptr;
    this->broj_golova = nullptr;
}

void fudbaler::printFudbalerInfo() const {
    std::cout<<"ID: "<<this->ID<<'\n';
    std::cout<<"Ime i prezime: "<<this->imePrezime<<'\n';
    std::cout<<"Pozicija: "<<this->pozicija<<'\n';
    std::cout<<"Broj golova: "<<*this->broj_golova<<'\n';
}

void fudbaler::setFudbalerInfo(const int ID, char * const imePrezime, char * const pozicija, int * const broj_golova) {
    this->ID = ID;
    this->imePrezime = imePrezime;
    this->pozicija = pozicija;
    this->broj_golova = broj_golova;
}

const char* fudbaler::getPozicija() const {
    return this->pozicija;
}

int fudbaler::getBrojGolova() const {
    return *this->broj_golova;
}

bool fudbaler::arePozicijeSame(const char *pozicija) const {
    return strcmp(this->pozicija, pozicija) == 0;
}

struct Average {
    int sum {};
    int count {};

    Average();

    void addToSum(const int);
    float getAverage() const;
};

Average::Average() : sum(0), count(0) {}

void Average::addToSum(const int num) {
    this->sum += num;
    this->count++;
}

float Average::getAverage() const {
    if (!this->count) return 0.0f;

    return static_cast<float>(this->sum) / this->count;
}

void printBreakLine();
void clearBuffer();
void enterSize(std::size_t &, const char * const);

void handleCStringInput(char *, const std::size_t, const char * const);
void handleNumberInput(int *, const char * const, const int);
void handleNumberInput(int &, const char * const);

// Types intended to be used only for reading
using ReadOnlyFudbaleri = const fudbaler * const; 
using ReadOnlyKlubovi = ReadOnlyFudbaleri * const;

// Types intended to be used only for writing
using WritableFudbaleri = fudbaler *;
using WritableKlubovi = WritableFudbaleri*;

void allocateFudbaleri(WritableFudbaleri &, const std::size_t);
void deallocateFudbaleri(WritableFudbaleri &);

void allocateKlubovi(WritableKlubovi &, const std::size_t, const std::size_t);
void deallocateKlubovi(WritableKlubovi &, const std::size_t);

void printFudbaleri(ReadOnlyFudbaleri, const std::size_t);
void printKlubovi(ReadOnlyKlubovi, const std::size_t, const std::size_t);

void enterFudbaleri(WritableFudbaleri, const std::size_t);
void enterKlubovi(WritableKlubovi, const std::size_t, const std::size_t);

void printPositionAverageForAllClubs(WritableKlubovi, const std::size_t, const std::size_t);

Average getProsjek(WritableFudbaleri, const std::size_t, const char *);
void printBestAverageForPositionFromAllClubs(WritableKlubovi, const std::size_t, const std::size_t);

int main() {
    std::size_t rows {}, cols {};

    enterSize(rows, "Unesi duzinu redova: ");
    enterSize(cols, "Unesi duzinu kolona: ");
    std::cout<<std::endl;

    WritableKlubovi klubovi {};

    allocateKlubovi(klubovi, rows, cols);

    enterKlubovi(klubovi, rows, cols);
    printKlubovi(klubovi, rows, cols);

    printPositionAverageForAllClubs(klubovi, rows, cols);
    printBestAverageForPositionFromAllClubs(klubovi, rows, cols);

    deallocateKlubovi(klubovi, rows);

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

void handlePozicijaInput(char *input, const std::size_t bufferSize, const char *text) {
    do {
        handleCStringInput(input, bufferSize, text);

        if (!fudbaler::isValidnaPozicija(input)) {
            std::cout<<"Pozicija moze samo biti: ";
            fudbaler::printValidnePozicije();
            std::cout<<std::endl;
        } 
    } while(!fudbaler::isValidnaPozicija(input));
}

void handleNumberInput(int &input, const char *outputText) {
    do {
        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
        }

        std::cout<<outputText;
        std::cin>>input;
    } while(std::cin.fail());

    clearBuffer();
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
        } else if (*input < min) {
            std::cout<<"Unos treba biti veci od "<<min<<"\n";
            repeatLoop = true;
        }
    } while(repeatLoop);

    clearBuffer();
}

void allocateFudbaleri(WritableFudbaleri &fudbaleri, const std::size_t size) {
    fudbaleri = new fudbaler[size];
}

void deallocateFudbaleri(WritableFudbaleri &fudbaleri) {
    delete[] fudbaleri;

    fudbaleri = nullptr;
}

void allocateKlubovi(WritableKlubovi &klubovi, const std::size_t rows, const std::size_t cols) {
    klubovi = new WritableFudbaleri[rows];

    for (std::size_t i = 0; i < rows; i++) {
        allocateFudbaleri(*(klubovi + i), cols);
    }
}

void deallocateKlubovi(WritableKlubovi &klubovi, const std::size_t rows) {
    for (std::size_t i = 0; i < rows; i++) {
        deallocateFudbaleri(*(klubovi + i));
    }

    delete[] klubovi;

    klubovi = nullptr;
}

void printFudbaleri(ReadOnlyFudbaleri fudbaleri, const std::size_t size) {
    for (std::size_t i = 0; i < size; i++) {
        std::cout<<"Informacije za "<<i + 1<<". fudbalera\n";
        (fudbaleri + i)->printFudbalerInfo();
        if (i + 1 != size) {
            std::cout<<std::endl;
        }
    }

}

void printKlubovi(ReadOnlyKlubovi klubovi, const std::size_t rows, const std::size_t cols) {
    printBreakLine();
    for (std::size_t i = 0; i < rows; i++) {
        std::cout<<"Ispis fudbalera "<<i + 1<<". kluba\n";
        printFudbaleri(*(klubovi + i), cols);
        if (i + 1 != rows) {
            std::cout<<"\n\n";
        }
    } 
    printBreakLine();
}

void enterFudbaleri(WritableFudbaleri fudbaleri, const std::size_t size) {            
    for (std::size_t i = 0; i < size; i++) {
        int ID {};
        char *imePrezime { new char[MAX_BUFFER_SIZE] {} };
        char *pozicija { new char[MAX_BUFFER_SIZE] {} };      
        int *broj_golova { new int {} };
        
        std::cout<<"Unesi podatke za "<<i + 1<<". fudbalera\n";
            
        handleNumberInput(ID, "Unesi ID: ");
        handleCStringInput(imePrezime, MAX_BUFFER_SIZE, "Unesi ime i prezime: ");
        handlePozicijaInput(pozicija, MAX_BUFFER_SIZE, "Unesi poziciju: ");
        handleNumberInput(broj_golova, "Unesi broj golova: ", 0);

        (fudbaleri + i)->setFudbalerInfo(ID, imePrezime, pozicija, broj_golova);
        
        std::cout<<std::endl;
    }
}

void enterKlubovi(WritableKlubovi klubovi, const std::size_t rows, const std::size_t cols) {
    for (std::size_t i = 0; i < rows; i++) {
        std::cout<<"Unos podataka "<<i + 1<<". kluba\n";
        enterFudbaleri(*(klubovi + i), cols); 
        std::cout<<std::endl;
    } 
}

void printPositionAverageForAllClubs(WritableKlubovi klubovi, const std::size_t rows, const std::size_t cols) {
    Average avgN {}, avgO {}, avgP {};

    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t ii = 0; ii < cols; ii++) {
            if ((*(klubovi + i) + ii)->arePozicijeSame("N")) {
                avgN.addToSum((*(klubovi + i) + ii)->getBrojGolova()); 
            } else if ((*(klubovi + i) + ii)->arePozicijeSame("O")) {
                avgO.addToSum((*(klubovi + i) + ii)->getBrojGolova()); 
            } else if ((*(klubovi + i) + ii)->arePozicijeSame("P")) {
                avgP.addToSum((*(klubovi + i) + ii)->getBrojGolova()); 
            }
        }
    }

    printBreakLine();
    std::cout<<"Prosjek za igrace u poziciji 'N': "<<avgN.getAverage()<<std::endl;
    std::cout<<"Prosjek za igrace u poziciji 'O': "<<avgO.getAverage()<<std::endl;
    std::cout<<"Prosjek za igrace u poziciji 'P': "<<avgP.getAverage()<<std::endl;
    printBreakLine();
}

Average getProsjek(WritableFudbaleri fudbaleri, const std::size_t size, const char *pozicija) {
    Average average {};

    for (std::size_t i = 0; i < size; i++) {
        if ((fudbaleri + i)->arePozicijeSame(pozicija)) {
            average.addToSum((fudbaleri + i)->getBrojGolova());
        }
    }

    return average;
}

void printBestAverageForPositionFromAllClubs(WritableKlubovi klubovi, const std::size_t rows, const std::size_t cols) {
    char *pozicija { new char[MAX_BUFFER_SIZE] {} };      
        
    handlePozicijaInput(pozicija, MAX_BUFFER_SIZE, "Unesi poziciju za najveci prosjek od svih klubova: ");

    std::size_t bestIndex { 0 };
    Average bestAverage { getProsjek(*(klubovi + bestIndex), cols, pozicija) };
    Average tempAverage {};

    for (std::size_t i = 0; i < rows; i++) {
        tempAverage = getProsjek(*(klubovi + i), cols, pozicija);        

        if (tempAverage.getAverage() > bestAverage.getAverage()) {
            bestAverage = tempAverage;
            bestIndex = i;
        }
    }

    printBreakLine();
    std::cout<<"Klub sa najboljim prosjekom za poziciju '"<<pozicija<<"' je klub "<<bestIndex + 1<<'\n';
    printFudbaleri(*(klubovi + bestIndex), cols);
    printBreakLine();
}