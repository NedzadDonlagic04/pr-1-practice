#include<iostream>

bool h(int);
int s(int);
void unos(int &, const char);
void ispisBrojevaSUslovom(const int, const int);

int main() {
    int n {}, x {};

    unos(n, 'n');
    unos(x, 'x');

    ispisBrojevaSUslovom(n, x);

    return 0;
}

bool h(int x) {
    if (!x) return true;

    while (x) {
        if (x % 10 % 2 == 0) return true;
        x /= 10;
    }

    return false;
}

int s(int x) {
    int suma {0};

    while (x) {
        suma += x % 10;
        x /= 10;
    }

    return suma;
}

void unos(int &broj, const char znakVarijable) {
    do {
        std::cout<<"Unesite '"<<znakVarijable<<"': \n";
        std::cin>>broj;

        if (broj <= 0)
            std::cout<<"Varijabla "<<znakVarijable<<" treba biti veca od 0\n";
    } while(broj <= 0);
}

void ispisBrojevaSUslovom(const int n, const int x) {
    std::cout<<"Ispis svih brojeva\n";

    for (int i = 1; i <= n; i += 2)
        if (!h(i) && s(i) >= x)
            std::cout<<i<<' ';

    std::cout<<std::endl;
}