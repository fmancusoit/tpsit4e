#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h>

int globale = 3;

void forkexample() { 
    pid_t p; 
    p = fork();

    if (p < 0) { 
      perror("fork fail"); 
      exit(1); 
    } else if ( p == 0) {      // child process because return value zero
        int globale2 = globale + 5;
        printf("\nHello from Child!\n > Variabile nel child: %i\n", globale2); 
    } else {     // parent process because return value non-zero.
        int globale3 = globale + 2; 
        printf("\nHello from Parent!\n > Variabile nel parent: %i\n\n", globale3); 
    }
        
}

int main() { 
    printf("Variabile globale: %i\n", globale);
    forkexample(); 
    return 0; 
} 