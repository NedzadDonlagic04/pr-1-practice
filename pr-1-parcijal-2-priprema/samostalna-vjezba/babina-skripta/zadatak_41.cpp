#include<iostream>
#include<limits>
#include<optional>
#include<iomanip>
#include<cmath>

constexpr std::size_t BUFFER_SIZE { 200 };

struct figura {
    int ID {};
    char *nazivFigure {};
    float *visinaFigure {};

    figura();
    ~figura();

    void enterInfo(const int);
    void printInfo() const;

    [[nodiscard]] int getID() const;
    [[nodiscard]] float getVisinaFigure() const;

};

using WritableFigure = figura**;
using ReadOnlyFigure = const figura * const * const;

void clearBuffer();
void printBreakLine();
void printErrorMsg(const char * const);
void enterSize(std::size_t &, const char * const);

void enterNum(float &, const char * const, const std::optional<int> = std::nullopt, const std::optional<int> = std::nullopt);
void enterText(char *, const std::size_t, const char * const);

void allocateFigure(WritableFigure&, const std::size_t);
void deallocateFigure(WritableFigure&, const std::size_t);

void enterFigure(WritableFigure, const std::size_t);
void printFigure(ReadOnlyFigure, const std::size_t);
void printFigurePretty(ReadOnlyFigure, const std::size_t);

[[nodiscard]] bool isSquareWhite(const std::size_t, const std::size_t);
[[nodiscard]] unsigned int getDigitWidth(const int);

[[nodiscard]] float roundTo2Decimals(const float);
[[nodiscard]] unsigned int getLongestDigitInFigures(ReadOnlyFigure, const std::size_t);

void printSpaces(const std::size_t);

[[nodiscard]] float* getSumOfSymmetricalPositionOnBoard(ReadOnlyFigure, const std::size_t);

int main() {
    std::size_t size {};

    enterSize(size, "Unesite dimenzije matrice: ");

    WritableFigure figure {};

    allocateFigure(figure, size);

    enterFigure(figure, size);
    printFigure(figure, size);
    printFigurePretty(figure, size);

    const float * const suma { getSumOfSymmetricalPositionOnBoard(figure, size) };

    std::cout<<"Suma simetricni bijeli polja na osnovu glavne dijagonale sa istom visinom: ";
    std::cout<<std::setprecision(2)<<std::fixed<<*suma<<std::endl;

    deallocateFigure(figure, size);
    delete suma;

    return 0;
}

figura::figura() {
    this->nazivFigure = new char[BUFFER_SIZE] {};
    this->visinaFigure = new float {};
}

figura::~figura() {
    delete[] this->nazivFigure;
    delete this->visinaFigure;
}

void figura::enterInfo(const int ID) {
    this->ID = ID;
    clearBuffer();
    enterText(this->nazivFigure, BUFFER_SIZE, "Unesi naziv figure: ");
    enterNum(*this->visinaFigure, "Unesi visinu figure: ", 1);
    *this->visinaFigure = roundTo2Decimals(*this->visinaFigure);
}

void figura::printInfo() const {
    std::cout<<"ID: "<<this->ID<<'\n';
    std::cout<<"Naziv figure: "<<std::quoted(this->nazivFigure)<<'\n';
    std::cout<<"Visina figure: "<<*this->visinaFigure<<'\n';
}

int figura::getID() const {
    return this->ID;
}

