#include<iostream>

void unos(int &);
void raspisiFibSekvencuDoN(const int);

int main() {
    int n {};

    unos(n);

    std::cout<<"Fibonacijeva sekvenca za uneseni broj: ";
    raspisiFibSekvencuDoN(n);

    std::cin.get();
    return 0;
}

void unos(int &unos) {
    do {
        std::cout<<"Unesi broj clanova fibonacijeve sekvence za raspisati: ";
        std::cin>>unos;

        if (unos < 1)
            std::cout<<"Uneseni broj mora biti veci od 1\n";
    } while(unos < 1);
}

void raspisiFibSekvencuDoN(const int n) {
    int prviClan {1}, drugiClan {1};

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            std::cout<<prviClan<<' ';
            prviClan += drugiClan;
        } else {
            std::cout<<drugiClan<<' ';
            drugiClan += prviClan;
        }
    }
    std::cout<<std::endl;
}