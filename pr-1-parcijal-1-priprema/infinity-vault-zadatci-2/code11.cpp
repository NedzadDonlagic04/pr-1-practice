#include<iostream>

/*
    Napisati program koji će omogućiti korisniku 
    unos dva minimalno trocifrena prirodna broja 
    m i n (n > m, m > 100, n < 500). Zatim napraviti 
    funkciju koja će vratiti aritmetičku sredinu svih 
    srednjih cifara svih brojeva u rangu od m do n.

    Također ta funkcija treba ispisati najveću srednju 
    cifru navedenog ranga.
*/

void unos(int &, const char, const int, const int);
void ispisiArSredinuINajvecuCifru(const int, const int);

int main() {
    int m {}, n {};

    unos(m, 'm', 100, 499);
    unos(n, 'n', m, 500);

    ispisiArSredinuINajvecuCifru(m, n);

    return 0;
}

void unos(int &broj, const char znakVarijable, const int min, const int max) {
    do {
        std::cout<<"Unesi neki trocifreni broj ("<<znakVarijable<<"): ";
        std::cin>>broj;

        if (broj <= min)
            std::cout<<"Uneseni broj treba biti veci od "<<min<<'\n';
        else if (broj >= max)
            std::cout<<"Uneseni broj treba biti manji od "<<max<<'\n';

    } while(broj <= min || broj >= max);
}

void ispisiArSredinuINajvecuCifru(const int m, const int n) {
    int suma {0}, najvecaCifa {-1}; 
    short srednjaCifra {};

    for (int i = m; i <= n; i++) {
        srednjaCifra = i / 10 % 10;

        najvecaCifa = std::max(najvecaCifa, (int)srednjaCifra);
        suma += (i / 10 % 10);
    }
    
    std::cout<<"U intervalu ["<<m<<", "<<n<<"] aritmeticka sredina zbira svih srednji cifri broja je ";
    std::cout<<float(suma) / (n - m)<<'\n';
    std::cout<<"Najveca srednja cifra iz intervala je "<<najvecaCifa<<std::endl;
}