#include<iostream>

bool isFirstDigitEven(int x);
bool isPrime(int x);
bool isSortedDesc(int x);

void unosOpcije(short &);
void opcija1();
void opcija2();
void unosN(int &, const int);
void unosM(int &);

int main() {
    short opcija {};

    do {
        unosOpcije(opcija);
        if (opcija == 1) {
            opcija1();
        } else if (opcija == 2) {
            opcija2();
        } else if (opcija != 3) {
            std::cout<<"Unesena opcija ne postoji\n";
        }
    } while(opcija != 3);

    return 0;
}

bool isFirstDigitEven(int x) {
    while (x / 10) {
        x /= 10;
    }

    return x % 2 == 0;
}

bool isPrime(int x) {
    if (x == 2 || x == 3) {
        return true;
    } else if (x <= 1 || x % 2 == 0 || x % 3 == 0) {
        return false;
    }

    for (int i = 5; i * i <= x; i += 6) {
        if (x % i == 0 || x % (i + 2) == 0) {
            return false;
        }
    }

    return true;
}

bool isSortedDesc(int x) {
    int lastDigit {x % 10};
    x /= 10;

    while (x) {
        if (lastDigit > x % 10) {
            return false;
        }
        lastDigit = x % 10;
        x /= 10;
    }

    return true;
}

void unosOpcije(short &opcija) {
    std::cout<<"Unesite opciju: ";
    std::cin>>opcija;
}

void opcija1() {
    int m {}, n {};

    unosM(m);
    unosN(n, m);

    for (; m <= n; m++) {
        if (isFirstDigitEven(m)) {
            std::cout<<m<<' ';
        }
    }
    std::cout<<std::endl;
}

void opcija2() {
    int n {};

    unosN(n, 2);

    for (int i = 2; i <= n; i++) {
        if (isPrime(i) && isSortedDesc(i)) {
            std::cout<<i<<' ';
        }
    }
    std::cout<<std::endl;
}

void unosM(int &m) {
    do {
        std::cout<<"Unesi broj (m): ";
        std::cin>>m;

        if (m <= 0) {
            std::cout<<"Unos treba biti broj veci od 0\n";
        }
    } while(m <= 0);
}

void unosN(int &n, const int min) {
    do {
        std::cout<<"Unesi broj (n): ";
        std::cin>>n;

        if (n < min) {
            std::cout<<"Unos treba biti broj veci ili jednak "<<min<<"\n";
        }
    } while(n < min);
}