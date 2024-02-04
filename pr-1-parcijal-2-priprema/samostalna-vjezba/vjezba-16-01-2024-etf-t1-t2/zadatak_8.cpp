#include<iostream>
#include<limits>

constexpr unsigned int CURRENT_YEAR { 2024 };

void clearBuffer();
void enterGender(char &, const char * const);
void enterYearOfBirth(unsigned int &, const char * const);

[[nodiscard]] const char* getFullGenderName(const char);
[[nodiscard]] const char* getRole(const unsigned int);

int main() {
    char gender {};
    unsigned int yearOfBirth {};
    unsigned int age {};

    enterYearOfBirth(yearOfBirth, "Unesite godinu rodjenja osobe: ");
    enterGender(gender, "Unesite spol osobe (m/M ili z/Z): ");

    age = CURRENT_YEAR - yearOfBirth;

    std::cout<<"Osoba ima "<<age<<" godina/e/u, ";
    std::cout<<"klasificirana je u kategoriju: '"<<getRole(age);
    std::cout<<"', "<<getFullGenderName(gender)<<" je.\n";

    return 0;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterGender(char &gender, const char * const outputText) {
    clearBuffer();
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>gender;

        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
            repeatLoop = true;
        } else if (std::towlower(gender) != 'z' && std::tolower(gender) != 'm') {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
            repeatLoop = true;
        }
    } while(repeatLoop);
}

void enterYearOfBirth(unsigned int &yearOfBirth, const char * const outputText) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>yearOfBirth;

        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
            repeatLoop = true;
        } else if (yearOfBirth < 1 || yearOfBirth > CURRENT_YEAR) {
            std::cout<<"Godina rodena treba biti u intervalu [1, "<<CURRENT_YEAR<<"]\n";
            clearBuffer();
            repeatLoop = true;
        }
    } while(repeatLoop);
}

const char* getFullGenderName(const char gender) {
    return (std::tolower(gender) == 'z')? "zensko" : "musko";
}

const char* getRole(const unsigned int age) {
    if (age < 6) {
        return "prije skole";
    } else if (age < 14) {
        return "osnovna skola";
    } else if (age < 18) {
        return "srednja skola";
    } else if (age < 23) {
        return "fakultet";
    }
    return "ostalo";
}