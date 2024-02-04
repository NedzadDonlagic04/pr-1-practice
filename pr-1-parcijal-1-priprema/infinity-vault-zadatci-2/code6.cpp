#include<iostream>

/* 
    Napisati program koji će omogućiti korisniku unos broja 
    n (uz uslov 10 <= n <= 1000). Zatim simulirati unos n 
    slučajnih vrijednosti. Simuliranje unosa ostvariti funkcijom rand() % 1000 + 1.
    Izračunati statističke podatke u kojem procentu se od n
    generisanih slučajnih vrijednosti pojavljuje prost broj.

    Npr. Ako je generisano 10 brojeva (n = 10): 5,7,4,13,17,20,25,23,30,45,
    u ovom uzorku od 10 brojeva postoji 5 prostih brojeva pa je procenat prostih brojeva u ovom slučaju 50%.

    (Napomena: Po želji kreirati dodatne funkcije da se olakša rješavanje zadatka.)
*/

void unos(int &);
int baciKocku();
bool jesilProst(int);
void ispisiProcenatBacanja(const int);

int main() {
    int n {};

    unos(n);
    ispisiProcenatBacanja(n);

    return 0;
}

void unos(int &broj) {
    do {
        std::cout<<"Unesi broj bacanja (n): ";
        std::cin>>broj;

        if (broj < 10 || broj > 1000)
            std::cout<<"Unesi broj ne smije biti manji od 10 ili veci od 1000\n";
    } while(broj < 10 || broj > 1000);
}

int baciKocku() {
    return rand() % 100 + 1;
}

bool jesilProst(int broj) {
    if (broj <= 1) return false;

    for (int i = 2; i * i <= broj; i++)
        if (broj % i == 0) 
            return false;

    return true;
}

void ispisiProcenatBacanja(const int brojBacanja) {
    int brojProsti {0};

    for (int i = 0; i < brojBacanja; i++) 
        if (jesilProst(baciKocku())) 
            brojProsti++;

    std::cout<<"Za "<<brojBacanja<<" pojavljuje se "<<float(brojProsti) / brojBacanja * 100<<"%\n";
}