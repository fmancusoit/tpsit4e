//
// Created by Francesco Pacenza on 31/12/24.
//

/*
 * Si scriva un programma C/C++ che simuli il calcolo del saldo e della giacenza media
 * di un conto corrente di una banca sfruttando al massimo il parallelismo e la programmazione multithreading.
 * Il programma dovrà stampare in STDOUT il saldo totale della banca, il saldo attuale di ogni conto corrente
 * e le giacenze medie di tutti i conti correnti.
 *
 * Il saldo di un conto corrente è calcolato come la somma delle entrate meno la somma delle uscite.
 * La giacenza media di un conto corrente è calcolata come la media aritmetica delle giacenze storiche del conto corrente.
 * Il saldo totale della banca è calcolato come la somma dei saldi di tutti i conti correnti.
 *
 * Il programma dovrà essere strutturato nel seguente modo:
 * - Creare una struct ContoCorrente che contenga i seguenti campi:
 *    - un campo per il PID del processo
 *    - un campo per il TID del thread
 *    - un intero dal nome "numeroConto" che rappresenta il numero del conto corrente
 *    - un array di interi dal nome "entrate" che rappresenta lo storico delle ultime N entrate del conto corrente
 *    - un array di interi dal nome "uscite" che rappresenta lo storico delle ultime N le uscite del conto corrente
 *    - un array di interi dal nome "giacenzaStoriche" che rappresenta lo storico del saldo del conto corrente
 *    - un intero dal nome "saldo" che rappresenta il saldo attuale del conto corrente
 *
 * - Creare una funzione calcolaSaldo che calcoli il saldo del conto corrente
 *  - la funzione dovrà ricevere come argomento una struct ContoCorrente
 *  - la funzione dovrà aggiornare il valore del saldo attuale del conto corrente
 *  - la funzione dovrà restituire il saldo del conto corrente al main thread
 *
 * - Creare una funzione calcolaGiacenzaMedia che calcoli la giacenza media del conto corrente
 *  - la funzione dovrà ricevere come argomento una struct ContoCorrente
 *  - la funzione dovrà stampare in STDOUT la giacenza media del conto corrente
 *
 * - Viene fornito come aiuto la struttura del main e di alcune funzioni di utilità.
 * - Affinchè il codice di esempio possa essere correttamente compilato senza errori è necessario
 *   modificare la struttura del programma al fine di renderla compatibile con le funzioni di utilità fornite.
*/

#include <iostream>
#include <pthread.h>
#include <vector>
#include <unistd.h>
using namespace std;

///////////////////////////////////////////////////////////////////////
// NON CANCELLARE QUESTI PARAMETRI
// Numero massimo di elementi nella history delle entrate e delle uscite del conto corrente
const int MAX_HISTORY=10;
// ID progressivo per i conti correnti
static int ID_PROGRESSIVO_CONTO_CORRENTE = 1;
// Numero massimo di thread
const int nThreads=4;
///////////////////////////////////////////////////////////////////////

// Crea qui la struct del ContoCorrente
struct ContoCorrente {
    pid_t pid;
    pthread_t tidSaldo;
    pthread_t tidGiacenza;
    int numeroConto;
    int entrate[MAX_HISTORY];
    int uscite[MAX_HISTORY];
    int giacenzaStoriche[MAX_HISTORY];
    int saldo;
};

void* calcolaSaldo(void* args) {
    ContoCorrente* cc = (ContoCorrente*) args;
    int totEntrate = 0;
    int totUscite = 0;
    for(int i = 0; i < MAX_HISTORY; ++i) {
        totEntrate += cc->entrate[i];
        totUscite += cc->uscite[i];
    }
    cc->saldo = totEntrate - totUscite;
    cout << endl << "Saldo attuale conto: " << cc->saldo;
    return nullptr;
}

// Crea qui la funzione calcolaGiacenzaMedia: la giacenza media è la media aritmetica delle giacenze storiche del conto corrente
void* calcolaGiacenzaMedia(void* args) {
    ContoCorrente* cc = (ContoCorrente*) args;
    int g = 0;
    for(int i = 0; i < MAX_HISTORY; ++i) {
        g += cc->giacenzaStoriche[i];
    }
    g = g / MAX_HISTORY;

    cout << endl << "Giacenza media conto: " << g;
    return nullptr;
}


