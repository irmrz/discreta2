
#include "APIParte2.h"

int main() {
  
  Grafo g = ConstruirGrafo();

  u32 n = NumeroDeVertices(g);

  u32 *orden_1 = malloc(sizeof(u32) * n);
  u32 *orden_2 = malloc(sizeof(u32) * n);
  u32 *color_1 = malloc(sizeof(u32) * n);
  u32 *color_2 = malloc(sizeof(u32) * n);

  for (u32 i = 0; i < n; i++) {
    orden_1[i] = i;
  }

  u32 primer_coloreo = Greedy(g, orden_1, color_1);
  for (u32 i = 0; i < n; i++) {
    orden_2[i] = orden_1[i];
    color_2[i] = color_1[i];
  }
  
  u32 coloreo_min_imparPar = primer_coloreo;
  u32 coloreo_min_jedi = primer_coloreo;

  u32 greedy_1 = 0;
  u32 greedy_2 = 0;
  char imparPar;
  char jedi;


  for (size_t i = 0; i < 500; i++) {
    if (i % 16 == 0) {
      /*Swap de mins*/
      u32 aux = coloreo_min_imparPar;
      coloreo_min_imparPar = coloreo_min_jedi;
      coloreo_min_jedi = aux;

      /*Swap orden*/
      u32 *aux_orden = orden_1;
      orden_1 = orden_2;
      orden_2 = aux_orden;

      /*Swap coloreo*/
      u32 *aux_coloreo = color_1;
      color_1 = color_2;
      color_2 = aux_coloreo;
    }

    imparPar = OrdenImparPar(n, orden_1, color_1);
    greedy_1 = Greedy(g, orden_1, color_1);
    jedi = OrdenJedi(g, orden_2, color_2);
    greedy_2 = Greedy(g, orden_2, color_2);

    /* Check de que ande todo bien y seteamos el coloreo minimo */

    if (coloreo_min_imparPar >= greedy_1)
      coloreo_min_imparPar = greedy_1;
    else {
      printf("Se rompe el invariante en imparPar -> greedy:%u -> min_IP:%u\n",
             greedy_1, coloreo_min_imparPar);
      exit(EXIT_FAILURE);
    }

    if (coloreo_min_jedi >= greedy_2)
      coloreo_min_jedi = greedy_2;
    else {
      printf("Se rompe el invariante en jedi -> greedy:%u -> min_jedi: %u\n",
             greedy_2, coloreo_min_jedi);
      exit(EXIT_FAILURE);
    }

    if (imparPar == (char)1) {
      printf("Error en imparPar\n");
      exit(EXIT_FAILURE);
    }
    if (jedi == (char)1) {
      printf("Error en Jedi\n");
      exit(EXIT_FAILURE);
    }
  }

  u32 coloreo_min = coloreo_min_imparPar < coloreo_min_jedi
                        ? coloreo_min_imparPar
                        : coloreo_min_jedi;

  
  printf("Coloreo minimo imparPar: %u\n", coloreo_min_imparPar);
  printf("Coloreo minimo Jedi: %u\n", coloreo_min_jedi);
  printf("Coloreo minimo: %u\n", coloreo_min);
  

  free(orden_1);
  free(orden_2);
  free(color_1);
  free(color_2);
  DestruirGrafo(g);

  return 0;
}
