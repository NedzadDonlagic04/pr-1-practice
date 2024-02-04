#include<iostream>
#include<limits>

constexpr std::size_t ARR_SIZE { 3 };

void clearBuffer();
bool enterNum(int &);
void enterArray(int (&)[ARR_SIZE], const char * const);

void printWhatNumberIsInWhatInterval(int (&)[ARR_SIZE]);

int main() {
    int numbers[ARR_SIZE] {};

    enterArray(numbers, "Unesite 3 cijela broja: ");
    printWhatNumberIsInWhatInterval(numbers);

    return 0;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterNum(int &num, const char * const outputText) {
    do {
        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
        } 

        std::cout<<outputText;
        std::cin>>num;
    } while(std::cin.fail());
}

bool enterNum(int &num) {
    std::cin>>num;

    if (std::cin.fail()) {
        std::cout<<"Nevalidan unos\n";
        clearBuffer();
        return false;
    }
    return true;    
}

void enterArray(int (&arr)[ARR_SIZE], const char * const outputText) {
    std::cout<<outputText;

    for (std::ptrdiff_t i = 0; i < std::size(arr); i++) {
        if (!enterNum(arr[i])) {
            i = -1;
            std::cout<<outputText;
        }
    }
}

void printWhatNumberIsInWhatInterval(int (&arr)[ARR_SIZE]) {
    constexpr int INTERVALI[][2] {
        {-1, 1},
        {-20, -8},
        {40, 50},
        {77, 101}
    };

    bool isNumInInterval {};
    bool areNumsInSameInterval { true };

    std::ptrdiff_t lastUsedInterval { -1 };

    for (const auto num : arr) {
        isNumInInterval = false;

        for (std::size_t i = 0; i < std::size(INTERVALI); i++) {
            if (num >= INTERVALI[i][0] && num <= INTERVALI[i][1]) {
                std::cout<<"Broj "<<num<<" pripada intervalu ";
                std::cout<<'['<<INTERVALI[i][0]<<", "<<INTERVALI[i][1]<<"]\n"; 

                if (lastUsedInterval == -1) {
                    lastUsedInterval = i;
                } else if (lastUsedInterval != i) {
                    areNumsInSameInterval = false;
                }

                isNumInInterval = true;
                break;
            }
        }

        if (!isNumInInterval) {
            std::cout<<"Broj "<<num<<" ne pripada niti jednom intervalu\n";
        }
    }

    if (areNumsInSameInterval && lastUsedInterval != -1) {
        std::cout<<"Svi brojevi pripadaju jednom intervalu\n";
    } else {
        std::cout<<"Svi brojevi ne pripadaju jednom te istom intervalu\n";
    }
}