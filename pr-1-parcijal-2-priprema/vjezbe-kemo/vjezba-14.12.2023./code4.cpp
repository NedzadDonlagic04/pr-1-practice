#include<iostream>
#include<cmath>

// A bunch of UB below

/*
    U adresnoj aritmetici, koriste se tri operatora:
    -> operator '&' (ampersand) :: address-of operator (operator referenciranja)
    -> operator '*' (asterisk) :: dereference operator (operator dereferenciranja)
    -> operator '[]' (square brackets) :: dereference operator (operator dereferenciranja)

    Address-of vraca adresu varijabli/elemenata niza i sl.
    &varijabla;     // hex vrijednost (0xccaaff0011)
    &(varijabla);   // alternativno zapisivanje

    Operator '*':
    *adresa_varijable;      // uzima adresu i vraca vrijednost na toj adresi / lokaciji
    *(adresa_varijable);    // alternativni nacin

    Operator '[]':
    adresa_varijable[i];
    (adresa_varijable)[i];  // alternativni nacin

    Operator '[]' radi sljedece stvari:
    -> pomak od 'i' koraka u odnosu na proslijedenu adresu varijable
    -> dereferenciranje te adrese [cita vrijednost upisanu na toj adresi]

    Operator '[]' u sebi sadrzi (po defaultu) operator '*'.

    Operatori dereferenciranja '[]' i '*' su inverzni operatoru '&'.

    Sta to znaci?
    operator '&': input: varijabla/vrijednost -> output: adresa
    operatori '*', '[]': input adresa -> output: varijabla/vrijednost
*/

int main() {
    int x {11};     // lokalna varijabla na steku

    std::cout<<"Adresa 'x': "<<&x<<std::endl;
    std::cout<<"Adresa lokacija nakon 'x': "<<&x + 1<<std::endl;
    std::cout<<"Adresa lokacije prije 'x': "<<&x - 1<<std::endl;

    int y {22};     // lokalna varijabla na steku

    std::cout<<"Adresa 'y': "<<&y<<std::endl;
    std::cout<<"Adresna udaljenost izmedu 'x' i 'y' je: "<<std::abs(&x - &y)<<std::endl;

    std::cout<<*(&x)<<std::endl;
    std::cout<<*&x<<std::endl;
    // ovdje operator '*' dereferencira adresu koju vrati komanda "&x"
    // operator '*' cita vrijednost na lokaciji '&x'

    std::cout<<*(&x + 1)<<std::endl;
    // operator '*' cita vrijednost na lokaciji '&x + 1'

    std::cout<<*(&x - 5)<<std::endl;

    std::cout<<(&x)[1]<<std::endl;  // isto kao *(&x + 1);
    // operator '[]'
    // uzima se adresa of 'x' i radimo pomjeranje za 1 korak
    // i onda citamo vrijednost na toj lokaciji

    std::cout<<(&x + 5)[-1]<<std::endl;
    // adresa od 'x' + 5 (5 mjesta udesno)
    // idemo jedno mjesto ulijevo citamo vrijednost na toj lokaciji
    // koju smo dobili
    // *(&x + 4);

    return 0;
}