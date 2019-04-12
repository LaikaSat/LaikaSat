/* Libreria dibuja.h */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "lista.h"
#include "functions.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// Funciones contenidas en la libreria
void dibuja(nodo*, int, int, char);
////////////////////////////////////

/*
* Esta funcion recibe un a lista de puntos, su numero de elementos y un entero
* que indica las dimensiones de la matriz (n1xn2) y dibuja el gráfico.
*/
void dibuja(nodo* lista, int n, int n2, char color){
	int m[n][n2]; //matriz
	//Inicializar matriz
  for(int i = 0; i < n; i++) for(int j = 0; j < n2; j++) m[i][j] = 0;
	///////////////////

	//Cargar puntos en la matriz
	int v;
  for(int i = 0; i < sizeLista(lista); i++){
    v = elemento(lista, i);
		if(v>=n){
			m[0][i] = 2;
		}else{
			m[n-v][i] = 1;
		}

  }
	/////////////

	//Dibujar matriz
  system("clear");
	//clear();
	for(int i = 0; i < n+1; i++){
		for(int j = -1; j < n2; j++){
      if (j==-1) {
        printf( ANSI_COLOR_RESET "|" ANSI_COLOR_RESET);
      }else if(i==n){
        printf(ANSI_COLOR_RESET "_" ANSI_COLOR_RESET);
      }else{
        switch (m[i][j]){
					case 0: printf(" "); break;
					case 1: switch(color){
										case 'm': printf(ANSI_COLOR_MAGENTA "o" ANSI_COLOR_MAGENTA); break;
										case 'g': printf(ANSI_COLOR_GREEN "o" ANSI_COLOR_GREEN); break;
										case 'y': printf(ANSI_COLOR_YELLOW "o" ANSI_COLOR_YELLOW); break;
										case 'b': printf(ANSI_COLOR_BLUE "o" ANSI_COLOR_BLUE); break;
										case 'c': printf(ANSI_COLOR_CYAN "o" ANSI_COLOR_CYAN); break;
									} break;
					case 2: printf(ANSI_COLOR_RED "x" ANSI_COLOR_RED); break;
					default: printf(" "); break;
        }
      }
    }
		printf("\n");
	}
	free(m);
	//////////////////
}













void dibujaTemperatura(nodo* lista, int n, int n2, char color){
	system("clear");
	int m[n+1][n2+1]; //matriz
	//Inicializar matriz
  for(int i = 0; i < n+1; i++) for(int j = 0; j < n2+1; j++) m[i][j] = 0;
	///////////////////

	//Cargar puntos en la matriz
	int v;
  for(int i = 0; i < sizeLista(lista); i++){
    v = elemento(lista, i);
		v = ((v+10)/2);
		if(((v+10)/2)>30){
			m[0][i] = 2;
		}else{
			m[n-v][i] = 1;
		}
  }
	/////////////

	//Dibujar matriz
	for(int i = 0; i < n+2; i++){
		for(int j = -3; j < n2; j++){
      if(j==-1){
        printf( ANSI_COLOR_RESET "│" ANSI_COLOR_RESET);
      }else if (j==-3){
				if((((n+10)-i*2)>9)||((((n+10)-i*2)<0)&&(((n+10)-i*2)>-10))) printf(ANSI_COLOR_RESET " %d" ANSI_COLOR_RESET, (n+10)-i*2);
				else if(((n+10)-i*2)==-10) printf(ANSI_COLOR_RESET "%d" ANSI_COLOR_RESET, (n+10)-i*2);
				else if(((n+10)-i*2)==-12) printf("   ");
				else printf(ANSI_COLOR_RESET "  %d" ANSI_COLOR_RESET, (n+10)-i*2);
			}else if((i==n+1)&&(j>0)){
        printf(ANSI_COLOR_RESET "_" ANSI_COLOR_RESET);
      }else if(j>0){
        switch(m[i][j]){
					case 0: printf(" "); break;
					case 1: switch(color){
										case 'm': printf(ANSI_COLOR_MAGENTA "●" ANSI_COLOR_MAGENTA); break;
										case 'g': printf(ANSI_COLOR_GREEN "o" ANSI_COLOR_GREEN); break;
										case 'y': printf(ANSI_COLOR_YELLOW "o" ANSI_COLOR_YELLOW); break;
										case 'b': printf(ANSI_COLOR_BLUE "o" ANSI_COLOR_BLUE); break;
										case 'c': printf(ANSI_COLOR_CYAN "o" ANSI_COLOR_CYAN); break;
									} break;
					case 2: printf(ANSI_COLOR_RED "◌" ANSI_COLOR_RED); break;
					default: printf(" "); break;
        }
      }
    }
		printf("\n");
	}
	//////////////////

}




























