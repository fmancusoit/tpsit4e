#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

bool primo(int n) {
    int div = 0;
    for (int i = 1; i <= n; i++) {
        if ((n % i) == 0) {
            div++;
        }
    }
    if (div == 2) {
        return true;
    } else {
        return false;
    }
}

int main(int argc, char const* argv[]) {
    
    int nproc = 0;
    int min = 0;
    int max = 0;
        
    while (true) {
        cout << endl << " > Inserisci numero minimo: ";
        cin >> min;
        if (min >= 0) {
            break;
        }
        cout << endl << "[E] Inserisci un numero maggiore o uguale a 0!";
    }

    while (true) {
        cout << endl << " > Inserisci numero massimo: ";
        cin >> max;
        if (max > min) {
            break;
        }
        cout << endl << "[E] Inserisci un numero maggiore del minimo!";
    }

    while (true) {
        cout << endl << " > Inserisci numero di processi: ";
        cin >> nproc;
        if (nproc > 0 && nproc < 9) {
            break;
        }
        cout << endl << "[E] Inserisci un numero maggiore di 0 e/o minore di 9!";
    }

    int intervallo = (max - min) + 1;
    int intervalliproc = intervallo / nproc;
    int resto = intervallo % nproc;

    int minint = min;

    for (int i = 0; i < nproc; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            cout << "Errore FORK";
            exit(1);
        } else if (pid == 0) {
            int maxint = minint + intervalliproc - 1;
            if (i == nproc - 1) {
                maxint += resto;
            }

            int cont = 0;
            for (int j = minint; j <= maxint; j++) {
                if (primo(j)) {
                    cont++;
                }
            }
            exit(cont);
        }

        minint = minint + intervalliproc;
    }

    int contatore = 0;
    for (int i = 0; i < nproc; i++) {
        int *status = new int();
        pid_t pid_terminated = wait(status);

        if(WIFEXITED(*status)) {
            int codice = WEXITSTATUS(*status);
            contatore = contatore + codice;
        }

        delete status;
    }

    cout << endl << "Il numero di numeri primi trovati è " << contatore << endl << endl;

    return 0;
}