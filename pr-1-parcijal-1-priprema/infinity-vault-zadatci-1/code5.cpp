#include <iostream>

/* 
    Poštujući sve faze procesa programiranja, napisati program 
    koji korisniku omogućava unos cijelog broja N, te izračunava 
    vrijednost sume faktorijela neparnih brojeva u intervalu [1, N].
    Suma faktorijela prikazana je sljedećom formulom: 
    S = 1! + 3! + 5! + ... + N!
*/

void unos(int &);
unsigned long long faktorijal(const int);
unsigned long long sumaNeparnihFaktorijalaDoN(const int);

int main() {
    int N {};

    unos(N);

    std::cout<<"Suma neparnih faktorijala od [1, "<<N<<" je "<<sumaNeparnihFaktorijalaDoN(N)<<std::endl;

    std::cin.get();
    return 0;
}

void unos(int &unos) {
    std::cout<<"Unesi prirodan broj (N): ";
    std::cin>>unos;
}

unsigned long long faktorijal(int broj) {
    unsigned long long faktorijal {1ull};

    for (; broj >= 2; broj--)
        faktorijal *= broj;
    
    return faktorijal;
}

unsigned long long sumaNeparnihFaktorijalaDoN(const int N) {
    unsigned long long suma {0ull};
    
    for (int i = 1; i <= N; i += 2)
        suma += faktorijal(i);

    return suma;
}