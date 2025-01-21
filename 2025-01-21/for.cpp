#include <bits/stdc++.h>
using namespace std;

void* stampaThread(void* args) {
    cout << "Quel patato di totò" << endl;
    return nullptr;
}

int main(int args, char* const argv[]) {
    int nthread = 0;
    cout << "Inserisci numero thread: ";
    cin >> nthread;
    vector<pthread_t> tid(nthread);

    for (int i = 0; i < nthread; i++) { // Creo tutti i thread
        pthread_t pid;
        tid[i] = pid;
        if(pthread_create(&tid[i], nullptr, stampaThread, nullptr) != 0) {
            // Crea e gestisce l'errore del thread
            cerr << endl << "Errore nella creazione del thread" << endl;
            return 1;
        }
    }

    cout << endl;

    for (int i = 0; i < nthread; i++) { // Join di tutti i thread
        cout << tid[i] << endl;
    }

    for (int i = 0; i < nthread; i++) { // Join di tutti i thread
        if(pthread_join(tid[i], nullptr) != 0) {
            // Join del thread e gestione dell'errore
            cerr << endl << "Errore nel Join del thread" << endl;
            return 1;
        }
    }

    return 0;
}