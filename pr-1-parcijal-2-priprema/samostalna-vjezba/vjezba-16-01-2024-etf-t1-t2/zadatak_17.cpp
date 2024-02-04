#include<iostream>
#include<limits>

void clearBuffer();
void enterDate(int &, int &, int &, const char * const);

[[nodiscard]] bool isValidDate(const int, const int, const int);
[[nodiscard]] bool isLeapYear(const int);
[[nodiscard]] unsigned int getDayForMonth(const int, const int);
[[nodiscard]] const char* getWordForMonth(const int);

int main() {
    int day {}, month {}, year {};

    enterDate(day, month, year, "Unesite dan, mjesec i godinu (razdvojite razmakom): ");    

    std::cout<<"Uneseni datum je "<<day<<". "<<getWordForMonth(month)<<' ';
    std::cout<<year<<". godine\n";

    return 0;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterDate(int &day, int &month, int &year, const char * const outputText) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>day>>month>>year;

        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
            repeatLoop = true;
        } else if (!isValidDate(day, month, year)) {
            std::cout<<"Nevalidan datum\n";
            clearBuffer();
            repeatLoop = true;
        }

    } while(repeatLoop);
}

bool isValidDate(const int day, const int month, const int year) {
    if (year < 1 || year > 4000) {
        return false;
    } else if (month < 1 || month > 12) {
        return false;
    } else if (day < 1 || day > getDayForMonth(month, year)) {
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
const char* getWordForMonth(const int month) {
    switch(month) {
        case 1:
            return "januar";
        case 2:
            return "februar";
        case 3:
            return "mart";
        case 4:
            return "april";
        case 5:
            return "maj";
        case 6:
            return "juni";
        case 7:
            return "juli";
        case 8:
            return "august";
        case 9:
            return "septembar";
        case 10:
            return "oktobar";
        case 11:
            return "novembar";
        default:
            return "decembar";
    }
}