///////////////////////////////////////////////////////////////////////
// NON CANCELLARE QUESTA FUNZIONE DI UTILITA'
ContoCorrente createContoCorrente() {
    ContoCorrente cc;
    cc.numeroConto = ID_PROGRESSIVO_CONTO_CORRENTE++;
    cc.saldo = 0;
    for (int h=0; h<MAX_HISTORY; ++h) {
        cc.entrate[h] = random()%1000+200;
        cc.uscite[h] = random()%100+15;
        cc.giacenzaStoriche[h] = random()%1000+100;
    }
    return cc;
}

// Questa funzione di utilità serve per stampare tutti i dati del conto corrente. è già implementata ed è
// utile in caso di debug. Non serve modificarla.
void printConto(ContoCorrente cc) {
    cout<<"############################################"<<endl;
    cout<<"Conto corrente #"<<cc.numeroConto<<endl;
    cout<<"Entrate: ";
    for (int h=0; h<MAX_HISTORY; ++h)
        cout<<cc.entrate[h]<<" ";
    cout<<endl;
    cout<<"Uscite: ";
    for (int h=0; h<MAX_HISTORY; ++h)
        cout<<cc.uscite[h]<<" ";
    cout<<endl;
    cout<<"Saldo attuale: "<<cc.saldo<<endl;
    cout<<"Storico saldo: ";
    for (int h=0; h<MAX_HISTORY; ++h)
        cout<<cc.giacenzaStoriche[h]<<" ";
    cout<<endl;
    cout<<"############################################"<<endl<<endl;
}
///////////////////////////////////////////////////////////////////////


int main(int argc, char const* argv[]) {
    srand(time(nullptr));
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Inserire qui il codice per la creazione dei thread e la gestione del calcolo del saldo e della giacenza media //
    // Generare n conti correnti e salvarli in un array di dimensione nThreads (la variabile nThread è gia definita) //
    // è possibile utilizzare la funzione createContoCorrente() per generare un conto corrente                       //
    // L'esercizio può essere svolto utilizzando i costrutti basilari di C/C++ e la libreria pthread ma              //
    // è consentito l'uso di qualsiasi struttura dati C/C++ di cui si è a conoscenza e che non si è                  //
    // studiata a lezione                                                                                            //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    ContoCorrente arrayCC[nThreads] = {};

    for (int i = 0; i < nThreads; ++i) {
        // Genero n CC e li salvo in un array di dimensione nThreads
        arrayCC[i] = createContoCorrente();
    }
    
    for (int i = 0; i < nThreads; i++) {
        // Calcolo il saldo totale della banca sommando i singoli saldi calcolati
        pthread_t tid;
        arrayCC[i].pid = getpid();
        arrayCC[i].tidSaldo = tid;
        if (pthread_create(&arrayCC[i].tidSaldo, nullptr, calcolaSaldo, &arrayCC[i]) != 0){
            cerr << endl << "Errore creazione thread Saldo";
        }
    }

    for (int i = 0; i < nThreads; i++) {
        // Calcolo e stampa Giacenza Media
        pthread_t tid;
        arrayCC[i].pid = getpid();
        arrayCC[i].tidGiacenza = tid;
        if (pthread_create(&arrayCC[i].tidGiacenza, nullptr, calcolaGiacenzaMedia, &arrayCC[i]) != 0){
            cerr << endl << "Errore creazione thread Giacenza";
        }
    }

    for (int i = 0; i < nThreads; i++) {
        // Raccolgo i thread
        if (pthread_join(arrayCC[i].tidSaldo, nullptr) != 0){
            cerr << endl << "Errore join thread Saldo";
        }

        if (pthread_join(arrayCC[i].tidGiacenza, nullptr) != 0){
            cerr << endl << "Errore join thread Giacenza";
        }
    }

    int totSaldoBanca = 0;

    for (int i = 0; i < nThreads; i++) {
        totSaldoBanca += arrayCC[i].saldo;
    }

    cout << endl << endl << "Saldo Totale Banca: " << totSaldoBanca << endl<< endl;

    return 0;
}