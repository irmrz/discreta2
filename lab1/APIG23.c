#include "APIG23.h"
#include "EstructuraGrafo23.h"
#include "abb.h"



// g el grafo que tiene los dos vertices, el indice de los dos vertices para agregarlo al indice de neigbours

static void add_neighbour(Grafo g, u32 vertice_index, u32 vecino_index){   
    
    assert(g != NULL);
    if(vertice_index > g->n_vertices){
        printf("%u \n", vertice_index);
        assert(vertice_index != vertice_index);
    }

    u32 grado = g->lista_vert[vertice_index].grado; // Numero de vecinos que tiene el vertice "vertice_index"
    u32 capacity = g->lista_vert[vertice_index].capacity;

    if (capacity == grado)
    {
        u32 new_capacity = capacity == 0 ? 1 : 2 * capacity;
        g->lista_vert[vertice_index].vecinos =realloc(g->lista_vert[vertice_index].vecinos, new_capacity * sizeof(u32));
        g->lista_vert[vertice_index].capacity = new_capacity;
    }
    g->lista_vert[vertice_index].vecinos[grado] = vecino_index;
    g->lista_vert[vertice_index].grado++;
}


Grafo ConstruirGrafo(){
    Grafo g = NULL;
    g = malloc(sizeof(struct GrafoSt));
    Lado * temp_cont = NULL;

    /* Leer n y m */
    int auxbool = 0;
    char queimprime[1];
    while (!auxbool)
    {
        scanf(" %c",queimprime);

        if (queimprime[0] == 'c'){
            do {
                scanf("%c",queimprime);
            } while (queimprime[0] != '\n');
        }else{
            auxbool = 1;
        }
         
    }
    /* 
    No se agrega la 'p' ya que es consumida por el ciclo de arriba para saber a partir de que linea se consiguen los datos
    Tambien lee salto de linea ¡OJO AL PIOJO!
    */
    scanf(" edge %u %u\n", &g->n_vertices, &g->m_lados); 
    printf("n: %u m: %u\n",g->n_vertices,g->m_lados);
    

    g->lista_vert = malloc(g->n_vertices * sizeof(struct Vertice_s));
    int res;
    
    abb vertex_tree = abb_empty();
    
    temp_cont = malloc(g->m_lados * sizeof(struct Lado_s));
    
    
    printf("cargando vertices\n");    
            

    for (u32 i = 0; i < g->m_lados; i++){
        res = scanf("e %u %u\n", &temp_cont[i].a, &temp_cont[i].b);
        if (res != 2)
        {
            printf("Error in format\n");
            exit(EXIT_FAILURE);
        }
        vertex_tree = abb_add(vertex_tree,temp_cont[i].a);
        vertex_tree = abb_add(vertex_tree, temp_cont[i].b);
    }

    //abb_dump(vertex_tree);

    printf("todos los vertices cargados\n");
    
    
    abb_set_index_and_load(vertex_tree,g->lista_vert,0);

    //abb_set_index(vertex_tree,0);

    //load_pre_ord_vert(vertex_tree,g->lista_vert);
    
    printf("vertices generados\n");
    u32 lado_i, lado_d;
    u32 aux_ind_2 = 0;
    u32 aux_ind = 0;
    
    lado_i= 0;
    lado_d= 0;
   
    
    for (u32 i = 0; i < g->m_lados; i++){

        lado_i = temp_cont[i].a;
        lado_d = temp_cont[i].b;

        if (lado_i != g->lista_vert[aux_ind].nombre){
            aux_ind_2 = 0;
            aux_ind = get_index(vertex_tree,lado_i);
        }
        if (lado_d!=g->lista_vert[aux_ind_2].nombre){
            aux_ind_2 = get_index(vertex_tree,lado_d);
        }
        
        add_neighbour(g,aux_ind,aux_ind_2);
        add_neighbour(g,aux_ind_2,aux_ind);

    }
    u32 max_grado =0;

    for (u32 i = 0; i < g->n_vertices; i++){
        if (max_grado<g->lista_vert[i].grado){
            max_grado = g->lista_vert[i].grado;
        }    
    }
    

    g->delta = max_grado;
    printf("grado: %u\n",g->delta);

    printf("vecinos añadidos\n");


    abb_destroy(vertex_tree);
    free(temp_cont);

    return g;
}


void DestruirGrafo(Grafo G){

    for (u32 i = 0; i < G->n_vertices; i++)
    {
        free(G->lista_vert[i].vecinos);
    }
    free(G->lista_vert);
    free(G);
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