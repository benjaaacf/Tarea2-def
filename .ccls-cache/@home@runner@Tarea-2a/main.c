#include "mapa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

void limpiarBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}


//Funcion para mostrar el menu principal

void mostrarMenu() {
  printf("\n==============================================================\n");
  printf("\n                       Registro Turistico\n");
  printf(
      "\n==============================================================\n\n");
  printf("1. Registrar punto de interes\n");
  printf("2. Mostrar datos de punto de interés\n");
  printf("3. Eliminar punto de interes\n");
  printf("4. Registrar turista\n");
  printf("5. Agregar lugar favorito a turista\n");
  printf("6. Mostrar turistas por pais\n");
  printf("7. Mostrar todos los puntos de interes de un tipo\n");
  printf("8. Importar puntos de interes y turistas\n");
  printf("9. Exportar puntos de interes y turistas\n");
  printf("0. Finalizar Registro\n\n");
}

int main() {
  Mapa *mapa = crearMapa(MAX);

  while (1) {
    mostrarMenu();
    int opcion;
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);

    limpiarBuffer();

    switch (opcion) {
    case 1: {
      //Registro De puntos de interes
      char nombre[MAX], tipo[MAX], direccion[MAX], horario[MAX],
          descripcion[MAX];
      printf("\nIngrese nombre del punto de interes: ");
      fgets(nombre, sizeof(nombre), stdin);
      nombre[strcspn(nombre, "\n")] = '\0';
      printf("Ingrese tipo del punto de interes: ");
      fgets(tipo, sizeof(tipo), stdin);
      tipo[strcspn(tipo, "\n")] = '\0';
      printf("Ingrese direccion del punto de interes: ");
      fgets(direccion, sizeof(direccion), stdin);
      direccion[strcspn(direccion, "\n")] = '\0';
      printf("Ingrese el horario del punto de interes: ");
      fgets(horario, sizeof(horario), stdin);
      horario[strcspn(horario, "\n")] = '\0';
      printf("Ingrese la descripcion del punto de interes: ");
      fgets(descripcion, sizeof(descripcion), stdin);
      descripcion[strcspn(descripcion, "\n")] = '\0';

      PuntoInteres *puntoInteres = (PuntoInteres *)malloc(sizeof(PuntoInteres));
      strncpy(puntoInteres->nombre, nombre, MAX);
      strncpy(puntoInteres->tipo, tipo, MAX);
      strncpy(puntoInteres->direccion, direccion, MAX);
      strncpy(puntoInteres->horario, horario, MAX);
      strncpy(puntoInteres->descripcion, descripcion, MAX);

      registrarPto(mapa, puntoInteres->nombre, puntoInteres);
      printf("Punto de interes registrado.\n");
      break;
    }
    case 2: {
      //Mostrar datos de un punto de interes
      
      char nombre[MAX];
      printf("\nIngrese nombre del punto de interes: ");
      fgets(nombre, sizeof(nombre), stdin);
      nombre[strcspn(nombre, "\n")] = '\0';

      PuntoInteres *puntoInteres = buscarPto(mapa, nombre);
      if (puntoInteres != NULL) {
        printf("Nombre: %s\n", puntoInteres->nombre);
        printf("Tipo: %s\n", puntoInteres->tipo);
        printf("Dirección: %s\n", puntoInteres->direccion);
        printf("Horario: %s\n", puntoInteres->horario);
        printf("Descripción: %s\n", puntoInteres->descripcion);
      } else {
        printf("\nPunto de interes no registrado.\n");
      }
      break;
    }
    case 3: {

      //Eliminar puntos de interes
      char nombre[MAX];
      printf("\nIngrese nombre del punto de interes: ");
      fgets(nombre, sizeof(nombre), stdin);
      nombre[strcspn(nombre, "\n")] = '\0';

      PuntoInteres *puntoInteres = buscarPto(mapa, nombre);

      if (puntoInteres != NULL) {
        eliminarPto(mapa, nombre);
        printf("\nEl punto de interes fue eliminado!\n");
      } else {

        printf("\nPunto de interes no registrado.\n");
      }

      break;
    }
    case 4: {

      //Registrar turistas
      
      char pasaporte[MAX], nombre[MAX], pais[MAX];
      printf("\nIngrese numero de pasaporte: ");
      fgets(pasaporte, sizeof(pasaporte), stdin);
      pasaporte[strcspn(pasaporte, "\n")] = '\0';
      printf("Ingrese nombre: ");
      fgets(nombre, sizeof(nombre), stdin);
      nombre[strcspn(nombre, "\n")] = '\0';
      printf("Ingrese pais de origen: ");
      fgets(pais, sizeof(pais), stdin);
      pais[strcspn(pais, "\n")] = '\0';

      Turista *turista = (Turista *)malloc(sizeof(Turista));
      strncpy(turista->pasaporte, pasaporte, MAX);
      strncpy(turista->nombre, nombre, MAX);
      strncpy(turista->pais, pais, MAX);
      turista->lugaresFavoritos = NULL;

      registrarTurista(mapa, turista->pasaporte, turista);
      printf("\nTurista registrado!\n");
      break;
    }
    case 5: {
      char pasaporte[MAX], nombreLugar[MAX];
      printf("\nIngres numero de pasaporte: ");
      fgets(pasaporte, sizeof(pasaporte), stdin);
      pasaporte[strcspn(pasaporte, "\n")] = '\0';
      printf("Ingrese nombre del lugar favorito: ");
      fgets(nombreLugar, sizeof(nombreLugar), stdin);
      nombreLugar[strcspn(nombreLugar, "\n")] = '\0';

      Turista *turista = buscarTurista(mapa, pasaporte);
      if (turista != NULL) {
        agregarFavorito(turista, nombreLugar);
        printf("Lugar favorito agregado!\n");
      } else {
        printf("\nTurista no registrado.\n");
      }
      break;
    }
    case 6: {
      char pais[MAX];
      printf("\nIngrese pais del turista: ");
      fgets(pais, sizeof(pais), stdin);
      pais[strcspn(pais, "\n")] = '\0';

      printf("\nTuristas de %s\n", pais);
      mostrarPorPais(mapa, pais);
      break;
    }
    case 7: {
      char tipo[MAX];
      printf("\nIngrese el tipo del punto de interes: ");
      fgets(tipo, sizeof(tipo), stdin);
      tipo[strcspn(tipo, "\n")] = '\0';

      printf("\nPuntos de interes de tipo %s\n", tipo);
      mostrarPtsTipo(mapa, tipo);
      break;
    }
    case 8: {
      char archivoPuntos[MAX], archivoTuristas[MAX];
      printf("\nIngrese nombre del archivo de puntos de interes: ");
      fgets(archivoPuntos, sizeof(archivoPuntos), stdin);
      archivoPuntos[strcspn(archivoPuntos, "\n")] = '\0';
      printf("Ingrese nombre del archivo de turistas: ");
      fgets(archivoTuristas, sizeof(archivoTuristas), stdin);
      archivoTuristas[strcspn(archivoTuristas, "\n")] = '\0';

      importar(mapa, archivoPuntos, archivoTuristas);
      printf("Datos importados!\n");
      break;
    }
    case 9: {
      char archivoPuntos[MAX], archivoTuristas[MAX];
      printf("\nIngrese nombre del archivo para exportar puntos de interes: ");
      fgets(archivoPuntos, sizeof(archivoPuntos), stdin);
      archivoPuntos[strcspn(archivoPuntos, "\n")] = '\0';
      printf("Ingrese nombre del archivo para exportar turistas: ");
      fgets(archivoTuristas, sizeof(archivoTuristas), stdin);
      archivoTuristas[strcspn(archivoTuristas, "\n")] = '\0';

      exportar(mapa, archivoPuntos, archivoTuristas);
      printf("Datos exportados!\n");
      break;
    }
    case 0: {
      destruirMapa(mapa);
      printf("Finalizando programa!\n");
      return 0;
    }
    default:
      printf("Opcion invalida.\n");
    }
  }
}
