#include<iostream>
#include<cstddef>
#include<limits>

// Struktura uzeta iz opisa zadatka
struct fudbaler {
    int *godRodjenja {};
    int *brojIgraca {};
    int *golovi {};

    fudbaler();
    ~fudbaler();

    void setFudbalerInfo(const int, const int, const int);
    void printFudbalerInfo() const;
    void freeFudbalerInfo();

    int getGolovi() const;
};

fudbaler::fudbaler() : godRodjenja(nullptr), brojIgraca(nullptr), golovi(nullptr) {}

fudbaler::~fudbaler() {
    this->freeFudbalerInfo();    
}
    
void fudbaler::setFudbalerInfo(const int godRodjenja, const int brojIgraca, const int golovi) {
    this->freeFudbalerInfo();

    this->godRodjenja = new int{ godRodjenja };
    this->brojIgraca = new int{ brojIgraca };
    this->golovi = new int{ golovi };
}

void fudbaler::printFudbalerInfo() const {
    std::cout<<"(God. rodenja: "<<*this->godRodjenja<<", Broj igraca: "<<*this->brojIgraca<<", Golovi: "<<*this->golovi<<")";
}

void fudbaler::freeFudbalerInfo() {
    delete this->godRodjenja;
    delete this->brojIgraca;
    delete this->golovi;

    this->godRodjenja = nullptr;
    this->brojIgraca = nullptr;
    this->golovi = nullptr;
}
    
int fudbaler::getGolovi() const {
    return *this->golovi;
}

void clearBuffer();
void enterSize(std::size_t &, const char *);

using FudbalerTeam = const fudbaler * const;

void allocateFudbalers(fudbaler **&, const std::size_t, const std::size_t);
void deallocateFudbalers(fudbaler **, const std::size_t);

void printFudbalersInfo(FudbalerTeam * const, const std::size_t, const std::size_t);
void enterFudbalersInfo(fudbaler **, const std::size_t, const std::size_t, const bool = false);

void printSpecificTeamInfo(FudbalerTeam, const std::size_t, const char *);

FudbalerTeam findBestOrWorstTeamByGoals(FudbalerTeam * const, const std::size_t, const std::size_t, const bool = false); 
const fudbaler& findBestOrWorstPlayerByGoals(FudbalerTeam, const std::size_t, const bool = false);

void enterNum(int &, const int, const int, const char *);

int generateRandomNum(const int, const int);

int main() {
    std::size_t rows {}, cols {};

    enterSize(rows, "Unesi duzinu redova: ");
    enterSize(cols, "Unesi duzinu kolona: ");

    fudbaler **fudbaleri {};

    allocateFudbalers(fudbaleri, rows, cols);

    enterFudbalersInfo(fudbaleri, rows, cols, true);
    //                                          ^ change this to false to have user input
    printFudbalersInfo(fudbaleri, rows, cols);

    FudbalerTeam bestTeam { findBestOrWorstTeamByGoals(fudbaleri, rows, cols) };
    FudbalerTeam worstTeam { findBestOrWorstTeamByGoals(fudbaleri, rows, cols, true) };

    printSpecificTeamInfo(bestTeam, cols, "Najbolji tim:\n");
    printSpecificTeamInfo(worstTeam, cols, "Najgori tim:\n");

    const fudbaler &bestPlayer { findBestOrWorstPlayerByGoals(worstTeam, cols) };
    const fudbaler &worstPlayer { findBestOrWorstPlayerByGoals(worstTeam, cols, true) };

    std::cout<<"Od najgoreg tima, najbolji igrac je ";
    bestPlayer.printFudbalerInfo();
    std::cout<<", a najgori igrac je ";
    worstPlayer.printFudbalerInfo();
    std::cout<<std::endl;

    deallocateFudbalers(fudbaleri, rows);

    return 0;
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
}

void allocateFudbalers(fudbaler **&fudbaleri, const std::size_t rows, const std::size_t cols) {
    fudbaleri = new fudbaler*[rows];

    for (std::size_t i = 0; i < rows; i++) {
        *(fudbaleri + i) = new fudbaler[cols];
    }
}

