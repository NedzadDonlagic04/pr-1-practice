#include<iostream>
#include<cmath>

/*
    Napisati program koji na osnovu unesenog cijelog broja N
    pronalazi i ispisuje srednju cifru ako broj N ima neparan 
    broj cifara, odnosno aritmeticku sredinu (tip float) srednje 
    dvije cifre ako broj N ima parni broj cifara, a zatim pronaci 
    najmanji broj tipa int sa kojim se srednja cifra ili aritmeticka 
    sredina srednjih cifri treba pomnoziti da bi se dobio broj koji je 
    veci od inicijalnog zadanog broja.

    Npr. za broj 75631 srednja cifra je 6, najmanja integer vrijednost 
    sa kojom treba pomnoziti broj 6 da bi se dobio broj veci od 75631 
    je 12606 jer je 12606 * 6 = 75636, 75636 > 75631 ili za broj 984354 
    aritmeticka sredina srednje dvije cifre je 3.5, najmanja integer 
    vrijednost sa kojom treba pomnoziti broj 3.5 da bi se dobio broj 
    veci od 984354 je 281245 jer je 281245 * 3.5 = 984357.5, 984357.5 > 984354

    (Napomena: Potrebno je voditi računa o tipovima podataka.)
*/

void unos(int &);
int getBrojCifaraBroja(int);
float getSrednjaCifraBroja(int);
int getMinimalnUmnozakDaBudeVeciBroj(float, int);

int main() {
    int N {};

    unos(N);

    const float srednjiBroj { getSrednjaCifraBroja(N) }; 
    const int minimalniUmnozak { getMinimalnUmnozakDaBudeVeciBroj(srednjiBroj, N) };

    std::cout<<"Za broj "<<N<<" srednja cifra je "<<srednjiBroj<<'\n';
    std::cout<<"Najmanja integer vrijednost sa kojom se treba pomnoziti broj "<<srednjiBroj;
    std::cout<<" da bi se dobio broj veci od "<<N<<" je "<<minimalniUmnozak<<std::endl;

    return 0;
}

void unos(int &broj) {
    std::cout<<"Unesi neki broj: ";
    std::cin>>broj;
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

int getMinimalnUmnozakDaBudeVeciBroj(float broj, int ciljaniBroj) {
    return ciljaniBroj / broj + ((broj < 0)? -1 : 1);
    //                              ^ u slucaju da je neg broj trebamo rezultat umanjit za 1 a ne povecat
}