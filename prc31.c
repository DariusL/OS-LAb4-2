#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>
#include <stdlib.h>

static int gautas_signalas = 0;

void funkcija () {
	system("who");
	signal(getppid(), SIGUSR2);
	gautas_signalas = 1;
}



int main( void ) {
	pid_t  pid;

	signal(SIGUSR1, funkcija);

	pid = fork();
	if ( pid == -1 ) {
		perror("Klaida! Nepavyko sukurti vaiko.");
		exit   (1);
	}
	if ( pid != 0 ) {
		printf("TEVAS: mano pid = %ld\n", getpid());
		printf("TEVAS: mano vaiko pid = %ld\n", pid);
		system("ps");
		sleep( 3 );
		kill( pid, SIGUSR1 );
		printf( "TEVAS: signala pasiunciau.\n" );
		wait( NULL );
		printf( "TEVAS: baigiu darba.\n" );
		return 0;
	} else {
		sleep (1);
		printf( "VAIKAS: mano PID = %ld\n", getpid() );
		while(1)
			if ( gautas_signalas == 1 ) {
				printf( "VAIKAS: signala gavau!\n" );
				sleep( 1 );
				printf( "VAIKAS: baigiu darba.\n" );
				return 0;
			}
	}
}
