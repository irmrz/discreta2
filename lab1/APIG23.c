#include "APIG23.h"
#include "EstructuraGrafo23.h"


u32 NumeroDeVertices(Grafo G) {
    assert(G != NULL);
    return G->n_vertices;
}

u32 NumeroDeLados(Grafo G) {
    assert(G != NULL);
    return G->m_lados;
}

u32 Delta(Grafo G) {
    assert(G != NULL);
    return G->delta;
}

u32 Nombre(u32 i,Grafo G) {
    assert(G != NULL);
    assert(i < G->n_vertices);
    return G->lista_vert[i].nombre;
}

u32 Grado(u32 i,Grafo G) {
    assert(G != NULL);
    assert(i < G->n_vertices);
    return G->lista_vert[i].grado;
}

u32 IndiceVecino(u32 j,u32 i,Grafo G) {
    if (i >= G->n_vertices)
    {
        return ERROR;
    }
    else if (j >= G->lista_vert[i].grado)
    {
        return ERROR;
    }
    else
    {
        return G->lista_vert[i].vecinos[j];
    }
}