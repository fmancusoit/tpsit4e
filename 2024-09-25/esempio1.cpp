// Differenza fra memoria statica e dinamica

// argc e argv = argomenti principali dell'argomento
// se li omettiamo il programma non può essere configurato nella preconfigurazione

// int main (int argc, char const *argv[])

#include <iostream>
using namespace std;




// Array dinamico

// int* array_heap; --> può puntare ad una variabile o un array
// array_heap = new int[SIZE]; --> inizializza questo puntatore ad un array
//              new --> alloca memoria
//              SIZE --> quante celle prendere

// ora l'array punta ad una cella, che è la prima dell'array
// i valori invece di essere casuali, ora sono tutti 0

// SIZE dell'array ora è dinamica, e viene stabilita in run-time, non durante la programmazione

// 