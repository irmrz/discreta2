#include "APIG23.h"
#include "APIParte2.h"
#include "EstructuraGrafo23.h"
#include "abb.h"
#include <time.h>

int N =10;


int main (){
  clock_t t1;
  t1 = clock();
  printf("empieza el juego: %f\n", ((double)(t1))/CLOCKS_PER_SEC);
  Grafo g = ConstruirGrafo();
  printf("grafo cargado: %f\n", ((double)(clock()-t1)/CLOCKS_PER_SEC));

  u32 n = NumeroDeVertices(g);
  u32 cota = Delta(g);
  u32 *orden = malloc(sizeof(u32)*n);
  for (u32 i = 0; i < n; i++) {
    orden[i] = i;
  }
  u32 *color = malloc(sizeof(u32)*n);

  clock_t t;
  t = clock();
  printf("antes de greedy: %f\n", ((double)(t))/CLOCKS_PER_SEC);
  printf("Delta: %u\tColor count: %u\n", cota, Greedy(g,orden,color));
  printf("despues de greedy: %f\n", ((double)(clock()-t)/CLOCKS_PER_SEC));

  printf("\n\n");
  /* Tiempo de orde impar */
  t = clock();
  printf("antes de imparPar: %f\n", ((double)(t))/CLOCKS_PER_SEC);
  printf("char: %c\n", OrdenImparPar(n,orden,color));
  printf("despues de imparPar: %f\n", ((double)(clock()-t)/CLOCKS_PER_SEC));
  printf("Delta: %u\tColor count: %u\n", cota, Greedy(g,orden,color));

  printf("\n\n");
  /* Tiempo de orden jedi */
  t = clock();
  printf("antes de Jedi: %f\n", ((double)(t))/CLOCKS_PER_SEC);
  printf("char: %c\n", OrdenJedi(g,orden,color));
  printf("despues de Jedi: %f\n", ((double)(clock()-t)/CLOCKS_PER_SEC));
  printf("Delta: %u\tColor count: %u\n", cota, Greedy(g,orden,color));

  /*
  for (size_t i = 0; i < 16; i++){
  
    printf("char: %c\n", OrdenImparPar(n,orden,color));

    printf("Delta: %u\tColor count: %u\n", cota, Greedy(g,orden,color));

    printf("char: %c\n", OrdenJedi(g,orden,color));

    printf("Delta: %u\tColor count: %u\n", cota, Greedy(g,orden,color));
  }
  */
  
  free(orden);
  free(color);
  DestruirGrafo(g);
  
  return 0;
}