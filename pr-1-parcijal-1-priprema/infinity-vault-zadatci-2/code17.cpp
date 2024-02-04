#include<iostream>

/*
    Napisati program koji će omogućiti korisniku unos 
    broja n (uz uslov 10 <= n <= 1000). Zatim simulirati 
    unos n slučajnih vrijednosti. Simuliranje unosa ostvariti 
    funkcijom rand()% 1000 + 1. Izračunati statitičke podatke 
    u kojem procentu se od n generisanih slučajnih vrijednosti 
    pojavljuje savršen broj . Za neki broj se kaze da je savrsen 
    ako je jednak sumi svih svojih djelilaca (ne uključujući njega samog).
    Npr. 28 je savršen broj : njegovi djelioci su 1 , 2 , 4 , 7 i 14 , 
    a 1 + 2 + 4 + 7 + 14 = 28 Jedini savršeni brojevi od 1 do 100 su brojevi 6 i 28
*/

void unos(int &);
int generisiSlucajnuVrijednost();
bool jelBrojSavrsen(int);
void ispisiSavrseneBrojevDoN(const int);

int main() {
    int n {};

    unos(n);
    ispisiSavrseneBrojevDoN(n);

    return 0;
}

void unos(int &broj) {
    do {
        std::cout<<"Unesi neki broj: ";
        std::cin>>broj;

        if (broj < 10)
            std::cout<<"Unos treba biti veci ili jednak 10\n";
        else if (broj > 1000)
            std::cout<<"Unos treba biti manji ili jednak 1000\n";
    } while(broj < 10 || broj > 1000);
}

int generisiSlucajnuVrijednost() {
    return rand() % 1000 + 1;
}

bool jelBrojSavrsen(int broj) {
    int sum {0};

    for (int i = 1; i <= broj / 2; i++) 
        if (broj % i == 0)
            sum += i;

    return broj == sum;
}

void ispisiSavrseneBrojevDoN(const int n) {
    std::cout<<"Savrseni brojevi u intervalu [1, "<<n<<"] su: ";

    for (int i = 1; i <= n; i++)
        if (jelBrojSavrsen(i))
            std::cout<<i<<' ';

    std::cout<<std::endl;
}