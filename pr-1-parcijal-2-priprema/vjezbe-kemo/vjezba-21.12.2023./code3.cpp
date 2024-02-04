#include<iostream>

/*
    Nizovi karaktera (tekstovi)
    Niz karaktera je niz karakternih simbola smjestenih u statickoj ili dinamickoj memoriji.
*/

int main() {
    // deklaracija statickog niza karaktera [bez inicijalizacije] -- niz ima 'junk' vrijednosti
    char arr[20];

    /*
        Svaki niz karaktera (bio on staticki ili dinamicki) mora biti konkretne velicine.
        U ovom nasem slucaju, velicina = 20.
        Pojedinacni karakteri zauzimaju pozicije (indekse) od 0 [prvi element] do 19 [zadnji element].
        Svaki element ima svoju memorijsku adresu, i te adrese su u KONTINUIRANOM bloku.

        Kako se razlikuje od integer niza?
        Kod nizova karaktera, UVIJEK mora biti rezervisano jedno mjesto za specijalni znak koji se zove
        null-terminirajuci karakter (terminator).
        Njegova oznaka je '\0', koji ima svoj ASCII kod.
        '\0' koristi se da oznaci granicu izmedu tekstualnog sadrzaja i "junk" dijela.

        On se dodaje na kraj sadrzaja automatski (ne dodaje se na kraj NIZA).
        Moguce je dodati ga rucno, a ako se to ne uradi - on se dodaje automatski.
        Sta to znaci efektivno?
        Niz ima velicinu 50
        --> 49 je slobodnih mjesta za pohranu sadrzaja
        --> 1 mjesto je rezervisano za '\0' znak
        U gornjem primjeru "char arr[20];" nedostaje inicijalizacija pa prema tome nema ni '\0'
    */

   std::cout<<arr<<std::endl;   // ispis svih karaktera do '\0'

    /*
        Kako se ispisuju?
        Moguce je ispisivati nizove karaktera 'for' petljom ali se NE PREPORUCUJE.
        
        'arr' je adresa prvog karaktera u nizu.
        Ispis nizova karaktera je INTERNO programiran da kada treba ispisati 'arr' tj. adresu niza,
        umjesto da se ispise hex vrijednost, ispisat ce se svi karakteri do terminatora.
        Kako nismo uradili inicijalizaciju, on ce pokusati da ispise sadrzaj kojeg nema
        -- pa je rezultat junk vrijednost
    */

    return 0;
}