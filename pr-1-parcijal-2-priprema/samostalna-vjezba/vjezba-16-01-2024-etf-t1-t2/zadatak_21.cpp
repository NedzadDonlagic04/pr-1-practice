#include<iostream>
#include<ctime>
#include<iomanip>

void getCurrentTimeInfo(unsigned int &, unsigned int &, unsigned int &);

void printDogFeedingInfo(const unsigned int, const unsigned int, const unsigned int);
void printCatFeedingInfo(const unsigned int, const unsigned int);
void printTurtleFeedingInfo(const unsigned int, const unsigned int);

int main() {
    unsigned int hours {};
    unsigned int minutes {};
    unsigned int weekDay {};

    getCurrentTimeInfo(hours, minutes, weekDay);

    if (hours < 8) {
        std::cout<<"Ljubimci ne smiju jesti prije 08:00h gospodo!\n";
    } else {
        std::cout<<std::setprecision(2)<<std::fixed;
        printDogFeedingInfo(hours, minutes, weekDay);
        printCatFeedingInfo(hours, weekDay);
        printTurtleFeedingInfo(hours, weekDay);
    }

    return 0;
}

void getCurrentTimeInfo(unsigned int &hours, unsigned int &minutes, unsigned int &weekDay) {
    const std::time_t currentTime = std::time(0);   // get time now
    const std::tm* currentFormattedTime = std::localtime(&currentTime);

    hours = currentFormattedTime->tm_hour;
    minutes = currentFormattedTime->tm_min;
    weekDay = currentFormattedTime->tm_wday;

    if (weekDay == 0) {
        weekDay = 7;
    }
}

void printDogFeedingInfo(const unsigned int hours, const unsigned int minutes, const unsigned int weekDay) {
    if ((hours * 60 + minutes) > 18 * 60) {
        std::cout<<"Pas treba da jede "<<weekDay * 7<<" krekera\n";
    } else {
        const float totalFoodKg { (hours + minutes + weekDay) / 34.0f };
        const float meatPercent { totalFoodKg / 3 };

        std::cout<<"Pas treba da jede "<<totalFoodKg<<"kg hrane, ";
        std::cout<<"od toga je "<<meatPercent<<"kg mesa i ";
        std::cout<<totalFoodKg - meatPercent<<"kg ostale hrane\n";
    }
}

void printCatFeedingInfo(const unsigned int hours, const unsigned int weekDay) {
    const float totalFoodKg { ((2 * hours) / 40.0f) + (weekDay / 7.0f) };

    std::cout<<"Macka treba da jede "<<totalFoodKg<<"kg macije hrane\n";
}

void printTurtleFeedingInfo(const unsigned int hours, const unsigned int weekDay) {
    const float totalFoodKg { (7.0f + hours) / (weekDay + 154) };

    std::cout<<"Kornjaca treba da jede "<<totalFoodKg<<"kg hrane za kornjace\n";

    if (weekDay == 4) {
        std::cout<<"Takoder je kornjaci potrebno staviti kalcij u obrok\n";
    }
}