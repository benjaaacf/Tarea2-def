#ifndef MAPA_H
#define MAPA_H
#define MAX 100


// Definicion de structs a utilizar
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

Mapa *crearMapa(int capacidad);
void destruirMapa(Mapa *mapa);

void registrarPto(Mapa *mapa, char *nombre, PuntoInteres *puntoInteres);
PuntoInteres *buscarPto(Mapa *mapa, char *nombre);
void eliminarPto(Mapa *mapa, char *nombre);

void registrarTurista(Mapa *mapa, char *pasaporte, Turista *turista);
Turista *buscarTurista(Mapa *mapa, char *pasaporte);

void agregarFavorito(Turista *turista, char *nombreLugar);
NodoLista *buscarFav(Turista *turista);

void mostrarPorPais(Mapa *mapa, char *pais);
void mostrarPtsTipo(Mapa *mapa, char *tipo);

void importar(Mapa *mapa, char *archivoPuntos, char *archivoTuristas);
void exportar(Mapa *mapa, char *archivoPuntos, char *archivoTuristas);

#endif