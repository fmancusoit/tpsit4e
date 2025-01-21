/*
    Calcolare i numeri primi di un determinato intervallo dividendolo in tanti thread
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> numeri;
int nThread = 0;

bool isPrimo(int* n) {
    if (*n > 1) {
        for (int i = 2; i < *n; ++i) {
            if ((*n % i) == 0) {
                // se è divisibile
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

struct parametri {
    int posizione;
    int salto;
    int resto;
};

void* funzioneThread(void* args) {
    parametri* argomenti = (parametri*)args;

    int pos = argomenti->posizione;
    int n1 = pos * argomenti->salto;
    int n2 = n1 + argomenti->salto - 1;
    if (argomenti->posizione == nThread) {
        // è l'ultimo thread
        n2 = n2 + 1 + argomenti->resto;
    }
    for (int i = n1; i <= n2; ++i) {
        if (isPrimo(&numeri[i])) {
            cout << endl << " > Numero primo trovato! " << numeri[i];
        }
    }

    return nullptr;
}

int main(int argc, char* const argv[]) {
    int dim = 0;
    
    while(true) {
        cout << endl << "Inserisci dimensione vettore: ";
        cin >> dim;
        if (dim > 0) {
            break;
        }
        cout << endl << " [E] La dimensione deve essere >0!";
    }

    while(true) {
        cout << endl << "Inserisci numero thread: ";
        cin >> nThread;
        if (nThread > 0) {
            break;
        }
        cout << endl << " [E] Il numero deve essere >0!";
    }

    for (int i = 0; i < dim; ++i) {
        int temp = 0;
        cout << endl << " > Inserisci numero " << i+1 << ": ";
        cin >> temp;
        numeri.push_back(temp);
    }

    int sezioni = dim / nThread;
    int resto = 0;
    if ((nThread * sezioni) != dim) {
        resto = dim - (sezioni * nThread);
    }

    vector<parametri> argomenti(sezioni);
    vector<pthread_t> idThread(nThread);

    for (int i = 0; i < sezioni; ++i) {
        // Lancio i thread
        pthread_t pid;
        idThread[i] = pid;
        argomenti[i].posizione = i;
        argomenti[i].salto = sezioni;
        if(i == sezioni-1) {
            argomenti[i].resto = resto;
        } else {
            argomenti[i].resto = 0;
        }
        if (pthread_create(&idThread[i], nullptr, funzioneThread, &argomenti[i]) != 0) {
            cerr << endl << "Errore creazione thread";
        }
    }

    for (int i = 0; i < sezioni; ++i) {
        // Raccolgo i thread
        if (pthread_join(idThread[i], nullptr) != 0) {
            cerr << endl << "Errore join thread";
        }
    }



    return 0;
}