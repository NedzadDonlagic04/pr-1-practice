#include<iostream>

int brojac = 0;

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
    for (int i = 2; i <= broj - i; i++, brojac++) {
        if (jesilProst(i) && jesilProst(broj - i)) {
            std::cout<<broj<<" = "<<i<<" + "<<broj-i<<std::endl;
            break;
        }
    }
}