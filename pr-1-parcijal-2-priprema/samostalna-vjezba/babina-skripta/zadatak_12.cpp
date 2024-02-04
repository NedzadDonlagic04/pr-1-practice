#include<iostream>
#include<limits>
#include<random>

constexpr std::size_t ARR_SIZE { 50 };
//                              ^ minimalno treba biti 4, zbog postavke ispisa i ostatka zadatka
constexpr std::size_t BUFFER_SIZE { 256 };

struct SpecializedArray {
    int arr[ARR_SIZE] {};
    bool colorSpotArr[ARR_SIZE] {};

    SpecializedArray();
    
    void enterArray();
    void fillArrayWithRandomNums(const int, const int);

    void printArray();

    [[nodiscard]] bool areLast3ArrElsInIncrementsBy1(const std::size_t);
    [[nodiscard]] unsigned int countRepetitionsBy4();
};

void clearBuffer();
// Be warned this one uses ANSI escape codes
void printErrorMsg(const char * const);
void enterNum(int &, const char * const);

int main() {
    SpecializedArray spArr {};

    // spArr.enterArray();
    spArr.fillArrayWithRandomNums(1, 5);

    unsigned int repetitionCount { spArr.countRepetitionsBy4() };
    
    spArr.printArray();

    std::cout<<"Broj ponavljanja sekvenci gdje se nalaze 4 uzastopna broja je ";
    std::cout<<repetitionCount<<std::endl;

    return 0;
}

SpecializedArray::SpecializedArray() : arr { 0 }, colorSpotArr { false } {}

void SpecializedArray::enterArray() {
    char outputText[BUFFER_SIZE] {};

    for (std::size_t i = 0; i < ARR_SIZE; i++) {
        std::sprintf(outputText, "Unesi broj na index poziciju %lu: ", i);
        enterNum(this->arr[i], outputText);
    }

    std::cout<<std::endl;
}

void SpecializedArray::fillArrayWithRandomNums(const int from, const int to) {
    std::random_device dev {};
    std::mt19937 rng { dev() };
    std::uniform_int_distribution<std::mt19937::result_type> dist (from, to);

    for (std::size_t i = 0; i < ARR_SIZE; i++) {
        this->arr[i] = dist(rng);
    }
}

void SpecializedArray::printArray() {
    std::cout<<"Niz: ";

    for (std::size_t i = 0; i < ARR_SIZE; i++) {
        if (this->colorSpotArr[i]) {
            std::cout<<"\033[31m";
        } 

        std::cout<<this->arr[i];

        if (i + 1 != ARR_SIZE) {
            std::cout<<", ";
        }

        std::cout<<"\033[39m";
    }

    std::cout<<std::endl;
}

bool SpecializedArray::areLast3ArrElsInIncrementsBy1(const std::size_t i) {
    return  this->arr[i] - this->arr[i - 1] == 1 && 
            this->arr[i] - this->arr[i - 2] == 2 && 
            this->arr[i] - this->arr[i - 3] == 3;
}

unsigned int SpecializedArray::countRepetitionsBy4() {
    unsigned int counter { 0 };

    for (std::size_t i = 3; i < ARR_SIZE; i++) {
        if (this->areLast3ArrElsInIncrementsBy1(i) ) {
            counter++;
            this->colorSpotArr[i] = true;
            this->colorSpotArr[i - 1] = true;
            this->colorSpotArr[i - 2] = true;
            this->colorSpotArr[i - 3] = true;
        }
    }

    return counter;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterNum(int &num, const char * const outputText) {
    do {
        if (std::cin.fail()) {
            printErrorMsg("Nevalidan unos\n");
            clearBuffer();
        }

        std::cout<<outputText;
        std::cin>>num;
    } while(std::cin.fail());
}

// Be warned this one uses ANSI escape codes
void printErrorMsg(const char * const errorMsg) {
    std::cout<<"\033[31m";
    std::cout<<errorMsg;
    std::cout<<"\033[39m";
}
