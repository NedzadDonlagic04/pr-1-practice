#include<iostream>
#include<cstddef>
#include<limits>
#include<cmath>

constexpr std::size_t MAX_BUFFER_SIZE { 256 };

struct kosarkas {
    char *ID {};
    char *imePrezime {};
    int *postignutiKosevi {};

    kosarkas() = default;
    ~kosarkas();

    void freeKosarkasInfo();
    void printKosarkasInfo() const;

    void setKosarkasInfo(char * const, char * const, int * const);

    int getPostignutiKosevi() const;
};

kosarkas::~kosarkas() {
    this->freeKosarkasInfo();
}

void kosarkas::freeKosarkasInfo() {
    delete this->ID;
    delete this->imePrezime;
    delete this->postignutiKosevi;

    this->ID = nullptr;
    this->imePrezime = nullptr;
    this->postignutiKosevi = nullptr;
}

void kosarkas::printKosarkasInfo() const {
    std::cout<<"ID: "<<this->ID<<'\n';
    std::cout<<"Ime i prezime: "<<this->imePrezime<<'\n';
    std::cout<<"Postignuti kosevi: "<<*this->postignutiKosevi<<'\n';
}

void kosarkas::setKosarkasInfo(char * const ID, char * const imePrezime, int * const postignutiKosevi) {
    this->ID = ID;
    this->imePrezime = imePrezime;
    this->postignutiKosevi = postignutiKosevi;
}

int kosarkas::getPostignutiKosevi() const {
    return *this->postignutiKosevi;
}

void printBreakLine();
void clearBuffer();
void enterSize(std::size_t &, const char * const);

void handleCStringInput(char *, const std::size_t, const char * const);
void handleNumberInput(int *, const char * const, const int);

// Types intended to be used only for reading
using ReadOnlyKlubovi = const kosarkas * const; 
using ReadOnlyKosarkasi = ReadOnlyKlubovi * const;

// Types intended to be used only for writing 
using WritableKlubovi = kosarkas *;
using WritableKosarkasi = WritableKlubovi*;

void allocateKlubovi(WritableKlubovi &, const std::size_t);
void deallocateKlubovi(WritableKlubovi &);

void allocateKosarkasi(WritableKosarkasi &, const std::size_t, const std::size_t);
void deallocateKosarkasi(WritableKosarkasi &, const std::size_t);

void printKlubovi(ReadOnlyKlubovi, const std::size_t);
void printKosarkasi(ReadOnlyKosarkasi, const std::size_t, const std::size_t);

void enterKlubovi(WritableKlubovi, const std::size_t);
void enterKosarkasi(WritableKosarkasi, const std::size_t, const std::size_t);

int getPlayerTotalScoreInAllClubs(ReadOnlyKlubovi, const std::size_t);
ReadOnlyKlubovi getWorstPlayerInEntireLeague(ReadOnlyKosarkasi, const std::size_t, const std::size_t);

std::size_t findBestKlub(ReadOnlyKosarkasi, const std::size_t, const std::size_t);
ReadOnlyKlubovi getBestPlayerFromBestClub(ReadOnlyKosarkasi, const std::size_t, const std::size_t);

void printSkillDiffBetweenPlayers(ReadOnlyKlubovi, ReadOnlyKlubovi, const std::size_t, const char * const);

int main() {
    std::size_t rows {}, cols {};

    enterSize(rows, "Unesi duzinu redova: ");
    enterSize(cols, "Unesi duzinu kolona: ");
    std::cout<<std::endl;

    WritableKosarkasi kosarkasi {};

    allocateKosarkasi(kosarkasi, rows, cols);

    enterKosarkasi(kosarkasi, rows, cols);
    printKosarkasi(kosarkasi, rows, cols);

    ReadOnlyKlubovi worstPlayer { getWorstPlayerInEntireLeague(kosarkasi, rows, cols) };

    printBreakLine();
    std::cout<<"Ispis informacija najgoreg igraca u ligi:\n";
    printKlubovi(worstPlayer, cols);
    printBreakLine();

    ReadOnlyKlubovi bestPlayerFromBestClub { getBestPlayerFromBestClub(kosarkasi, rows, cols) };

    printBreakLine();
    std::cout<<"Ispis informacija najboljeg igraca iz najboljeg tima:\n";
    printKlubovi(worstPlayer, cols);
    printBreakLine();

    printSkillDiffBetweenPlayers(bestPlayerFromBestClub, worstPlayer, cols, "Razlika u postignutim kosevima izmedu ova dva igraca je: ");

    deallocateKosarkasi(kosarkasi, rows);

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

void handleNumberInput(int *input, const char *outputText, const int min) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>*input;

        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
            repeatLoop = true;
        } else if (*input < min) {
            std::cout<<"Unos treba biti veci od "<<min<<'\n';
            repeatLoop = true;
        }
    } while(repeatLoop);

    clearBuffer();
}

void allocateKlubovi(WritableKlubovi &klubovi, const std::size_t size) {
    klubovi = new kosarkas[size];
}

void deallocateKlubovi(WritableKlubovi &klubovi) {
    delete[] klubovi;

    klubovi = nullptr;
}

void allocateKosarkasi(WritableKosarkasi &kosarkasi, const std::size_t rows, const std::size_t cols) {
    kosarkasi = new kosarkas*[rows];

    for (std::size_t i = 0; i < rows; i++) {
        allocateKlubovi(kosarkasi[i], cols);
    }
}

