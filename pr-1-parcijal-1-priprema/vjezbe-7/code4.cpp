#include<iostream>

bool isLeap(const int);
int getDaysTotal(int, int);
bool isValid(const int, const int, const int);
bool isOlder(const int, const int, const int, const int, const int, const int);
void unosDatuma(int &, int &, int &, const int);
unsigned long long getDatumInNumericalForm(const int, const int, const int);

int main() {
    int d1 {}, m1 {}, y1{};
    int d2 {}, m2 {}, y2{};
    int d3 {}, m3 {}, y3{};

    unosDatuma(d1, m1, y1, 1);
    unosDatuma(d2, m2, y2, 2);
    unosDatuma(d3, m3, y3, 3);

    std::cout<<"Najstariji datum od unesena tri je: ";

    if (isOlder(d1, m1, y1, d2, m2, y2) && isOlder(d1, m1, y1, d3, m3, y3)) 
        std::cout<<d1<<'.'<<m1<<'.'<<y1<<std::endl;
    else if (isOlder(d2, m2, y2, d1, m1, y1) && isOlder(d2, m2, y2, d3, m3, y3))
        std::cout<<d2<<'.'<<m2<<'.'<<y2<<std::endl;
    else 
        std::cout<<d3<<'.'<<m3<<'.'<<y3<<std::endl;

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

void unosDatuma(int &d, int &m, int &y, const int kojiDatum) {
    std::cout<<"Datum ["<<kojiDatum<<"]\n";
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

/*
    https://stackoverflow.com/questions/14580471/c-convert-string-date-1-4-2000-to-int-date-20000104/14581614#14581614
*/
unsigned long long getDatumInNumericalForm(const int d, const int m, const int y) {
    return d + 32ULL * m + 512ULL * y;
    //         2^5           2^9
}

bool isOlder(const int d1, const int m1, const int y1, const int d2, const int m2, const int y2) {
    const unsigned long long datum1 { getDatumInNumericalForm(d1, m1, y1) };
    const unsigned long long datum2 { getDatumInNumericalForm(d2, m2, y2) };

    return datum1 < datum2;
}