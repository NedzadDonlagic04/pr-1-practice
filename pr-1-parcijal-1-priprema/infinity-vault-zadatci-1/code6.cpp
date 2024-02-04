#include <iostream>

/* 
    Napišite program, poštujući sve faze procesa programiranja, 
    koji će ispisati sve troznamenkaste brojeve koji su jednaki 
    sumi faktorijela svojih znamenki.

    ABC = A! + B! + C!
*/

bool jelUslovZadatkaIspunjen(const int);
int faktorijal(int);

int main() {
    std::cout<<"Trocifreni brojevi koji ispunjavaju uslov: \n";
    for (int i = 100; i <= 999; i++) 
        if (jelUslovZadatkaIspunjen(i))
            std::cout<<i<<'\n';

    std::cin.get();
    return 0;
}

bool jelUslovZadatkaIspunjen(const int broj) {
    return broj == faktorijal(broj % 10) + faktorijal(broj / 10 % 10) + faktorijal(broj / 100 % 10);
}

int faktorijal(int broj) {
    int faktorijal {1};

    for (; broj >= 2; broj--)
        faktorijal *= broj;
    
    return faktorijal;
}