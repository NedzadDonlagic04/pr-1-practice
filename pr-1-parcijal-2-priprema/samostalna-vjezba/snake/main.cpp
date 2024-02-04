/*
g++ main.cpp ./src/utility.cpp ./src/vecUtility.cpp ./src/snakeUtility.cpp -o run
*/

#include<iostream>

#include"./includes/utility.hpp"
#include"./includes/snakeUtility.hpp"
#include"./includes/vecUtility.hpp"

int main() {
    // Randomize the seed for the rng
    std::srand(time(NULL));

    int **snakePieces {};
    int snakePiecesSize {0}, snakePiecesCapacity {2};
    //      ^ used size             ^ actual size
    // capacity starting at 2 so we don't need an if else
    // when resizing using the x + (x >> 1) formula
    snakeUtils::initializeSnakePieces(snakePieces, snakePiecesSize, snakePiecesCapacity);

    int applePoint[2] {};
    snakeUtils::generateNewApplePosition(snakePieces, snakePiecesSize, applePoint);

    snakeUtils::printInstructions();
    utils::waitForEnter();

    bool isGameOngoing {true};
    char tempDirection {}, direction { snakeUtils::INITIAL_DIRECTION };
    unsigned long long previousTime = time(NULL);

    while (isGameOngoing) {
        utils::clearTerminal();

        snakeUtils::printGameScreen(snakePieces, snakePiecesSize, applePoint, isGameOngoing);
        utils::sleep100ms();

        if (utils::isKeyPressed()) {
            tempDirection = utils::getPressedKey(); 

            direction = snakeUtils::getValidKey(direction, tempDirection);
        }

        utils::sleep100ms();
        snakeUtils::moveSnake(direction, snakePieces, snakePiecesSize, snakePiecesCapacity, applePoint);

        previousTime = time(NULL);
    }

    std::cout<<"\n\nGame Over\n";
    std::cout<<"Amount of apples collected: "<<snakePiecesSize - 2<<"\n";
    //                                                          ^ because we start with 2 pieces

    vecUtil::arrUninitialize(snakePieces, snakePiecesSize);    

    return 0;
}