#include<iostream>
#include<iomanip>

// globalna konstanta koja odreduje max broj redova za matricu
const int MAX_ROWS { 100 };

// globalna konstanta koja odreduje max broj kolona za matricu
const int MAX_COLUMNS { 100 };

void enterMatrix(int matrica[][MAX_COLUMNS], const int rows, const int cols) {
    if (rows > MAX_ROWS || cols > MAX_COLUMNS) {
        return;
    }

    for (int i = 0; i < rows; i++) {
        for (int ii = 0; ii < cols; ii++) {
            std::cout<<"Unesite element ["<<i<<", "<<ii<<"]: ";
            std::cin>>matrica[i][ii];   // dvostruko referenciranje 
            // (krecemo se po adresnom prostoru prvo redova pa onda kolona)
        }
    }
}

void printMatrix(int matrica[][MAX_COLUMNS], const int rows, const int cols) {
    if (rows > MAX_ROWS || cols > MAX_COLUMNS) {
        return;
    }

    for (int i = 0; i < rows; i++) {
        for (int ii = 0; ii < cols; ii++) {
            std::cout<<std::setw(3)<<matrica[i][ii]<<' ';
        }
        std::cout<<std::endl;
    }
}

int getRandomValue(const int from, const int to) {
    // u pitanju je uniformna distribucija (svaki broj u opsegu ima istu
    // vjerovatnocu
    // [5-10]: 5, 6, 7, 8, 9, 10

    // rand() --> funkcija generise slucajnu cjelobrojnu vrijednost.
    // rand() % 8 --> vraca jednu od vrijednosti u opsegu 0 ... 7
    // rand() % 8 + 5 --> vraca jednu vrijednost u opsegu 5 ... 12

    // dakle, 8 je sirina opsega, a 5 je pocetni broj

    // rand() % (13 - 5 + 1) + 5 --> rand() % 9 + 5 --> [0..8] + 5 --> [5..13] 

    return rand() % (to - from + 1) + from;
}

void setRandomValues(int matrica[][MAX_COLUMNS], const int rows, const int cols, const int from, const int to) {
    if (rows > MAX_ROWS || cols > MAX_COLUMNS) {
        return;
    }

    for (int i = 0; i < rows; i++) {
        for (int ii = 0; ii < cols; ii++) {
            matrica[i][ii] = getRandomValue(from, to); 
        }
    }
}

/*
    Prilikom pokretanja programa, primjecujemo kako program generise uvijek ISTE SLUCAJNE vrijednosti.
    Zbog toga kazemo da su ove vrijednosti - PSEUDORANDOM vrijednosti buduci da postoji odredeni 
    faktor determinizma (predvidivosti ili odredenosti).
    
    Taj unutarnji faktor koji odreduje redoslijed generisanja slucajnih brojeva, zove se SEED.
    SEED je jedan cijeli broj, koji je defaultno settovan na odredenu vrijednost.
    (mi ne znamo koja je to vrijednost, ali znamo da je ta vrijednost uvijek ista)

    ISTI SEED --> polucuje iste slucajne vrijednosti svaki put kad se pokrene program
    Seed se moze rucno promjeniti koristenjem funkcije 'srand':

    srand(42);

    Seed = 42, to znaci da se generisu slucajni karakteristicni bas za vrijednost seed-a od 42

    Za dobijanje pravih (cistih) [engl. pure random number] slucajnih vrijednosti
    potrebno je da seed bude drugaciji svaki put kad se program pokrece.

    To se moze postici pozivom sljedece funkcije:
    srand(time(NULL));

    Ovdje se vrijednost 'seed'-a asocira uz procesorsko vrijeme.
    Buduci da procesorsko vrijeme nikad nije isto - samim tim vrijednost 'seed'-a nikad nece biti
    ista.
*/

int main() {
    srand(time(NULL));

    int r {}, c {};
    
    do {
        std::cout<<"Unesite broj redova: ";
        std::cin>>r;

        std::cout<<"Unesite broj kolona: ";
        std::cin>>c;
    } while(r < 0 || r > MAX_ROWS || c < 0 || c > MAX_COLUMNS);

    int matrica[MAX_ROWS][MAX_COLUMNS] {};

    setRandomValues(matrica, r, c, 6, 10);
    printMatrix(matrica, r, c);

    return 0;
}