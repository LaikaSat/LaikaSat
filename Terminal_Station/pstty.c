#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void term(int);

int main(int argc, char const *argv[]) {

  pid_t pid1 = fork();
	if(pid1==0){ execlp("stty", "stty", "-f", "/dev/cu.usbmodem14201", "9600", NULL); }

  signal(SIGINT, &term);

	execlp("cat", "cat", "/dev/cu.usbmodem14201", NULL);	//Ejecuta

  return 0;
}

void term(int x){ exit(1); }
