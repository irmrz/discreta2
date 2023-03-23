#ifndef EstructuraGrafos3_H
#define EstructuraGrafos3_H

#include "APIG23.h"
#include <stdint.h>
#include <assert.h>

/* Definición de u32*/
typedef unsigned int u32;

/* Vertice*/
typedef struct Vertice_s *vertice;

struct Vertice_s {
    u32 nombre;
    u32 index;
    u32 grado;
    u32 *vecinos;
};

/* Grafo */
struct GrafoSt{
   u32 n_vertices; 
   u32 m_lados;
   u32 delta;
   struct Vertice_s *lista_vert;
};
#endif