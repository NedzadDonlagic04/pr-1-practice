#include<iostream>
#include<numeric>
#include<optional>
#include<iomanip>
#include<limits>

constexpr std::size_t ARR_SIZE { 5 };

void clearBuffer();

bool enterGrade(unsigned int &, const std::optional<unsigned int> = std::nullopt, const std::optional<unsigned int> = std::nullopt);
void enterGrades(unsigned int (&)[ARR_SIZE], const char * const);

int main() {
    unsigned int grades[ARR_SIZE] {};

    enterGrades(grades, "Unesite 5. ocjena: ");

    unsigned int sumOfGrades { std::accumulate(grades, grades + ARR_SIZE, 0u) };

    std::cout<<"Zbir unesenih ocjena je "<<sumOfGrades<<", a prosjek je: ";
    std::cout<<std::fixed<<std::setprecision(2)<<static_cast<double>(sumOfGrades) / ARR_SIZE<<std::endl;

    return 0;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool enterGrade(unsigned int &num, const std::optional<unsigned int> min, const std::optional<unsigned int> max) {
    std::cin>>num;

    if (std::cin.fail()) {
        std::cout<<"Nevalidan unos\n";
        clearBuffer();
        return false;
    } else if (min && num < min.value()) {
        std::cout<<"Uneseni broj treba biti veci od "<<min.value()<<std::endl;
        clearBuffer();
        return false;
    } else if (max && num > max.value()) {
        std::cout<<"Uneseni broj treba biti manji od "<<max.value()<<std::endl;
        clearBuffer();
        return false;
    }

    return true;
}

void enterGrades(unsigned int (&arr)[ARR_SIZE], const char * const outputText) {
    std::cout<<outputText;

    for (std::ptrdiff_t i = 0; i < std::size(arr); i++) {
        if (!enterGrade(arr[i], 6, 10)) {
            i = -1;
            std::cout<<outputText;
        }
    }
}