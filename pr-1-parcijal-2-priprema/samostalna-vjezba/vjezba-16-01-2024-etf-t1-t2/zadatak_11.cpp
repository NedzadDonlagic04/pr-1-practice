#include<iostream>
#include<cmath>
#include<limits>
#include<memory>

struct Time {
    unsigned int days {};
    unsigned int hours {};
    unsigned int minutes {};
    unsigned int seconds {}; 

    Time() = default;
    Time(const int);

    [[nodiscard]] std::unique_ptr<char[]> getFormattedTime() const;
};

[[nodiscard]] unsigned int countDigits(const int);
[[nodiscard]] std::unique_ptr<char[]> intToCharPtr(int);

void clearBuffer();
void enterNum(int &, const char * const);

int main() {
    int seconds {};

    enterNum(seconds, "Unesite broj sekundi: ");

    Time time(seconds);

    std::cout<<"Pretvoreno: "<<time.getFormattedTime().get()<<std::endl;

    return 0;
}

Time::Time(int seconds) {
    this->days = seconds / 86400;
    seconds -= this->days * 86400;

    this->hours = seconds / 3600;
    seconds -= this->hours * 3600;

    this->minutes = seconds / 60;
    seconds -= this->minutes * 60;

    this->seconds = seconds;

    // Debugging
/*     std::cout<<this->days<<"d "<<this->hours<<"h "<<this->minutes<<"m ";
    std::cout<<this->seconds<<"s\n"; */
}

std::unique_ptr<char[]> Time::getFormattedTime() const {
    std::unique_ptr<char[]> formattedTime { new char[100] };

    std::sprintf(formattedTime.get(), "%ud %uh %um %us", this->days, this->hours, this->minutes, this->seconds);

    return formattedTime;
}

unsigned int countDigits(const int num) {
    if (num < 0) {
        return 1;
    }

    const bool isNeg { num < 0 };

    return std::log10(std::abs(num)) + 1 + isNeg;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterNum(int &num, const char * const outputText) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>num;

        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
            repeatLoop = true;
        } else if (num < 0) {
            std::cout<<"Unos ne moze biti broj manji od 0\n";
            clearBuffer();
            repeatLoop = true;
        }
    } while(repeatLoop);
}