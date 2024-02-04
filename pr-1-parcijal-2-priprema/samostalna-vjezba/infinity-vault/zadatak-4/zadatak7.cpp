#include<iostream>
#include<cstddef>
#include<cmath>
#include<limits>
#include<iomanip>

constexpr std::size_t MAX_BUFFER_SIZE { 256 };
constexpr std::size_t CHESS_BOARD_SIZE { 4 };

constexpr short TEXT_RED { 0 }, 
                TEXT_BLUE { 1 }, 
                TEXT_GREEN { 2 }, 
                TEXT_DEFAULT { -1 };

constexpr short BG_WHITE { 0 },
                BG_BLACK { 1 },
                BG_DEFAULT { -1 }; 

struct figura {
    int ID {};
    char *nazivFigure {};
    float *visinaFigure {}; 

    figura() = default;
    ~figura(); 

    void setFiguraInfo(const int, char * const, float * const);
    float getVisinaFigure() const;

    void printFiguraInfo() const;
};

figura::~figura() {
    delete this->nazivFigure;
    delete this->visinaFigure;

    this->nazivFigure = nullptr;
    this->visinaFigure = nullptr;
}
    
void figura::setFiguraInfo(const int ID, char * const nazivFigure, float * const visinaFigure) {
    this->ID = ID;
    this->nazivFigure = nazivFigure;
    this->visinaFigure = visinaFigure;
}

float figura::getVisinaFigure() const {
    return *this->visinaFigure;
}

void figura::printFiguraInfo() const {
    std::cout<<"ID: "<<this->ID<<std::endl;
    std::cout<<"Naziv figure: "<<this->nazivFigure<<std::endl;
    std::cout<<"Visina figure: "<<*this->visinaFigure<<std::endl;
}

const char *setTextColor(const short);
const char *setBGColor(const short);

void printBreakLine();
void clearBuffer();

void handleCStringInput(char *, const std::size_t, const char * const);
void handleNumberInput(float *, const char * const, const int);
void handleNumberInput(int &, const char * const, const int);

void enterValuesIntoChessBoard(figura (&)[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE], short &);
void printChessBoard(figura (&)[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE], const short);

short getDigitCount(const int);
void twoDecimalRound(float *);

bool isBoardSquareWhite(const std::size_t, const std::size_t);

float* calcAverageBlackSquareValuesBelowSideDiagonal(figura (&)[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE]);

int main() {
    figura chessBoard[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE] {};
    short biggestDigitCount {};
    
    enterValuesIntoChessBoard(chessBoard, biggestDigitCount);
    printChessBoard(chessBoard, biggestDigitCount + 1);

    float *averageInBlackSquaresBelowSideDiagonal { calcAverageBlackSquareValuesBelowSideDiagonal(chessBoard) };

    printBreakLine(); 
    std::cout<<"Prosjecna vrijednost ispod sporedne dijagonale u crnim poljima je: ";
    std::cout<<*averageInBlackSquaresBelowSideDiagonal<<std::endl; 
    printBreakLine(); 

    return 0;
}    

const char *setTextColor(const short color) {
    switch(color) {
        case 0:     // red
            return "\033[31m";
        case 1:     // blue 
            return "\033[36m";
        case 2:     // green
            return "\033[92m";
        default:     // default / reset 
            return "\033[0m";
    }
}

const char *setBGColor(const short color) {
    switch(color) {
        case 0:     // white 
            return "\033[47m";
        case 1:     // black 
            return "\033[40m";
        default:     // default / reset 
            return "\033[0m";
    }
}

void printBreakLine() {
    std::cout<<"-----------------------------------------------\n";
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

void handleNumberInput(int &input, const char *outputText, const int min) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>input;

        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
            repeatLoop = true;
        } else if (input < min) {
            std::cout<<"Unos treba biti veci od "<<min<<'\n';
            repeatLoop = true;
        }
    } while(repeatLoop);

    clearBuffer();
}

void enterValuesIntoChessBoard(figura (&board)[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE], short &biggestDigitCount) {
    biggestDigitCount = 1;

    for (std::size_t i = 0; i < CHESS_BOARD_SIZE; i++) {
        for (std::size_t ii = 0; ii < CHESS_BOARD_SIZE; ii++) {
            std::cout<<"Unos podataka figure ["<<i<<", "<<ii<<"]\n";

            int ID {};
            char *nazivFigure { new char[MAX_BUFFER_SIZE] };
            float *visinaFigure { new float {} }; 

            handleNumberInput(ID, "Unesi ID: ", 0);
            handleCStringInput(nazivFigure, MAX_BUFFER_SIZE, "Unesi naziv figure: ");
            handleNumberInput(visinaFigure, "Unesi visinu figure: ", 0);

            twoDecimalRound(visinaFigure);

            board[i][ii].setFiguraInfo(ID, nazivFigure, visinaFigure);

            biggestDigitCount = std::max(biggestDigitCount, getDigitCount(board[i][ii].getVisinaFigure()));

            std::cout<<std::endl;
        }
        std::cout<<std::endl;
    }

    // in case we have something post decimal point
    // so stuff like .34 we add 3 more spaces
    biggestDigitCount += 3;
}

void printChessBoard(figura (&board)[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE], const short textWidth) {
    for (std::size_t i = 0; i < CHESS_BOARD_SIZE; i++) {
        for (std::size_t ii = 0; ii < CHESS_BOARD_SIZE; ii++) {
            if (i == ii || i + ii == CHESS_BOARD_SIZE - 1) {
                std::cout<<setTextColor(TEXT_RED);
            } else if (i < ii) {
                std::cout<<setTextColor(TEXT_GREEN);
            } else {
                std::cout<<setTextColor(TEXT_BLUE);
            }

            if (isBoardSquareWhite(i, ii)) {
                std::cout<<setBGColor(BG_WHITE);
            } else {
                std::cout<<setBGColor(BG_BLACK);
            }
             
            std::cout<<std::setw(textWidth)<<board[i][ii].getVisinaFigure();
            std::cout<<setBGColor(BG_DEFAULT)<<setTextColor(TEXT_DEFAULT);
        }
        std::cout<<std::endl;
    }
}

bool isBoardSquareWhite(const std::size_t row, const std::size_t col) {
    return (row + col) % 2 != 0;
}

short getDigitCount(const int num) {
    return std::log10(num) + 1;
}

void twoDecimalRound(float *num) {
    *num *= 100;
    *num = std::ceil(*num) / 100;
}

float* calcAverageBlackSquareValuesBelowSideDiagonal(figura (&board)[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE]) {
    float average { 0.0f };
    int counter { 0 };

    // if [0,1] is white it will return true and add to the 1, putting
    // us at [0, 2] the first black square
    std::size_t initialBlackSquare = 1 + isBoardSquareWhite(CHESS_BOARD_SIZE - 1, 1);

    for (std::ptrdiff_t i = CHESS_BOARD_SIZE - 1; i >= 1; i--) {
        for (std::size_t ii = initialBlackSquare; ii < CHESS_BOARD_SIZE; ii += 2) {
            average += board[i][ii].getVisinaFigure();
            counter++;
        }
        initialBlackSquare++;
    }

    average = (counter)? average / counter : 0.0f;

    return new float { average };
}
