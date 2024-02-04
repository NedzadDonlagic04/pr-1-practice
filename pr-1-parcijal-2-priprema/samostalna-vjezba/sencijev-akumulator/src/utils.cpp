#include"./../includes/utils.hpp"
#include"./../includes/memory.hpp"
#include"./../includes/oneAddressMachine.hpp"

#include<iostream>
#include<limits>
#include<optional>

namespace utils {
    std::size_t getDigitCount(const int num) {
        if (num == 0) {
            return 1;
        }

        bool isNegative { num < 0 };

        return std::log10(std::abs(num)) + 1 + isNegative;
    }

    std::size_t getDigitCount(const unsigned int num) {
        if (num == 0) {
            return 1;
        }

        return std::log10(num) + 1;
    }

    void repeatCharacter(const char sign, const int repetitions) {
        for (int i = 0; i < repetitions; i++) {
            std::cout<<sign;
        }
    }

    void drawLineBorder(const int repetitions) {
        repeatCharacter('-', 2 * repetitions + 3);
        std::cout<<std::endl;
    }

    void printFormatedMemoryLine(const char * const addressText, const char * const valueText, const int maxWidth) {
        std::cout<<'|';
        repeatCharacter(' ', maxWidth - strlen(addressText));
        std::cout<<addressText;
        std::cout<<'|';
        repeatCharacter(' ', maxWidth - strlen(valueText));
        std::cout<<valueText;
        std::cout<<'|';
        std::cout<<std::endl;
    }

    void printFormatedMemoryLine(const memory::AddressType address, const int value, const int maxWidth) {
        std::cout<<'|';
        repeatCharacter(' ', maxWidth - getDigitCount(address));
        std::cout<<address;
        std::cout<<'|';
        repeatCharacter(' ', maxWidth - getDigitCount(value));
        std::cout<<value;
        std::cout<<'|';
        std::cout<<std::endl;
    }

    void clearBuffer() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    void clearTerminalANSI() {
        std::cout<<"\033[2J\033[H";
    }
    
    void handleSizeInput(std::size_t &size) {
        bool repeatLoop {};

        do {
            repeatLoop = false;

            std::cout<<"Enter size: ";
            std::cin>>size;

            if (std::cin.fail()) {
                std::cout<<"Invalid input\n";
                clearBuffer();
                repeatLoop = true;
            } else if (size < 2 || size > 1000) {
                std::cout<<"Size has to be in the range [2, 1000]\n";
                repeatLoop = true;
            }
        } while(repeatLoop);
    }

    void handleNumInput(int &num, const char * const outputText, const std::optional<int> min) {
        bool repeatLoop {};

        do {
            repeatLoop = false;

            std::cout<<outputText;
            std::cin>>num;

            if (std::cin.fail()) {
                std::cout<<"Invalid input\n";
                clearBuffer();
                repeatLoop = true;
            } else if (min && num < min.value()) {
                std::cout<<"Input has to be bigger or equal to "<<min.value()<<'\n';
                repeatLoop = true;
            }
        } while(repeatLoop);
    }

    void handleNumInput(memory::AddressType &num, const char * const outputText, const std::optional<int> min) {
        bool repeatLoop {};

        do {
            repeatLoop = false;

            std::cout<<outputText;
            std::cin>>num;

            if (std::cin.fail()) {
                std::cout<<"Invalid input\n";
                clearBuffer();
                repeatLoop = true;
            } else if (min && num < min.value()) {
                std::cout<<"Input has to be bigger or equal to "<<min.value()<<'\n';
                repeatLoop = true;
            }
        } while(repeatLoop);
    }

    void handleMemoryLinesInput(memory::Memory &memory) {
        std::size_t i = 0;

        while (i < memory.capacity) {
            memory::AddressType address {};
            int value {};

            std::cout<<"Input for memory line "<<i + 1<<"\n";
            utils::handleNumInput(address, "Enter address: ", 0);
            utils::handleNumInput(value, "Enter value: ");

            if (memory.addAddressValue(address, value)) {
                i++;
            } else {
                std::cout<<"Memory address already exists\n";
            } 
        }

        std::cout<<std::endl;
    }

    std::unique_ptr<char[]> substr(const char * const str, const std::size_t begin, const std::size_t size) {
        std::unique_ptr<char[]> subStr {};

        if (begin >= size) {
            subStr = std::make_unique<char[]>(1);
            subStr[0] = '\0';
            return subStr;
        }

        const std::size_t newSize { size - begin + 1 };

        subStr = std::make_unique<char[]>(newSize);

        for (std::size_t i = 0; i < newSize - 1 && str[begin + i] != '\0'; i++) {
            subStr[i] = str[begin + i];
        }

        subStr[newSize - 1] = '\0';

        return subStr;
    }
}