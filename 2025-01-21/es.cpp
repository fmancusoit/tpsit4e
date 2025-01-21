/*
Si suppone di avere una pizzeria e di dover gestire gli ordini di quest'ultima, che sono 10 per ogni giornata.
Nella pizzeria ci sono in servizio x pizzaioli e y aiutanti (x+y = numero thread), i pizzaioli si occupano di
creare la base per la pizza (cioè una margherita) mentre gli aiutanti si occupano di aggiungere uno dei tre topping disponibili alle pizze.
* L'ORDINE IN CUI VENGONO SVOLTE LE OPERAZIONI NON HA IMPORTANZA !! * [cioè non importa se vengono messi prima i topping e poi il sugo e la mozzarella]
La giornata si conclude quando tutti e 10 gli ordini sono stati completati (sono passati dal pizzaiolo e dall'aiutante)

Creare quindi un programma sviluppato nel seguente modo :

    - Gli ordini delle pizze giornalieri saranno rappresentati da una struttura dati statica di capienza 10 di tipo pizza che dovrà
      essere condivisa tra i thread (cioè tutti thread dovranno averne una)

    - "pizza" è il nome della classe che ogni elemento dell'array dovrà avere, cioè una struttura dati composta da:

            - Pid processo
            - Tid del thread
            - Tipo di pizza (Valore numerico tra 1 a 3 casuale)
            - Booleano per rappresentare il lavoro dei pizzaioli
            - Booleano per rappresentare il lavoro degli aiutanti

    Cosa dovranno fare rispettivamente le due entità?

        Pizzaiolo -- > Controlla il campo booleano e se è false verrà settato a true, nulla altrimenti

        Aiutante -- >  Genera un numero da 1 a 3, se è uguale a quello nel campo "tipo pizza" && il booleano ha valore false lo setta a true, altrimenti va avanti


    - Ogni thread dovrà controllare TUTTE le pizze, il lavoro non viene quindi diviso tra i thread

    - Le pizze rilasciate devono essere riprese e guarnite da un altro thread

    - Il main termina quando tutti i booleani hanno valore true
*/

#include <bits/stdc++.h>
using namespace std;

int nOrdini = 10;
int completati = nOrdini*2;

struct Pizza {
    pid_t pid;
    pthread_t tidp; // id thread pizzaioli
    pthread_t tida; // id thread aiutanti
    int tipo;
    bool pizzaioli;
    bool aiutanti;
};

void* aiutante(void* args) {
    Pizza* argomenti = (Pizza*)args;
    bool controllo = argomenti->aiutanti;
    int random = rand()%3+1;
    if (!controllo && (argomenti->tipo == random)) {
        argomenti->aiutanti = true;
        completati--;
        // Se l'aiutante coincide con il tipo di pizza e non è stata già finita, la completa
    }
    return nullptr;
}

void* pizzaiolo(void* args) {
    Pizza* argomenti = (Pizza*)args;
    bool controllo = argomenti->pizzaioli;
    if (!controllo) {
        argomenti->pizzaioli = true;
        // Metto sugo e mozzarella sulla pizza
        completati--;
    }
    return nullptr;
}

int main(int args, char* const argv[]) {
    vector<Pizza> ordini(nOrdini);
    int pizzaioli = 0;
    int aiutanti = 0;

    srand(time(0)); // Seed numeri casuali
    
    while(true) {
        cout << endl << "Inserisci numero pizzaioli: ";
        cin >> pizzaioli;
        if (pizzaioli > 0) {
            break;
        }
        cout << endl << " [E] Il numero di pizzaioli deve essere almeno 1!";
    }

    while(true) {
        cout << endl << "Inserisci numero aiutanti: ";
        cin >> aiutanti;
        if (aiutanti > 0) {
            break;
        }
        cout << endl << " [E] Il numero di aiutanti deve essere almeno 1!";
    }

    for(int i = 0; i < nOrdini; i++) {
        // Assegno tipi casuali alle pizze
        ordini[i].tipo = rand()%3+1;

        // Assegno il pid del processo padre
        ordini[i].pid = getpid();

        // Ordini da fare
        ordini[i].pizzaioli = false;
        ordini[i].aiutanti = false;
    }

    for(int i = 0; i < nOrdini; i++) {
        // Lanciatore thread pizzaioli
        pthread_t pid;
        ordini[i].tidp = pid;
        if (pthread_create(&ordini[i].tidp, nullptr, pizzaiolo, &ordini[i]) != 0) {
            cerr << endl << " [E] Errore nella creazione del thread pizzaiolo";
            return 1;
        }
    }

    while(completati > 0) {
        for(int i = 0; i < nOrdini; i++) {
            // Lanciatore thread aiutanti
            pthread_t pid;
            ordini[i].tida = pid;
            if (pthread_create(&ordini[i].tida, nullptr, aiutante, &ordini[i]) != 0) {
                cerr << endl << " [E] Errore nella creazione del thread aiutante";
                return 1;
            }
        }
        
        for(int i = 0; i < nOrdini; i++) {
            if (pthread_join(ordini[i].tida, nullptr) != 0) {
                cerr << endl << " [E] Errore nel join del thread aiutante";
                return 1;
            }
        }
    }
    
    for(int i = 0; i < nOrdini; i++) {
        // Raccoglitore thread
        if (pthread_join(ordini[i].tidp, nullptr) != 0) {
            cerr << endl << " [E] Errore nel join del thread pizzaiolo";
            return 1;
        }
    }

    if (completati == 0) {
        cout << endl << " > Tutti gli ordini sono stati completati!" << endl << endl;
    }

    return 0;
}