void dibujaTempHum(nodo* listaT, nodo* listaH, int n, int n2, char color1, char color2){
	//system("clear");
	printf(" (Cº)\t\t\t\t\t TEMPERATURA\t\t\t\t            (%%)\t\t\t\t\t\t  HUMEDAD\n");
	int m[n+1][n2+1]; //matriz
	int h[n+1][n2+1];
	//Inicializar matriz
  for(int i = 0; i < n+1; i++) for(int j = 0; j < n2+1; j++) m[i][j] = 0;
	for(int i = 0; i < n+1; i++) for(int j = 0; j < n2+1; j++) h[i][j] = 0;
	///////////////////

	//Cargar puntos en la matriz de temperatura
	int v;
  for(int i = 0; i < sizeLista(listaT); i++){
    v = elemento(listaT, i);
		if(v>30){
			m[0][i] = 2;
		}else if(v<-10){
			m[n][i] = 2;
		}else{
			m[n-((v+10)/2)][i] = 1;
		}
  }
	/////////////

	//Cargar puntos en la matriz de humedad
  for(int i = 0; i < sizeLista(listaH); i++){
    v = elemento(listaH, i);
		if(v>100){
			h[0][i] = 2;
		}else if(v<0){
			h[n][i] = 2;
		}else{
			h[n-(v/5)][i] = 1;
		}
  }
	/////////////

	//Dibujar matriz
	for(int i = 0; i < n+2; i++){
		for(int j = -3; j < (n2*2)+3; j++){
			printf( ANSI_COLOR_RESET "" ANSI_COLOR_RESET);
      if((j==-1)||(j==(n2+4))){
        printf( ANSI_COLOR_RESET "│" ANSI_COLOR_RESET);
      }else if(j==-2){
				if((((n+10)-i*2)>9)||((((n+10)-i*2)<0)&&(((n+10)-i*2)>-10))) printf(ANSI_COLOR_RESET " %d" ANSI_COLOR_RESET, (n+10)-i*2);
				else if(((n+10)-i*2)==-10) printf(ANSI_COLOR_RESET "%d" ANSI_COLOR_RESET, (n+10)-i*2);
				else if(((n+10)-i*2)==-12) printf("%d", (n+10)-i*2);
				else printf(ANSI_COLOR_RESET "  %d" ANSI_COLOR_RESET, (n+10)-i*2);
			}else if(j==n2+3){
				if((100-(i*5))==-5) printf("   ");
				else if((100-(i*5))<10) printf("   %d", 100-(i*5));
				else if((100-(i*5))==100) printf(" %d", 100-(i*5));
				else printf("  %d", 100-(i*5));
			}else if((i==n+1)&&(j>=0)&&(j<n2)){
        printf(ANSI_COLOR_RESET "_" ANSI_COLOR_RESET);
      }else if((i==n+1)&&(j>n2+4)&&(j<(n2*2)+3)){
        printf(ANSI_COLOR_RESET "_" ANSI_COLOR_RESET);
      }else if((j>0)&&(j<n2+1)){
        switch(m[i][j]){
					case 0: printf(" "); break;
					case 1: switch(color1){
										case 'm': printf(ANSI_COLOR_MAGENTA "●" ANSI_COLOR_MAGENTA); break;
										case 'g': printf(ANSI_COLOR_GREEN "●" ANSI_COLOR_GREEN); break;
										case 'y': printf(ANSI_COLOR_YELLOW "●" ANSI_COLOR_YELLOW); break;
										case 'b': printf(ANSI_COLOR_BLUE "●" ANSI_COLOR_BLUE); break;
										case 'c': printf(ANSI_COLOR_CYAN "●" ANSI_COLOR_CYAN); break;
									} break;
					case 2: printf(ANSI_COLOR_RED "◌" ANSI_COLOR_RED); break;
					default: printf(" "); break;
        }
      }else if(j>n2+5){
        switch(h[i][j-(n2+5)]){
					case 0: printf(" "); break;
					case 1: switch(color2){
										case 'm': printf(ANSI_COLOR_MAGENTA "●" ANSI_COLOR_MAGENTA); break;
										case 'g': printf(ANSI_COLOR_GREEN "●" ANSI_COLOR_GREEN); break;
										case 'y': printf(ANSI_COLOR_YELLOW "●" ANSI_COLOR_YELLOW); break;
										case 'b': printf(ANSI_COLOR_BLUE "●" ANSI_COLOR_BLUE); break;
										case 'c': printf(ANSI_COLOR_CYAN "●" ANSI_COLOR_CYAN); break;
									} break;
					case 2: printf(ANSI_COLOR_RED "◌" ANSI_COLOR_RED); break;
					default: printf(" "); break;
        }
      }
    }
		printf(ANSI_COLOR_RESET "\n" ANSI_COLOR_RESET);
	}
	//////////////////

}


























