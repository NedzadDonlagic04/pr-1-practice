#include<iostream>
#include<limits>
#include<optional>
#include<cmath>

constexpr std::size_t BUFFER_SIZE { 256 };

void clearBuffer();
void printErrorMsg(const char * const);
void enterNum(int &, const char * const, const std::optional<int> = std::nullopt, const std::optional<int> = std::nullopt);

[[nodiscard]] bool slozeni(const int);
[[nodiscard]] float ispis(int, const int);

int main() {
    int m {}, n {};

    enterNum(m, "Unesi pocetak intervala (m): ", 11, 99);
    enterNum(n, "Unesi kraj intervala (n): ", 501, 1999);

    const float aritmetickaSredina { ispis(m, n) };

    std::cout<<"Aritmeticka sredina od brojeva ispisanih iznad je: "<<aritmetickaSredina<<std::endl;

    return 0;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printErrorMsg(const char * const errorMsg) {
    std::cout<<"\033[31m";
    std::cout<<errorMsg;
    std::cout<<"\033[39m";
}

void enterNum(int &num, const char * const outputText, const std::optional<int> min, const std::optional<int> max) {
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

bool slozeni(const int num) {
    if (num == 2 || num == 3) {
        return false;
    } else if (num <= 1 || num % 2 == 0 || num % 3 == 0) {
        return true;
    }

    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) {
            return true;
        }
    }

    return false;
}

float ispis(int m, const int n) {
    float sum { 0.0f };
    unsigned int counter { 0u };

    std::cout<<"Slozeni brojevi u intervalu ["<<m<<", "<<n<<"]: ";
    for (; m <= n; m++) {
        if (slozeni(m)) {
            std::cout<<m<<' ';
            sum += m;
            counter++;
        }
    }
    std::cout<<std::endl;

    return (counter)? sum / counter : 0.0f;
}