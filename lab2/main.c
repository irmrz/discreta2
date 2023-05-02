
#include "APIParte2.h"
#include <time.h>
#include "testing.h"


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
  
  u32 coloreo_min_imparPar = primer_coloreo;
  u32 coloreo_min_jedi = primer_coloreo;

  u32 greedy_1 = 0;
  u32 greedy_2 = 0;
  char imparPar;
  char jedi;
  bool switches = true;

  t1 = clock();
  printf("\n");
  printf("Antes del bucle: %fs\n", ((double)(t1))/CLOCKS_PER_SEC);

  t1 = clock();
  for (size_t i = 0; i < 500; i++){
    
    if (i % 16 == 0) {
      switches = !switches;

      /*Swap de mins*/
      u32 aux = coloreo_min_imparPar;
      coloreo_min_imparPar = coloreo_min_jedi;
      coloreo_min_jedi = aux;

      /*Swap orden*/

      /*Swap coloreo*/
    }

    if (switches) {
      
      imparPar = OrdenImparPar(n, orden_1, color_1);

      if (!ordenIP(g, orden_1, color_1))
      {
        printf("Orden invalido en imparPar\n");
        exit(EXIT_FAILURE);
      }
      
      greedy_1 = Greedy(g, orden_1, color_1);

      /* Checkeamos que los coloreos sean correctos*/
      if (!coloreo_prop(g,color_1)){
        printf("Coloreo invalido en imparPar\n");
        exit(EXIT_FAILURE);
      }


      jedi = OrdenJedi(g, orden_2, color_2);

      if (!ordenJ(g, orden_2, color_2))
      {
        printf("Orden invalido en Jedi\n");
        exit(EXIT_FAILURE);
      }

      greedy_2 = Greedy(g, orden_2, color_2);

      /* Checkeamos que los coloreos sean correctos*/

      if (!coloreo_prop(g,color_2)){
        printf("Coloreo invalido en Jedi\n");
        exit(EXIT_FAILURE);
      }

      

      
      /* Check de que ande todo bien y seteamos el coloreo minimo */
      
      if (coloreo_min_imparPar >= greedy_1) coloreo_min_imparPar = greedy_1;
      else
      {
        printf("Se rompe el invariante en imparPar -> greedy:%u -> min_IP:%u\n", greedy_1, coloreo_min_imparPar);
        exit(EXIT_FAILURE);
      }


      if (coloreo_min_jedi >= greedy_2) coloreo_min_jedi = greedy_2;
      else
      {
        printf("Se rompe el invariante en jedi -> greedy:%u -> min_jedi: %u\n", greedy_2, coloreo_min_jedi);
        exit(EXIT_FAILURE);
      }
      
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
      if (!ordenIP(g, orden_2, color_2))
      {
        printf("Orden invalido en imparPar\n");
        exit(EXIT_FAILURE);
      }

      greedy_1 = Greedy(g, orden_2, color_2);
      
      if (!coloreo_prop(g,color_2)){
        printf("Coloreo invalido en imparPar\n");
        exit(EXIT_FAILURE);
      }
      
      jedi = OrdenJedi(g, orden_1, color_1);

      if (!ordenJ(g, orden_1, color_1))
      {
        printf("Orden invalido en Jedi\n");
        exit(EXIT_FAILURE);
      }

      greedy_2 = Greedy(g, orden_1, color_1);
      
      if (!coloreo_prop(g,color_1)){
        printf("Coloreo invalido en Jedi\n");
        exit(EXIT_FAILURE);
      }
      

      /* Check de que ande todo bien y seteamos el coloreo minimo */
      
      if (coloreo_min_imparPar >= greedy_1) coloreo_min_imparPar = greedy_1;
      else
      {
        printf("Se rompe el invariante en imparPar ->%u\n", greedy_1);
        exit(EXIT_FAILURE);
      }
      
      if (coloreo_min_jedi >= greedy_2) coloreo_min_jedi = greedy_2;
      else
      {
        printf("Se rompe el invariante en jedi -> %u\n", greedy_2);
        exit(EXIT_FAILURE);
      }

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

  u32 coloreo_min = coloreo_min_imparPar < coloreo_min_jedi ? coloreo_min_imparPar : coloreo_min_jedi;

  printf("\n");
  printf("Bucle finalizado: %fm\n", (((double)(clock()-t1)/CLOCKS_PER_SEC)) / 60);
  printf("\n");

  printf("\n");
  printf("Coloreo minimo imparPar: %u\n",coloreo_min_imparPar);
  printf("Coloreo minimo Jedi: %u\n",coloreo_min_jedi);
  printf("Coloreo minimo: %u\n",coloreo_min);
  printf("\n");

  free(orden_1);
  free(orden_2);
  free(color_1);
  free(color_2);
  DestruirGrafo(g);
  
  return 0;
}
