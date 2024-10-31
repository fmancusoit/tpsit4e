#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;

int main(int argc, const char* argv[]) {

    pid_t pid1 = fork();

    if (pid1 < 0) {
        cout << "Errore FORK";
        exit(1);
    } else if (pid1 == 0) {
        // Primo figlio
        int tempo = rand() % 4 + 1;
        sleep(tempo);

        int somma = 0;
        for (int i = 1; i < 11; i++) {
            somma += i;
        }
        exit(somma);
    }

    pid_t pid2 = fork();

    if (pid2 < 0) {
        cout << "Errore FORK";
        exit(1);
    } else if (pid2 == 0) {
        // Secondo figlio
        int tempo = rand() % 6 + 1;
        sleep(tempo);

        int prodotto = 1;
        for (int i = 1; i < 6; i++) {
            prodotto *= i;
        }
        exit(prodotto);
    }

    pid_t pid3 = fork();

    if (pid3 < 0) {
        cout << "Errore FORK";
        exit(1);
    } else if (pid3 == 0) {
        // Terzo figlio
        int tempo = rand() % 3 + 1;
        sleep(tempo);
        exit(tempo);
    }

    for(int i = 0; i < 3; i++) {
        int *status = new int();
        pid_t pid_terminated = wait(status);

        if(WIFEXITED(*status)) {
            int codice = WEXITSTATUS(*status);
            cout << endl << "Il processo con PID " << pid_terminated << " è terminato con codice di uscita " << codice << endl;
        }

        delete status;
    }

    cout << endl << "Tutti i processi sono terminati, fine" << endl << endl;

    return 0;
}