#include<iostream>
#include<iomanip>
#include<cstring>
#include<limits>
#include<optional>
#include<cmath>

constexpr std::size_t BUFFER_SIZE { 4096 }; 

// Dodo ja da malo ljepse formatira se ispis
unsigned int longestDigitWidth {};

struct Glumac { 
    char* ime = nullptr; 
    char* prezime = nullptr; 
    char drzava[40] = ""; 
    int brojFilmova = 0; // označava broj redova u dinamičkoj matrici  
    int brojKorisnika = 0; // označava broj kolonu u dinamičkoj matrici 
    int** ocjene = nullptr; // matrica dimenzija (brojFilmova × brojKorisnika) 
     
    void unos(); // funkcija clanica za alokaciju i unos vrijednosti 
    float* getAveragesByUsers(); 
    void ispis(); 
    void dealokacije(); 
}; 

[[nodiscard]] unsigned int getDigitWidth(const int);

void clearBuffer();
void enterText(char * const, const std::size_t, const char * const);
void enterNum(int &, const char * const, const std::optional<int> = std::nullopt, const std::optional<int> = std::nullopt);

void allocateMatrix(int **&, const std::size_t, const std::size_t);
void deallocateMatrix(int **&, const std::size_t);

void enterMatrix(int * const * const, const std::size_t, const std::size_t);

int main() {
    Glumac glumac {};

    glumac.unos();
    glumac.ispis();

    float *averages { glumac.getAveragesByUsers() };

    std::cout<<"Ispis prosjecnih ocjena glumaca po svakom korisniku:\n";
    for (std::size_t i = 0; i < glumac.brojKorisnika; i++) {
        std::cout<<averages[i]<<' ';
    }
    std::cout<<std::endl;

    glumac.dealokacije();
    delete[] averages;

    return 0;
}

void Glumac::unos() {
    longestDigitWidth = 1;

    this->ime = new char[BUFFER_SIZE] {};
    this->prezime = new char[BUFFER_SIZE] {};

    enterText(this->ime, BUFFER_SIZE, "Unesite ime: ");
    enterText(this->prezime, BUFFER_SIZE, "Unesite prezime: ");
    
    enterText(this->drzava, 40, "Unesite drzavu: ");
    enterNum(this->brojFilmova, "Unesite broj filmova: ", 2, 1000);
    enterNum(this->brojKorisnika, "Unesite broj korisnika: ", 2, 1000);

    allocateMatrix(this->ocjene, this->brojFilmova, this->brojKorisnika);
    enterMatrix(this->ocjene, this->brojFilmova, this->brojKorisnika);
}

float* Glumac::getAveragesByUsers() {
    float *averages { new float[this->brojKorisnika] {} };

    for (std::size_t i = 0; i < this->brojKorisnika; i++) {
        averages[i] = 0;
        for (std::size_t ii = 0; ii < this->brojFilmova; ii++) {
            averages[i] += this->ocjene[ii][i];
        }
        averages[i] /= this->brojFilmova;
    }

    return averages;
}

void Glumac::ispis() {
    std::cout<<"Ime i prezime: "<<this->ime<<' '<<this->prezime<<'\n';
    std::cout<<"Drzava: "<<this->drzava<<'\n';
    std::cout<<"Broj filmova: "<<this->brojFilmova<<'\n';
    std::cout<<"Broj korisnika: "<<this->brojKorisnika<<'\n';

    std::cout<<"----------------------------------------------------\n";
    for (std::size_t i = 0; i < this->brojFilmova; i++) {
        for (std::size_t ii = 0; ii < this->brojKorisnika; ii++) {
            std::cout<<std::setw(longestDigitWidth)<<this->ocjene[i][ii]<<' ';
        }
        std::cout<<std::endl;
    }
    std::cout<<"----------------------------------------------------\n";
}

void Glumac::dealokacije() {
    deallocateMatrix(this->ocjene, this->brojFilmova);
}

unsigned int getDigitWidth(const int num) {
    if (num == 0) {
        return 1;
    }

    bool isNeg { num < 0 };

    return std::log10(num) + 1 + isNeg;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterText(char * const text, const std::size_t bufferSize, const char * const outputText) {
    do {
        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
        }

        std::cout<<outputText;
        std::cin.getline(text, bufferSize);
    } while(std::cin.fail());
}

void enterNum(int &num, const char * const outputText, const std::optional<int> min, const std::optional<int> max) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>num;

        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            repeatLoop = true;
            clearBuffer();
        } else if (min && num < min.value()) {
            std::cout<<"Unos ne smije biti manji od "<<min.value()<<std::endl;
            repeatLoop = true;
            clearBuffer();
        } else if (max && num > max.value()) {
            std::cout<<"Unos ne smije biti veci od "<<max.value()<<std::endl;
            repeatLoop = true;
            clearBuffer();
        }
    } while(repeatLoop);
}

void allocateMatrix(int **&matrix, const std::size_t rows, const std::size_t cols) {
    matrix = new int*[rows] {};

    for (std::size_t i = 0; i < rows; i++) {
        matrix[i] = new int[cols] {};
    }
}

void deallocateMatrix(int **&matrix, const std::size_t rows) {
    for (std::size_t i = 0; i < rows; i++) {
        delete[] matrix[i];
    }

    delete[] matrix;
    matrix = nullptr;
}

void enterMatrix(int * const * const matrix, const std::size_t rows, const std::size_t cols) {
    char outputText[BUFFER_SIZE] {};
    
    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t ii = 0; ii < cols; ii++) {
            std::sprintf(outputText, "Unesite ocjenu glumca za ulogu u filmu %lu od strane korisnika %lu: " , i, ii);

            enterNum(matrix[i][ii], outputText, 1, 10);

            longestDigitWidth = std::max(longestDigitWidth, getDigitWidth(matrix[i][ii]));
        }
        std::cout<<std::endl;
    }
}