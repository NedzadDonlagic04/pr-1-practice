#include<iostream>
#include<cmath>

/*
    Napisati program koji će uzastopno učitavati cijele 
    brojeve m i n (1 <= m <= 50, 1 <= n <= 500) i pronalaziti 
    srednju cifru njihovog proizvoda/umnoška. Program treba 
    ispisivati srednju cifru samo ako je veća od prethodno izračunate 
    srednje cifre. Prva pronađena srednja cifra se svakako ispisuje. 
    Program se forsirano prekida ako korisnik unese n = 0. Program se 
    prirodno završava ako je pronađena srednja cifra 9. Primjer izvršenja:

    unesi m i n: 10, 15
    srednja cifra/sredina proizvoda brojeva 10 i 15 (10 * 15 = 150) je: 5
    unesi m i n: 10, 42
    srednja cifra/sredina proizvoda brojeva 10 i 42 (10 * 42 = 420) je: ne ispisuje se
    unesi m i n: 12, 31
    srednja cifra/sredina proizvoda brojeva 12 i 31 (12 * 31 = 372) je: 7
    unesi m i n: 149, 20
    srednja cifra/sredina proizvoda brojeva 149 i 20 (149 * 20 = 2980) je: 8.5
    unesi m i n: 150, 0
    forsirani prekid...
*/

/*
    uslov m > 50 sam uradio kao m > 150 jer se iznad moze vidjeti da se u m unosi broj kao 149 i 150
    i ne ocekuje se neki ponovni unos ili ista slicno
    isto vazi za 1 < n, ako uradimo ovo ne mozemo prihvatiti 0 kao prekid
*/

void unosMiN(int &, int &);
int getBrojCifaraBroja(int);
float getSrednjaCifraBroja(int);

int main() {
    int m {}, n {};
    float srednjaCifra {}, zadnjaSrednjaCifra {-1};

    do {
        unosMiN(m, n);

        srednjaCifra = getSrednjaCifraBroja(m * n);

        std::cout<<"srednja cifra/sredina proizvoda brojeva "<<m<<" i "<<n;
        std::cout<<" ("<<m<<" * "<<n<<" = "<<m * n<<" ) je: ";

        if (zadnjaSrednjaCifra == -1 || srednjaCifra > zadnjaSrednjaCifra)
            std::cout<<srednjaCifra<<'\n';
        else if(n)
            std::cout<<"ne ispisuje se\n";

        zadnjaSrednjaCifra = std::max(zadnjaSrednjaCifra, srednjaCifra);
    } while(n && zadnjaSrednjaCifra != 9);

    std::cout<<std::endl;

    return 0;
}

void unosMiN(int &m, int &n) {
    char jediZarez {};
    do {
        std::cout<<"unesi m i n: ";
        std::cin>>m>>jediZarez>>n;
        /* 
            Malo sam nesiguran da li su bas htjeli da unos 
            bude 10, 15
            Ovaj , pravi problem, a nismo radili dovoljno
            nacina da ga se rijesimo pa ja ovdje efektivno
            "hranim" taj zarez u varijablu koja se nikad
            ne koristi
        */

        if (m < 1 || m > 150 || n < 0 || n > 500)
            std::cout<<"nepravilan unos\n";
    } while(m < 1 || m > 150 || n < 0 || n > 500);
}

int getBrojCifaraBroja(int broj) {
    int brojac { 0 };

    while (broj) {
        brojac++;
        broj /= 10;
    }

    return brojac;
}

float getSrednjaCifraBroja(int broj) {
    broj = std::abs(broj);
    
    const int brojCifara { getBrojCifaraBroja(broj) };
    float srednjaCifra {};
    
    if (broj >= 100)
        broj /= std::pow(10, brojCifara / 2 - (brojCifara % 2 == 0));
    //                                          ^ u slucaju da je broj cifara paran
    //                                          kao 1234, da ne smaknemo 34, smaket cemo samo 4

    srednjaCifra = broj % 10;

    if (brojCifara % 2 == 0) {
        srednjaCifra += broj / 10 % 10;
        srednjaCifra /= 2;
    }

    return srednjaCifra;
}