void deallocateKosarkasi(WritableKosarkasi &kosarkasi, const std::size_t rows) {
    for (std::size_t i = 0; i < rows; i++) {
        deallocateKlubovi(kosarkasi[i]);
    }

    delete[] kosarkasi;

    kosarkasi = nullptr;
}

void printKlubovi(ReadOnlyKlubovi klubovi, const std::size_t size) {
    for (std::size_t i = 0; i < size; i++) {
        std::cout<<"Informacije za "<<i + 1<<". klub\n";
        klubovi[i].printKosarkasInfo();
        if (i + 1 != size) {
            std::cout<<std::endl;
        }
    }

}

void printKosarkasi(ReadOnlyKosarkasi kosarkasi, const std::size_t rows, const std::size_t cols) {
    printBreakLine();
    for (std::size_t i = 0; i < rows; i++) {
        std::cout<<"Ispis klubova za "<<i + 1<<". kosarkasa\n";
        printKlubovi(kosarkasi[i], cols);
        if (i + 1 != rows) {
            std::cout<<"\n\n";
        }
    } 
    printBreakLine();
}

void enterKlubovi(WritableKlubovi klubovi, const std::size_t size) {            
    for (std::size_t i = 0; i < size; i++) {
        char *ID { new char[MAX_BUFFER_SIZE] {} };
        char *imePrezime { new char[MAX_BUFFER_SIZE] {} };
        int *postignutiKosevi { new int {} };
        
        std::cout<<"Unesi podatke za "<<i + 1<<". klub\n";
            
        handleCStringInput(ID, MAX_BUFFER_SIZE, "Unesi ID: ");
        handleCStringInput(imePrezime, MAX_BUFFER_SIZE, "Unesi ime i prezime: ");
        handleNumberInput(postignutiKosevi, "Unesi broj postignutih koseva: ", 0);

        klubovi[i].setKosarkasInfo(ID, imePrezime, postignutiKosevi);
        std::cout<<std::endl;
    }
}

void enterKosarkasi(WritableKosarkasi kosarkasi, const std::size_t rows, const std::size_t cols) {
    for (std::size_t i = 0; i < rows; i++) {
        std::cout<<"Unos podataka "<<i + 1<<". kosarkasa\n";
        enterKlubovi(kosarkasi[i], cols); 
        std::cout<<std::endl;
    } 
}

int getPlayerTotalScoreInAllClubs(ReadOnlyKlubovi klubovi, const std::size_t size) {
    int total { 0 };

    for (std::size_t i = 0; i < size; i++) {
        total += klubovi[i].getPostignutiKosevi();
    } 

    return total;
}

int getTotalClubScores(ReadOnlyKosarkasi kosarkasi, const std::size_t rows, const std::size_t clubCol) {
    int total { 0 };

    for (std::size_t i = 0; i < rows; i++) {
        total += kosarkasi[i][clubCol].getPostignutiKosevi();
    }

    return total;
}

ReadOnlyKlubovi getWorstPlayerInEntireLeague(ReadOnlyKosarkasi kosarkasi, const std::size_t rows, const std::size_t cols) {
    std::size_t worstIndex { 0 };
    int worstScore { getPlayerTotalScoreInAllClubs(kosarkasi[worstIndex], cols) };
    int tempWorstScore {};

    for (std::size_t i = 1; i < rows; i++) {
        tempWorstScore = getPlayerTotalScoreInAllClubs(kosarkasi[i], cols);

        if (worstScore > tempWorstScore) {
            worstScore = tempWorstScore;
            worstIndex = i;
        }

        if (worstScore == 0) {
            break;
        }
    } 

    return kosarkasi[worstIndex];
}

std::size_t findBestKlub(ReadOnlyKosarkasi kosarkasi, const std::size_t rows, const std::size_t cols) {
    std::size_t bestKlubIndex { 0 };
    int bestKlubScore { getTotalClubScores(kosarkasi, rows, bestKlubIndex) };
    int tempBestKlubScore {};

    for (std::size_t i = 1; i < cols; i++) {
        tempBestKlubScore = getTotalClubScores(kosarkasi, rows, i);

        if (bestKlubScore < tempBestKlubScore) {
            bestKlubScore = tempBestKlubScore;
            bestKlubIndex = i;
        }
    }

    return bestKlubIndex;
}

ReadOnlyKlubovi getBestPlayerFromBestClub(ReadOnlyKosarkasi kosarkasi, const std::size_t rows, const std::size_t cols) {
    std::size_t bestKlubIndex { findBestKlub(kosarkasi, rows, cols) };

    std::size_t bestPlayerIndex { 0 };
    int bestPlayerScore { kosarkasi[bestPlayerIndex][bestKlubIndex].getPostignutiKosevi() };
    int tempBestPlayerScore {};

    for (std::size_t i = 1; i < rows; i++) {
        tempBestPlayerScore = kosarkasi[i][bestKlubIndex].getPostignutiKosevi();

        if (bestPlayerScore < tempBestPlayerScore) {
            bestPlayerScore = tempBestPlayerScore;
            bestPlayerIndex = i;
        }
    }

    return kosarkasi[bestPlayerIndex];
}

void printSkillDiffBetweenPlayers(ReadOnlyKlubovi kosarkas1, ReadOnlyKlubovi kosarkas2, const std::size_t cols, const char * const outputText) {
    std::cout<<outputText;

    int kosarkas1Total { getPlayerTotalScoreInAllClubs(kosarkas1, cols) }; 
    int kosarkas2Total { getPlayerTotalScoreInAllClubs(kosarkas2, cols) }; 

    std::cout<<std::abs(kosarkas1Total - kosarkas2Total)<<std::endl;
}