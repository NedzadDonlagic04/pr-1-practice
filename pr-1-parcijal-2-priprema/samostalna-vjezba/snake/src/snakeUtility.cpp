#include"./../includes/snakeUtility.hpp"
#include"./../includes/vecUtility.hpp"
#include"./../includes/utility.hpp"

#include<iostream>

namespace snakeUtils {
    void printInstructions() {
        std::cout<<"Welcome to Budget Snake\n";
        std::cout<<"To move use the awsd keys\n";
        std::cout<<"Press enter to start the game, good luck!\n";
    }

    void printField(int *snakeHeadPoint, bool &isGameOnGoing) {
        for (int y = 1; y <= FIELD_ROWS; y++) {
            for (int x = 1; x <= FIELD_COLS; x++) {
                if (y == 1 || x == 1 || y == FIELD_ROWS || x == FIELD_COLS) {
                    std::cout<<getColor(DARK_GREEN);

                    // Check if the snake has hit any borders
                    if (snakeHeadPoint[0] == x && snakeHeadPoint[1] == y) {
                        isGameOnGoing = false;
                    }
                } else {
                    std::cout<<getColor(GREEN);
                }

                std::cout<<PIXEL_WIDTH;
                std::cout<<getColor(DEFAULT);
            }
            std::cout<<'\n';
        }
    }

    void printSnake(int **pieces, const int piecesSize, bool &isGameOngoing) {
        for (int i = 0; i < piecesSize; i++) {
            // Move cursor to position
            std::cout<<"\033["<<pieces[i][1]<<";"<<pieces[i][0] * 2 - 1<<"H";

            // Set bg color
            if (i == 0) {
                std::cout<<getColor(DARK_MAGENTA);
            } else {
                std::cout<<getColor(MAGENTA);
            }
            // Print pixel width and reset back to default bg color
            std::cout<<PIXEL_WIDTH<<getColor(DEFAULT);

            // Move cursor back to the bottom of the terminal
            std::cout<<"\033["<<FIELD_ROWS<<";"<<0<<"H\n";

            if (i && pieces[i][0] == pieces[0][0] && pieces[i][1] == pieces[0][1]) {
                isGameOngoing = false;
            }
        }

        std::cout<<'\n';
    }

    void printApple(int *applePoint) {
        std::cout<<"\033["<<applePoint[1]<<";"<<applePoint[0] * 2 - 1<<"H";

        std::cout<<getColor(RED)<<PIXEL_WIDTH<<getColor(DEFAULT);

        // Move cursor back to the bottom of the terminal
        std::cout<<"\033["<<FIELD_ROWS<<";"<<0<<"H\n";
    }

    void printGameScreen(int **pieces, const int piecesSize, int* applePoint, bool &isGameOngoing) {
        printField(pieces[0], isGameOngoing);
        printApple(applePoint);
        printSnake(pieces, piecesSize, isGameOngoing);
    }

    const char *getColor(const int color) {
        switch(color) {
            case 1:     // dark green
                return "\033[42m";
            case 2:     // light green
                return "\033[102m";
            case 3:     // light red
                return "\033[101m";
            case 4:     // dark magenta 
                return "\033[45m";
            case 5:     // magenta
                return "\033[105m";
            default:     // default bg color
                return "\033[49m";
        }
    }

    bool isValidKey(const char key) {
        for (int i = 0; i < std::size(VALID_KEYS); i++) {
            if (key == VALID_KEYS[i]) {
                return true;
            }
        }

        return false;
    }

    bool isValidDirection(const char direction, const char temp) {
        switch(direction) {
            case 'a':
                return temp != 'd';
            case 'w':
                return temp != 's';
            case 'd':
                return temp != 'a';
            default:
                return temp != 'w';
        }
    }

    char getValidKey(const char direction, const char temp) {
        if (isValidKey(temp) && isValidDirection(temp, direction)) {
            return temp; 
        }

        return direction;
    }

    void initializeSnakePieces(int **&pieces, int &piecesSize, int &piecesCapacity) {
        pieces = new int*[piecesCapacity];

        int headPoint[2] { SNAKE_STARTING_X, SNAKE_STARTING_Y };

        vecUtil::arrPush(pieces, piecesSize, piecesCapacity, headPoint);

        headPoint[0]++;     
        // increment allows for next push to be start of tail

        vecUtil::arrPush(pieces, piecesSize, piecesCapacity, headPoint);
    }

    bool isAppleEaten(int **pieces, const int *applePoint) {
        return pieces[0][0] == applePoint[0] && pieces[0][1] == applePoint[1];
    } 

    bool isValidAppleSpot(int **pieces, const int piecesSize, const int x, const int y) {
        for (int i = 0; i < piecesSize; i++) {
            if (pieces[i][0] == x && pieces[i][1] == y) {
                return false;
            } 
        }
        return true;
    }

    void generateNewApplePosition(int **pieces, const int piecesSize, int *applePoint) {
        int **validApplePoints {};
        int applePointsSize {0}, applePointCapacity {2};

        validApplePoints = new int*[applePointCapacity];

        for (int y = 2; y < FIELD_ROWS - 1; y++) {
            for (int x = 2; x < FIELD_COLS - 1; x++) {
                if (isValidAppleSpot(pieces, piecesSize, x, y)) {
                    int point[] = {x, y};

                    vecUtil::arrPush(validApplePoints, applePointsSize, applePointCapacity, point);
                }
            }
        }

        int validAppleIndex { utils::generateRandomNum(0, applePointsSize) };

        applePoint[0] = validApplePoints[validAppleIndex][0];
        applePoint[1] = validApplePoints[validAppleIndex][1];

        vecUtil::arrUninitialize(validApplePoints, applePointsSize);
    }

    void moveSnake(const char direction, int **&pieces, int &piecesSize, int &piecesCapacity, int *applePoint) {
        int newHeadPoint[] = { pieces[0][0], pieces[0][1] }; 

        switch(direction) {
            case 'a':
                newHeadPoint[0]--;
                break;
            case 'w':
                newHeadPoint[1]--;
                break;
            case 'd':
                newHeadPoint[0]++;
                break;
            case 's':
                newHeadPoint[1]++;
        }

        vecUtil::arrUnshift(pieces, piecesSize, piecesCapacity, newHeadPoint);
        
        if (isAppleEaten(pieces, applePoint)) {
            generateNewApplePosition(pieces, piecesSize, applePoint);
        } else {
            vecUtil::arrPop(piecesSize);
        }
    }
}