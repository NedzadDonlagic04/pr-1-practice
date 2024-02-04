#include<iostream>
#include<memory>
#include<limits>
#include<stdexcept>
#include<cstring>
#include<cmath>
#include<optional>

constexpr std::size_t DAY_SIZE { 15 };
constexpr std::size_t BUFFER_SIZE { 256 };

constexpr char DAYS_IN_WEEK[][DAY_SIZE] = {
    "Subota",
    "Nedelja",
    "Ponedeljak",
    "Utorak",
    "Srijeda",
    "Cetvrtak",
    "Petak",
};

struct Date {
    unsigned int day {};
    unsigned int month {};
    unsigned int year {};

    char dayInWeek[DAY_SIZE] {};

    unsigned long long numericDateValue {};

    Date() = default;
    Date(const unsigned int, const unsigned int, const unsigned int);

    void setDate(const unsigned int, const unsigned int, const unsigned int);
    [[nodiscard]] std::size_t getDayOfWeekIndex() const;
    [[nodiscard]] unsigned long long getNumericDateValue() const;

    [[nodiscard]] bool isDateBigger(const Date &);

    [[nodiscard]] std::unique_ptr<char[]> getFormattedDate() const;
    void printFormattedDate() const;
    void printDateInfo() const;

    [[nodiscard]] static bool isValidDate(const unsigned int, const unsigned int, const unsigned int);
    [[nodiscard]] static unsigned int getDayForMonth(const unsigned int, const unsigned int);
    [[nodiscard]] static unsigned long long calcNumericDateValue(const unsigned int, const unsigned int, const unsigned int);
    [[nodiscard]] static unsigned long long getDistanceBetweenDates(const Date &, const Date &);
};

struct Dates {
    std::unique_ptr<Date[]> dates {};
    const std::size_t size {};

    Dates() = default;
    Dates(const std::size_t);

    std::size_t getSize() const;
};

Dates::Dates(const std::size_t size) : dates(new Date[size] {}), size(size) {}

std::size_t Dates::getSize() const {
    return this->size;
}

void cpystr(const std::unique_ptr<char[]> &, const std::unique_ptr<char[]>, std::size_t &);
[[nodiscard]] std::unique_ptr<char[]> unsignedIntToCharPtr(unsigned int);
[[nodiscard]] unsigned int getDigitCount(const int);

void clearBuffer();
void handleSizeInput(std::size_t &, const char * const);

void enterDate(Date &, const std::size_t);
void enterDate(Date &, const char * const);
void enterDates(const Dates &);

void printDates(const Dates &);

void sortDates(const Dates &);

Date findClosestDate(const Dates &, const Date &);

int main() {
    std::size_t size {};

    handleSizeInput(size, "Enter amount of dates to input: ");

    const Dates dates { size };

    enterDates(dates);
    printDates(dates);
    
    sortDates(dates);

    std::cout<<"\nDate sort finished\n\n";
    printDates(dates);

    Date dateToFind {};
    enterDate(dateToFind, "Enter a date to find: ");

    Date closestDate { findClosestDate(dates, dateToFind) }; 

    std::cout<<"\nInfo about the date who's closest date is being searched for:\n";
    dateToFind.printDateInfo();
    std::cout<<std::endl;

    std::cout<<"Info about the closest date:\n";
    closestDate.printDateInfo();
    std::cout<<std::endl;

    return 0;
}

Date::Date(const unsigned int day, const unsigned int month, const unsigned int year) {
    this->setDate(day, month, year);
}

void Date::setDate(const unsigned int day, const unsigned int month, const unsigned int year) {
    this->day = day;
    this->month = month;
    this->year = year;

    if (!this->isValidDate(day, month, year)) {
        throw std::invalid_argument("Invalid date"); 
    }

    std::size_t dayOfWeekIndex { this->getDayOfWeekIndex() };

    std::strcpy(this->dayInWeek, DAYS_IN_WEEK[dayOfWeekIndex]);

    this->numericDateValue = this->calcNumericDateValue(day, month, year);
}
    
// This function will be implementing the "Zeller's congruence" algorithm from the links below
// https://en.wikipedia.org/wiki/Zeller%27s_congruence
// https://www.themathdoctors.org/zellers-rule-what-day-of-the-week-is-it/
std::size_t Date::getDayOfWeekIndex() const {
    const bool isJanOrFeb { this->month < 3 };

    const unsigned int month = this->month + ( isJanOrFeb? 12 : 0 );
    const unsigned int year = this->year - ( isJanOrFeb? 1 : 0 );

    return (this->day + 13 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) % 7;
}

unsigned long long Date::getNumericDateValue() const {
    return this->numericDateValue;
}

bool Date::isDateBigger(const Date &date) {
    return this->numericDateValue > date.numericDateValue;
}
    
std::unique_ptr<char[]> Date::getFormattedDate() const {
    const std::size_t size { getDigitCount(this->day) + getDigitCount(this->month) + getDigitCount(this->year) + 4 };
    // The 4 is 3 for periods 1 for \0

    std::size_t index { 0 };

    std::unique_ptr<char[]> dateAsCharPtr { new char[size] };

    // Convert the day part and store it inside the date string
    cpystr(dateAsCharPtr, unsignedIntToCharPtr(this->day), index);
    dateAsCharPtr[index++] = '.';

    // Convert the month part and store it inside the date string
    cpystr(dateAsCharPtr, unsignedIntToCharPtr(this->month), index);
    dateAsCharPtr[index++] = '.';

    // Convert the year part and store it inside the date string
    cpystr(dateAsCharPtr, unsignedIntToCharPtr(this->year), index);
    dateAsCharPtr[index++] = '.';

    dateAsCharPtr[index] = '\0';

    return dateAsCharPtr;
}

