#include "APIG23.h"
#include "EstructuraGrafo23.h"
#include "abb.h"

int N =10;


int main (){

  Grafo g = ConstruirGrafo();
  DestruirGrafo(g);
  
  return 0;
}