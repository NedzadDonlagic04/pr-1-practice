#include<iostream>
#include<random>
#include<iomanip>
#include<memory>
#include<cstring>
#include<limits>
#include<cmath>
#include<optional>

constexpr std::size_t MATRIX_ROWS { 7 };
constexpr std::size_t MATRIX_COLS { 24 };
constexpr std::size_t BUFFER_SIZE { 256 };

void clearBuffer();
void printBreakLine();
void printErrorMsg(const char * const);
void enterNum(float &, const char * const, const std::optional<float> = std::nullopt, const std::optional<float> = std::nullopt);

void enterSingleDayTemperature(float (&)[MATRIX_COLS]);
void printSingleDayTemperature(const float (&)[MATRIX_COLS]);
void generateTemperatureData(float (&)[MATRIX_ROWS][MATRIX_COLS]);

[[nodiscard]] float roundTo2Decimals(const float);
[[nodiscard]] const char* getDayOfTheWeekName(const unsigned int);
[[nodiscard]] std::unique_ptr<char[]> getHourFormattedAsCString(const unsigned int);

[[nodiscard]] float getAverageTempForDay(const float (&)[MATRIX_COLS]);
[[nodiscard]] float* getDanWithWorstOrBestAvgTemp(float (&)[MATRIX_ROWS][MATRIX_COLS], const bool = true);

void printSpecificDanInfo(const float * const, const std::size_t, const char * const);

[[nodiscard]] float getAverageTempForHour(const float (&)[MATRIX_ROWS][MATRIX_COLS], const std::size_t);
[[nodiscard]] std::size_t getHourWithWorstOrBestAvgForEachDay(const float (&)[MATRIX_ROWS][MATRIX_COLS], const bool = true);

[[nodiscard]] float getAverageTempForHour(const float (&)[MATRIX_ROWS][MATRIX_COLS], const std::size_t);