void deallocateFudbalers(fudbaler **fudbaleri, const std::size_t rows) {
    for (std::size_t i = 0; i < rows; i++) {
        delete[] *(fudbaleri + i);
    }

    delete[] fudbaleri;
}

void printFudbalersInfo(FudbalerTeam * const fudbaleri, const std::size_t rows, const std::size_t cols) {
    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t ii = 0; ii < cols; ii++) {
            (*(fudbaleri + i) + ii)->printFudbalerInfo();
        }
        std::cout<<std::endl;
    } 
}

void enterFudbalersInfo(fudbaler **fudbaleri, const std::size_t rows, const std::size_t cols, const bool generateTestValues) {
    if (generateTestValues) {
        std::srand(time(NULL));
    }

    int godRodjenja {}, brojIgraca {}, golovi {};

    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t ii = 0; ii < cols; ii++) {
            if (generateTestValues) {
                godRodjenja = generateRandomNum(1980, 2000);
                brojIgraca = generateRandomNum(1, 30);
                golovi = generateRandomNum(0, 4);
            } else {
                std::cout<<"Unesi podatke za fudbalera ["<<i<<"]["<<ii<<"]\n";

                enterNum(godRodjenja, 1980, 2000, "Unesi godine rodenja igraca: ");
                enterNum(brojIgraca, 1, 30, "Unesite broj dresa igraca: ");
                enterNum(golovi, 0, 4, "Unesi broj golova igraca: ");
            }
            (*(fudbaleri + i) + ii)->setFudbalerInfo(godRodjenja, brojIgraca, golovi);
        }
    } 
}

void printSpecificTeamInfo(FudbalerTeam fudbaleri, const std::size_t size, const char *outputText) {
    std::cout<<outputText;
    for (std::size_t i = 0; i < size; i++) {
        (fudbaleri + i)->printFudbalerInfo();
    }
    std::cout<<std::endl;
}

FudbalerTeam findBestOrWorstTeamByGoals(FudbalerTeam * const fudbaleri, const std::size_t rows, const std::size_t cols, const bool findWorst) {
    std::size_t teamIndex {};
    float prosjekGolova {}, tempProsjekGolova {}; 
    
    for (std::size_t i = 0; i < rows; i++) {
        tempProsjekGolova = 0;

        for (std::size_t ii = 0; ii < cols; ii++) {
            tempProsjekGolova += (*(fudbaleri + i) + ii)->getGolovi();
        }

        tempProsjekGolova /= cols;

        if (i == 0) {
            teamIndex = i;
            prosjekGolova = tempProsjekGolova;
        } else if (findWorst && prosjekGolova > tempProsjekGolova) {
            teamIndex = i;
            prosjekGolova = tempProsjekGolova;
        } else if (!findWorst && prosjekGolova < tempProsjekGolova) {
            teamIndex = i;
            prosjekGolova = tempProsjekGolova;
        }
    }

    return *(fudbaleri + teamIndex);
}

const fudbaler& findBestOrWorstPlayerByGoals(FudbalerTeam fudbaleri, const std::size_t size, const bool findWorst) {
    std::size_t playerIndex {};
    int brojGolova {};
    
    for (std::size_t i = 0; i < size; i++) {
        if (i == 0) {
            playerIndex = i;
            brojGolova = (fudbaleri + i)->getGolovi();
        } else if (findWorst && brojGolova > (fudbaleri + i)->getGolovi()) {
            playerIndex = i;
            brojGolova = (fudbaleri + i)->getGolovi();
        } else if (!findWorst && brojGolova < (fudbaleri + i)->getGolovi()) {
            playerIndex = i;
            brojGolova = (fudbaleri + i)->getGolovi();
        }
    }

    return *(fudbaleri + playerIndex);
}

void enterNum(int &num, const int min, const int max, const char *text) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<text;
        std::cin>>num;
        
        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
            repeatLoop = true;
        } else if (num < min || num > max) {
            std::cout<<"Unos treba biti u intervalu ["<<min<<", "<<max<<"]\n";
            repeatLoop = true;
        }
    } while(repeatLoop);
}

int generateRandomNum(const int from, const int to) {
    return std::rand() % (to - from + 1) + from;
}