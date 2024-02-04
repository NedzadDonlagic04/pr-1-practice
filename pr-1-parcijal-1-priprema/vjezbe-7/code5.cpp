#include<iostream>

bool isLeap(const int);
int getDaysTotal(int, int);
bool isValid(const int, const int, const int);
int getBrojDanaPoreduUGodini(int, const int, const int);
void unosDatuma(int &, int &, int &);

int main() {
    int d {}, m {}, y{};

    unosDatuma(d, m, y);
    std::cout<<"Uneseni datum je "<<getBrojDanaPoreduUGodini(d, m, y);
    std::cout<<" dan u godini.\n";

    return 0;
}

bool isLeap(const int y) {
    return (y % 400 == 0) || (y % 100 != 0 && y % 4 == 0);
}

int getDaysTotal(const int m, const int y) {
    switch(m) {
        case 2:
            return isLeap(y)? 29 : 28;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
    }
    return 31;
}

bool isValid(const int d, const int m, const int y) {
    bool yearCondition { y < 0 };
    bool monthCondition { m < 1 || m > 12 };
    bool dayCondition { d < 1 || d > getDaysTotal(m, y) };
    
    return !(dayCondition || monthCondition || yearCondition);
}

void unosDatuma(int &d, int &m, int &y){
    do {
        std::cout<<"Unesite dan:\n";
        std::cin>>d;

        std::cout<<"Unesite mjesec:\n";
        std::cin>>m;

        std::cout<<"Unesite godinu:\n";
        std::cin>>y;

        if (!isValid(d, m, y))
            std::cout<<"Nevalidan datum\n";
    } while(!isValid(d, m, y));
}

int getBrojDanaPoreduUGodini(int d, const int m, const int y) {
    for (int i = 1; i < m; i++) 
        d += getDaysTotal(i, y);

    return d;
}