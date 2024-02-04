#include<iostream>
#include<limits>
#include<optional>
#include<cstring>
#include<memory>

constexpr std::size_t IME_I_PREZIME_SIZE { 200 };
constexpr std::size_t TIP_SIZE { 2 };
constexpr std::size_t BUFFER_SIZE { 4096 };

constexpr char VALIDNI_TIPOVI[][TIP_SIZE] {
    "D",
    "Q",
    "A"
};

struct uposlenik {
    int ID {};
    char *ime_i_prezime {};
    char *tip {}; 
    // prihvatiti samo slova D, Q, A (developer, quality assurance i architect)
    float *plata {};

    uposlenik();
    ~uposlenik();

    void enterInfo();
    void printInfo() const;

    [[nodiscard]] const char * getTip() const;
    [[nodiscard]] float getPlata() const;

    [[nodiscard]] static const char * getFullNameOfTip(const char * const);
    [[nodiscard]] static bool isValidTip(const char * const);
    static void printValidTipovi();
};

struct Average {
    int counter {};
    int sum {};

    Average();
    void addToSum(const int);
    [[nodiscard]] float getAverage() const;
};

using WritableUposlenici = uposlenik*;
using WritableITFirme = WritableUposlenici*;

using ReadOnlyUposlenici = const uposlenik * const;
using ReadOnlyITFirme = ReadOnlyUposlenici * const;

void clearBuffer();
void printBreakLine();
void printErrorMsg(const char * const);
void enterSize(std::size_t &, const char * const);

void enterNum(int &, const char * const);
void enterNum(float &, const char * const, const std::optional<int> = std::nullopt, const std::optional<int> = std::nullopt);
void enterText(char *, const std::size_t, const char * const);
void enterTip(char *, const char * const);

void allocateUposlenici(WritableUposlenici &, const std::size_t);
void allocateITFirme(WritableITFirme &, const std::size_t, const std::size_t);

void deallocateUposlenici(WritableUposlenici);
void deallocateITFirme(WritableITFirme &, const std::size_t);

void enterUposleniciArray(WritableUposlenici, const std::size_t);
void enterITFirmeMatrix(WritableITFirme, const std::size_t, const std::size_t);

void printUposleniciArray(ReadOnlyUposlenici, const std::size_t);
void printITFirmeMatrix(ReadOnlyITFirme, const std::size_t, const std::size_t);

void printAveragePerTypeForEachITFirm(ReadOnlyITFirme, const std::size_t, const std::size_t);

[[nodiscard]] float getAverageForUposleniciByType(ReadOnlyUposlenici, const std::size_t, const char *);
[[nodiscard]] std::size_t getITFirmWithBestTypeAverage(ReadOnlyITFirme, const std::size_t, const std::size_t, const char *);

int main() {
    std::size_t rows {}, cols {};
    WritableITFirme uposlenici {};

    enterSize(rows, "Unesi duzine redova: ");
    enterSize(cols, "Unesi duzine kolona: ");

    allocateITFirme(uposlenici, rows, cols);

    enterITFirmeMatrix(uposlenici, rows, cols);
    printITFirmeMatrix(uposlenici, rows, cols);
    printAveragePerTypeForEachITFirm(uposlenici, rows, cols);

    const std::unique_ptr<char[]> tip { new char[TIP_SIZE] };

    clearBuffer();
    enterTip(tip.get(), "Unesi tip za provjeru: ");

    std::size_t bestFirmForEnteredType { getITFirmWithBestTypeAverage(uposlenici, rows, cols, tip.get()) };

    std::cout<<"IT Firma sa najboljim prosjekom plate za uposlenika tipa \""<<uposlenik::getFullNameOfTip(tip.get())<<"\"";
    std::cout<<" je firma u redu broj "<<bestFirmForEnteredType + 1<<'\n';

    deallocateITFirme(uposlenici, rows);

    return 0;
}


uposlenik::uposlenik() {
    this->ime_i_prezime = new char[IME_I_PREZIME_SIZE] {};
    this->tip = new char[TIP_SIZE] {};
    this->plata = new float {};
}

