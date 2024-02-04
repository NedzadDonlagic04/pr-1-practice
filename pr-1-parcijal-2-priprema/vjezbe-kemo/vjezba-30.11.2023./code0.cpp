#include<iostream>

/*
    Niz (1D) :: pojam
    Data structures: vectors, lists, sets, hashmaps etc.
    Niz je struktura (engl. data structure)
    -> Omogucuje pohranjivanje podataka ISTOG tipa u KONTINUIRANI memorijski prostor.
    KONTINUIRANI / KONTINUALNI = NEISPREKIDANI (eng. continuous)

    Indeksiranje :: pristupanje elementima koristenjem indeksa tj. indikatora
    memorijske lokacije.
    Indeksiranje pocinje od 0.

    1D nizovi se ne mogu prosirivati, sto znaci da je potrebno unaprijed znati
    njihove dimenzije (broj elemenata).
    --> 1D nizovi se pohrenjuju na stack memoriji (~8 MB)
    --> Ako se stack memorija popuni (predjete preko ~8 MB) --> dobija se greska koja
    se zove stack overflow.
    --> Kada se radi sa jako puno podataka (jako puno memorije) koristi se dinamicka memorija
    (HEAP) [alocira resurse iz RAM-a]
*/

int main() {
    // deklaracija statickog niza (static array)
    int arr[5] {};

    /*
        naziv 'arr' cuva adresu prvog elementa u nizu (element sa indeksom 0)
        operator '[]' (nije nuzno vezan uz nizove, ali se najvise koristi sa nizovima)
        operator '[i]' prima adresu varijable sa lijeve strane
        i radi pomjeranje od 'i' koraka u odnosu na adresu 'arr' i vraca vrijednost
        koju pronalazi na datoj lokaciji
        arr[i];
    */

    // za dohvacanje broja elemenata u nizu koristimo funkciju 'size'
    std::cout<<"Broj elemenata: "<<std::size(arr)<<std::endl;
    // funkciju 'size' koristimo da izbjegnemo hardkodiranje
    // 'hardkodiranje' - setovanje fiksnih vrijednosti unaprijed, koje je tesko promjeniti
    // kasnije ako dodje do promjene nekih drugih dijelova koda

    // vrijednost 5 je ovdje hardkodirana
    // ako se promjeni duzina niza mora se ovdje isto promjeniti
/*     for (int i = 0; i < 5; i++) {

    } */

    // bolje zbog code reusability
    for (int i = 0; i < std::size(arr); i++) {
        std::cout<<"Unesite element na lokaciji "<<i<<std::endl;
        std::cin>>arr[i];   // upis vrijednosti na lokaciju 'i'
    }

    std::cout<<"\n\nIspis elemenata niza:\n";

    for (int i = 0; i < std::size(arr); i++) {
        std::cout<<"Index: "<<i<<'\n';
        std::cout<<"Adresa: "<<&arr[i]<<'\n';
        std::cout<<"Vrijednost: "<<arr[i]<<"\n\n";
    }

    /*
        vise o adresnoj (pokazivackog) aritmetici kasnije..
        adresna aritmetika je pojam koji se odnosi na sabiranje i oduzimanje
        vrijednosti od memorijskih adresa
    */

    // Mali skok u buducnost za primjer adresne aritmetike
/*    int broj;
   (&broj)[2]; */

    return 0;
}