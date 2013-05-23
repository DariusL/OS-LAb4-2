#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>
#include <stdlib.h>

static int gautas_signalas1 = 0;
static int gautas_signalas2 = 0;

void funkcija1() {
	gautas_signalas1 = 1;
}

void funkcija2(){
	gautas_signalas2 = 1;
}



int main( void ) {
	pid_t  pid;

	signal(SIGUSR1, funkcija1);
	signal(SIGUSR2, funkcija2);

	pid = fork();
	if ( pid == -1 ) {
		perror("Klaida! Nepavyko sukurti vaiko.");
		exit   (1);
	}
	if ( pid != 0 ) {
		printf("TEVAS: mano pid = %ld\n", getpid());
		printf("TEVAS: mano vaiko pid = %ld\n", pid);
		sleep( 3 );
		kill( pid, SIGUSR1 );
		printf( "TEVAS: signala pasiunciau.\n" );
		while(gautas_signalas2 == 0);
		kill(pid, SIGKILL);
		sleep(5);
		printf( "TEVAS: baigiu darba.\n" );
		return 0;
	} else {
		printf( "VAIKAS: mano PID = %ld\n", getpid() );
		while(gautas_signalas1 == 0);
		system("who");
		kill(getppid(), SIGUSR2);
		while(1);
		return 0;
	}
}
