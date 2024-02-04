#include<iostream>

int brojac = 0;
int cachedProstiBroj = 5;

void unos(int &, const char, const int);
void ispisiSveParneOdADoB(int, const int);
bool jesilProst(int);
void goldbach(const int);


int main() {
    int A {}, B {};
    
    unos(A, 'A', 100);
    unos(B, 'B', A + 100);

    ispisiSveParneOdADoB(A, B);

    std::cout<<"\n\nBrojac: "<<brojac<<"\n\n";

    std::cin.get();
    return 0;
}

void unos(int &unos, const char znakVarijable, const int min) {
    do {
        std::cout<<"Unesi broj ("<<znakVarijable<<"): ";
        std::cin>>unos;

        if (unos <= min)
            std::cout<<"Uneseni broj ne moze biti manji od "<<min<<'\n';
    } while(unos <= min);
}

void ispisiSveParneOdADoB(int A, const int B) {
    for(A = A + (A % 2 != 0); A <= B; A += 2)
        goldbach(A);
}

bool jesilProst(const int broj) {
    if (broj == 2 || broj == 3) return true;
    else if (broj <= 1 || broj % 2 == 0 || broj % 3 == 0) return false;

    for (int i = 5; i * i <= broj; i += 6) 
        if (broj % i == 0 || broj % (i + 2) == 0) 
            return false;

    return true;
}

void goldbach(const int broj) {
    if (jesilProst(3) && jesilProst(broj - 3)) {
        std::cout<<broj<<" = 3 + "<<broj - 3<<'\n';
    } else if (jesilProst(cachedProstiBroj) && jesilProst(broj - cachedProstiBroj)) {
        std::cout<<broj<<" = "<<cachedProstiBroj<<" + "<<broj - cachedProstiBroj<<'\n';
        cachedProstiBroj += 6;
    } else if (jesilProst(cachedProstiBroj + 2) && jesilProst(broj - cachedProstiBroj - 2)) {
        std::cout<<broj<<" = "<<cachedProstiBroj + 2<<" + "<<broj - cachedProstiBroj - 2<<'\n';
        cachedProstiBroj += 6;
    } else {
        for (int i = 5; i <= broj - i; i += 6, brojac++) {
            if (jesilProst(i) && jesilProst(broj - i)) {
                std::cout<<broj<<" = "<<i<<" + "<<broj - i<<'\n';
                cachedProstiBroj = i + 6;
                break;
            } else if (jesilProst(i + 2) && jesilProst(broj - i - 2)) {
                std::cout<<broj<<" = "<<i + 2<<" + "<<broj - i - 2<<'\n';
                cachedProstiBroj = i + 6;
                break;
            }
        }
    }
}