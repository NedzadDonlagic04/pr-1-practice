#include<iostream>

void deposit(float &, const float);
void withdraw(float &, const float);
void checkBalance(const float);
void displayMenu();
void unosOpcije(short &);
void izvrsiOpciju(const short, float &);

int main() {
    float balance {0};
    short opcija {};

    do {
        displayMenu();
        unosOpcije(opcija);
        izvrsiOpciju(opcija, balance);
    } while(opcija != 4);

    return 0;
}

void deposit(float &balance, const float amount) {
    balance += amount;
    std::cout<<"Uplaceno je: "<<amount<<". Novo stanje na racunu: "<<balance<<" KM\n"; 
}

void withdraw(float &balance, const float amount) {
    balance -= amount;
    std::cout<<"Povuceno iznod od: "<<amount<<". Novo stanje na racunu: "<<balance<<" KM\n"; 
}

void checkBalance(const float balance) {
    std::cout<<"\nIznos stanja na racunu "<<balance<<" KM.\n";
}

void displayMenu() {
    std::cout<<"\n";
    std::cout<<"*** Menu ***\n";
    std::cout<<"1. Uplata\n2. Isplata\n3. Provjera stanja\n4. Izlaz\n";
}

void unosOpcije(short &opcija) {
    do {
        std::cout<<"Unesite vas izbor: ";
        std::cin>>opcija;

        if (opcija < 1 || opcija > 4) {
            std::cout<<"Nevazeca opcija\n";
            displayMenu();
        }
    } while (opcija < 1 || opcija > 4);
}

void unosAmount(float &amount, const short opcija) {
    do {
        std::cout<<"\nUnesite vrijednost "<<(opcija == 1? "uplate" : "isplate")<<": ";
        std::cin>>amount;

        if (amount < 0)
            std::cout<<"Nevalidan novcani unos\n"; 

    } while (amount < 0); 
} 

void izvrsiOpciju(const short opcija, float &balance) {
    float amount {};

    if (opcija == 1 || opcija == 2)
        unosAmount(amount, opcija);

    if (opcija == 1) 
        deposit(balance, amount);
    else if (opcija == 2) 
        withdraw(balance, amount);
    else if (opcija == 3) 
        checkBalance(balance);
}