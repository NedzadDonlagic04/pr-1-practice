#include<iostream>
#include<iomanip>
#include<limits>
#include<optional>
#include<cmath>

constexpr std::size_t ROW_SIZE { 2 };
constexpr std::size_t COL_SIZE { 3 };
constexpr std::size_t BUFFER_SIZE { 256 };
constexpr std::size_t BIGGER_BUFFER_SIZE { 4096 };

void clearBuffer();
void printBreakLine();
void printErrorMsg(const char * const);
void enterNum(float &, const char * const, const std::optional<int> = std::nullopt, const std::optional<int> = std::nullopt);

unsigned int enterPayForUposlenik(float (&)[ROW_SIZE][COL_SIZE], const std::size_t, std::size_t);

[[nodiscard]] float roundTo2Decimals(const float);
[[nodiscard]] unsigned int getDigitWidth(const int);
[[nodiscard]] bool isEqual(const float, const float, const float = 0.01);
[[nodiscard]] float ispisPlateUposlenika(const float (*)[COL_SIZE], const char * const, const unsigned int);

[[nodiscard]] float getAvgPayForUposlenik(const float (*)[COL_SIZE]);
[[nodiscard]] std::size_t getUposlenikWithHighestAvgPay(const float (&)[ROW_SIZE][COL_SIZE]);

int main() {
    float uposlenici[ROW_SIZE][COL_SIZE] { 0.0f };
    unsigned int longestDigit { 0 }, tempLongestDigit {};

    for (std::size_t i = 0; i < ROW_SIZE; i++) {
        printBreakLine();
        for (std::size_t ii = 0; ii < COL_SIZE; ii++) {
            tempLongestDigit = enterPayForUposlenik(uposlenici, i, ii);

            longestDigit = std::max(longestDigit, tempLongestDigit);
        }
        printBreakLine();
    }

    char textMsgOutputBuffer[BIGGER_BUFFER_SIZE] {};

    std::cout<<"Plate uposlenika po mjesecu:\n";
    for (std::size_t i = 0; i < ROW_SIZE; i++) {
        std::sprintf(textMsgOutputBuffer, "Ispis plata uposlenika %lu za sve mjesece: ", i + 1);

        const float avgPay { ispisPlateUposlenika(uposlenici + i, textMsgOutputBuffer, longestDigit) };

        std::cout<<"Za ovog uposlenika je prosjecna godisnja plata "<<avgPay<<std::endl;
        std::cout<<std::endl;
    }

    const std::size_t uposlenikSNajvecomPlatom { getUposlenikWithHighestAvgPay(uposlenici) };

    std::cout<<"Uposlenik s najvecom prosjecnom platom godisnje je uposlenik ";
    std::cout<<uposlenikSNajvecomPlatom + 1<<std::endl;

    return 0;
}

unsigned int enterPayForUposlenik(float (&uposlenici)[ROW_SIZE][COL_SIZE], const std::size_t uposlenikIndex, std::size_t monthIndex) {
    constexpr char NAZIVI_MJESECA[][BUFFER_SIZE] {
        "januar",
        "februar",
        "mart",
        "april",
        "maj",
        "juni",
        "juli",
        "august",
        "septembar",
        "oktobar",
        "novembar",
        "decembar",
    };

    if (monthIndex > std::size(NAZIVI_MJESECA)) {
        monthIndex = 0;
    }

    char textMsgOutputBuffer[BIGGER_BUFFER_SIZE] {};
    float &trenutniUposlenik { uposlenici[uposlenikIndex][monthIndex] };

    std::sprintf(textMsgOutputBuffer, "Unesite platu za uposlenika %lu za mjesec \"%s\": ", uposlenikIndex + 1, NAZIVI_MJESECA[monthIndex]);

    enterNum(trenutniUposlenik, textMsgOutputBuffer, 0);     

    trenutniUposlenik = roundTo2Decimals(trenutniUposlenik);

    return getDigitWidth(trenutniUposlenik) + 2;
}

float roundTo2Decimals(const float num) {
    return std::floor(num * 100) / 100;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printBreakLine() {
    std::cout<<"------------------------------------\n";
}

void printErrorMsg(const char * const errorMsg) {
    std::cout<<"\033[31m";
    std::cout<<errorMsg;
    std::cout<<"\033[39m";
}

void enterNum(float &num, const char * const outputText, const std::optional<int> min, const std::optional<int> max) {
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

unsigned int getDigitWidth(const int num) {
    if (!num) {
        return 1;
    }

    const bool isNeg { num < 0 };

    return std::log10(std::abs(num)) + 1 + isNeg;
}

bool isEqual(const float f1, const float f2, const float epsilon) {
    return std::abs(f1 - f2) <= epsilon;
}

float ispisPlateUposlenika(const float (*uposlenik)[COL_SIZE], const char * const outputText, const unsigned int width) {
    float sum { 0.0f };

    std::cout<<outputText;

    for (std::size_t i = 0; i < COL_SIZE; i++) {
        if (isEqual(uposlenik[0][i], 0)) {
            std::cout<<std::setw(width)<<" "<<' '; 
        } else {
            std::cout<<std::setw(width)<<uposlenik[0][i]<<' ';
        }

        sum += uposlenik[0][i];
    }

    std::cout<<std::endl;

    return (sum)? roundTo2Decimals(sum / COL_SIZE) : 0.0f;
}

float getAvgPayForUposlenik(const float (*uposlenik)[COL_SIZE]) {
    float sum { 0.0f };

    for (std::size_t i = 0; i < COL_SIZE; i++) {
        sum += uposlenik[0][i];
    }

    return (sum)? roundTo2Decimals(sum / COL_SIZE) : 0.0f;
}

std::size_t getUposlenikWithHighestAvgPay(const float (&uposlenici)[ROW_SIZE][COL_SIZE]) {
    std::size_t bestAvgIndex { 0 };
    float bestAvg { getAvgPayForUposlenik(uposlenici + bestAvgIndex) };
    float tempAvg {};

    for (std::size_t i = 1; i < ROW_SIZE; i++) {
        tempAvg = getAvgPayForUposlenik(uposlenici + i);

        if (tempAvg > bestAvg) {
            bestAvg = tempAvg;
            bestAvgIndex = i;
        }
    }

    return bestAvgIndex;
}