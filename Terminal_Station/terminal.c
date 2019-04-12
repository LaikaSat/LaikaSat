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
#include "graphics.h"

#define N 20
#define M 86

void fin(int);

int pid_lector, idCola;

int main(int argc, char const *argv[]) {

	system("clear"); //Limpiar terminal
	printf("\n********************************\n");
	printf("*        TERMINAL CANSAT       *\n");
	printf("*          Version 1.0         *\n");
	printf("********************************\n\n");

  key_t key = ftok("./", 23);
	if(key == (key_t) -1) exit(-1);

  idCola = msgget(key, 0666 | IPC_CREAT); //Crea la cola
	if(idCola==(-1)){ printf("[Terminal] Error al crear cola.\n"); exit(-1); }

  //Creacion de lector
  pid_lector = fork();
	if(pid_lector == (-1)) exit (-1);
	if(!pid_lector) execlp("./lector", "./lector", NULL);	//Ejecuta: p
	////////////////////////

  signal(SIGINT, &fin);

	nodo* listaP = creaLista();
	nodo* listaT = creaLista();
  nodo* listaH = creaLista();
  nodo* listaA = creaLista();
	nodo* listaDummie = creaLista(); //Necesario por algo

  datos data; data.t = data.h = data.a = data.p = data.v = 0;
	char link[70]; //Link maps

	//sleep(4);
	system("clear");
	dibujaGraficos(listaT, listaH, listaA, listaP, N, M, 'm', 'b', 'c', 'y');
	dibujaFeed(data);
  while(1){
    msgrcv(idCola, &data, sizeof(data), 0, 0); //Desencolar

		writeDataBase(data); //Escribe los datos en la base de datos

		coordToMaps(link, data.x, data.y); //Crear link a maps
		mapLinkToFile(link); //Escribir link de maps en archivo

		data.t = kelvinToCelsius(data.t); //Pasar kelvins a celsius

    insertar2(&listaT, (int)data.t, M);
    insertar2(&listaH, (int)data.h, M);
    insertar2(&listaA, (int)data.a, M);
    insertar2(&listaP, (int)data.p, M);

		system("clear");
    dibujaGraficos(listaT, listaH, listaA, listaP, N, M, 'm', 'b', 'c', 'y');
		printf("\n");
    dibujaFeed(data);
		
  }

  return 0;
}

//Señal para finalizar (ctrl+c)
void fin(int n){
  kill(SIGUSR1, pid_lector); //Finalizar lector
	msgctl(idCola, IPC_RMID, 0); //Eliminar cola
	exit(1);
}
