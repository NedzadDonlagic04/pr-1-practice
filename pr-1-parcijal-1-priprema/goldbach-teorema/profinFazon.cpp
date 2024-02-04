#include<iostream>
using namespace std;

int counter = 0;
 
void goldbach(int);
bool prost(int);
 
int main() {
    int a;
    int b;
 
    do
    {
        cout << "Molimo unesite prvu granicu ranga: " << endl;
        cin >> a;
    } while (a < 50);
 
    do
    {
        cout << "Molimo unesite drugu granicu ranga: " << endl;
        cin >> b;
    } while (b < (a + 100));
 
    (a % 2 != 0) ? a++ : 1;
 
    for (int i = a; i < b; i+=2)
    {
        goldbach(i);    
    }
 
    cout<<'\n'<<counter<<'\n';
 
    return 0;
}
 
void goldbach(int broj) {
    for (int i = broj / 2, j = broj / 2; i < broj; i ++, j --, counter++)
    {
        if (prost(i) && prost(j))
        {
            cout << "Broj " << broj << " = " << i << " + " << j << endl;
            break;
        }
    }
}
 
bool prost(int broj) {
    for (int i = 2; i < broj / 2; i++)
    {
        if (broj % i == 0)
        {
            return false;
        }
    }
    return true;
}