uposlenik::~uposlenik() {
    delete[] this->ime_i_prezime;
    delete[] this->tip;
    delete this->plata;
}

void uposlenik::enterInfo() {
    enterNum(this->ID, "Unesite ID uposlenika: ");
    clearBuffer();

    enterText(this->ime_i_prezime, IME_I_PREZIME_SIZE, "Unesite ime i prezime uposlenika: ");
    enterTip(this->tip, "Unesite tip uposlenika: ");

    enterNum(*this->plata, "Unesite platu uposlenika: ", 1);
}

void uposlenik::printInfo() const {
    std::cout<<"ID: "<<this->ID<<'\n';
    std::cout<<"Ime i prezime: "<<this->ime_i_prezime<<'\n';
    std::cout<<"Tip: "<<this->getFullNameOfTip(this->tip)<<'\n';
    std::cout<<"Plata: "<<*this->plata<<'\n';
}

const char * uposlenik::getTip() const {
    return this->tip;
}

float uposlenik::getPlata() const {
    return *this->plata;
}

const char * uposlenik::getFullNameOfTip(const char * const tip){
    if (std::strcmp(tip, "D") == 0) {
        return "Developer";
    } else if (std::strcmp(tip, "Q") == 0) {
        return "Quality assurance";
    } else if (std::strcmp(tip, "A") == 0) {
        return "Architect";
    }
    return "";
}

bool uposlenik::isValidTip(const char * const tip) {
    for (const auto VALIDNI_TIP : VALIDNI_TIPOVI) {
        if (std::strcmp(tip, VALIDNI_TIP) == 0) {
            return true;
        }
    }

    return false;
}

void uposlenik::printValidTipovi() {
    std::cout<<"Validni tipovi su: ";
    for (std::size_t i = 0; i < std::size(VALIDNI_TIPOVI); i++) {
        std::cout<<VALIDNI_TIPOVI[i];

        if (i + 1 != std::size(VALIDNI_TIPOVI)) {
            std::cout<<", ";
        }
    }
    std::cout<<std::endl;
}


Average::Average() : sum(0), counter(0) {}

void Average::addToSum(const int num) {
    this->sum += num;
    this->counter++;
}

float Average::getAverage() const {
    if (!this->sum) {
        return 0;
    }

    return static_cast<float>(this->sum) / this->counter;
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

void enterSize(std::size_t &size, const char * const outputText) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>size;

        if (std::cin.fail()) {
            printErrorMsg("Nevalidan unos\n");
            clearBuffer();
            repeatLoop = true;
        } else if (size < 2 || size > 1000) {
            printErrorMsg("Duzina treba biti u intervalu [2, 1000]\n");
            clearBuffer();
            repeatLoop = true;
        }
         
    } while(repeatLoop);
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

void enterText(char *text, const std::size_t bufferSize, const char * const outputText) {
    do {
        if (std::cin.fail()) {
            printErrorMsg("Nevalidan unos\n");
            clearBuffer();
        }

        std::cout<<outputText;
        std::cin.getline(text, bufferSize);
    } while(std::cin.fail());
}

void enterTip(char *tip, const char * const outputText) {
    do {
        uposlenik::printValidTipovi();
        enterText(tip, TIP_SIZE, outputText);

        if (!uposlenik::isValidTip(tip)) {
            printErrorMsg("Nevalidan tip uposlenika\n");
        }
    } while(!uposlenik::isValidTip(tip));
}

void allocateUposlenici(WritableUposlenici &uposlenikTemp, const std::size_t cols) {
    uposlenikTemp = new uposlenik[cols];
}

void allocateITFirme(WritableITFirme &uposlenici, const std::size_t rows, const std::size_t cols) {
    uposlenici = new uposlenik*[rows];

    for (std::size_t i = 0; i < rows; i++) {
        allocateUposlenici(*(uposlenici + i), cols);
    }
}

void deallocateUposlenici(WritableUposlenici uposlenikTemp) {
    delete[] uposlenikTemp;
}

