#include<iostream>
#include<cmath>

/* 
    Napisati program kojim će se izračunati 20
    uzastopnih vrijednosti brzine i pređenog puta objekta 
    u slobodnom padu u razmaku od po 3 sec. Prilikom računanja 
    potrebno je i ispisati na ekran uzastopno brzinu i pređeni 
    put zajedno za svaki period od 3sec. Obratiti pažnju da se 
    koriste ispravni tipovi podataka. Formula za brzinu slobodnog 
    pada je: v = g * t; g=9.81 Formula za pređeni put pri slobodnom 
    padu je: s=(g/2)*pow(t,2)

    Primjer izlaza:

    Situacija u 3-oj sekundi je:
    Brzina: 29.43
    Predjeni put: 44.145

    Situacija u 6-oj sekundi je:
    Brzina: 58.86
    Predjeni put: 176.58

    Situacija u 9-oj sekundi je:
    Brzina: 88.29
    Predjeni put: 397.305

    Situacija u 12-oj sekundi je:
    Brzina: 117.72
    Predjeni put: 706.32
*/

int main() {
    const float GRAVITACIONO_UBRZANJE { 9.81 };

    for (int t = 3; t <= 60; t += 3) {
        std::cout<<"Situacija u "<<t<<"-oj sekundi je: \n";
        std::cout<<"Brzina: "<<GRAVITACIONO_UBRZANJE * t<<'\n';
        std::cout<<"Predjeni put: "<<(GRAVITACIONO_UBRZANJE / 2) * std::pow(t, 2)<<"\n\n";
    }

    return 0;
}