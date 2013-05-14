#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	const char Kl_pran[] = "fork() klaida, nepavyko sukurti naujo proceso!";
	pid_t pid;

	if(argc < 2){
		printf("reikia vieno argumento\n");
		return 1;
	}
	printf("Paleidziame pirmaji procesa ...\n");
	pid = fork();
	if ( pid < 0 ) {
		perror( Kl_pran );
		exit( 1 );
	}
	if ( pid == 0 ) {
		execl("/home/darlap1/lab2/proc61b.sh","procesas", argv[1], (const char*)0 );
		perror("pirmo execl() klaida");
		exit( 3 );
	}
	else {
		wait(NULL);
		printf("Pirmasis procesas baige darba.\n");

		printf("Tevas baigia darba\n");
		return 0;	
	}
}