//Para dibujar la presion: 70-110
//Para dibujar la altura: 0-2000


void dibujaAltPres(nodo* listaA, nodo* listaP, int n, int n2, char color1, char color2){
	//system("clear");
	printf(" (m)\t\t\t\t\t     ALTURA\t\t\t\t\t    (kPa)\t\t\t\t\t   PRESION\n");
	int m[n+1][n2+1]; //matriz
	int h[n+1][n2+1];
	//Inicializar matriz
  for(int i = 0; i < n+1; i++) for(int j = 0; j < n2+1; j++) m[i][j] = 0;
	for(int i = 0; i < n+1; i++) for(int j = 0; j < n2+1; j++) h[i][j] = 0;
	///////////////////

	//Cargar puntos en la matriz de altura
	int v;
  for(int i = 0; i < sizeLista(listaA); i++){
    v = elemento(listaA, i);
		v = v/100;
		if(v>n){
			m[0][i] = 2;
		}else if(v<0){
			m[n][i] = 2;
		}else{
			m[n-v][i] = 1;
		}
  }
	/////////////

	//Cargar puntos en la matriz de presion
  for(int i = 0; i < sizeLista(listaP); i++){
    v = elemento(listaP, i);
		v = ((v/1000)-70)/2; //entre 70 y 110
		if(v>n){
			h[0][i] = 2;
		}else if(v<0){
			h[n][i] = 2;
		}else{
			h[n-v][i] = 1;
		}
  }
	/////////////

	//Dibujar matriz
	for(int i = 0; i < n+2; i++){
		for(int j = -3; j < (n2*2)+3; j++){
			printf( ANSI_COLOR_RESET "" ANSI_COLOR_RESET);
      if((j==-1)||(j==(n2+4))){
        printf( ANSI_COLOR_RESET "│" ANSI_COLOR_RESET);
      }else if(j==-3){ //indice de altura
				if(((n-i)*100)==0) printf(ANSI_COLOR_RESET "   %d" ANSI_COLOR_RESET, (n-i)*100);
				else if(((n-i)*100)==-100) printf(ANSI_COLOR_RESET "%d" ANSI_COLOR_RESET, (n-i)*100);
				else if(((n-i)*100)>=1000) printf(ANSI_COLOR_RESET "%d" ANSI_COLOR_RESET, (n-i)*100);
				else if(((n-i)*100)<1000) printf(ANSI_COLOR_RESET " %d" ANSI_COLOR_RESET, (n-i)*100);
			}else if(j==n2+2){ //indice de presion
				if((70+(n-i)*2)>98) printf(ANSI_COLOR_RESET " %d" ANSI_COLOR_RESET, 70+(n-i)*2);
				else if(((70+(n-i)*2)>68) && ((70+(n-i)*2)<=98)) printf(ANSI_COLOR_RESET "  %d" ANSI_COLOR_RESET, 70+(n-i)*2);
				else printf(ANSI_COLOR_RESET " %d" ANSI_COLOR_RESET, 70+(n-i)*2);
			}else if((i==n+1)&&(j>=0)&&(j<n2)){
        printf(ANSI_COLOR_RESET "_" ANSI_COLOR_RESET);
      }else if((i==n+1)&&(j>n2+4)&&(j<(n2*2)+2)){
        printf(ANSI_COLOR_RESET "_" ANSI_COLOR_RESET);
      }else if((j>0)&&(j<n2+1)){
        switch(m[i][j]){
					case 0: printf(" "); break;
					case 1: switch(color1){
										case 'm': printf(ANSI_COLOR_MAGENTA "●" ANSI_COLOR_MAGENTA); break;
										case 'g': printf(ANSI_COLOR_GREEN "●" ANSI_COLOR_GREEN); break;
										case 'y': printf(ANSI_COLOR_YELLOW "●" ANSI_COLOR_YELLOW); break;
										case 'b': printf(ANSI_COLOR_BLUE "●" ANSI_COLOR_BLUE); break;
										case 'c': printf(ANSI_COLOR_CYAN "●" ANSI_COLOR_CYAN); break;
									} break;
					case 2: printf(ANSI_COLOR_RED "◌" ANSI_COLOR_RED); break;
					default: printf(" "); break;
        }
      }else if(j>n2+5){
        switch(h[i][j-(n2+5)]){
					case 0: printf(" "); break;
					case 1: switch(color2){
										case 'm': printf(ANSI_COLOR_MAGENTA "●" ANSI_COLOR_MAGENTA); break;
										case 'g': printf(ANSI_COLOR_GREEN "●" ANSI_COLOR_GREEN); break;
										case 'y': printf(ANSI_COLOR_YELLOW "●" ANSI_COLOR_YELLOW); break;
										case 'b': printf(ANSI_COLOR_BLUE "●" ANSI_COLOR_BLUE); break;
										case 'c': printf(ANSI_COLOR_CYAN "●" ANSI_COLOR_CYAN); break;
									} break;
					case 2: printf(ANSI_COLOR_RED "◌" ANSI_COLOR_RED); break;
					default: printf(" "); break;
        }
      }
    }
		printf(ANSI_COLOR_RESET "\n" ANSI_COLOR_RESET);
	}
	//////////////////
}

void dibujaGraficos(nodo* listaT, nodo* listaH, nodo* listaA, nodo* listaP, int n, int n2, char color1, char color2, char color3, char color4){
	system("clear");
	dibujaTempHum(listaT, listaH, n, n2, 'm', 'b');
	printf("\n");
	dibujaAltPres(listaA, listaP, n, n2, 'c', 'y');
	//printf("\n");
}

void printNivel(float num){
	num = (int)num;
	for(size_t i = 0; i < num; i++) printf("█");
}

void dibujaFeed(datos data){
	printf("Temperatura |"); printNivel(data.t); printf(" %d Cº \n", (int)data.t);
	printf("Humedad     |"); printNivel(data.h); printf(" %d %% \n", (int)data.h);
	printf("Altura      |"); printNivel(data.a/100); printf(" %d m \n", (int)data.a);
	printf("Presion     |"); printNivel(data.p/10000); printf(" %d Pa \n", (int)data.p);
	printf("Velocidad   |"); printNivel(data.v/2); printf(" %d m/s  \n", (int)data.v);
	printf("GPS:\t X = %f;\t Y = %f;\n", data.x, data.y);
}

