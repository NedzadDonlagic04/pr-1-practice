#include<iostream>

/*
    Razlike izmedu staticke i dinamicke memorije:
    ->  staticka je compile-time (alocira se prije kompajliranja)
        dok dinamicka je run-time (alocira se u toku izvodenja)
    ->  staticke varijable / nizovi (dealociraju se same), a dinamicke
        varijable / nizovi (potrebno ih je rucno dealocirati)
    ->  statickom memorijom upravlja OS, a dinamickom se upravlja rucno
        
    Koristi se komanda 'new'
    new int;    // vraca adresu novokreirane dinamicke varijable

    Dinamicke varijable su neimenovane, sto znaci da je potrebno da se
    koristi pokazivac koji ce cuvati njihovu/e adresu/e.
*/

int main() {
    // std::cout<<new int<<std::endl;       // adresa varijable (hex vrijednost)
    
    // std::cout<<(new int) + 5<<std::endl;    // hex vrijednost + 5
    // std::cout<<(new int) - 1<<std::endl;    // hex vrijednost - 1
    // std::cout<<*(new int)<<std::endl;

    // std::cout<<new int(5)<<std::endl;           // 1. kreiranje, 2. inicijalizacija, 3. vracanje vrijednosti 
    // std::cout<<*(new int(5))<<std::endl;           // 1. kreiranje, 2. inicijalizacija, 3. vracanje vrijednosti, 4. dereferenciranje

    // kreiranje statickog pokazivaca (i inicijalizacija istog na adresu dinamicke varijable)
    int *p { new int };         // bez inicijalizacije
    int *p2 { new int{34} };     // sa inicijalizacijom

    *p = 0;         // promjena vrijednosti dinamicke varijable (setovanje iste na 0)
    // p = 0;          // p = NULL; p = nullptr;   // anuliranje pokazivaca [setovanje istog na nultu adresu]
    // nulta adresa (0x000000000) ... 
    // i ona pripada kernelu OS-a (ona se ne moze citati, niti se stvari mogu u nju upisivati)
    *p2 = 354;

    // 'p' i 'p2' se uklanjaju automatski jer su lokalne varijable, ali se nece ukloniti dinamicke varijable
    // dinamicke varijable na koje oni pokazuju
    delete p;       // dealokacija dinamicke memorije koja pocinje sa adresom 'p'
    // ovjde se pokazivac 'p' setuje na neku junk hex vrijednost
    // takav pokazivac se zove hanging pointer
    delete p2;      // dealokacija dinamicke memorije koja pocinje sa adresom 'p2'
    // ovjde se pokazivac 'p' setuje na neku junk hex vrijednost
    // takav pokazivac se zove hanging pointer

    /*
    int broj {33};

    delete &broj;   // ovo je primjer nevalidnog koristenja 'delete'-a, a koji je sintaksicki ispravan
    */

    return 0;
}