float figura::getVisinaFigure() const {
    return *this->visinaFigure;
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

void allocateFigure(WritableFigure &figure, const std::size_t size) {
    figure = new figura*[size] {};

    for (std::size_t i = 0; i < size; i++) {
        figure[i] = new figura[size] {};
    }
}

void deallocateFigure(WritableFigure &figure, const std::size_t size) {
    for (std::size_t i = 0; i < size; i++) {
        delete[] figure[i];
    }

    delete[] figure;
    figure = nullptr;
}

void enterFigure(WritableFigure figure, const std::size_t size) {
    for (std::size_t i = 0; i < size; i++) {
        for (std::size_t ii = 0; ii < size; ii++) {
            printBreakLine();
            std::cout<<"Unos informacija za figuru ["<<i<<", "<<ii<<"]\n";
            figure[i][ii].enterInfo(i * 10 + ii);
            printBreakLine();
        }
    }
}

void printFigure(ReadOnlyFigure figure, const std::size_t size) {
    for (std::size_t i = 0; i < size; i++) {
        for (std::size_t ii = 0; ii < size; ii++) {
            printBreakLine();
            std::cout<<"Ispis informacija figure ["<<i<<", "<<ii<<"]\n";
            figure[i][ii].printInfo();
            printBreakLine();
        }
    }
}

/* 
    Zbog pokusaje urednog ispisa ovdje su koristene 2 for petlje unutar 1 for petlje
    u slucaju da je potrebna neka veca optimizacija trebat ce se zrtvovati estetika
    Works fine on my machine tho
*/
void printFigurePretty(ReadOnlyFigure figure, const std::size_t size) {
    const unsigned int longestDigitWidth { getLongestDigitInFigures(figure, size) + 1};
    
    int currentID {};
    float currentVisinaFigure {};

    const auto defaultPrecision { std::cout.precision() };
    std::cout<<std::setprecision(2)<<std::fixed<<std::endl;

    std::cout<<"Ploca figura:\n";

    for (std::size_t i = 0; i < size; i++) {
        for (std::size_t ii = 0; ii < size; ii++) {
            currentID = figure[i][ii].getID();

            if (isSquareWhite(i, ii)) {
                std::cout<<"\033[47m";
            } else {
                std::cout<<"\033[40m";
            }   

            printSpaces(longestDigitWidth - getDigitWidth(currentID));
            std::cout<<currentID;

            if (ii + 1 != size) {
                std::cout<<' ';
            }

            // Reset back to default bg
            std::cout<<"\033[49m";
        }
        std::cout<<std::endl;

        for (std::size_t ii = 0; ii < size; ii++) {
            currentVisinaFigure = figure[i][ii].getVisinaFigure();         

            if (isSquareWhite(i, ii)) {
                std::cout<<"\033[47m";
            } else {
                std::cout<<"\033[40m";
            }   

            printSpaces(longestDigitWidth - getDigitWidth(currentVisinaFigure) - 3);
            std::cout<<currentVisinaFigure;

            if (ii + 1 != size) {
                std::cout<<' ';
            }

            // Reset back to default bg
            std::cout<<"\033[49m";
        }
        std::cout<<std::endl;
    }

    // Restore default precision
    std::cout<<std::setprecision(defaultPrecision)<<std::fixed;
}

bool isSquareWhite(const std::size_t row, const std::size_t col) {
    return (row + col) % 2 != 0;
}

unsigned int getDigitWidth(const int num) {
    if (!num) {
        return 1;
    }

    const bool isNeg { num < 0 };

    return std::log10(std::abs(num)) + 1 + isNeg;
}

float roundTo2Decimals(const float num) {
    return std::floor(num * 100) / 100;
}

unsigned int getLongestDigitInFigures(ReadOnlyFigure figure, const std::size_t size) {
    unsigned int longestDigitWidth { 0 };

    for (std::size_t i = 0; i < size; i++) {
        for (std::size_t ii = 0; ii < size; ii++) {
            longestDigitWidth = std::max(longestDigitWidth, getDigitWidth(figure[i][ii].getID())); 
            longestDigitWidth = std::max(longestDigitWidth, getDigitWidth(figure[i][ii].getVisinaFigure()) + 3); 
            // the 3 is for the decimal part, IE 123.45 it's for the .45 part
        }
    }

    return longestDigitWidth;
}

void printSpaces(const std::size_t size) {
    for (std::size_t i = 0; i < size; i++) {
        std::cout<<' ';
    }
}

float* getSumOfSymmetricalPositionOnBoard(ReadOnlyFigure figure, const std::size_t size) {
    const bool is00Black { !isSquareWhite(0, 0) }; 
    float *sum { new float { 0.0f } };

    for (std::size_t i = 0; i < size; i++) {
        for (std::size_t ii = i + is00Black; ii < size; ii += 2) {
            if (figure[i][ii].getVisinaFigure() == figure[ii][i].getVisinaFigure()) {
                *sum += (2 * figure[i][ii].getVisinaFigure());
            } else {
                *sum = -1.0f;
                return sum;
            }
        }
    }

    return sum;
}