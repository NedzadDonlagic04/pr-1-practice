#include<iostream>
#include<iomanip>

/*
    Foreach petlja bez koristenja interne [ugradene] reference
*/

const int MAX_SIZE {20};
const int WIDTH_SIZE {3};

int main() {
    int arr[MAX_SIZE] {0};

    for (int &el : arr) {
        el += 5;
    }

    /*
    for (int el : arr) {
        el += 5;
    }

        U svakoj iteraciji kreira se 'el' kao kopija varijable iz niza
        Svaka izmjena / manipulacija desava se nad kopijom 'el' a ne nad
        orginalnom varijablom.
    */

    for (const int el : arr) {
        std::cout<<std::setw(WIDTH_SIZE)<<el<<' ';
    }

    std::cout<<std::endl;

    // Obavezno koristiti reference kada je potrebno mijenjati vrijednosti iz niza
    // Dok kada se radi samo ispis vrijednosti, tada je svejedno

    /*
        Koristenje kljucne rijeci 'auto'
        'auto' je kljucna rijec koja se koristi za automatsko prepoznavanje
        tipa podatka.

        auto x = 5;     // 5 je integer literal -> x ce biti tipa 'int'
        auto y = 3.14;  // 3.14 je double literal -> y ce biti tipa 'double'
        auto z = 4.44f; // 4.44f je float literal -> z ce biti tipa 'float'
    */

    for (auto &el : arr) {  // tip reference se prepoznaje na osnovu tipa niza / kontejnera / strukture podatka
        el += 15;           // el = el + 15
    }

    for (const int el : arr) {
        std::cout<<std::setw(WIDTH_SIZE)<<el<<' ';
    }

    std::cout<<std::endl;

    return 0;
}