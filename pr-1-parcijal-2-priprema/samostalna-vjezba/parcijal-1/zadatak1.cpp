#include<iostream>
#include<cmath>

bool isValid(int, int);
int toDecimal(int, int);

void enterBase(int &);
void enterNumber(int &, const int);

int main() {
    int base {}, x {};

    enterBase(base);
    enterNumber(x, base);

    std::cout<<"Uneseni broj "<<x<<" u bazi "<<base<<" je broj ";
    std::cout<<toDecimal(x, base)<<" u dekadnom sistemu"<<std::endl;

    return 0;
}

bool isValid(int x, int base) {
    while (x) {
        if (x % 10 >= base) {
            return false;
        }

        x /= 10;
    }

    return true;
}

int toDecimal(int x, int base) {
    int decimalniBroj {0};

    for (int i = 0; x; i++, x /= 10) {
        decimalniBroj += x % 10 * std::pow(base, i);
    }

    return decimalniBroj;
}

void enterBase(int &base) {
    do {
        std::cout<<"Unesi bazu: ";
        std::cin>>base;

        if (base < 2 || base > 10) {
            std::cout<<"Unesena baza treba biti u intervalu [2, 10]\n";
        }
    } while (base < 2 || base > 10);
}

void enterNumber(int &num, const int base) {
    do {
        std::cout<<"Unesi broj u bazi "<<base<<": ";
        std::cin>>num;

        if (!isValid(num, base)) {
            std::cout<<"Uneseni broj "<<num<<" nije validan u bazi "<<base<<'\n';            
        } else if (num < 0) {
            std::cout<<"Uneseni broj ne smije biti negativan\n";
        }
    } while (!isValid(num, base) || num < 0);
}