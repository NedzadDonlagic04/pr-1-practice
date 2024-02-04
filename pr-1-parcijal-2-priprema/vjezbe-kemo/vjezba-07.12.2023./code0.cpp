#include<iostream>

/*
    STACK memorija :: pojam
    Stack memorija u programiranju [C++, C#, ...] odnosi se na dio memorije
    koji se koristi za skladistenje lokalnih varijabli i podataka tokom izvrsavanja
    funkcija.

    Radi na principu LIFO - Last In, First Out
    --> posljednji podaci koji su smjesteni na stek, bit ce prvi koji se uklanjaju.

    Stek memorija je memorija velicine 1 MB i koristi se za pohranu tzv. stek
    okvira (engl. stack frame/s).

    Stack frame je okvir za pohranu svih podataka.
    (varijabli, nizova, i sl.) koji su potrebni za izvrsenje odredene funkcije.

    Da bi se funkcija izvrsila, potrebno je (naravno) da se ista pozove, a jednom
    kada bude pozvana, za istu se formira novi stack okvir koji se dodaje u stek
    memoriju.

    Kako se funkcije dodaju na stack? Odgovor: Dodaju se na vrh (prilikom poziva
    funkcije)
    Kako se uklanjaju funkcije sa stacka? (Kako se brisu stvari sa stacka)?
    Odgovor: Uklanjanje se vrsi sa vrha.

    Neka je dat program gdje je potrebno uraditi obrtanje cifara za uneseni broj i neka
    su datte sljedece funkcije
    * countDigits
    * reverse
    * main
    
    Kako izgleda stek memorija za ovaj problem konkretno?

    1. Nakon poziva main funkcije stack memorija izgleda ovako:
    |               |
    |               |
    |               |
    | main          |

    2. Main funkcija poziv zahtijeva korisnicki unos broja i poziv
    funkcije 'reverse'
    Kada se pozove funkcija 'reverse', stack izgleda ovako:
    |               |
    |               |
    | reverse       |
    | main          |

    Svaka funkcija predstavlja zaseban stack-frame (sa pripadajucim varijablama i
    nizovima).

    3. 'reverse' funkcija poziva funkciju 'countDigits', nakon cega stack izgleda
    ovako:
    |               |
    | countDigits   |
    | reverse       |
    | main          |

    4. 'countDigits' je zadnja funkcija u lancu poziva (ne poziva niti jednu drugu funkciju)
    i prema tome nakon njenog izvrsenja, ista se uklanja sa steka:
    |               |
    |               |
    | reverse       |
    | main          |

    5. Slijedi izvrsenje preostalog koda u 'reverse' funkciji i uklanjanje iste sa steka:
    |               |
    |               |
    |               |
    | main          |

    6. Slijedi izvrsenje preostalog koda u 'main' funkciji i uklanjanje iste sa steka. 
    [KRAJ PROGRAMA]

    Stek je podatkovna struktura (engl. data structure):
    --> Nisu indeksirani elementi
    --> Dodaju se elementi istog tipa
    --> Dodavanje se obicno zove 'push' a uklanjanje 'pop'



    Rekurzija :: pojam
    Rekurzija je programski koncept u kojem funkcija poziva samu sebe.
    U principu, svaki iterativni program moze se prevesti u rekurzivni
    program. Vazi i suprotno, svaki rekurzivni program moze se prevesti
    u iterativni program.

    Primjeri iz stvarnog svijeta gdje se koriste rekurzivni programi:
    --> QuickSort [sort brzi od klasicnih iterativnih sortiranja tipa bubbleSort, insertionSort, ...]
    --> MergeSort [sort brzi od klasicnih iterativnih sortiranja tipa bubbleSort, insertionSort, ...]
    --> Fraktali  [fraktalna geometrija] :: Mandelbrotov skup
    --> Towers of Hanoi
    --> Fibonacijev niz [--> Golden Ratio]
    --> Binary Search

    Osnovni elementi rekurzija ukljucuju:
    1. rekurzivni poziv :: [funkcija poziva samu sebe]
    2. bazni slucaj :: To je uslov koji odreduje kada rekurzivni pozivi treba da prestanu

    Bez baznog slucaja,
    rekurzivna funkcija bi se beskonacno pozivala [nalik na beskonacno izvrsenje petlje].

    Beskonacno pozivanje uzrokuje beskonacno dodavanje stek okvira na stek, koji je ipak
    ogranicena memorija [1MB].
    Ovakva greska se zove STACK OVERFLOW.

    Recursion depth :: pojam
    Maksimalan broj mogucih poziva funkcije i zavisi od:
    --> operativnog sistema
    --> velicine steka
    --> postavke kompajlera
    Drugim rijecima, recusion depth oznacava maksimalni kapacitet steka.

    Postoje dva tipa rekurzije:
    1. 'head' rekurzija :: 
        --> tip rekurzije gdje se rekurzivni poziv nalazi ispred ostalog koda
        [ispred ostalih funkcionalnosti] 
    2. 'tail' rekurzija ::
        --> tip rekurzija gdje se rekurzivni poziv nalazi iza ostalog koda
        [iza svih ostalih funkcionalnosti] 

    HEAD rekurzija obicno izgleda ovako:
    void func() {
        1. bazni slucaj
        2. rekurzivni poziv
        3. ostali kod
    }

    TAIL rekurzija obicno izgleda ovako:
    void func() {
        1. bazni slucaj
        2. kod 
        3. rekurzivni poziv
    }

    Call stack :: pojam
    Izraz "stek poziva" u C++ odnosi se na mehanizam koji se koristi za pracenje
    redoslijeda poziva funkcija tokom izvrsavanja programa.

    Izraz "call stack" i "memorija steka"
    (ili jednostavno "stek") su povezani, ali ne predstavljaju istu stvar.

    Call Stack (Stek poziva): Predstavlja strukturu podataka
    koja se koristi za pracenje redoslijeda poziva funkcija tokom izvrsavanja programa.
    Memorija steka odnosi se na dio memorije racunara koji se koristi za skladistenje
    lokalnih varijabli i kontrolnih podataka tokom izvrsavanja programa.
*/

int main() {

    return 0;
}