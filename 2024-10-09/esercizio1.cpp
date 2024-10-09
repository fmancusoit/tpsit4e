#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int proc1() {
    // Primo figlio
    // Calcola la somma di numeri da 1 a 10 e termina con il risultato come codice di uscita

    int somma = 0;
    for (int i = 1; i < 11; i++) {
        somma = somma + i;
    }

    return somma;
}

int proc2() {
    // Secondo figlio
    // Calcola il prodotto di numeri da 1 a 5 e termina con il risultato come codice di uscita

    int prodotto = 1;
    for (int i = 1; i < 6; i++) {
        prodotto *= i;
    }

    return prodotto;
}



int main(int argc, char const* argv[]) {

    // Primo figlio
    pid_t pid = fork();

    if (pid < 0) {
        cout << "Errore nel FORK" << endl;
        exit(1);

    } else if (pid == 0) {
        // Codice primo figlio
        cout << " > Avvio primo figlio" << endl;
        
        srand(time(NULL));
        int random = rand()%1+3;
        sleep(random);

	    exit(proc1());
    }

    // Secondo figlio
    pid_t pid = fork();

    if (pid < 0) {
        cout << "Errore nel FORK" << endl;
        exit(1);

    } else if (pid == 0) {
        // Codice secondo figlio
        cout << " > Avvio secondo figlio" << endl;
        
        srand(time(NULL));
        int random = rand()%1+3;
        sleep(random);

	    exit(proc2());
    }

    cout << "Padre" << endl;

    return 0;
}