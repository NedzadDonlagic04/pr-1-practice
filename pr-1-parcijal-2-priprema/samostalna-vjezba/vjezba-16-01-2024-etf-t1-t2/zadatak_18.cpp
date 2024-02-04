#include<iostream>
#include<functional>
#include<limits>
#include<optional>
#include<cmath>

struct Operation {
    const char *name {};
    const char key {};
    std::function<double()> calc {};

    Operation() = default;
    Operation(const char *, const char, std::function<double()>);

    [[nodiscard]] const char* getName() const;
    [[nodiscard]] char getKey() const;
};

void clearBuffer();
[[nodiscard]] bool isValidOperation(const char, const Operation *, const std::size_t);
void printAllOptions(const Operation *, const std::size_t);

void enterOperation(char &, const Operation *, const std::size_t);

[[nodiscard]] Operation& findOperation(const char, Operation *, const std::size_t);

void enterNum(double &, const char * const, const std::optional<double> = std::nullopt, const std::optional<double> = std::nullopt);

[[nodiscard]] double handleSum();
[[nodiscard]] double handleSub();
[[nodiscard]] double handleMul();
[[nodiscard]] double handleDiv();
[[nodiscard]] double handlePow2();
[[nodiscard]] double handleSqrt2();

int main() {
    Operation operations[] {
        Operation("Sabiranje", '+', handleSum),
        Operation("Oduzimanje", '-', handleSub),
        Operation("Mnozenje", '*', handleMul),
        Operation("Dijeljenje", '/', handleDiv),
        Operation("Kvadriranje", '#', handlePow2),
        Operation("Korjenovanje", '&', handleSqrt2),
    };

    char operation {};

    enterOperation(operation, operations, std::size(operations));

    Operation currentOperation { findOperation(operation, operations, std::size(operations)) };

    const double result { currentOperation.calc() };

    std::cout<<"Rezultat operacije \""<<currentOperation.getName()<<"\"";
    std::cout<<" je "<<result<<std::endl;

    return 0;
}

Operation::Operation(const char *name, const char key, std::function<double()> calc)
    : name(name), key(key), calc(calc) {}

const char* Operation::getName() const {
    return this->name;
}

char Operation::getKey() const {
    return this->key;
}

void clearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool isValidOperation(const char operation, const Operation *operations, const std::size_t size) {
    for (std::size_t i = 0; i < size; i++) {
        if (operation == operations[i].getKey()) {
            return true;
        }
    }

    return false;
}

void printAllOptions(const Operation *operations, const std::size_t size) {
    std::cout<<"--- Moj mini kalkulator ---\n";
    for (std::size_t i = 0; i < size; i++) {
        std::cout<<operations[i].getName()<<": "<<operations[i].getKey()<<'\n';
    }
    std::cout<<std::endl;
}

void enterOperation(char &operation, const Operation *operations, const std::size_t size) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        printAllOptions(operations, size);

        std::cout<<"Odaberite operaciju: "; 
        std::cin>>operation;

        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearBuffer();
            repeatLoop = true;
        } else if (!isValidOperation(operation, operations, size)) {
            std::cout<<"Izabrana operacija ne postoji\n";
            clearBuffer();
            repeatLoop = true;
        }
    } while(repeatLoop);
}

Operation& findOperation(const char operation, Operation *operations, const std::size_t size) {
    for (std::size_t i = 1; i < size; i++) {
        if (operation == operations[i].getKey()) {
            return operations[i];
        }
    }
    
    return operations[0];
}

void enterNum(double &num, const char * const outputText, const std::optional<double> min, const std::optional<double> max) {
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

double handleSum() {
    double a {}, b {};

    enterNum(a, "Unesite prvi broj: ");
    enterNum(b, "Unesite drugi broj: ");

    return a + b;
}

double handleSub() {
    double a {}, b {};

    enterNum(a, "Unesite prvi broj: ");
    enterNum(b, "Unesite drugi broj: ");

    return a - b;
}

double handleMul() {
    double a {}, b {};

    enterNum(a, "Unesite prvi broj: ");
    enterNum(b, "Unesite drugi broj: ");

    return a * b;
}

double handleDiv() {
    double a {}, b {};

    enterNum(a, "Unesite prvi broj: ");
    enterNum(b, "Unesite drugi broj: ");

    return (b)? a / b : std::numeric_limits<double>::infinity();
}

double handlePow2() {
    double a {};

    enterNum(a, "Unesite broj: "); 

    return std::pow(a, 2);
}

double handleSqrt2() {
    double a {};

    enterNum(a, "Unesite broj: ", 0); 

    return std::sqrt(a);
}