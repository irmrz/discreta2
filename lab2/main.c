#include "APIG23.h"
#include "APIParte2.h"
#include "EstructuraGrafo23.h"
#include "abb.h"

int N =10;


int main (){

  Grafo g = ConstruirGrafo();
  u32 n = NumeroDeVertices(g);
  u32 cota = Delta(g);
  u32 *orden = malloc(sizeof(u32)*n);
  for (u32 i = 0; i < n; i++) {
    orden[i] = i;
  }
  u32 *color = malloc(sizeof(u32)*n);
  printf("Delta: %u\tColor count: %u\n", cota, Greedy(g,orden,color));

  printf("char: %c\n", OrdenImparPar(n,orden,color));

  /*
  for(u32 i = 0; i < n; i++){
        printf("Indice: %u \n",orden[i]);
  }
  */

  printf("Delta: %u\tColor count: %u\n", cota, Greedy(g,orden,color));
  
  for(u32 i = 0; i < n; i++){
        printf("Indice: %u \tColor: %u\n",orden[i],color[orden[i]]);
  }

  DestruirGrafo(g);
  
  return 0;
}