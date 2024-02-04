#include<iostream>

/*
    Pokazivaci :: pojam

    Pokazivac je specijalna varijabla za cuvanje adrese variable
    ili elementa u nizu.

    Pokazivac se sastoji od 3 komponent:
    -> naziv [engl. identifier]
    -> adresa pokazivaca [lokacija pokazivaca u memoriji]
    -> vrijednost pokazivaca [adresa varijable koju cuva]
    
    Adrese varijabli su adrese prvog reda.
    Adrese pokazivaca su adrese drugog reda.

    Pokazivac moze cuvati ISKLJUCIVO jednu memorijsku adresu.
    To moze biti adresa samostalne varijable a isto tako moze biti adresa
    varijable koja je dio niza.

    Pokazivac moze cuvati adresu varijable koja se moze nalaziti u:
    -> statickoj memoriji (stack ili stek)
    -> dinamickoj memoriji (heap) 

    Deklaracija pokazivaca se uvijek radi na isti nacin:
    TIP_PODATKA *naziv;

    Napomena: operator '*' [dereferenciranje] nije isto sto i simbol '*' koristen
    za deklaraciju. Isti slucaj imamo sa simbolom '&' koji moze oznacavati dvije
    razlicite stvari u zavisnosti od konteksta gdje se pojavljuje.
*/

int main() {
    int a {5};
    // deklaracija varijable 'a' na steku [varijabla lokalnog opsega]
    // njen "zivotni vijek" (engl. lfe cycle) zavrsava sa main funkcijom

    // kreiramo pokazivacku varijablu 'p', koja se nalazi takoder
    // na stack memoriji
    // pokazivac 'p' se takoder uklanja sa main funkcijom
    int *p {&a};    // adresa od 'a' se upisuje u pokazivacku varijablu 'p'

    // operacije
    *p;         // citanje adrese 'a'
    (*p)++;     // citanje adrese od 'a' i uvecanje vrijednosti za 1
    p++;        // p = p + 1; u pokazivac 'p' se upisuje adresa
                // koja se dobija operacijom "p + 1"

    std::cout<<a<<std::endl; 
    std::cout<<"Adresa od 'a': "<<&a<<std::endl;
    std::cout<<"Adresa na koju pokazuje 'p': "<<p<<std::endl;
    std::cout<<"Vrijednost od 'p': "<<*p<<std::endl;

    return 0;
}