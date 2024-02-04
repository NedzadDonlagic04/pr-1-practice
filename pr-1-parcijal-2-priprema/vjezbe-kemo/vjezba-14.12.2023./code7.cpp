#include<iostream>

/*
    Pokazivaci i staticki nizovi
*/

int main() {
    int arr[6] {};  // kreiranje niza na stack-u (staticki niz)

    // Jer je profa rekao "Mozete pokazivac nazvati kako god hocete"
    int *kakoGodHocete {};  // "viseci pokazivac" (engl. hanging pointer)
    // ima defaultnu hexadecimalnu "junk vrijednost"

    kakoGodHocete = arr;    // pokazivacu se dodijeljuje adresa 'arr'

    for (int i = 0; i < std::size(arr); i++) {
        std::cout<<"Unesite vrijednost na lokaciji "<<i<<": ";
        // 1. nacin
        // std::cin>>arr[i];
        // 2. nacin
        // std::cin>>*(arr + i);        // u pozadini nesto kao *(0x1234ff00bb)
        // 3. nacin
        // std::cin>>kakoGodHocete[i];
        // 4. nacin
        std::cin>>*(kakoGodHocete + i); // u pozadini nesto kao *(0x1234ff00bb)
        // pomak + dereferenciranje
    }

    for (int i = 0; i < std::size(arr); i++) {
        std::cout<<*(kakoGodHocete + i)<<' ';
        // pomak + dereferenciranje
    }
    std::cout<<std::endl;

    return 0;
}