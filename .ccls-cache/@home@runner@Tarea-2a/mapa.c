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
  strncpy(nuevoNodo->clave, nombre, MAX);
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
  strncpy(nuevoNodo->clave, pasaporte, MAX);
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

Turista *buscarTurista(Mapa *mapa, char *pasaporte) {
  unsigned int indice = hash(pasaporte, mapa->capacidad);
  NodoHash *actual = mapa->tabla[indice];

  while (actual != NULL) {
    if (strcmp(actual->clave, pasaporte) == 0) {
      return (Turista *)actual->valor;
    }
    actual = actual->siguiente;
  }

  return NULL;
}

void agregarFavorito(Turista *turista, char *nombreLugar) {
  NodoLista *nuevoNodo = (NodoLista *)malloc(sizeof(NodoLista));
  strncpy(nuevoNodo->nombre, nombreLugar, MAX);
  nuevoNodo->siguiente = turista->lugaresFavoritos;
  turista->lugaresFavoritos = nuevoNodo;
}

NodoLista *buscarFav(Turista *turista) { return turista->lugaresFavoritos; }

void mostrarPorPais(Mapa *mapa, char *pais) {
  for (int i = 0; i < mapa->capacidad; i++) {
    NodoHash *actual = mapa->tabla[i];
    while (actual != NULL) {
      Turista *turista = (Turista *)actual->valor;
      if (strcmp(turista->pais, pais) == 0) {
        printf("Pasaporte: %s, Nombre: %s\n", turista->pasaporte,
               turista->nombre);
        NodoLista *lugaresFavoritos = buscarFav(turista);
        printf("Lugares Favoritos:\n");
        while (lugaresFavoritos != NULL) {
          printf("- %s\n", lugaresFavoritos->nombre);
          lugaresFavoritos = lugaresFavoritos->siguiente;
        }
      }
      actual = actual->siguiente;
    }
  }
}

void mostrarPtsTipo(Mapa *mapa, char *tipo) {
  for (int i = 0; i < mapa->capacidad; i++) {
    NodoHash *actual = mapa->tabla[i];
    while (actual != NULL) {
      PuntoInteres *puntoInteres = (PuntoInteres *)actual->valor;
      if (strcmp(puntoInteres->tipo, tipo) == 0) {
        printf("Nombre: %s, Tipo: %s\n", puntoInteres->nombre,
               puntoInteres->tipo);
        printf("Dirección: %s\n", puntoInteres->direccion);
        printf("Horario: %s\n", puntoInteres->horario);
        printf("Descripción: %s\n", puntoInteres->descripcion);
      }
      actual = actual->siguiente;
    }
  }
}

void importar(Mapa *mapa, char *archivoPuntos, char *archivoTuristas) {
  FILE *filePuntos = fopen(archivoPuntos, "r");
  if (!filePuntos) {
    printf("Error al abrir el archivo de puntos de interés.\n");
    return;
  }

  FILE *fileTuristas = fopen(archivoTuristas, "r");
  if (!fileTuristas) {
    printf("Error al abrir el archivo de turistas.\n");
    fclose(filePuntos);
    return;
  }

  char linea[MAX * 5]; // Suponemos un formato de línea adecuado
  while (fgets(linea, sizeof(linea), filePuntos) != NULL) {
    char *nombre = strtok(linea, ",");
    char *tipo = strtok(NULL, ",");
    char *direccion = strtok(NULL, ",");
    char *horario = strtok(NULL, ",");
    char *descripcion = strtok(NULL, "\n");

    PuntoInteres *puntoInteres = (PuntoInteres *)malloc(sizeof(PuntoInteres));
    strncpy(puntoInteres->nombre, nombre, MAX);
    strncpy(puntoInteres->tipo, tipo, MAX);
    strncpy(puntoInteres->direccion, direccion, MAX);
    strncpy(puntoInteres->horario, horario, MAX);
    strncpy(puntoInteres->descripcion, descripcion, MAX);

    registrarPto(mapa, puntoInteres->nombre, puntoInteres);
  }

  while (fgets(linea, sizeof(linea), fileTuristas) != NULL) {
    char *pasaporte = strtok(linea, ",");
    char *nombre = strtok(NULL, ",");
    char *pais = strtok(NULL, "\n");

    Turista *turista = (Turista *)malloc(sizeof(Turista));
    strncpy(turista->pasaporte, pasaporte, MAX);
    strncpy(turista->nombre, nombre, MAX);
    strncpy(turista->pais, pais, MAX);
    turista->lugaresFavoritos = NULL;

    registrarTurista(mapa, turista->pasaporte, turista);
  }

  fclose(filePuntos);
  fclose(fileTuristas);
}

void exportar(Mapa *mapa, char *archivoPuntos, char *archivoTuristas) {
  FILE *filePuntos = fopen(archivoPuntos, "w");
  if (!filePuntos) {
    printf("Error al abrir el archivo de puntos de interés para escribir.\n");
    return;
  }

  FILE *fileTuristas = fopen(archivoTuristas, "w");
  if (!fileTuristas) {
    printf("Error al abrir el archivo de turistas para escribir.\n");
    fclose(filePuntos);
    return;
  }

  for (int i = 0; i < mapa->capacidad; i++) {
    NodoHash *actual = mapa->tabla[i];
    while (actual != NULL) {
      if (actual->valor != NULL) {
        if (strcmp(actual->clave, actual->valor) == 0) {
          
          PuntoInteres *puntoInteres = (PuntoInteres *)actual->valor;
          fprintf(filePuntos, "%s,%s,%s,%s,%s\n", puntoInteres->nombre,
                  puntoInteres->tipo, puntoInteres->direccion,
                  puntoInteres->horario, puntoInteres->descripcion);
        } else {
          
          Turista *turista = (Turista *)actual->valor;
          fprintf(fileTuristas, "%s,%s,%s\n", turista->pasaporte,
                  turista->nombre, turista->pais);

          NodoLista *lugaresFavoritos = buscarFav(turista);
          while (lugaresFavoritos != NULL) {
            fprintf(fileTuristas, "%s,%s\n", turista->pasaporte,
                    lugaresFavoritos->nombre);
            lugaresFavoritos = lugaresFavoritos->siguiente;
          }
        }
      }
      actual = actual->siguiente;
    }
  }

  fclose(filePuntos);
  fclose(fileTuristas);
}