#include "APIG23.h"
#include "APIParte2.h"
#include "EstructuraGrafo23.h"
#include "abb.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main (){
  clock_t t1;
  t1 = clock();
  printf("Empieza la ejecucion: %fs\n", ((double)(t1))/CLOCKS_PER_SEC);
  Grafo g = ConstruirGrafo();
  printf("\n");
  printf("Grafo cargado: %fs\n", ((double)(clock()-t1)/CLOCKS_PER_SEC));

  u32 n = NumeroDeVertices(g);
  u32 cota = Delta(g);

  u32 *orden_1 = malloc(sizeof(u32)*n);
  u32 *orden_2 = malloc(sizeof(u32)*n);
  u32 *color_1 = malloc(sizeof(u32)*n);
  u32 *color_2 = malloc(sizeof(u32)*n);

  for (u32 i = 0; i < n; i++) {
    orden_1[i] = i;
  }

  u32 primer_coloreo = Greedy(g, orden_1, color_1);
  for (u32 i = 0; i < n; i++) {
    orden_2[i] = orden_1[i];
    color_2[i] = color_1[i];
  }
  printf("\n");
  printf("Primer coloreo: %u\tDelta: %u\n", primer_coloreo, cota);
  printf("\n");
  
  u32 coloreo_min = primer_coloreo;
  u32 greedy_1 = 0;
  u32 greedy_2 = 0;
  char imparPar;
  char jedi;
  bool switches = true;

  t1 = clock();
  printf("\n");
  printf("Antes del bucle: %fs\n", ((double)(t1))/CLOCKS_PER_SEC);
  printf("\n");

  t1 = clock();
  for (size_t i = 0; i < 500; i++){
    
    if (i % 16 == 0) {
      switches = !switches;
    }

    if (switches) {
      imparPar = OrdenImparPar(n, orden_1, color_1);
      greedy_1 = Greedy(g, orden_1, color_1);
      jedi = OrdenJedi(g, orden_2, color_2);
      greedy_2 = Greedy(g, orden_2, color_2);
      
      /* Check de que ande todo bien y seteamos el coloreo minimo */
      coloreo_min = coloreo_min > greedy_1 ? greedy_1 : coloreo_min;
      coloreo_min = coloreo_min > greedy_2 ? greedy_2 : coloreo_min;
      if (imparPar == '1') {
        printf("Error en imparPar\n");
        exit(EXIT_FAILURE);
      }
      if (jedi == '1') {
        printf("Error en Jedi\n");
        exit(EXIT_FAILURE);
      }
    }
    else {
      imparPar = OrdenImparPar(n, orden_2, color_2);
      greedy_1 = Greedy(g, orden_2, color_2);
      jedi = OrdenJedi(g, orden_1, color_1);
      greedy_2 = Greedy(g, orden_1, color_1);
      
      /* Check de que ande todo bien y seteamos el coloreo minimo */
      coloreo_min = coloreo_min > greedy_1 ? greedy_1 : coloreo_min;
      coloreo_min = coloreo_min > greedy_2 ? greedy_2 : coloreo_min;
      if (imparPar == '1') {
        printf("Error en imparPar\n");
        exit(EXIT_FAILURE);
      }
      if (jedi == '1') {
        printf("Error en Jedi\n");
        exit(EXIT_FAILURE);
      }
 
    }
  }

  printf("\n");
  printf("Bucle finalizado: %fm\n", (((double)(clock()-t1)/CLOCKS_PER_SEC)) / 60);
  printf("\n");

  printf("\n");
  printf("Coloreo minimo: %u\n",coloreo_min);
  printf("\n");

  free(orden_1);
  free(orden_2);
  free(color_1);
  free(color_2);
  DestruirGrafo(g);
  
  return 0;
}
