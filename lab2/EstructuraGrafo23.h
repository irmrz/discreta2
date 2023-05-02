#ifndef EstructuraGrafos3_H
#define EstructuraGrafos3_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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
typedef struct grafo_s {
   u32 n_vertices; 
   u32 m_lados;
   u32 delta;
   struct Vertice_s *lista_vert;
}GrafoSt;

typedef struct Lado_s
    {
        u32 a;
        u32 b;
    }Lado;

#endif