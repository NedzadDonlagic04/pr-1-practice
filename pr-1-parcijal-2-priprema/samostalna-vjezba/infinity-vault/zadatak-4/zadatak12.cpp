#include<iostream>
#include<cstddef>
#include<cmath>
#include<limits>
#include<iomanip>

constexpr std::size_t CHESS_BOARD_SIZE { 8 };

constexpr short TEXT_RED { 0 }, 
                TEXT_BLUE { 1 }, 
                TEXT_GREEN { 2 }, 
                TEXT_DEFAULT { -1 };
const char *setTextColor(const short);

constexpr short BG_WHITE { 0 },
                BG_BLACK { 1 },
                BG_DEFAULT { -1 }; 
const char *setBGColor(const short);

void clearBuffer();
void enterChessBoardValue(int &, const std::size_t, const std::size_t);

void enterValuesIntoChessBoard(int (&)[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE], short &);
void printChessBoard(int (&)[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE], const short);

short getDigitCount(const int);

bool isBoardSquareWhite(const std::size_t, const std::size_t);
bool isNumEvenWithOddDigitCount(const int);
bool isNumOddWithEvenDigitCount(const int);

float calcAverageWhiteSquareValuesAboveDiagonal(int (&)[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE]);
float calcAverageBlackSquareValuesBelowSideDiagonal(int (&)[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE]);

int main() {
    int chessBoard[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE] {};
    short biggestDigitCount {};
    
    enterValuesIntoChessBoard(chessBoard, biggestDigitCount);
    printChessBoard(chessBoard, biggestDigitCount + 1);

    const float averageValuesAboveDiagonal { calcAverageWhiteSquareValuesAboveDiagonal(chessBoard) };
    std::cout<<"Prosjek elemenata iznad glavne dijagonale na bijelim poljima je: "<<averageValuesAboveDiagonal<<std::endl;

    const float averageValuesBelowSideDiagonal { calcAverageBlackSquareValuesBelowSideDiagonal(chessBoard) };
    std::cout<<"Prosjek elemenata ispod sporedne dijagonale na crnim poljima je: "<<averageValuesBelowSideDiagonal<<std::endl;

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

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterChessBoardValue(int &input, const std::size_t row, const std::size_t col) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<"Unesi broj na index ["<<row<<"]["<<col<<"]: ";
        std::cin>>input;

        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
            repeatLoop = true;
        } else if (isBoardSquareWhite(row, col) && !isNumOddWithEvenDigitCount(input)) {
            std::cout<<"Unos treba biti neparan broj sa parnim brojem cifara\n";
            repeatLoop = true;
        } else if (!isBoardSquareWhite(row, col) && !isNumEvenWithOddDigitCount(input)) {
            std::cout<<"Unos treba biti paran broj sa neparnim brojem cifara\n";
            repeatLoop = true;
        }
    } while(repeatLoop);
}

void enterValuesIntoChessBoard(int (&board)[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE], short &biggestDigitCount) {
    biggestDigitCount = 1;

    for (std::size_t i = 0; i < CHESS_BOARD_SIZE; i++) {
        for (std::size_t ii = 0; ii < CHESS_BOARD_SIZE; ii++) {
            if (isBoardSquareWhite(i, ii)) {
                enterChessBoardValue(board[i][ii], i, ii);
            } else {
                enterChessBoardValue(board[i][ii], i, ii);
            }

            biggestDigitCount = std::max(biggestDigitCount, getDigitCount(board[i][ii]));
        }
        std::cout<<std::endl;
    }
}

void printChessBoard(int (&board)[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE], const short textWidth) {
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
             
            std::cout<<std::setw(textWidth)<<board[i][ii];
            std::cout<<setBGColor(BG_DEFAULT)<<setTextColor(TEXT_DEFAULT);
        }
        std::cout<<std::endl;
    }
}

bool isBoardSquareWhite(const std::size_t row, const std::size_t col) {
    return (row + col) % 2 == 0;
}

short getDigitCount(const int num) {
    return std::log10(num) + 1;
}

bool isNumEvenWithOddDigitCount(const int num) {
    short digitCount { getDigitCount(num) };

    return (digitCount % 2 != 0) && (num % 2 == 0);
}

bool isNumOddWithEvenDigitCount(const int num) {
    short digitCount { getDigitCount(num) };

    return (digitCount % 2 == 0) && (num % 2 != 0);
}

float calcAverageWhiteSquareValuesAboveDiagonal(int (&board)[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE]) {
    float average { 0.0f };
    int counter { 0 };

    // if [0, 0] is black it will return true and add to the 1, putting
    // us at [0, 1] the first white square
    std::size_t initialWhiteSquare = 1 + !isBoardSquareWhite(0, 1);

    for (std::size_t i = 0; i < CHESS_BOARD_SIZE - 1; i++) {
        for (std::size_t ii = initialWhiteSquare; ii < CHESS_BOARD_SIZE; ii += 2) {
            average += board[i][ii];
            counter++;
        }
        initialWhiteSquare++;
    }

    // std::cout<<average<<' '<<counter<<std::endl;

    return (counter)? average / counter : 0.0f;
}

float calcAverageBlackSquareValuesBelowSideDiagonal(int (&board)[CHESS_BOARD_SIZE][CHESS_BOARD_SIZE]) {
    float average { 0.0f };
    int counter { 0 };

    // if [0,1] is white it will return true and add to the 1, putting
    // us at [0, 2] the first black square
    std::size_t initialBlackSquare = 1 + isBoardSquareWhite(CHESS_BOARD_SIZE - 1, 1);

    for (std::ptrdiff_t i = CHESS_BOARD_SIZE - 1; i >= 1; i--) {
        for (std::size_t ii = initialBlackSquare; ii < CHESS_BOARD_SIZE; ii += 2) {
            average += board[i][ii];
            counter++;
        }
        initialBlackSquare++;
    }

    // std::cout<<average<<' '<<counter<<std::endl;

    return (counter)? average / counter : 0.0f;
}
