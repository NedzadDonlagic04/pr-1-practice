#pragma once

#ifndef SNAKE_UTILITY
#define SNAKE_UTILITY

namespace snakeUtils {
    // Field size
    inline constexpr int FIELD_ROWS {11}, FIELD_COLS {20};

    // Color constants
    inline constexpr int DEFAULT {0}, DARK_GREEN {1}, GREEN {2}, RED {3}, DARK_MAGENTA {4}, MAGENTA {5};

    inline constexpr char PIXEL_WIDTH[] {"  "};
    inline constexpr char VALID_KEYS[] {'a', 'w', 's', 'd'};
    inline constexpr char INITIAL_DIRECTION { VALID_KEYS[0] };

    // Initial position for important pieces on the field
    inline constexpr int APPLE_STARTING_X {5}, APPLE_STARTING_Y = FIELD_ROWS / 2 + 1;
    inline constexpr int SNAKE_STARTING_X {APPLE_STARTING_X + 8}, SNAKE_STARTING_Y {APPLE_STARTING_Y};
    
    void printInstructions();
    void printGameScreen(int **, const int, int*, bool &);
    void printField(int *, bool &);
    void printApple(int *);
    void printSnake(int **, const int, bool &);

    char getValidKey(const char, const char);
    const char *getColor(const int);

    void initializeSnakePieces(int **&, int &, int &);

    bool isAppleEaten(int **, const int *);
    bool isValidAppleSpot(int **, const int, const int, const int);
    void generateNewApplePosition(int **, const int , int *);

    void moveSnake(const char, int **&, int &, int &, int *);
}

#endif