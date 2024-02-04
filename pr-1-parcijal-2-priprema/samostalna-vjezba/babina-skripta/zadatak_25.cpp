#include<iostream>
#include<iomanip>
#include<cstring>
#include<limits>
#include<cmath>
#include<optional>
#include<random>
#include<utility>

constexpr std::size_t VRSTA_PADAVINE_SIZE { 256 };
constexpr std::size_t BUFFER_SIZE { 256 };
constexpr std::size_t DA_LI_POSTOJI_PADAVINA { 3 };
constexpr char VRSTE_PADAVINA[][VRSTA_PADAVINE_SIZE] {
    "Snijeg",
    "Kisa",
    "Suncano",
    "Jako suncano",
    "Blago suncano",
    "Led sa jakim vjetrom",
    "Kisela kisa",
};
constexpr char PADAVINE_OPCIJE[][DA_LI_POSTOJI_PADAVINA] {
    "da",
    "ne"
};
constexpr bool PADAVINE_OPCIJE_BOOL_VALUE[DA_LI_POSTOJI_PADAVINA] {
    true,
    false,
};

struct vrijeme {
    float *temperatura {};
    float *vlaznostZraka {};
    bool *padavine {};
    char *vrstaPadavine {};
    float *kolicinaPadavine {};

    vrijeme();
    ~vrijeme();

    void enterVrijemeInfo();
    void setVrijemeInfo(const float, const float, const bool, const char * const, const float);
    void printVrijemeInfo() const;

    [[nodiscard]] float getTemperatura() const;
    [[nodiscard]] bool getPadavine() const;
};

using ReadOnlySatiUDanu = const vrijeme * const;
using WritableSatiUDanu = vrijeme *;
using ReadOnlyDani = ReadOnlySatiUDanu * const;
using WritableDani = WritableSatiUDanu *;

void clearBuffer();
void printBreakLine();
void printErrorMsg(const char * const);
void enterSize(std::size_t &, const char * const);
void toLowerEntireText(char * const);
[[nodiscard]] std::ptrdiff_t getPadavinaIndex(char * const);

void enterNum(float &, const char * const, const std::optional<float> = std::nullopt, const std::optional<float> = std::nullopt);
void enterText(char *, const std::size_t, const char * const, const char * const * const = nullptr);

void allocateDani(WritableDani &, const std::size_t, const std::size_t);
void deallocateDani(WritableDani &, const std::size_t);

void enterDani(WritableDani, const std::size_t, const std::size_t);
void generateRandomDaniInfo(WritableDani, const std::size_t, const std::size_t);

void printSatiUDanu(ReadOnlySatiUDanu, const std::size_t, const char * const);
void printDani(ReadOnlyDani, const std::size_t, const std::size_t);

[[nodiscard]] float getAvgTempForDay(ReadOnlyDani, const std::size_t);
[[nodiscard]] ReadOnlyDani getDayWithLowestOrHighestAvgTemp(ReadOnlyDani, const std::size_t, const std::size_t, const bool = true);

[[nodiscard]] float getPercentOfDayWithTempHigherThan(ReadOnlySatiUDanu, const std::size_t, const float, const bool = true);
[[nodiscard]] float roundTo2Dec(const float);

[[nodiscard]] float getAvgTempForHour(ReadOnlyDani, const std::size_t, const std::size_t);
[[nodiscard]] std::size_t getIndexForHourWithAvgTemp(ReadOnlyDani, const std::size_t, const std::size_t, const bool = true);

void printHoursForEveryDay(ReadOnlyDani, const std::size_t, const std::size_t, const char * const);

