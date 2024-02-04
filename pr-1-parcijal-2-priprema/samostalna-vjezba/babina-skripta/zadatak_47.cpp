#include<iostream>
#include<optional>
#include<limits>

constexpr std::size_t FULLNAME_SIZE { 30 };

struct datum {
    int d {};
    int m {};
    int g {};
};

struct student {
    int IB {};
    char imeiPrezime[FULLNAME_SIZE] {};
    datum rodjenja {};
    float prosjecnaOcjena {};
};

void printBreakLine();
void clearBuffer();
void enterSize(std::size_t &, const char * const);

// In a perfect world templates would have saved us from this
// But this is not a perfect world
void enterNum(float &, const char * const, const std::optional<float> = std::nullopt, const std::optional<float> = std::nullopt);
void enterNum(int &, const char * const, const std::optional<int> = std::nullopt, const std::optional<int> = std::nullopt);
void enterDate(datum &, const char * const);

[[nodiscard]] bool isValidDate(const datum * const);
[[nodiscard]] bool isLeapYear(const int);
[[nodiscard]] unsigned int getDayForMonth(const int, const int);

using ReadOnlyStudenti = const student * const;
using WritableStudenti = student*;
using ReadOnlyGeneracije = const student * const * const;
using WritableGeneracije = student**;

void allocateGenerations(WritableGeneracije&, const std::size_t, const std::size_t);
void deallocateGenerations(WritableGeneracije&, const std::size_t);

void printStudenti(ReadOnlyStudenti, const std::size_t);
void printGeneracije(ReadOnlyGeneracije, const std::size_t, const std::size_t);

void printFormattedDate(const datum &, const char * const);
void printStudentiInfo(const student &);
void enterStudentInfo(student &);

void enterStudenti(WritableStudenti, const std::size_t);
void enterGeneracije(WritableGeneracije, const std::size_t, const std::size_t);

[[nodiscard]] std::size_t getIndexForBestOrWorstGenerationByProsjekOcjena(ReadOnlyGeneracije, const std::size_t, const std::size_t, const bool = false);
[[nodiscard]] std::size_t getIndexForBestOrWorstPredmetByProsjekOcjena(ReadOnlyGeneracije, const std::size_t, const std::size_t, const bool = false);

int main() {
    std::size_t rows {}, cols {};

    enterSize(rows, "Unesi duzinu redova: ");
    enterSize(cols, "Unesi duzinu kolona: ");
    std::cout<<std::endl;

    WritableGeneracije generacije {};

    allocateGenerations(generacije, rows, cols);

    enterGeneracije(generacije, rows, cols);
    printGeneracije(generacije, rows, cols);

    const std::size_t bestGenerationByProsjek { getIndexForBestOrWorstGenerationByProsjekOcjena(generacije, rows, cols, true) };
    const std::size_t worstPredmetByProsjek { getIndexForBestOrWorstPredmetByProsjekOcjena(generacije, rows, cols) };

    std::cout<<"Index za generaciju sa najboljim prosjekom je "<<bestGenerationByProsjek<<std::endl;
    std::cout<<"Index za predmet sa najgorim prosjekom je "<<worstPredmetByProsjek<<std::endl;

    deallocateGenerations(generacije, rows);

    return 0;
}

void printBreakLine() {
    std::cout<<"-----------------------------------------------\n";
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterSize(std::size_t &size, const char *outputText) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>size;

        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
            repeatLoop = true;
        } else if (size < 2 || size > 1000) {
            std::cout<<"Unos mora biti u intervalu [2, 1000]\n";
            repeatLoop = true;
        }
    } while (repeatLoop);

    clearBuffer();
}

void allocateGenerations(WritableGeneracije &generacije, const std::size_t rows, const std::size_t cols) {
    generacije = new WritableStudenti[rows] {};
    for (std::size_t i = 0; i < rows; i++) {
        generacije[i] = new student[cols];
    }
}

