#include<iostream>

/* 
    Postujuci sve faze procesa programiranja napisati program 
    koji ce pronaci i ispisati sve brojeve od X do Y ( ukljucujuci 
    granicne vrijednosti) koji su djeljivi svim svojim ciframa.

    Na primjer, broj 36 je djeljiv svim svojim ciframa (36/6=6 i 36/3=12).

    Brojeve X i Y unosi korisnik i oni moraju biti u opsegu od 10 do 6000.

    Obavezno koristiti bar jednu funkciju.
*/

void unos(int &, const char);
void ispisiBrojeveUzUslovZadatka(int, const int);
bool jelBrojDjeljivSaSvimCiframa(const int);

int main() {
    int X {}, Y {};

    unos(X, 'X');
    unos(Y, 'Y');
    ispisiBrojeveUzUslovZadatka(X, Y);

    std::cin.get();
    return 0;
}

void unos(int &unos, const char znakVarijable) {
    do {
        std::cout<<"Unesi broj ("<<znakVarijable<<"): ";
        std::cin>>unos;

        if (unos < 10 || unos > 6000)
            std::cout<<"Uneseni broj mora biti u intervalu od [10, 6000]\n";
    } while(unos < 10 || unos > 6000);
}

bool jelBrojDjeljivSaSvimCiframa(const int orginalniBroj) {
    int kopija {orginalniBroj};

    while (kopija) {
        int zadnjaCifra {kopija % 10};
        if (!zadnjaCifra || (orginalniBroj % zadnjaCifra != 0))
            return false;

        kopija /= 10;
    }

    return true;
}

void ispisiBrojeveUzUslovZadatka(int X, const int Y) {
    for (; X <= Y; X++)
        if (jelBrojDjeljivSaSvimCiframa(X))
            std::cout<<X<<' ';
    
    std::cout<<std::endl;
}