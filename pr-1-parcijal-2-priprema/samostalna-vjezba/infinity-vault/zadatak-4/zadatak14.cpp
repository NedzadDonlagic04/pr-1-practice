#include<iostream>
#include<cstddef>
#include<limits>

constexpr std::size_t MAX_BUFFER_SIZE { 256 };

struct student {
    char *ID {};
    char *imePrezime {};
    float *prosjek{};

    student() = default;
    ~student();

    void freeStudent();
    void printStudentInfo() const;

    void setStudentInfo(char * const, char * const, float * const);

    [[nodiscard]] float getProsjek() const;
    [[nodiscard]] const char* getID() const;
};

student::~student() {
    this->freeStudent();
}

void student::freeStudent() {
    delete this->ID;
    delete this->imePrezime;
    delete this->prosjek;

    this->ID = nullptr;
    this->imePrezime = nullptr;
    this->prosjek = nullptr;
}

void student::printStudentInfo() const {
    std::cout<<"ID: "<<this->ID<<'\n';
    std::cout<<"Ime i prezime: "<<this->imePrezime<<'\n';
    std::cout<<"Prosjek: "<<*this->prosjek<<'\n';
}

void student::setStudentInfo(char * const ID, char * const imePrezime, float * const prosjek) {
    this->ID = ID;
    this->imePrezime = imePrezime;
    this->prosjek = prosjek;
}

float student::getProsjek() const {
    return *this->prosjek;
}

const char* student::getID() const {
    return this->ID;
}

void printBreakLine();
void clearBuffer();
void enterSize(std::size_t &, const char * const);

void handleCStringInput(char *, const std::size_t, const char * const);
void handleNumberInput(float *, const char * const, const int, const int);

// Types intended to be used only for reading
using ReadOnlyStudenti = const student * const; 
using ReadOnlyFakulteti = ReadOnlyStudenti * const;

// Types intended to be used only for writing 
using WritableStudenti = student *;
using WritableFakulteti = WritableStudenti*;

void allocateStudenti(WritableStudenti &, const std::size_t);
void deallocateStudenti(WritableStudenti &);

void allocateFakulteti(WritableFakulteti &, const std::size_t, const std::size_t);
void deallocateFakulteti(WritableFakulteti &, const std::size_t);

void printStudenti(ReadOnlyStudenti, const std::size_t);
void printFakulteti(ReadOnlyFakulteti, const std::size_t, const std::size_t);

void enterStudenti(WritableStudenti, const std::size_t);
void enterFakulteti(WritableFakulteti, const std::size_t, const std::size_t);

[[nodiscard]] float getWholeFakultetProsjek(ReadOnlyStudenti, const std::size_t);
std::size_t getFakultetWithBestProsjek(ReadOnlyFakulteti, const std::size_t, const std::size_t);

[[nodiscard]] const student& getStudentWithBestProsjek(ReadOnlyFakulteti, const std::size_t, const std::size_t);

int main() {
    std::size_t rows {}, cols {};

    enterSize(rows, "Unesi duzinu redova: ");
    enterSize(cols, "Unesi duzinu kolona: ");
    std::cout<<std::endl;

    WritableFakulteti fakulteti {};

    allocateFakulteti(fakulteti, rows, cols);

    enterFakulteti(fakulteti, rows, cols);
    printFakulteti(fakulteti, rows, cols);

    getFakultetWithBestProsjek(fakulteti, rows, cols);
    const student &bestStudent { getStudentWithBestProsjek(fakulteti, rows, cols) }; 

    printBreakLine();
    bestStudent.printStudentInfo();
    printBreakLine();

    deallocateFakulteti(fakulteti, rows);

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

void handleCStringInput(char *input, const std::size_t bufferSize, const char *outputText) {
    std::cout<<outputText;
    std::cin.getline(input, bufferSize);
}

void handleNumberInput(float *input, const char *outputText, const int min, const int max) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>*input;

        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
            repeatLoop = true;
        } else if (*input < min || *input > max) {
            std::cout<<"Unos treba biti u intervalu ["<<min<<", "<<max<<"]\n";
            repeatLoop = true;
        }
    } while(repeatLoop);

    clearBuffer();
}

void allocateStudenti(WritableStudenti &studenti, const std::size_t size) {
    studenti = new student[size];
}

void deallocateStudenti(WritableStudenti &studenti) {
    delete[] studenti;

    studenti = nullptr;
}