void deallocateGenerations(WritableGeneracije &generacije, const std::size_t rows) {
    for (std::size_t i = 0; i < rows; i++) {
        delete[] generacije[i];
    }
    delete[] generacije;
}

void printFormattedDate(const datum &date, const char * const outputText) {
    std::cout<<outputText;
    std::cout<<date.d<<'.'<<date.m<<'.'<<date.g<<".g.\n";
}

void printStudentiInfo(const student &studentInfo) {
    std::cout<<"IB: "<<studentInfo.IB<<std::endl;
    std::cout<<"Ime i prezime: "<<studentInfo.imeiPrezime<<std::endl;
    printFormattedDate(studentInfo.rodjenja, "Datum rodjenja: ");
    std::cout<<"Prosjecna ocjena: "<<studentInfo.prosjecnaOcjena<<std::endl;
}

void printStudenti(ReadOnlyStudenti studenti, const std::size_t size) {
    for (std::size_t i = 0; i < size; i++) {
        std::cout<<"Informacije za "<<i + 1<<". studenta\n";
        printStudentiInfo(*(studenti + i));
        
        if (i + 1 != size) {
            std::cout<<std::endl;
        }
    }
}

void printGeneracije(ReadOnlyGeneracije generacije, const std::size_t rows, const std::size_t cols) {
    printBreakLine();
    std::cout<<"Ispis informacija o generacijama\n";
    for (std::size_t i = 0; i < rows; i++) {
        std::cout<<"Ispis informacija "<<i + 1<<". generacije\n";
        printStudenti(*(generacije+ i), cols);
        if (i + 1 != rows) {
            std::cout<<"\n\n";
        }
    } 
    printBreakLine();
}

void enterNum(float &num, const char * const outputText, const std::optional<float> min, const std::optional<float> max) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>num;

        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
            repeatLoop = true;
        } else if (min && num < min.value()) {
            std::cout<<"Uneseni broj treba biti veci od "<<min.value()<<std::endl;
            clearBuffer();
            repeatLoop = true;
        } else if (max && num > max.value()) {
            std::cout<<"Uneseni broj treba biti manji od "<<max.value()<<std::endl;
            clearBuffer();
            repeatLoop = true;
        }
    } while(repeatLoop);
}

void enterNum(int &num, const char * const outputText, const std::optional<int> min, const std::optional<int> max) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>num;

        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
            repeatLoop = true;
        } else if (min && num < min.value()) {
            std::cout<<"Uneseni broj treba biti veci od "<<min.value()<<std::endl;
            clearBuffer();
            repeatLoop = true;
        } else if (max && num > max.value()) {
            std::cout<<"Uneseni broj treba biti manji od "<<max.value()<<std::endl;
            clearBuffer();
            repeatLoop = true;
        }
    } while(repeatLoop);
}

void enterDate(datum &date, const char * const outputText) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>date.d>>date.m>>date.g;

        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
            repeatLoop = true;
        } else if (!isValidDate(&date)) {
            std::cout<<"Nevalidan datum\n";
            clearBuffer();
            repeatLoop = true;
        }

    } while(repeatLoop);
}

bool isValidDate(const datum * const date) {
    if (date->g < 1 || date->g > 4000) {
        return false;
    } else if (date->m < 1 || date->m > 12) {
        return false;
    } else if (date->d < 1 || date->d > getDayForMonth(date->m, date->g)) {
        return false;
    }

    return true;
}

