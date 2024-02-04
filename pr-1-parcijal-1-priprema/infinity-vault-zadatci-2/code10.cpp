#include<iostream>

/*
    Napisati program koji rješava sljedeći problem. Date su firma 
    A, B i C sa godišnjim prihodima: A - prihod 10M eura B - prihod 
    7M eura C - prihod 5M eura sa sljedećim stabilnim fiksnim godišnjim 
    rastom prihoda za koji pretpostavljamo da se neće mijenjati A - 2.05%
    B - 2.80% C - 4.30% Potrebno je pronaći koja firma će prva prestići 
    firmu A u godišnjem prihodu i za koliko godina će se to desit.

    Također potrebno je ispisati koliko će sve tri firme imati godišnji 
    prihod u toj godini.
*/

int main() {
    int godina {0};
    float A { 10.0f }, B { 7.0f }, C { 5.0f };
    const float rastA { 2.05f / 100.0f }, rastB { 2.8f / 100.0f }, rastC { 4.3f / 100.0f };

    while (B <= A && C <= A) {
        A = A + A * rastA;
        B = B + B * rastB;
        C = C + C * rastC;

        godina++;
    }
        
    std::cout<<"Firma "<<((B > A)? 'B' : 'C')<<" je prestigla firmu A nakon "<<godina<<" godina\n";

    std::cout<<"Firma A prihod na kraju: "<<A<<'\n';
    std::cout<<"Firma B prihod na kraju: "<<B<<'\n';
    std::cout<<"Firma C prihod na kraju: "<<C<<'\n';

    return 0;
}