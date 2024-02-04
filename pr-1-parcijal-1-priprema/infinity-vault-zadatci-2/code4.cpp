#include<iostream>
#include<cmath>

/*
    Napisati program koji omogućava korisniku unos 
    prirodnog broja N (50 < N < 5000000). Zatim uneseni 
    broj proslijediti funkciji kao parametar po referenci.
    U funkciji je od unesenog broja potrebno kreirati novi 
    broj teko što će se poredak cifri unesenog broja obrnuti.
    Prilikom obrtanja potrebno je odbaciti neparne cifre.

    Npr. Za uneseni broj 1234567 obrnuti broj bez neparnih 
    cifara je 642.
*/

void unos(int &);
void obrniBrojIzostaviNeparneCifre(int &);

int main() {
    int N {};

    unos(N);
    std::cout<<"Broj "<<N<<" nakon obrcanja je ";
    obrniBrojIzostaviNeparneCifre(N);
    std::cout<<N<<std::endl;

    return 0;
}

void unos(int &broj) {
    do {
        std::cout<<"Unesi broj (N): ";
        std::cin>>broj;

        if (broj <= 50 || broj >= 5000000)
            std::cout<<"Uneseni broj mora biti veci od 50 ali manji od 5000000\n";
    } while(broj <= 50 || broj >= 5000000);
}

void obrniBrojIzostaviNeparneCifre(int &broj) {
    int obrnutBroj {0};
    short zadnjaCifra {};

    while (broj) {
        zadnjaCifra = broj % 10;

        if (zadnjaCifra % 2 == 0)
            obrnutBroj = obrnutBroj * 10 + zadnjaCifra;

        broj /= 10;
    }

    broj = obrnutBroj;
}