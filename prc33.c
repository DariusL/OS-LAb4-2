#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main( void ) {
    const char Kl_pran[] = "fork() klaida, nepavyko sukurti naujo proceso!";
    pid_t pid;

    printf("Paleidziame pirmaji procesa ...\n");
    pid = fork();
    if ( pid < 0 ) {
        perror( Kl_pran );
	exit( 1 );
    }
    if ( pid == 0 ) {
        execl("/home/darlap1/lab2/proc3b.sh", "Pirmas procesas", "vienas", "du", (const char*)0 );
        perror("pirmo execl() klaida");
        exit( 3 );
    }
    else {
        wait(NULL);
        printf("Pirmasis procesas baige darba.\n");

        printf("Paleidziame antraji procesa ...\n");
        pid = fork ();
        if ( pid < 0 ) {
            perror( Kl_pran );
	    exit( 2 );
	}
        if ( pid == 0 ) {
            execl("/home/darlap1/lab2/proc3c.sh", "trys", "keturi", (const char*)0 );
            perror("antro execl() klaida");
            exit( 3 );
	}
        else {
            wait(NULL);
            printf("Ir antras baigesi.\n");
            return 0;
        }
    }
}
