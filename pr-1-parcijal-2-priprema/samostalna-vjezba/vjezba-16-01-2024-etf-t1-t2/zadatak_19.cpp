#include<iostream>
#include<optional>
#include<limits>

void clearBuffer();
void enterNum(int &, const char * const, const std::optional<int> = std::nullopt, const std::optional<int> = std::nullopt);

[[nodiscard]] const char* getCurrentDiscountDescription(const int);
[[nodiscard]] float discountItemPrice(const int);

int main() {
    int currentHour {};

    enterNum(currentHour, "Unesite trenutne sate: ");

    if (currentHour < 8 || currentHour > 17) {
        std::cout<<"Prodavnica je zatvorena\n";
    } else {
        int itemPrice {};

        enterNum(itemPrice, "Unesite cijenu proizvoda: ", 0);

        std::cout<<getCurrentDiscountDescription(itemPrice)<<std::endl;
        std::cout<<"Trenutna cijena artikla je "<<discountItemPrice(itemPrice)<<"KM\n";
    }

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

const char* getCurrentDiscountDescription(const int itemPrice) {
    if (itemPrice < 15) {
        return "Cijena artikla je povecana za 15%";
    } else if (itemPrice > 45) {
        return "Cijena artikla je smanjena za 12%";
    }

    return "Cijena artikla je smanjena za 4KM";
}

float discountItemPrice(const int itemPrice) {
    if (itemPrice < 15) {
        return itemPrice + itemPrice * 0.15f;
    } else if (itemPrice > 45) {
        return itemPrice - itemPrice * 0.12f;
    }

    return itemPrice - 4;
}