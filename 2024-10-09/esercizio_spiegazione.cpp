/* 
Processo figlio calcola il prodotto fra 2 numeri, se il risultato è pari, exit(2), altrimenti exit(255)
Processo padre si mette in attesa della fine del figlio, poi stampa a video se è pari o dispari
*/

#include <iostream>
#include <unistd.h> // Fork Exit
#include <sys/wait.h> // Wait
using namespace std;

int calcolaProdotto() {
    int a = 0;
    int b = 0;
    cout << "Inserisci il primo numero: ";
    cin >> a;
    cout << "Inserisci il secondo numero: ";
    cin >> b;
    return a*b;
}

int main(int argc, char const* argv[]) {

    pid_t pid = fork(); // PID del processo, la funzione fork genera un processo figlio

    if (pid < 0) {
        // Errore nella creazione del processo figlio, interrompo tutto (anche il main)
        cout << "Errore nel FORK" << endl;
        exit(1); // Obbligatorio
    }

    // Utilizzo di un if per stabilire il codice eseguito dal figlio o dal padre

    if (pid == 0) {
        // Tutto il codice qui dentro verrà eseguito dal processo figlio
        int numero = calcolaProdotto();
        if (numero % 2 == 0) {
            exit(2);
        }
        exit(255);

    } else if (pid > 0) { // ELSE non necessario, in quanto il figlio arrivato al suo EXIT terminerà senza proseguire
        // Tutto il codice qui dentro verrà eseguito dal processo padre

        int* status = new int();

        // se si hanno più processi figli, per richiamare l'exit giusto si utilizza pid_terminated
        // pid_terminated = id del processo appena terminato
        // status = stato + exit code del processo terminato

        pid_t pid_terminated = wait(status); // la variabile int * verrà aggiornata con il contenuto dell'EXIT CODE (2 byte - stato di uscita e codice di uscita)

        if (WIFEXITED(*status)) { // WaitIFExited = controlla il contenuto di status, se è uscito ritorna true o false
            int exitCode = WEXITSTATUS(*status); // WaitEXITSTATUS = prende il codice di uscita partendo dal puntatore status

            if (exitCode == 2 ){
                cout << endl << "Il processo con PID: " << pid_terminated << " è terminato e il risultato è pari" << endl;
            } else {
                cout << endl << "Il processo con PID: " << pid_terminated << " è terminato e il risultato è dispari" << endl;
            }
        }

        delete status; // da inserire subito, per evitare errori e problemi di gestione di memoria

    }


    return 0;
}