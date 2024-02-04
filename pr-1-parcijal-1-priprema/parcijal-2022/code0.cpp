#include<iostream>

/*
 *  Napisati program koji ostvaruje slijedece funkcionalnosti:
 *  - Omoguciti unos dvije integer vrijednosti a i b uz uvjete a > 200,
 *    b > a + 100
 *  - u rangu a - b pronaci sve parne brojeve i ispisati ih u obliku zbira dva palindroma
 *    (Palindrom je broj koji je jednak broju koji se dobije obrtanjem cifara tog broja
 *    Npr. 145141 je palindrom jer mu je ista vrijednost i ako se napise u obrnutom
 *    poretku cifara, dok 123 nije palindrom jer u obrnutom poretku cifara se dobije broj 321 
 *    123 != 321)
 *  - Ukoliko se broj ne moze izraziti kao zbir dva palindroma, potrebno je ispisati
 *    poruku "Broj (ovjde navesti broj) se ne moze izraziti kao zbir dva palindroma"
 *
 *    Primjer ispisa:
 *    366 ne moze biti izrazen kao zbir dva palindroma
 *    368 = 313 + 55
 *    370 = 282 + 88
 *    372 = 191 + 181
 *    374 ne moze biti izrazen kao zbir dva palindroma
 *    376 = 343 + 33
 *    378 ne moze biti izrazen kao zbir dva palindroma
 *    380 = 303 + 77
 *    382 ne moze biti izrazen kao zbir dva palindroma
 *    384 = 373 + 11
 *    386 ne moze biti izrazen kao zbir dva palindroma
 *    388 = 333 + 55
 *    390 ne moze biti izrazen kao zbir dva palindroma
 *    392 = 383 + 9
 *    394 ne moze biti izrazen kao zbir dva palindroma
 *    396 = 363 + 33
 *    398 ne moze biti izrazen kao zbir dva palindroma
 *    400 = 323 + 77
 */

int brojac { 0 };
int cachedPalindrom {0};

int obrniBroj(int);
bool jelBrojPalindrom(const int);
void unos(int &, const char, const int);
void ispisiParneBrojeveKaoZbirPalindroma(int, const int);
void ispisiBrojKaoZbirDvaPalindroma(int);

int main() {
    int a {}, b {};

    unos(a, 'a', 200);
    unos(b, 'b', a + 100);

    ispisiParneBrojeveKaoZbirPalindroma(a, b);

    std::cout<<brojac<<std::endl;

    return 0;
}

int obrniBroj(int broj) {
    int obrnutBroj {0};

    while(broj) {
        obrnutBroj = obrnutBroj * 10 + broj % 10;
        broj /= 10;
    }

    return obrnutBroj;
}

bool jelBrojPalindrom(const int broj) {
    return broj == obrniBroj(broj); 
}

void unos(int &broj, const char znakVarijable, const int min) {
    do {
        std::cout<<"Unesi vrijednost u varijabli '"<<znakVarijable<<"': ";
        std::cin>>broj;

        if (broj <= min)
            std::cout<<"Uneseni broj treba biti veci od "<<min<<'\n';
    } while(broj <= min);
}

int getNextPalindrom(int broj) {
    do {
        broj++;
    } while(!jelBrojPalindrom(broj));

    return broj;
}

void ispisiBrojKaoZbirDvaPalindroma(int broj) {
    if (jelBrojPalindrom(cachedPalindrom) && jelBrojPalindrom(broj - cachedPalindrom)) {
        std::cout<<broj<<" = "<<cachedPalindrom<<" + "<<broj-cachedPalindrom<<'\n';
        cachedPalindrom = getNextPalindrom(cachedPalindrom);
    } else {
        for (int i = 0; i <= broj - i; i = getNextPalindrom(i), brojac++) {
            if (jelBrojPalindrom(i) && jelBrojPalindrom(broj - i)) {
                std::cout<<broj<<" = "<<i<<" + "<<broj-i<<'\n';
                cachedPalindrom = getNextPalindrom(i);
                break;
            } 
        }
    }
}

void ispisiParneBrojeveKaoZbirPalindroma(int odakle, const int dokle) {
    for (odakle = odakle + (odakle % 2 != 0); odakle <= dokle; odakle += 2)
        ispisiBrojKaoZbirDvaPalindroma(odakle);
}