void allocateFakulteti(WritableFakulteti &fakulteti, const std::size_t rows, const std::size_t cols) {
    fakulteti = new WritableStudenti[rows];

    for (std::size_t i = 0; i < rows; i++) {
        allocateStudenti(fakulteti[i], cols);
    }
}

void deallocateFakulteti(WritableFakulteti &fakulteti, const std::size_t rows) {
    for (std::size_t i = 0; i < rows; i++) {
        deallocateStudenti(fakulteti[i]);
    }

    delete[] fakulteti;

    fakulteti = nullptr;
}

void printStudenti(ReadOnlyStudenti studenti, const std::size_t size) {
    for (std::size_t i = 0; i < size; i++) {
        std::cout<<"Informacije za "<<i + 1<<". studenta\n";
        (studenti + i)->printStudentInfo();
        if (i + 1 != size) {
            std::cout<<std::endl;
        }
    }
}

void printFakulteti(ReadOnlyFakulteti fakulteti, const std::size_t rows, const std::size_t cols) {
    printBreakLine();
    std::cout<<"Ispis informacija o univerzitetu\n";
    for (std::size_t i = 0; i < rows; i++) {
        std::cout<<"Ispis studenata "<<i + 1<<". fakulteta\n";
        printStudenti(*(fakulteti + i), cols);
        if (i + 1 != rows) {
            std::cout<<"\n\n";
        }
    } 
    printBreakLine();
}

void enterStudenti(WritableStudenti studenti, const std::size_t size) {            
    for (std::size_t i = 0; i < size; i++) {
        char *ID { new char[MAX_BUFFER_SIZE] {} };
        char *imePrezime { new char[MAX_BUFFER_SIZE] {} };
        float *prosjek { new float {} };
        
        std::cout<<"Unesi podatke za "<<i + 1<<". studenta\n";
            
        handleCStringInput(ID, MAX_BUFFER_SIZE, "Unesi ID: ");
        handleCStringInput(imePrezime, MAX_BUFFER_SIZE, "Unesi ime i prezime: ");
        handleNumberInput(prosjek, "Unesi prosjek: ", 0, 10);

        (studenti + i)->setStudentInfo(ID, imePrezime, prosjek);
        
        std::cout<<std::endl;
    }
}

void enterFakulteti(WritableFakulteti fakulteti, const std::size_t rows, const std::size_t cols) {
    for (std::size_t i = 0; i < rows; i++) {
        std::cout<<"Unos podataka "<<i + 1<<". kosarkasa\n";
        enterStudenti(*(fakulteti + i), cols); 
        std::cout<<std::endl;
    } 
}

float getWholeFakultetProsjek(ReadOnlyStudenti studenti, const std::size_t size) {
    float average { 0.0f };

    for (std::size_t i = 0; i < size; i++) {
        average += (studenti + i)->getProsjek();
    }

    return average / size;
}

std::size_t getFakultetWithBestProsjek(ReadOnlyFakulteti fakulteti, const std::size_t rows, const std::size_t cols) {
    std::size_t bestIndex { 0 };
    float bestAverage { getWholeFakultetProsjek(*fakulteti, cols) };
    float tempAverage {};

    for (std::size_t i = 0; i < rows; i++) {
        tempAverage = getWholeFakultetProsjek(*(fakulteti + i), cols);

        if (tempAverage > bestAverage) {
            bestAverage = tempAverage;
            bestIndex = i;
        }

        if (bestAverage == 10) {
            break;
        }
    }

    printBreakLine();
    std::cout<<"Index najboljeg fakulteta po prosjeku je: "<<bestIndex<<std::endl;
    printBreakLine();

    return bestIndex;
}

const student& getStudentWithBestProsjek(ReadOnlyFakulteti fakulteti, const std::size_t rows, const std::size_t cols) {
    std::size_t bestRow {}, bestCol {};
    float bestProsjek {}, tempProsjek {};

    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t ii = 0; ii < cols; ii++) {
            tempProsjek = (*(fakulteti + i) + ii)->getProsjek();

            if (i == 0 && ii == 0) {
                bestRow = i;
                bestCol = ii;
                bestProsjek = tempProsjek;
            } else if (bestProsjek < tempProsjek) {
                bestRow = i;
                bestCol = ii;
                bestProsjek = tempProsjek;
            }
        }
    }

    return *(*(fakulteti + bestRow) + bestCol);
}
