#ifndef MAPA_H
#define MAPA_H

#define MAX_CHAR_LENGTH 100

typedef struct {
  char nombre[MAX_CHAR_LENGTH];
  char tipo[MAX_CHAR_LENGTH];
  char direccion[MAX_CHAR_LENGTH];
  char horario[MAX_CHAR_LENGTH];
  char descripcion[MAX_CHAR_LENGTH];
} PuntoInteres;

typedef struct {
  char pasaporte[MAX_CHAR_LENGTH];
  char nombre[MAX_CHAR_LENGTH];
  char pais[MAX_CHAR_LENGTH];
  struct NodoLista *lugaresFavoritos;
} Turista;

typedef struct NodoLista {
  char nombre[MAX_CHAR_LENGTH];
  struct NodoLista *siguiente;
} NodoLista;

typedef struct NodoHash {
  char clave[MAX_CHAR_LENGTH];
  void *valor;
  struct NodoHash *siguiente;
} NodoHash;

typedef struct {
  NodoHash **tabla;
  int capacidad;
} Mapa;