bool isLeapYear(const int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

unsigned int getDayForMonth(const int month, const int year) {
    const bool isLeap { isLeapYear(year) };

    switch(month) {
        case 2:
            return 28 + isLeap;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        default:
            return 31;
    }
}

void enterStudentInfo(student &studentInfo) {
    enterNum(studentInfo.IB, "Unesi IB: ", 0);

    clearBuffer();
    std::cout<<"Unesi ime i prezime: ";
    std::cin.getline(studentInfo.imeiPrezime, FULLNAME_SIZE);

    enterDate(studentInfo.rodjenja, "Unesi datum rodenja: ");
    enterNum(studentInfo.prosjecnaOcjena, "Unesi prosjek ocjena: ", 0, 10);
}

void enterStudenti(WritableStudenti studenti, const std::size_t size) {
    for (std::size_t i = 0; i < size; i++) {
        std::cout<<"Unos informacija za "<<i + 1<<". studenta\n";
        enterStudentInfo(*(studenti + i));         
        
        if (i + 1 != size) {
            std::cout<<std::endl;
        }
    }
}

void enterGeneracije(WritableGeneracije generacije, const std::size_t rows, const std::size_t cols) {
    printBreakLine();
    std::cout<<"Unos informacija o generacijama\n";
    for (std::size_t i = 0; i < rows; i++) {
        std::cout<<"Unos informacija "<<i + 1<<". generacije\n";
        enterStudenti(*(generacije+ i), cols);
        if (i + 1 != rows) {
            std::cout<<"\n\n";
        }
    } 
    printBreakLine();
}

float getProsjekForStudentiByRow(ReadOnlyGeneracije generacije, const std::size_t rowToFind, const std::size_t cols) {
    float prosjek { 0.0f };

    for (std::size_t i = 0; i < cols; i++) {
        prosjek += generacije[rowToFind][i].prosjecnaOcjena;
    }
    
    return prosjek / cols;
}

float getProsjekForStudentiByCol(ReadOnlyGeneracije generacije, const std::size_t rows, const std::size_t colToFind) {
    float prosjek { 0.0f };

    for (std::size_t i = 0; i < rows; i++) {
        prosjek += generacije[i][colToFind].prosjecnaOcjena;
    }

    return prosjek / rows;
}

std::size_t getIndexForBestOrWorstGenerationByProsjekOcjena(ReadOnlyGeneracije generacije, const std::size_t rows, const std::size_t cols, const bool findBest) {
    std::size_t foundIndex { 0 };
    float currentIndexProsjek { getProsjekForStudentiByRow(generacije, foundIndex, cols) };
    float tempProsjek {};

    for (std::size_t i = 1; i < rows; i++) {
        tempProsjek = getProsjekForStudentiByRow(generacije, i, cols);

        if (findBest && tempProsjek > currentIndexProsjek) {
            currentIndexProsjek = tempProsjek;
            foundIndex = i;
        } else if (!findBest && tempProsjek < currentIndexProsjek) {
            currentIndexProsjek = tempProsjek;
            foundIndex = i;
        }

        if (findBest && currentIndexProsjek == 10) {
            break;
        } else if (!findBest && currentIndexProsjek == 0) {
            break;
        }
    }

    // Debugging
    // std::cout<<currentIndexProsjek<<std::endl;

    return foundIndex;
}

std::size_t getIndexForBestOrWorstPredmetByProsjekOcjena(ReadOnlyGeneracije generacije, const std::size_t rows, const std::size_t cols, const bool findBest) {
    std::size_t foundIndex { 0 };
    float currentIndexProsjek { getProsjekForStudentiByCol(generacije, rows, foundIndex) };
    float tempProsjek {};

    for (std::size_t i = 1; i < cols; i++) {
        tempProsjek = getProsjekForStudentiByCol(generacije, rows, i);

        if (findBest && tempProsjek > currentIndexProsjek) {
            currentIndexProsjek = tempProsjek;
            foundIndex = i;
        } else if (!findBest && tempProsjek < currentIndexProsjek) {
            currentIndexProsjek = tempProsjek;
            foundIndex = i;
        }

        if (findBest && currentIndexProsjek == 10) {
            break;
        } else if (!findBest && currentIndexProsjek == 0) {
            break;
        }
    }

    // Debugging
    // std::cout<<currentIndexProsjek<<std::endl;

    return foundIndex;
}