int main() {
    float temperaturaUSedmiciPoSatima[MATRIX_ROWS][MATRIX_COLS] {};

    char outputMsg[BUFFER_SIZE] {};
    std::unique_ptr<char[]> formattedTime {};

    // Entering values into the matrix
/*     for (std::size_t i = 0; i < MATRIX_ROWS; i++) {
        printBreakLine();
        std::cout<<"Unesite temperature za odredene sate za dan "<<std::quoted(getDayOfTheWeekName(i))<<std::endl;
        enterSingleDayTemperature(temperaturaUSedmiciPoSatima[i]);
        printBreakLine();
    } */
    // For easier testing matrix can be filled automatically
    generateTemperatureData(temperaturaUSedmiciPoSatima);

    // Values from the matrix 
    for (std::size_t i = 0; i < MATRIX_ROWS; i++) {
        printBreakLine();
        std::cout<<"Ispis temperatura za odredene sate za dan "<<std::quoted(getDayOfTheWeekName(i))<<std::endl;
        printSingleDayTemperature(temperaturaUSedmiciPoSatima[i]);
        printBreakLine();
    }

    const float * const dayWithWorstAvgTemp { getDanWithWorstOrBestAvgTemp(temperaturaUSedmiciPoSatima, false) };
    const float * const dayWithBestAvgTemp { getDanWithWorstOrBestAvgTemp(temperaturaUSedmiciPoSatima) };

    printSpecificDanInfo(dayWithWorstAvgTemp, MATRIX_COLS, "Ispis dana sa najgorom prosjecnom temperaturom\n");
    printSpecificDanInfo(dayWithBestAvgTemp, MATRIX_COLS, "Ispis dana sa najboljom prosjecnom temperaturom\n");

    const std::size_t hourWithWorstAvgTemp { getHourWithWorstOrBestAvgForEachDay(temperaturaUSedmiciPoSatima, false) };
    const std::size_t hourWithBestAvgTemp { getHourWithWorstOrBestAvgForEachDay(temperaturaUSedmiciPoSatima) };

    printBreakLine();
    std::cout<<"Sat sa najgorim prosjekom od svih dana je "<<std::quoted(getDayOfTheWeekName(hourWithWorstAvgTemp))<<std::endl;
    std::cout<<"Sat sa najboljim prosjekom od svih dana je "<<std::quoted(getDayOfTheWeekName(hourWithBestAvgTemp))<<std::endl;
    printBreakLine();

    printBreakLine();
    std::cout<<"Prosjecna temperatura u podne (12h) svih dana je ";
    std::cout<<roundTo2Decimals(getAverageTempForHour(temperaturaUSedmiciPoSatima, 12))<<"°C"<<std::endl;
    printBreakLine();

    return 0;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printBreakLine() {
    std::cout<<"----------------------------\n";
}

void printErrorMsg(const char * const errorMsg) {
    std::cout<<"\033[31m";
    std::cout<<errorMsg;
    std::cout<<"\033[39m";
}

void enterNum(float &num, const char * const outputText, const std::optional<float> min, const std::optional<float> max) {
    bool repeatLoop {};
    char errorMsg[BUFFER_SIZE] {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>num;

        if (std::cin.fail()) {
            printErrorMsg("Nevalidan unos\n");
            clearBuffer();
            repeatLoop = true;
        } else if (min && num < min.value()) {
            std::sprintf(errorMsg, "Unos ne moze biti manji od %f", min.value());
            printErrorMsg(errorMsg);
            clearBuffer();
            repeatLoop = true;
        } else if (max && num > max.value()) {
            std::sprintf(errorMsg, "Unos ne moze biti veci od %f", max.value());
            printErrorMsg(errorMsg);
            clearBuffer();
            repeatLoop = true;
        }
    } while(repeatLoop);
}

void enterSingleDayTemperature(float (&dan)[MATRIX_COLS]) {
    char outputMsg[BUFFER_SIZE] {};
    std::unique_ptr<char[]> formattedTime {};

    for (std::size_t i = 0; i < MATRIX_COLS; i++) {
        formattedTime = getHourFormattedAsCString(i);
        std::sprintf(outputMsg, "Unesite temperaturu za sat %s: ", formattedTime.get());

        enterNum(dan[i], outputMsg);
    }
}

void printSingleDayTemperature(const float (&dan)[MATRIX_COLS]) {
    for (std::size_t i = 0; i < MATRIX_COLS; i++) {
        std::cout<<std::quoted(getHourFormattedAsCString(i).get())<<" = "<<dan[i]<<"°C\n";
    }
}

void generateTemperatureData(float (&temperaturaUSedmiciPoSatima)[MATRIX_ROWS][MATRIX_COLS]) {
    std::random_device dev {};
    std::mt19937 rng { dev() };
    std::uniform_real_distribution<> temperatureDist { -50.0f, 50.0f };

    for (std::size_t i = 0; i < MATRIX_ROWS; i++) {
        for (std::size_t ii = 0; ii < MATRIX_COLS; ii++) {
            temperaturaUSedmiciPoSatima[i][ii] = roundTo2Decimals(temperatureDist(rng));
        }
    }
}

float roundTo2Decimals(const float num) {
    return std::round(num * 100) / 100;
}

const char* getDayOfTheWeekName(const unsigned int dayOfWeekNum) {
    switch(dayOfWeekNum) {
        case 0:
            return "ponedeljak";
        case 1:
            return "utorak";
        case 2:
            return "srijeda";
        case 3:
            return "cetvrtak";
        case 4:
            return "petak";
        case 5:
            return "subota";
        default:
            return "nedelja";
    }
}

std::unique_ptr<char[]> getHourFormattedAsCString(const unsigned int hour) {
    std::unique_ptr<char[]> hourFormattedAsCString { new char[std::strlen("00:00") + 1] {} };

    std::strcpy(hourFormattedAsCString.get(), "00:00");

    if (hour < 10) {
        hourFormattedAsCString[1] = hour + '0';
    } else {
        hourFormattedAsCString[0] = (hour / 10) + '0';
        hourFormattedAsCString[1] = (hour % 10) + '0';
    }

    return hourFormattedAsCString;
}

float getAverageTempForDay(const float (&temperaturaUSedmiciPoSatima)[MATRIX_COLS]) {
    float sum { 0.0f };

    for (std::size_t i = 0; i < MATRIX_COLS; i++) {
        sum += temperaturaUSedmiciPoSatima[i];
    }

    return sum / MATRIX_COLS;
}

float* getDanWithWorstOrBestAvgTemp(float (&temperaturaUSedmiciPoSatima)[MATRIX_ROWS][MATRIX_COLS], const bool findBest) {
    std::size_t findIndex { 0 };
    float currentAvg { getAverageTempForDay(temperaturaUSedmiciPoSatima[findIndex]) };
    float temp {};

    for (std::size_t i = 1; i < MATRIX_ROWS; i++) {
        temp = getAverageTempForDay(temperaturaUSedmiciPoSatima[i]);

        if (findBest && temp > currentAvg) {
            currentAvg = temp;
            findIndex = i;
        } else if (!findBest && temp < currentAvg) {
            currentAvg = temp;
            findIndex = i;
        }
    }

    return temperaturaUSedmiciPoSatima[findIndex];
}

void printSpecificDanInfo(const float * const dan, const std::size_t size, const char * const outputMsg) {
    printBreakLine();
    std::cout<<outputMsg;
    for (std::size_t i = 0; i < size; i++) {
        std::cout<<std::quoted(getHourFormattedAsCString(i).get())<<" = "<<dan[i]<<"°C\n";
    }
    printBreakLine();
}

float getAverageTempForHour(const float (&temperaturaUSedmiciPoSatima)[MATRIX_ROWS][MATRIX_COLS], const std::size_t hourIndex) {
    float sum { 0.0f };

    for (std::size_t i = 0; i < MATRIX_ROWS; i++) {
        sum += temperaturaUSedmiciPoSatima[i][hourIndex];
    }

    return sum / MATRIX_ROWS;
}

std::size_t getHourWithWorstOrBestAvgForEachDay(const float (&temperaturaUSedmiciPoSatima)[MATRIX_ROWS][MATRIX_COLS], const bool findBest) {
    std::size_t findIndex { 0 };
    float currentAvg { getAverageTempForHour(temperaturaUSedmiciPoSatima, findIndex) };
    float temp {};

    for (std::size_t i = 1; i < MATRIX_COLS; i++) {
        temp = getAverageTempForHour(temperaturaUSedmiciPoSatima, i);

        if (findBest && temp > currentAvg) {
            currentAvg = temp;
            findIndex = i;
        } else if (!findBest && temp < currentAvg) {
            currentAvg = temp;
            findIndex = i;
        }
    }

    return findIndex;
}