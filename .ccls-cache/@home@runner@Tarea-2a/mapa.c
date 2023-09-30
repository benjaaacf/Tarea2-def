#include "mapa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 100

unsigned int hash(char *clave, int capacidad) {
  unsigned int hash = 0;
  for (int i = 0; clave[i] != '\0'; i++) {
    hash += clave[i];
  }
  return hash % capacidad;
}

Mapa *crearMapa(int capacidad) {
  Mapa *mapa = (Mapa *)malloc(sizeof(Mapa));
  mapa->capacidad = capacidad;
  mapa->tabla = (NodoHash **)malloc(capacidad * sizeof(NodoHash *));
  for (int i = 0; i < capacidad; i++) {
    mapa->tabla[i] = NULL;
  }
  return mapa;
}

void destruirMapa(Mapa *mapa) {
  for (int i = 0; i < mapa->capacidad; i++) {
    NodoHash *actual = mapa->tabla[i];
    while (actual != NULL) {
      NodoHash *siguiente = actual->siguiente;
      free(actual->valor);
      free(actual);
      actual = siguiente;
    }
  }
  free(mapa->tabla);
  free(mapa);
}

void registrarPto(Mapa *mapa, char *nombre, PuntoInteres *puntoInteres) {
  unsigned int indice = hash(nombre, mapa->capacidad);

  NodoHash *nuevoNodo = (NodoHash *)malloc(sizeof(NodoHash));
  strncpy(nuevoNodo->clave, nombre, MAX_CHAR_LENGTH);
  nuevoNodo->valor = puntoInteres;
  nuevoNodo->siguiente = NULL;

  if (mapa->tabla[indice] == NULL) {
    mapa->tabla[indice] = nuevoNodo;
  } else {
    NodoHash *actual = mapa->tabla[indice];
    while (actual->siguiente != NULL) {
      actual = actual->siguiente;
    }
    actual->siguiente = nuevoNodo;
  }
}

PuntoInteres *buscarPto(Mapa *mapa, char *nombre) {
  unsigned int indice = hash(nombre, mapa->capacidad);
  NodoHash *actual = mapa->tabla[indice];

  while (actual != NULL) {
    if (strcmp(actual->clave, nombre) == 0) {
      return (PuntoInteres *)actual->valor;
    }
    actual = actual->siguiente;
  }

  return NULL;
}

void eliminarPto(Mapa *mapa, char *nombre) {
  unsigned int indice = hash(nombre, mapa->capacidad);
  NodoHash *actual = mapa->tabla[indice];
  NodoHash *anterior = NULL;

  while (actual != NULL) {
    if (strcmp(actual->clave, nombre) == 0) {
      if (anterior == NULL) {
        mapa->tabla[indice] = actual->siguiente;
      } else {
        anterior->siguiente = actual->siguiente;
      }
      free(actual->valor);
      free(actual);
      return;
    }
    anterior = actual;
    actual = actual->siguiente;
  }
}

void registrarTurista(Mapa *mapa, char *pasaporte, Turista *turista) {
  unsigned int indice = hash(pasaporte, mapa->capacidad);

  NodoHash *nuevoNodo = (NodoHash *)malloc(sizeof(NodoHash));
  strncpy(nuevoNodo->clave, pasaporte, MAX_CHAR_LENGTH);
  nuevoNodo->valor = turista;
  nuevoNodo->siguiente = NULL;

  if (mapa->tabla[indice] == NULL) {
    mapa->tabla[indice] = nuevoNodo;
  } else {
    NodoHash *actual = mapa->tabla[indice];
    while (actual->siguiente != NULL) {
      actual = actual->siguiente;
    }
    actual->siguiente = nuevoNodo;
  }
}
