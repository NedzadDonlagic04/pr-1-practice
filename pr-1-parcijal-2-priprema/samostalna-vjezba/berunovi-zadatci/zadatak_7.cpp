#include<iostream>
#include<limits>
#include<optional>

struct Datum { 
    int dan; 
    int mjesec; 
    int godina; 
 
    void unos(); 
    void ispis(); 
    bool isValid(); 
    int toInt(); 
}; 

Datum& min(Datum&, Datum&);
Datum& max(Datum&, Datum&);
int getDifferenceBetween(Datum&, Datum&);
Datum* getClosestDate(Datum*, int, Datum&);

[[nodiscard]] unsigned int getDayForMonth(const unsigned int, const unsigned int);
[[nodiscard]] bool isLeapYear(const unsigned int);

void clearBuffer();
void enterSize(std::size_t &, const char * const);

void allocateDates(Datum *&, const std::size_t);
void deallocateDates(Datum *&);

void enterNum(int &, const char * const, const std::optional<int> = std::nullopt, const std::optional<int> = std::nullopt);
void enterDates(Datum * const, const std::size_t);

void printDates(Datum * const, const std::size_t);

int main() {
    std::size_t size {};
    Datum * arr {};
    Datum datumZaPretragu {};

    enterSize(size, "Unesite dimenzije niza datuma: ");

    allocateDates(arr, size);

    enterDates(arr, size);
    printDates(arr, size);

    std::cout<<"Unosenje novog datuma za pretragu...\n";
    datumZaPretragu.unos();

    Datum * const closestDate { getClosestDate(arr, size, datumZaPretragu) };

    std::cout<<"Najblizi datum unesenom je:\n";
    closestDate->ispis();
    std::cout<<std::endl;

    deallocateDates(arr);

    return 0;
}

void Datum::unos() {
    do {
        enterNum(this->dan, "Unesite dan: ", 1, 31);
        enterNum(this->mjesec, "Unesite mjesec: ", 1, 12);
        enterNum(this->godina, "Unesite godinu: ", 1, 10000);

        if (!this->isValid()) {
            std::cout<<"Datum nije validan\n";
            std::cout<<"Molim Vas provjerite kalendar i unesite ponovno\n";
        }
    } while(!this->isValid());
}

void Datum::ispis() {
    std::cout<<this->dan<<'.'<<this->mjesec<<'.'<<this->godina;
}

bool Datum::isValid() {
    return this->dan >= 1 && this->dan <= getDayForMonth(this->mjesec, this->godina);
}

int Datum::toInt() {
    const bool isJanOrFeb { mjesec < 3 };

    const unsigned int month = mjesec + ( isJanOrFeb? 12 : 0 );
    const unsigned int year = godina - ( isJanOrFeb? 1 : 0 );

    return dan + (153 * month + 8) / 5 + year * 365 + year / 4 - year / 100 + year / 400;
}

Datum& min(Datum &d1, Datum &d2) {
    return (d1.toInt() < d2.toInt())? d1 : d2;
}

Datum& max(Datum &d1, Datum &d2) {
    return (d1.toInt() < d2.toInt())? d2 : d1;
}

int getDifferenceBetween(Datum &d1, Datum &d2) {
    return std::abs(d1.toInt() - d2.toInt());
}

Datum* getClosestDate(Datum *arr, int size, Datum &targetDatum) {
    std::size_t closestIndex { 0 };
    unsigned int closestDistance = getDifferenceBetween(arr[closestIndex], targetDatum);
    unsigned int tempDistance {};

    for (std::size_t i = 1; i < size; i++) {
        if (closestDistance == 0) {
            return &arr[closestIndex];
        }

        tempDistance = std::abs(arr[i].toInt() - targetDatum.toInt());

        if (tempDistance < closestDistance) {
            closestIndex = i;
            closestDistance = tempDistance;
        }
    }

    return &arr[closestIndex];
}

unsigned int getDayForMonth(const unsigned int month, const unsigned int year) {
    const bool isLeapYear { (year % 4 == 0 && year % 100 != 0) || year % 400 == 0 };

    switch(month) {
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        case 2:
            return 28 + isLeapYear;
        default:
            return 31;
    } 
}

bool isLeapYear(const unsigned int year) {
    return (year % 4 == 0) || (year % 400 == 0 && year % 100 != 0);
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterSize(std::size_t &size, const char * const outputText) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>size;

        if (std::cin.fail()) {
            std::cout<<"Invalid input\n";
            clearBuffer();
            repeatLoop = true;
        } else if (size < 2 || size > 1000) {
            std::cout<<"Unos treba biti u intervalu [2, 1000]\n";
            clearBuffer();
            repeatLoop = true;
        }
    } while(repeatLoop);
}

void allocateDates(Datum *&arr, const std::size_t size) {
    arr = new Datum[size] {};
}

void deallocateDates(Datum *&arr) {
    delete[] arr;
    arr = nullptr;
}

void enterNum(int &num, const char * const outputText, const std::optional<int> min, const std::optional<int> max) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>num;

        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            repeatLoop = true;
            clearBuffer();
        } else if (min && num < min.value()) {
            std::cout<<"Unos ne smije biti manji od "<<min.value()<<std::endl;
            repeatLoop = true;
            clearBuffer();
        } else if (max && num > max.value()) {
            std::cout<<"Unos ne smije biti veci od "<<max.value()<<std::endl;
            repeatLoop = true;
            clearBuffer();
        }
    } while(repeatLoop);
}

void enterDates(Datum * const arr, const std::size_t size) {
    for (std::size_t i = 0; i < size; i++) {
        std::cout<<"-------------------------------------\n";
        std::cout<<"Unesite datum na lokaciji "<<i<<":\n";
        arr[i].unos();
    }
}

void printDates(Datum * const arr, const std::size_t size) {
    for (std::size_t i = 0; i < size; i++) {
        std::cout<<"Datum "<<i<<": ";
        arr[i].ispis();
        std::cout<<std::endl;
    }
}