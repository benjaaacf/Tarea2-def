#ifndef MAPA_H
#define MAPA_H
#define MAX 100

typedef struct {
  char nombre[MAX];
  char tipo[MAX];
  char direccion[MAX];
  char horario[MAX];
  char descripcion[MAX];
} PuntoInteres;

typedef struct {
  char pasaporte[MAX];
  char nombre[MAX];
  char pais[MAX];
  struct NodoLista *lugaresFavoritos;
} Turista;

typedef struct NodoLista {
  char nombre[MAX];
  struct NodoLista *siguiente;
} NodoLista;

typedef struct NodoHash {
  char clave[MAX];
  void *valor;
  struct NodoHash *siguiente;
} NodoHash;

typedef struct {
  NodoHash **tabla;
  int capacidad;
} Mapa;