void Date::printFormattedDate() const {
    std::cout<<this->day<<'.'<<this->month<<'.'<<this->year<<".";
}

void Date::printDateInfo() const {
    std::cout<<this->day<<'.'<<this->month<<'.'<<this->year<<".";
    std::cout<<" = This was a '"<<this->dayInWeek<<"'";
}

bool Date::isValidDate(const unsigned int day, const unsigned int month, const unsigned int year) {
    if (year < 1 || year > 9999) {
        return false;
    } else if (month < 1 || month > 12) {
        return false;
    } else if (day < 1 || day > getDayForMonth(month, year)) {
        return false;
    }
    
    return true;
}

unsigned int Date::getDayForMonth(const unsigned int month, const unsigned int year) {
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

unsigned long long Date::calcNumericDateValue(const unsigned int day, const unsigned int month, const unsigned int year) {
    return day + month * 32ULL + year * 512ULL; 
    //                    2^5            2^9
}

unsigned long long Date::getDistanceBetweenDates(const Date &date1, const Date &date2) {
    unsigned long long longerDistance { std::max(date1.getNumericDateValue(), date2.getNumericDateValue()) };
    unsigned long long shorterDistance { std::min(date1.getNumericDateValue(), date2.getNumericDateValue()) };

    return longerDistance - shorterDistance;
}

unsigned int getDigitCount(const int num) {
    if (num == 0) {
        return 1;
    }

    return std::log10(std::abs(num)) + 1;
}

std::unique_ptr<char[]> unsignedIntToCharPtr(unsigned int num) {
    const std::size_t size { getDigitCount(num) + 1 };

    std::unique_ptr<char[]> numAsCharPtr { new char[size] {} };

    for (std::ptrdiff_t i = size - 2; i >= 0; i--) {
        numAsCharPtr[i] = (num % 10) + '0';
		num /= 10;
    }

    numAsCharPtr[size - 1] = '\0';

    return numAsCharPtr;
}

void cpystr(const std::unique_ptr<char[]> &str1, const std::unique_ptr<char[]> str2, std::size_t &startStr1Index) {
    for (std::size_t i = 0; str2[i] != '\0'; i++) {
        str1[startStr1Index++] = str2.get()[i];
    }
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void handleSizeInput(std::size_t &size, const char * const outputText) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>size;

        if (std::cin.fail()) {
            std::cout<<"Invalid size input\n";
            clearBuffer();
            repeatLoop = true;
        } else if (size < 2 || size > 1000) {
            std::cout<<"Size has to be in range [2, 1000]\n";
            repeatLoop = true;
        }
    } while(repeatLoop);
}

void enterDate(Date &date, const std::size_t index) {
    bool repeatLoop {};

    unsigned int day {}, month {}, year {};

    do {
        repeatLoop = false;

        std::cout<<"Enter date "<<index + 1<<": ";
        std::cin>>day>>month>>year;

        if (std::cin.fail()) {
            std::cout<<"Invalid input, make sure to properly space the date, I.E. '18 2 2004'\n";
            clearBuffer();
            repeatLoop = true;
        } else if (!Date::isValidDate(day, month, year)) {
            std::cout<<"Invalid date, check your calendar to be sure it exists\n";
            clearBuffer();
            repeatLoop = true;
        }
    } while(repeatLoop);

    date.setDate(day, month, year);
}

void enterDate(Date &date, const char * const outputText) {
    bool repeatLoop {};

    unsigned int day {}, month {}, year {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>day>>month>>year;

        if (std::cin.fail()) {
            std::cout<<"Invalid input, make sure to properly space the date, I.E. '18 2 2004'\n";
            clearBuffer();
            repeatLoop = true;
        } else if (!Date::isValidDate(day, month, year)) {
            std::cout<<"Invalid date, check your calendar to be sure it exists\n";
            clearBuffer();
            repeatLoop = true;
        }
    } while(repeatLoop);

    date.setDate(day, month, year);
}

void enterDates(const Dates &dates) {
    std::cout<<"Time to enter all the dates!\n";
    for (std::size_t i = 0; i < dates.getSize(); i++) {
        enterDate(dates.dates[i], i);
    }    
}

void printDates(const Dates &dates) {
    std::cout<<"Dates output\n";
    for (std::size_t i = 0; i < dates.getSize(); i++) {
        // std::cout<<"Date "<<i + 1<<": "<<dates.dates[i].getFormattedDate().get()<<std::endl;
        std::cout<<"Date "<<i + 1<<" info: ";
        dates.dates[i].printDateInfo();
        std::cout<<std::endl;
    }    
}

// Implements insertion sort
void sortDates(const Dates &dates) {
    for (std::size_t i = 1; i < dates.getSize(); i++) {
        for (std::size_t ii = i; ii >= 1 && dates.dates[ii].isDateBigger(dates.dates[ii - 1]); ii--) {
            if (dates.dates[ii].isDateBigger(dates.dates[ii - 1])) {
                std::swap(dates.dates[ii], dates.dates[ii - 1]);
            }
        }
    }
}

Date findClosestDate(const Dates &dates, const Date &date) {
    std::size_t closestDateIndex { 0 };
    unsigned long long closestDistance{ Date::getDistanceBetweenDates(dates.dates[closestDateIndex], date) };
    unsigned long long tempDistance {};

    for (std::size_t i = 1; i < dates.getSize(); i++) {
        tempDistance = Date::getDistanceBetweenDates(dates.dates[i], date);

        if (tempDistance < closestDistance) {
            closestDateIndex = i;
            closestDistance = tempDistance;
        }
    }

    return dates.dates[closestDateIndex];
}