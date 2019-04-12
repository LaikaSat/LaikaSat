/* Libreria lista.h */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

//Estructura nodo que contiene un punto y un puntero a otro nodo
typedef struct nodo{
  float valor;
  struct nodo *sig;
}nodo;

//Funciones contenidas en la libreria
nodo* creaLista();
int esVacia(nodo*);
void insertar(nodo**, float);
int sizeLista(nodo*);
void printLista(nodo*);
float elemento(nodo*, int);

/*
* Devuelve un puntero a una lista de puntos vacia.
*/
nodo* creaLista(){
  nodo* n = NULL;
  return n;
}

/*
* Recibe la cabecera de una lista y si es vacia devuelve 1, si no 0.
*/
int esVacia(nodo* cabecera){
  if(cabecera==NULL) return 1; else return 0;
}

/*
* Recibe la cabecera de una lista de puntos y un punto, y lo inserta en la lista.
*/
void insertar(nodo** cabecera, float v){
  if(esVacia(*cabecera)){ //Si es vacia
    nodo* nuevo = (nodo*)malloc(sizeof(nodo)); //Reservar memoria
    nuevo->valor = v; //Asignar el punto
    nuevo->sig = NULL; //Apuntar a null
    *cabecera = nuevo; //La cabecera apunta al punto
  }else{ //Si no es vacia
    nodo* actual = *cabecera; //El nodo auxiliar actual apunta al primero
    while(actual->sig!=NULL) actual = actual->sig; //Recorremos la lista hasta el final
    actual->sig = (nodo*)malloc(sizeof(nodo));
    actual->sig->valor = v; //Insertamos el punto
    actual->sig->sig = NULL;
  }
}

/*
* Devuelve el tamaño de una lista.
*/
int sizeLista(nodo* cabecera){
  if(esVacia(cabecera)) {
    return 0;
  }else{
    int i = 0;
    nodo* actual = cabecera;
    while(actual->sig!=NULL){ //Recorremos la lista hasta el final
      actual = actual->sig;
      i++;
    }
    i++;
    return i;
  }
}

/*
* Imprime la lista recibida.
*/
void printLista(nodo* cabecera) {
    nodo* actual = cabecera;
    while(actual!=NULL){
      printf("%f ", actual->valor);
      actual = actual->sig;
    }
    printf("\n");
}

/*
* Recibe una lista y un indice y devuelve el punto de la lista en la posicion
* del indice. Si no existe devuelve un punto con todos sus valores a -1.
*/
float elemento(nodo* cabecera, int posicion){
  nodo* actual = cabecera;
  int i = 0;
  float v;
  while((i!=posicion)&&(actual!=NULL)){
    actual = actual->sig;
    i++;
  }
  if(actual==NULL){
    v = -2000;
  }else{
    v = actual->valor;
  }
  return v;
}

/*
* Elimina el primer elemento
*/
void eliminaPrimero(nodo** cabecera){
  nodo* aux = *cabecera;
  *cabecera = aux->sig;
  free(aux);
}

/*
* Inserta un elemento en la lista. Si al insertarlo el tamaño se excede, se borra
* el primer elemento.
*/
void insertar2(nodo** cabecera, float v, int tamañoMax){
  int tamañoActual = sizeLista(*cabecera);
  if(tamañoActual+1>tamañoMax) eliminaPrimero(cabecera); //Si se excede el tamaño
  insertar(cabecera, v);
}