void deallocateITFirme(WritableITFirme &uposlenici, const std::size_t rows) {
    for (std::size_t i = 0; i < rows; i++) {
        deallocateUposlenici(*(uposlenici + i));
    }

    delete[] uposlenici;
    uposlenici = nullptr;
}

void enterUposleniciArray(WritableUposlenici uposlenici, const std::size_t size) {
    for (std::size_t i = 0; i < size; i++) {
        std::cout<<"Unos podataka uposlenika "<<i + 1<<'\n';
        (uposlenici + i)->enterInfo();

        if (i + 1 != size) {
            std::cout<<std::endl;
        }
    }
}

void enterITFirmeMatrix(WritableITFirme itFirme, const std::size_t rows, const std::size_t cols) {
    for (std::size_t i = 0; i < rows; i++) {
        printBreakLine();
        std::cout<<"Unesi podatke "<<i + 1<<". IT firme:\n";
        enterUposleniciArray(*(itFirme + i), cols);
        printBreakLine();
    }
}

void printUposleniciArray(ReadOnlyUposlenici uposlenici, const std::size_t size) {
    for (std::size_t i = 0; i < size; i++) {
        std::cout<<"Ispis podataka uposlenika "<<i + 1<<'\n';
        (uposlenici + i)->printInfo();

        if (i + 1 != size) {
            std::cout<<std::endl;
        }
    }
}

void printITFirmeMatrix(ReadOnlyITFirme itFirme, const std::size_t rows, const std::size_t cols) {
    for (std::size_t i = 0; i < rows; i++) {
        printBreakLine();
        std::cout<<"Ispis podataka "<<i + 1<<". IT firme:\n";
        printUposleniciArray(*(itFirme + i), cols);
        printBreakLine();
    }
}

void printAveragePerTypeForEachITFirm(ReadOnlyITFirme itFirme, const std::size_t rows, const std::size_t cols) {
    for (std::size_t i = 0; i < rows; i++) {
        Average avgD {};
        Average avgQ {};
        Average avgA {};

        for (std::size_t ii = 0; ii < cols; ii++) {
            const char* tip { (*(itFirme + i) + ii)->getTip() };
            const float plata { (*(itFirme + i) + ii)->getPlata() };

            if (std::strcmp(tip, "D") == 0) {
                avgD.addToSum(plata);
            } else if (std::strcmp(tip, "Q") == 0) {
                avgQ.addToSum(plata);
            } else if (std::strcmp(tip, "A") == 0) {
                avgA.addToSum(plata);
            }
        }

        printBreakLine();
        std::cout<<"Za firmu "<<i + 1<<". prosjeci po tipu su:\n";
        std::cout<<uposlenik::getFullNameOfTip("D")<<" - "<<avgD.getAverage()<<std::endl;
        std::cout<<uposlenik::getFullNameOfTip("Q")<<" - "<<avgQ.getAverage()<<std::endl;
        std::cout<<uposlenik::getFullNameOfTip("A")<<" - "<<avgA.getAverage()<<std::endl;
        printBreakLine();
    }
}

float getAverageForUposleniciByType(ReadOnlyUposlenici uposlenici, const std::size_t size, const char *wantedTip) {
    Average avg {};

    for (std::size_t i = 0; i < size; i++) {
        const char* tip { (uposlenici + i)->getTip() };
        const float plata { (uposlenici + i)->getPlata() };

        if (std::strcmp(tip, wantedTip) == 0) {
            avg.addToSum(plata);
        }
    }

    return avg.getAverage();
}

std::size_t getITFirmWithBestTypeAverage(ReadOnlyITFirme itFirme, const std::size_t rows, const std::size_t cols, const char *tip) {
    std::size_t bestFirmIndex { 0 };
    float bestFirmAvg { getAverageForUposleniciByType(*(itFirme + bestFirmIndex), cols, tip) };
    float tempAvg {};

    for (std::size_t i = 1; i < rows; i++) {
        tempAvg = getAverageForUposleniciByType(*(itFirme + i), cols, tip);

        if (bestFirmAvg < tempAvg) {
            bestFirmIndex = i;
            bestFirmAvg = tempAvg;
        }
    }

    return bestFirmIndex;
}