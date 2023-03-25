#include "APIG23.h"
#include "EstructuraGrafo23.h"


/*
static vertice make_vert(){

    //dar memoria para la estructura

    //asignarle un nombre, indice, y a grado asignarle 0 hasta que se agrege un vecino 

    //pedir memoria para el arreglo de vecinos
}

// g el grafo que tiene los dos grafos, el indice de los dos vertices para agregarlo al indice de neigbours

static void add_neighbour(Grafo g, u32 i, u32 j){   

    // reviso el tamaño del arrey de vertices del vertice i, si tiene espacio agrego j al 
    // arreglo de vecinos si no pido mas memoria antes de hacerlo. incremeto el grado de i

    //sugerencia agregar un campo de capacity para saber cuantos elementos puede soportar el array

    //hacer lo mismo con j

}


static void destruir_vertice(){

}
*/

Grafo ConstruirGrafo(){

    //leer los datos del archivo

    //pedir memoria para la estructura del grafo y la lista de vertices, en este momento ya sabremos
    // el numero de vertices y de lados

    //ordenar los datos y asignar un indice al vertices 

    //crear los vertices y agregar los vecinos segun corresponda

    // hacer un maximo para encontrar el vertice que tenga el mayor numero de vecinos y asignarlo al delta
    Grafo g = NULL;
    g = malloc(sizeof(struct GrafoSt));
    u32 * temp_cont = NULL;


    /* Leer n y m */
    int bool = 0;
    char queimprime[1];
    while (!bool)
    {
        scanf(" %c",queimprime);

        if (queimprime[0] == 'c'){
            do {
                scanf("%c",queimprime);
            } while (queimprime[0] != '\n');
        }else{
            bool = 1;
        }
         
    }
    /* No se agrega la 'p' ya que es consumida por el ciclo de arriba para saber a partir de que linea se consiguen los datos*/
    scanf(" edge %u %u", &g->n_vertices, &g->m_lados); 
    printf("n: %u m: %u\n",g->n_vertices,g->m_lados);
    
    temp_cont = malloc(g->m_lados*sizeof(u32));
    u32 *temp_cont_2 = malloc(g->m_lados*sizeof(u32));

    int res;
    
    scanf("%c\n",&queimprime[0]);
    for (u32 i = 0; i < g->m_lados; i++)
    {
        res = scanf("e %u %u\n", &temp_cont[i], &temp_cont_2[i]);
        if (res != 2)
        {
            printf("Error in format\n");
            exit(EXIT_FAILURE);
        }
        printf("scanf: %u %u\n",temp_cont[i], temp_cont_2[i]);
    }
    
    free(temp_cont);

    return g;
}


void DestruirGrafo(Grafo G){

    //
    G = G;

}


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