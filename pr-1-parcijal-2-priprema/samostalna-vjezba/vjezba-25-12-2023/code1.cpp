/*
Napisati program koji napravi strukturu Osoba, mozete koristiti
ovo tijelo strukture kao referencu kako trebaju izgledati
atributi i metode (moguce je drugacije metode koristiti, ali
ovi atributi nek ostanu isti).

const std::size_t MAX_STR_SIZE { 256 };

struct Osoba {
    char imeIPrezime[MAX_STR_SIZE] {};
    int godine {}; 

    void getImeIPrezimeInput();
    void getGodineInput();
    void getOsobaInfo() const;
};

Napraviti unos u niz od n osoba (korisnik unosi duzinu, ogranici da duzina
bude u intervalu [2, 1000]), izvrsiti unos podataka korisnika, onda 
sortirati i ispisati korisnike po godinama uzlazno.
*/

#include<iostream>
#include<cstddef>
#include<limits>

const std::size_t MAX_STR_SIZE { 256 };

struct Osoba {
    char imeIPrezime[MAX_STR_SIZE] {};
    int godine {}; 

    void getImeIPrezimeInput();
    void getGodineInput();
    void getOsobaInfo() const;
};

void clearInputBuffer();
bool isValidName(const char *);

void enterArrSize(std::size_t &);
void enterArrOsobe(Osoba *, const std::size_t);
void printArrOsobe(const Osoba *, const std::size_t);

void sortOsobeByAge(Osoba *, const std::size_t);

int main() {
    std::size_t arrSize {};

    enterArrSize(arrSize);
    
    Osoba *osobe { new Osoba[arrSize] };

    enterArrOsobe(osobe, arrSize);

    std::cout<<"Osobe prije sorta: \n";
    printArrOsobe(osobe, arrSize);

    sortOsobeByAge(osobe, arrSize);

    std::cout<<"Osobe poslije sorta: \n";
    printArrOsobe(osobe, arrSize);

    delete[] osobe;

    return 0;
}

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool isValidName(const char *fullName) {
    for (std::size_t i = 0; fullName[i] != '\0'; i++) {
        if (fullName[i] != ' ' && !isalpha(fullName[i])) {
            return false;
        }
    }
    return true;
}

void enterArrSize(std::size_t &size) {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<"Unesi duzinu niza (tj. broj osoba): ";
        std::cin>>size;

        if (std::cin.fail()) {
            std::cout<<"Nevalidan unos\n";
            clearInputBuffer();
            repeatLoop = true;
        } else if (size < 2 || size > 1000) {
            std::cout<<"Unos treba biti u intervalu [2, 1000]\n";
            repeatLoop = true;
        }
    } while(repeatLoop);
}

void enterArrOsobe(Osoba *osobe, const std::size_t size) {
    for (std::size_t i = 0; i < size; i++) {
        std::cout<<"Osoba "<<i + 1<<" info input\n";
        osobe[i].getImeIPrezimeInput();
        osobe[i].getGodineInput();
        std::cout<<'\n';
    }
}

void printArrOsobe(const Osoba *osobe, const std::size_t size) {
    for (std::size_t i = 0; i < size; i++) {
        std::cout<<"Osoba "<<i + 1<<" info\n";
        osobe[i].getOsobaInfo();
        std::cout<<'\n';
    }
}

void Osoba::getImeIPrezimeInput() {
    clearInputBuffer();
    do {
        std::cout<<"Unesi ime i prezime osobe: ";
        std::cin.getline(this->imeIPrezime, MAX_STR_SIZE); 

        if (!isValidName(this->imeIPrezime)) {
            std::cout<<"Nevalidno ime i/ili prezime\n";
        }
    } while(!isValidName(this->imeIPrezime));
}

void Osoba::getGodineInput() {
    bool repeatLoop {};

    do {
        repeatLoop = false;

        std::cout<<"Unesi godine osobe: ";
        std::cin>>this->godine;

        if (std::cin.fail()) {
            std::cout<<"Unos nije validan\n";
            clearInputBuffer();
            repeatLoop = true;
        } else if (this->godine < 0) {
            std::cout<<"Unesene godine ne mogu biti negativan broj\n";
            repeatLoop = true;
        } else if (this->godine > 130) {
            std::cout<<"Unesene godine ne mogu biti vece od 130\n";
            repeatLoop = true;
        }
    } while(repeatLoop);
}

void Osoba::getOsobaInfo() const {
    std::cout<<this->imeIPrezime<<" ima "<<this->godine<<" godina\n";
}

void sortOsobeByAge(Osoba *osobe, std::size_t size) {
    bool repeatLoop {};

    do {
        repeatLoop = false;
        size--;

        for (std::size_t i = 0; i < size; i++) {
            if (osobe[i].godine > osobe[i + 1].godine) {
                std::swap(osobe[i], osobe[i + 1]);
                repeatLoop = true;
            }
        }
    } while(repeatLoop);
}