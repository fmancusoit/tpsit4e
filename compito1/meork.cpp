#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

int main (int argc, char const* argv[]) {

    if ( fork() != 1 ) { // 1
        // 2 volte
        if ( fork() == 0 ) { // 1
            fork(); // 1
        }
        
    }

    cout<<"\n\nmiao"; // 1
    return 0;
}