int main() {
    std::size_t rows {}, cols {};

    enterSize(rows, "Unesite broj dana za mjeriti vrijeme: ");    
    enterSize(cols, "Unesite broj sati u danu za mjeriti vrijeme: ");    

    WritableDani dani {};

    allocateDani(dani, rows, cols);

    // enterDani(dani, rows, cols);
    generateRandomDaniInfo(dani, rows, cols);
    printDani(dani, rows, cols);

    ReadOnlyDani lowestAvgTempDan { getDayWithLowestOrHighestAvgTemp(dani, rows, cols, false) };
    ReadOnlyDani highestAvgTempDan { getDayWithLowestOrHighestAvgTemp(dani, rows, cols) };

    printSatiUDanu(*lowestAvgTempDan, cols, "Ispis sati dana sa najnizim prosjekom temperature\n");    
    printSatiUDanu(*highestAvgTempDan, cols, "Ispis sati dana sa najvecim prosjekom temperature\n");    

    const float percentOfDayWithLowestAvg { getPercentOfDayWithTempHigherThan(*lowestAvgTempDan, cols, 25.5f, false) };
    const float percentOfDayWithHighestAvg { getPercentOfDayWithTempHigherThan(*highestAvgTempDan, cols, 25.5f) };

    std::cout<<"Procenat sati u danu sa najmanjom prosjecnom temperaturom gdje je temperatura veca od 25.5°C je ";
    std::cout<<percentOfDayWithLowestAvg<<"%"<<std::endl;

    std::cout<<"Procenat sati u danu sa najvecom prosjecnom temperaturom gdje je temperatura veca od 25.5°C i ";
    std::cout<<" uzimaju se samo sati kad je bilo padavina "<<percentOfDayWithHighestAvg<<"%"<<std::endl;

    const std::size_t bestHourByAvgTemp { getIndexForHourWithAvgTemp(dani, rows, cols) };

    char outputMsg[BUFFER_SIZE] {};
    std::sprintf(outputMsg, "Ispis podataka za %lu. sat u svakom danu\n", bestHourByAvgTemp);
    printHoursForEveryDay(dani, rows, bestHourByAvgTemp, outputMsg);

    deallocateDani(dani, rows);

    return 0;
}

vrijeme::vrijeme() {
    this->temperatura = new float {};
    this->vlaznostZraka = new float {};
    this->padavine = new bool {};
    this->vrstaPadavine = new char[VRSTA_PADAVINE_SIZE] {};
    this->kolicinaPadavine = new float {};
}

vrijeme::~vrijeme() {
    delete this->temperatura;
    delete this->vlaznostZraka;
    delete this->padavine;
    delete[] this->vrstaPadavine;
    delete this->kolicinaPadavine;
}

void vrijeme::enterVrijemeInfo() {
    enterNum(*this->temperatura, "Unesite temperaturu: "); 
    enterNum(*this->vlaznostZraka, "Unesite vlaznost zraka: ", 0); 
    clearBuffer();

    char daLiPostojiPadavinaTemp[DA_LI_POSTOJI_PADAVINA] {};    
    std::ptrdiff_t indexOfPadavina {};
    
    do {
        enterText(daLiPostojiPadavinaTemp, DA_LI_POSTOJI_PADAVINA, "Da li postoji padavina (da / ne): ");

        indexOfPadavina = getPadavinaIndex(daLiPostojiPadavinaTemp);

        if (indexOfPadavina == -1) {
            printErrorMsg("Unesena opcija ne postoji\n");
            std::cout<<"Validne opcije su: ";
            for (std::size_t i = 0; i < std::size(PADAVINE_OPCIJE); i++) {
                std::cout<<std::quoted(PADAVINE_OPCIJE[i]);

                if (i + 1 != std::size(PADAVINE_OPCIJE)) {
                    std::cout<<", ";
                }
            }
            std::cout<<std::endl;
        }
    } while(indexOfPadavina == -1);

    *this->padavine = PADAVINE_OPCIJE_BOOL_VALUE[indexOfPadavina];

    enterText(this->vrstaPadavine, VRSTA_PADAVINE_SIZE, "Unesite vrstu padavine: ");
    enterNum(*this->kolicinaPadavine, "Unesite kolicinu padavine: ", 0); 
}

void vrijeme::setVrijemeInfo(const float temperatura, const float vlaznostZraka, const bool padavine, const char * const vrstaPadavine, const float kolicinaPadavine) {
    *this->temperatura = temperatura;
    *this->vlaznostZraka = vlaznostZraka;
    *this->padavine = padavine;
    std::strcpy(this->vrstaPadavine, vrstaPadavine); 
    *this->kolicinaPadavine = kolicinaPadavine;
}

void vrijeme::printVrijemeInfo() const {
    std::cout<<"Temperatura: "<<*this->temperatura<<std::endl;
    std::cout<<"Vlaznost zraka: "<<*this->vlaznostZraka<<std::endl;
    std::cout<<std::boolalpha<<"Padavina postoji: "<<*this->padavine<<std::endl<<std::noboolalpha;
    std::cout<<"Vrsta padavine: "<<std::quoted(this->vrstaPadavine)<<std::endl;
    std::cout<<"Kolicina padavine: "<<*this->kolicinaPadavine<<std::endl;
}

float vrijeme::getTemperatura() const {
    return *this->temperatura;
}

bool vrijeme::getPadavine() const {
    return *this->padavine;
}


