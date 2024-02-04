#include<iostream>
#include<cstddef>
#include<cmath>
#include<limits>
#include<iomanip>

constexpr std::size_t MAX_BUFFER_SIZE { 256 };

struct uposlenik {
    char *ID {};
    char *imePrezime{};
    float *plata{}; 

    uposlenik() = default;
    ~uposlenik(); 

    void setUposlenikInfo(char * const, char * const, float * const);
    float getPlata() const;

    void printUposlenikInfo() const;
};

// Types intended to be used only for reading
using ReadOnlyOdjel = const uposlenik * const; 
using ReadOnlyFirma = ReadOnlyOdjel * const;

// Types intended to be used only for writing 
using WritableOdjel = uposlenik *;
using WritableFirma = WritableOdjel*;

void printBreakLine();
void clearBuffer();

void enterSize(std::size_t &, const char *);

void handleCStringInput(char *, const std::size_t, const char * const);
void handleNumberInput(float *, const char * const, const int);

void allocateOdjel(WritableOdjel &, const std::size_t);
void deallocateOdjel(WritableOdjel &);

void allocateFirma(WritableFirma &, const std::size_t, const std::size_t);
void deallocateFirma(WritableFirma &, const std::size_t);

void printOdjel(ReadOnlyOdjel, const std::size_t);
void printFirma(ReadOnlyFirma, const std::size_t, const std::size_t);

void enterOdjel(WritableOdjel, const std::size_t);
void enterFirma(WritableFirma, const std::size_t, const std::size_t);

float getProsjekPlateOdjela(ReadOnlyOdjel, const std::size_t);
void printBestProsjekPlata(ReadOnlyFirma, const std::size_t, const std::size_t);

int main() {
    std::size_t rows {}, cols {};

    enterSize(rows, "Unesi duzinu redova: ");
    enterSize(cols, "Unesi duzinu kolona: ");
    std::cout<<std::endl;

    WritableFirma firma {};

    allocateFirma(firma, rows, cols);

    enterFirma(firma, rows, cols);
    printFirma(firma, rows, cols);
    printBestProsjekPlata(firma, rows, cols);

    deallocateFirma(firma, rows);

    return 0;
}    

uposlenik::~uposlenik() {
    delete this->ID;
    delete this->imePrezime;
    delete this->plata;

    this->ID = nullptr;
    this->imePrezime = nullptr;
    this->plata = nullptr;
}
    
void uposlenik::setUposlenikInfo(char * const ID, char * const imePrezime, float * const plata) {
    this->ID = ID;
    this->imePrezime = imePrezime;
    this->plata = plata;
}

float uposlenik::getPlata() const {
    return *this->plata;
}

void uposlenik::printUposlenikInfo() const {
    std::cout<<"ID: "<<this->ID<<std::endl;
    std::cout<<"Ime i prezime: "<<this->imePrezime<<std::endl;
    std::cout<<"Plata: "<<*this->plata<<std::endl;
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

void allocateOdjel(WritableOdjel &odjel, const std::size_t size) {
    odjel = new uposlenik[size];
}

void deallocateOdjel(WritableOdjel &odjel) {
    delete[] odjel;

    odjel = nullptr;
}

void allocateFirma(WritableFirma &firma, const std::size_t rows, const std::size_t cols) {
    firma = new WritableOdjel[rows];

    for (std::size_t i = 0; i < rows; i++) {
        allocateOdjel(firma[i], cols);
    }
}

void deallocateFirma(WritableFirma &firma, const std::size_t rows) {
    for (std::size_t i = 0; i < rows; i++) {
        deallocateOdjel(firma[i]);
    }

    delete[] firma;

    firma = nullptr;
}

void printOdjel(ReadOnlyOdjel odjel, const std::size_t size) {
    for (std::size_t i = 0; i < size; i++) {
        std::cout<<"Informacije za "<<i + 1<<". uposlenika\n";
        odjel[i].printUposlenikInfo();
        if (i + 1 != size) {
            std::cout<<std::endl;
        }
    }
}

void printFirma(ReadOnlyFirma firma, const std::size_t rows, const std::size_t cols) {
    printBreakLine();
    for (std::size_t i = 0; i < rows; i++) {
        std::cout<<"Ispis "<<i + 1<<". odjela firme\n";
        printOdjel(firma[i], cols);
        if (i + 1 != rows) {
            std::cout<<"\n\n";
        }
    } 
    printBreakLine();
}

void enterOdjel(WritableOdjel odjel, const std::size_t size) {
    char *ID {};
    char *imePrezime{};
    float *plata{}; 
    
    for (std::size_t i = 0; i < size; i++) {
        ID = new char[MAX_BUFFER_SIZE] {};     
        imePrezime = new char[MAX_BUFFER_SIZE] {};     
        plata = new float {};     
        
        std::cout<<"Unesi podatke za "<<i + 1<<". uposlenika\n";
            
        handleCStringInput(ID, MAX_BUFFER_SIZE, "Unesi ID: ");
        handleCStringInput(imePrezime, MAX_BUFFER_SIZE, "Unesi ime i prezime: ");
        handleNumberInput(plata, "Unesi platu: ", 0);

        odjel[i].setUposlenikInfo(ID, imePrezime, plata);
        
        if (i + 1 != size) {
            std::cout<<std::endl;
        }
    }
}

void enterFirma(WritableFirma firma, const std::size_t rows, const std::size_t cols) {
    for (std::size_t i = 0; i < rows; i++) {
        printBreakLine();
        std::cout<<"Unos "<<i + 1<<". odjela firme\n";
        enterOdjel(firma[i], cols); 
        printBreakLine();
    } 
}

float getProsjekPlateOdjela(ReadOnlyOdjel odjel, const std::size_t size) {
    float average { 0.0f };

    for (std::size_t i = 0; i < size; i++) {
        average += odjel[i].getPlata();
    }

    return average / size;
}

void printBestProsjekPlata(ReadOnlyFirma firma, const std::size_t rows, const std::size_t cols) {
    std::size_t bestProsjekIndex { 0 };
    float bestProsjek { getProsjekPlateOdjela(firma[bestProsjekIndex], cols) };
    float tempProsjek {};

    for (std::size_t i = 1; i < rows; i++) {
        tempProsjek = getProsjekPlateOdjela(firma[i], cols); 

        if (bestProsjek < tempProsjek) {
            bestProsjek = tempProsjek;
            bestProsjekIndex = i;
        }
    }

    printBreakLine();
    std::cout<<"Redni broj odjela sa najboljim prosjekom plate je "<<bestProsjekIndex + 1<<std::endl;
    std::cout<<"Najveci prosjek plate je "<<bestProsjek<<std::endl;
    printBreakLine();
}