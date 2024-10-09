// Programma C++ che dichiari una variabile di tipo intero e un puntatore ad interi
// Stampare in OUTPUT il valore di &nome_variabile_intera, il valore del puntatore e
// il risultato ottenuto dall'espressione &*variabile_puntatore

#include <iostream>
using namespace std;

int main() {

    int variabile = 3;
    int *p = NULL;

    p = &variabile;

    cout << p << endl;
    cout << *p << endl;
    cout << &*p << endl;

    return 0;
}