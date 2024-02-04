#include<iostream>
#include<limits>
#include<optional>
#include<memory>

void clearBuffer();

void enterNum(int &, const char * const, const std::optional<int>, const std::optional<int>);
void enterSign(char &, const char * const);

[[nodiscard]] std::unique_ptr<char[]> repeatSign(const char, const std::size_t);

int main() {
    char sign {};
    int num {};

    enterSign(sign, "Unesite znak kojim ce broj biti okruzen: ");
    enterNum(num, "Unesite prirodan broj u intervalu [0, 9]: ", 0, 9);

    auto lineOfSign { repeatSign(sign, 5) };

    std::cout<<lineOfSign.get()<<'\n';
    std::cout<<lineOfSign.get()<<'\n';
    std::cout<<sign<<' '<<num<<' '<<sign<<'\n';
    std::cout<<lineOfSign.get()<<'\n';
    std::cout<<lineOfSign.get()<<'\n';

    return 0;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enterNum(int &num, const char * const outputText, const std::optional<int> min, const std::optional<int> max) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<outputText;
        std::cin>>num;

        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
            repeatLoop = true;
        } else if (min && num < min.value()) {
            std::cout<<"Uneseni broj treba biti veci od "<<min.value()<<std::endl;
            clearBuffer();
            repeatLoop = true;
        } else if (max && num > max.value()) {
            std::cout<<"Uneseni broj treba biti manji od "<<max.value()<<std::endl;
            clearBuffer();
            repeatLoop = true;
        }
    } while(repeatLoop);
}

void enterSign(char &sign, const char * const outputText) {
    do {
        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
        }

        std::cout<<outputText;
        std::cin>>sign;
    } while(std::cin.fail());
}

std::unique_ptr<char[]> repeatSign(const char sign, const std::size_t count) {
    auto str { std::make_unique<char[]>(count + 1) };

    for (std::size_t i = 0; i < count; i++) {
        str[i] = sign;
    }

    str[count] = '\0';

    return str;
}