void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printBreakLine() {
    std::cout<<"-----------------------------\n";
}

void printErrorMsg(const char * const errorMsg) {
    std::cout<<"\033[31m";
    std::cout<<errorMsg;
    std::cout<<"\033[39m";
}

void enterSize(std::size_t &size, const char * const outputText) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>size;

        if (std::cin.fail()) {
            clearBuffer();
            printErrorMsg("Nevalidan unos\n");
            repeatLoop = true;
        } else if (size < 2 || size > 1000) {
            clearBuffer();
            printErrorMsg("Unos treba biti u intervalu [2, 1000]\n");
            repeatLoop = true;
        }

    } while(repeatLoop);
}

void toLowerEntireText(char * const text) {
    for (std::size_t i = 0; text[i] != '\0'; i++) {
        text[i] = std::tolower(text[i]);
    }
}

void enterNum(float &num, const char * const outputText, const std::optional<float> min, const std::optional<float> max) {
    bool repeatLoop {};
    char errorMsg[BUFFER_SIZE] {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>num;

        if (std::cin.fail()) {
            clearBuffer();
            printErrorMsg("Nevalidan unos\n");
            repeatLoop = true;
        } else if (min && num < min.value()) {
            std::sprintf(errorMsg, "Unos treba biti veci od %f\n", min.value());
            clearBuffer();
            printErrorMsg(errorMsg);
            repeatLoop = true;
        } else if (max && num > max.value()) {
            std::sprintf(errorMsg, "Unos treba biti manji od %f\n", max.value());
            clearBuffer();
            printErrorMsg(errorMsg);
            repeatLoop = true;
        }

    } while(repeatLoop);
}

std::ptrdiff_t getPadavinaIndex(char * const text) {
    toLowerEntireText(text);

    for (std::size_t i = 0; i < std::size(PADAVINE_OPCIJE); i++) {
        if (std::strcmp(text, PADAVINE_OPCIJE[i]) == 0) {
            return i;
        }
    }

    return -1;
}

void enterText(char *text, const std::size_t bufferSize, const char * const outputText, const char * const * const matchingTexts) {
    do {
        if (std::cin.fail()) {
            clearBuffer();
            printErrorMsg("Nevalidan unos\n");
        }

        std::cout<<outputText;
        std::cin.getline(text, bufferSize);
    } while(std::cin.fail());
}

void allocateDani(WritableDani &dani, const std::size_t rows, const std::size_t cols) {
    dani = new WritableSatiUDanu[rows] {};
    for (std::size_t i = 0; i < rows; i++) {
        *(dani + i) = new vrijeme[cols] {};
    }
}

void deallocateDani(WritableDani &dani, const std::size_t rows) {
    for (std::size_t i = 0; i < rows; i++) {
        delete[] *(dani + i);
    }
    delete[] dani;

    dani = nullptr;
}

void enterDani(WritableDani dani, const std::size_t rows, const std::size_t cols) {
    for (std::size_t i = 0; i < rows; i++) {
        printBreakLine();
        std::cout<<"Unos podataka za sate "<<i + 1<<". dana\n";
        for (std::size_t ii = 0; ii < cols; ii++) {
            std::cout<<"Unos za "<<ii + 1<<". sat\n";
            (*(dani + i) + ii)->enterVrijemeInfo();
            
            if (ii + 1 != cols) {
                std::cout<<std::endl;
            }
        }
        printBreakLine();
    }
}

void generateRandomDaniInfo(WritableDani dani, const std::size_t rows, const std::size_t cols) {
    std::random_device dev {};
    std::mt19937 rng { dev() };
    std::uniform_real_distribution<> tempDist { -50.0f, 50.0f };
    std::uniform_real_distribution<> vlaznostIKolicinaDist { 0.0f, 50.0f };
    std::uniform_int_distribution<std::mt19937::result_type> vrstaPadavineIndexDist (0, std::size(VRSTE_PADAVINA));
    std::uniform_int_distribution<std::mt19937::result_type> daLiImaPadavina (0, 1);

    float temperatura {};
    float vlaznostZraka {};
    bool padavine {};
    std::size_t vrstePadavinaIndex {};
    float kolicinaPadavine {};

    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t ii = 0; ii < cols; ii++) {
            temperatura = roundTo2Dec(tempDist(rng));
            vlaznostZraka = roundTo2Dec(vlaznostIKolicinaDist(rng));
            padavine = daLiImaPadavina(rng);
            std::size_t vrstePadavinaIndex = vrstaPadavineIndexDist(rng); 
            kolicinaPadavine = roundTo2Dec(vlaznostIKolicinaDist(rng));

            (*(dani + i) + ii)->setVrijemeInfo(temperatura, vlaznostZraka, padavine, VRSTE_PADAVINA[vrstePadavinaIndex], kolicinaPadavine);
        }
    }
}

