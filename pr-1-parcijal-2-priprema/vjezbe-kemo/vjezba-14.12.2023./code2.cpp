#include<iostream>

/*
    Imo ovaj dio nije bas najpametniji za uzet kao istinu ili citavu pricu
*/

/*
    Reference kao povratne vrijednost funkcija
*/

int& func() {
    int var {96};

    return var;
}

/*
    Koja ja razlika izmedu koristenja
    int func() i int& func() ?

    "int func()" vraca samo vrijednost neke varijable ili
    neku fiksnu vrijednost
    "int& func()" vraca cijelu varijablu sa njenom vrijednosti

    "static" kljucna rijec, prica za kasnije
*/

int main() {
    // dohvacanje varijable 'var' iz funkcije 'func'
    std::cout<<"Vrijednost varijable 'var': "<<func()<<std::endl;

    int temp {func()};
    /*
        Temp se kreira kao kopija varijable koju vraca poziv funkcije 'func'
        Ovdje se gubi podatak o varijabli 'var' iz 'func' funkcije
    */
    std::cout<<temp<<std::endl;

    int& temp2 {func()};
    /*
        'temp2' je referenca (drugi naziv) za varijablu 'var' iz funkcije 'func'
        Tako da, u ovom slucaju ne gubi se podatak (lokacije) variable 'var'
    */    
    std::cout<<temp2<<std::endl;

    return 0;
}