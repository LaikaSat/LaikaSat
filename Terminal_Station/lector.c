#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>

#define ESCRITURA 1
#define LECTURA 0

typedef struct datos{
	float t;
	float h;
	float p;
	float a;
	float x;
	float y;
	float v;
}datos;

typedef int tuberia[2]; //Tipo tuberia

void fin(int); //Manejador de señal SIGUSR1

pid_t pid; //PID pstty

int main(int argc, char const *argv[]) {

	tuberia	tub;
	pipe(tub); //Lectura bloqueante.

	key_t key = ftok("./", 23);
	if(key == (key_t) -1) exit(-1);

  	int idCola = msgget(key, 0666); //Crea la cola
	if(idCola==(-1)){ printf("[Lector] Error al obtener cola.\n"); exit(-1); }

  	pid = fork();
	if(pid==0){ //Hijo
		close(tub[LECTURA]); //Cierra la salida de la tuberia
		dup2(tub[ESCRITURA], STDOUT_FILENO); //Redirecciona la salida estandar a la entrada de la tuberia
		execlp("./pstty", "./pstty", NULL);	//Ejecuta: pstty
	}else{
		signal(SIGUSR1, &fin); //Declaracion de la señal para finalizar
		close(tub[ESCRITURA]); //Cierra la entrada de la tuberia
		dup2(tub[LECTURA], STDIN_FILENO); //Redirecciona la entrada estandar a la salida de la tuberia

		char str1[10], str2[10];
		datos data;

		printf("Iniciando terminal...\n");
		//sleep(4);
		while(1){
			fscanf(stdin,"%s %f %f %f %f %f %f %f %s\n", str1, &data.t, &data.h, &data.p, &data.a, &data.x, &data.y, &data.v, str2);
			if( (!strcmp(str1, "DATA")) && (!strcmp(str2, "FDATA")) ){
				/*printf("---------------------------\n");
				printf("Temperatura: %f\n", data.t);
				printf("Humedad: %f\n", data.h);
				printf("Presion: %f\n", data.p);
				printf("Altura: %f\n", data.a);
				printf("CoordX: %f\n", data.x);
				printf("CoordY: %f\n", data.y);
				printf("Velocidad: %f\n", data.v);
				printf("---------------------------\n");*/
				msgsnd(idCola, &data, sizeof(data), IPC_NOWAIT); //Encolar
			}
		}
	}

  return 0;
}

void fin(int n){ //Manejador señal SIGUSR1
	kill(SIGINT, pid); //Finalizar lector
	exit(1);
}
