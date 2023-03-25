#ifndef EstructuraGrafos3_H
#define EstructuraGrafos3_H

#include "APIG23.h"
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>

/* (2 ** 32) - 1*/
#define ERROR 4294967295

/* Definición de u32*/
typedef unsigned int u32;

/* Vertice*/
typedef struct Vertice_s *vertice;

struct Vertice_s {
    u32 nombre;
    u32 index;
    u32 grado;
    u32 capacity;
    u32 *vecinos; /* Equivalente a lista de índices de los vecinos*/
};

/* Grafo */
struct GrafoSt{
   u32 n_vertices; 
   u32 m_lados;
   u32 delta;
   struct Vertice_s *lista_vert;
};

typedef struct Lado_s
    {
        u32 a;
        u32 b;
    }Lado;

#endif