#include<iostream>

namespace caesar {
    constexpr std::size_t STR_SIZE {256}; 

    void handleStrInput(char *input, const std::size_t size) {
        std::cout<<"Input string: ";
        std::cin.getline(input, size);
    }
    
    void handleMoveInput(int &move) {
        std::cout<<"Input how many chars to move by: ";
        std::cin>>move;
    }

    void moveCharacter(char &letter, int move) {
        const char firstLetter { std::isupper(letter)? 'A' : 'a' };

        move %= 26;

        // In case the move is negative, convert it to the same thing
        // but with a positive value
        if (move < 0) {
            move = 26 + move;
        }

        letter -= firstLetter; 
        letter += move;
        letter = (letter % 26) + firstLetter;
    }

    void encodeCharacters(char *input, const std::size_t size, const int move) {
        for (std::size_t i = 0; i < size; i++) {
            // Skip non alpha chars
            if (!std::isalpha(input[i])) {
                continue;
            }
                
            moveCharacter(input[i], move);
        }
    }

    void decodeCharacters(char *input, const std::size_t size, const int move) {
        encodeCharacters(input, size, -move);
    }
}

int main() {
    char stringInput[caesar::STR_SIZE] {};
    int move {};

    caesar::handleStrInput(stringInput, std::size(stringInput));
    caesar::handleMoveInput(move);

    caesar::encodeCharacters(stringInput, std::size(stringInput), move);

    std::cout<<stringInput<<std::endl;

    caesar::decodeCharacters(stringInput, std::size(stringInput), move);

    std::cout<<stringInput<<std::endl;

    return 0;
}