#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct datos{
	float t;
	float h;
  float p;
	float a;
	float x;
	float y;
  float v;
}datos;

void coordToMaps(char*, float, float);
void mapLinkToFile(char*);
void writeDataBase(datos);

/*
* Recibe dos coordenadas y devuelve su link a maps.com en la variable string.
*/
void coordToMaps(char* string, float x, float y){
  snprintf(string, 70, "https://www.google.com/maps/search/%f,%f/", x, y);
}

/*
* Escribe el link de maps en un archivo de texto.
*/
void mapLinkToFile(char* link){
  FILE *f;
  f = fopen("mapsLink.txt", "w");
  fputs(link, f);
  fclose(f);
}

/*
* Escribe los datos en la base de datos.
*/
void writeDataBase(datos data){
  FILE *f;
  f = fopen("database.txt", "a");
  fprintf(f, "%f\t%f\t%f\t%f\t%f\t%f\t%f\n", data.t, data.h, data.a, data.p, data.x, data.y, data.v);
  fclose(f);
}

/*
* Transforma los kelvin a celsius.
*/
float kelvinToCelsius(float kelvin){
	return (kelvin-273.15);
}