void printSatiUDanu(ReadOnlySatiUDanu sati, const std::size_t size, const char * const outputText) {
    printBreakLine();
    std::cout<<outputText;
    for (std::size_t i = 0; i < size; i++) {
        std::cout<<"Ispis za "<<i + 1<<". sat\n";
        (sati + i)->printVrijemeInfo(); 
            
        if (i + 1 != size) {
            std::cout<<std::endl;
        }
    }
    printBreakLine();
}

void printDani(ReadOnlyDani dani, const std::size_t rows, const std::size_t cols) {
    for (std::size_t i = 0; i < rows; i++) {
        printBreakLine();
        std::cout<<"Ispis podataka za sate "<<i + 1<<". dana\n";
        for (std::size_t ii = 0; ii < cols; ii++) {
            std::cout<<"Ispis za "<<ii + 1<<". sat\n";
            (*(dani + i) + ii)->printVrijemeInfo();
            
            if (ii + 1 != cols) {
                std::cout<<std::endl;
            }
        }
        printBreakLine();
    }
}

float getAvgTempForDay(ReadOnlyDani dan, const std::size_t size) {
    float sum { 0.0f };

    for (std::size_t i = 0; i < size; i++) {
        sum += (*dan + i)->getTemperatura();
    }

    return sum / size;
}

ReadOnlyDani getDayWithLowestOrHighestAvgTemp(ReadOnlyDani dani, const std::size_t rows, const std::size_t cols, const bool findBest) {
    std::size_t findIndex { 0 };
    float currentTemp { getAvgTempForDay(dani + findIndex, cols) };
    float temp {};

    for (std::size_t i = 1; i < rows; i++) {
        temp = getAvgTempForDay(dani + i, cols);

        if (findBest && temp > currentTemp) {
            currentTemp = temp;
            findIndex = i;
        } else if (!findBest && temp < currentTemp) {
            currentTemp = temp;
            findIndex = i;
        }
    }
    
    return dani + findIndex;
}

float getPercentOfDayWithTempHigherThan(ReadOnlySatiUDanu sati, const std::size_t size, const float baseTemp, const bool takePadavineIntoConsideration) {
    unsigned int counter { 0u };

    for (std::size_t i = 0; i < size; i++) {
        if (takePadavineIntoConsideration && (sati + i)->getPadavine() && baseTemp < (sati + i)->getTemperatura()) {
            counter++;
        } else if (!takePadavineIntoConsideration && baseTemp < (sati + i)->getTemperatura()) {
            counter++;
        }
    }

    return roundTo2Dec(static_cast<float>(counter) / size * 100);
}

float roundTo2Dec(const float num) {
    return std::round(num * 100) / 100;
}

float getAvgTempForHour(ReadOnlyDani dani, const std::size_t rows, const std::size_t hourIndex) {
    float sum { 0.0f };

    for (std::size_t i = 0; i < rows; i++) {
        sum += (*(dani + i) + hourIndex)->getTemperatura();
    }

    return sum / rows;
}

std::size_t getIndexForHourWithAvgTemp(ReadOnlyDani dani, const std::size_t rows, const std::size_t cols, const bool findBest) {
    std::size_t findIndex { 0 };
    float currentTemp { getAvgTempForHour(dani, rows, findIndex) };
    float temp {};

    for (std::size_t i = 1; i < rows; i++) {
        temp = getAvgTempForHour(dani, i, findIndex);

        if (findBest && temp > currentTemp) {
            currentTemp = temp;
            findIndex = i;
        } else if (!findBest && temp < currentTemp) {
            currentTemp = temp;
            findIndex = i;
        }
    }
    
    return findIndex;
}

void printHoursForEveryDay(ReadOnlyDani dani, const std::size_t rows, const std::size_t hourIndex, const char * const outputText) {
    printBreakLine();
    std::cout<<outputText;
    for (std::size_t i = 0; i < rows; i++) {
        std::cout<<"Informacije za dati sat u danu "<<i + 1<<"\n";

        (*(dani + i) + hourIndex)->printVrijemeInfo();
        
        if (i + 1 != rows) {
            std::cout<<std::endl;
        }
    }
    printBreakLine();
}