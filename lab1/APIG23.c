#include "APIG23.h"
#include "EstructuraGrafo23.h"


static struct Vertice_s make_vert(u32 index, u32 name){

    struct Vertice_s aux_vert;

    aux_vert.index = index;
    aux_vert.nombre = name;
    aux_vert.grado = 0;

    /* No hay vertices no conexos -> van a tener al menos 1 vecino*/
    aux_vert.capacity = 0;

    aux_vert.vecinos = NULL;

    //printf("vertice creado name: %u index: %u\n",aux_vert.nombre,aux_vert.index);
    return aux_vert;
}


// g el grafo que tiene los dos grafos, el indice de los dos vertices para agregarlo al indice de neigbours

static void add_neighbour(Grafo g, u32 vertice_index, u32 vecino_index){   

    // reviso el tamaño del arrey de vertices del vertice i, si tiene espacio agrego j al 
    // arreglo de vecinos si no pido mas memoria antes de hacerlo. incremeto el grado de i

    //sugerencia agregar un campo de capacity para saber cuantos elementos puede soportar el array

    //hacer lo mismo con j
    
    assert(g != NULL);
    assert(vertice_index < g->n_vertices);

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


static void destruir_vertice(vertice v){
    v = v;
}


static int compare(const void *_a, const void *_b) {
 
        u32 *a, *b;
        
        a = (u32 *) _a;
        b = (u32 *) _b;
        
        return (*a - *b);
}

Grafo ConstruirGrafo(){

    //leer los datos del archivo

    //pedir memoria para la estructura del grafo y la lista de vertices, en este momento ya sabremos
    // el numero de vertices y de lados

    //ordenar los datos y asignar un indice al vertices 

    //crear los vertices y agregar los vecinos segun corresponda

    // hacer un maximo para encontrar el vertice que tenga el mayor numero de vecinos y asignarlo al delta
    Grafo g = NULL;
    g = malloc(sizeof(struct GrafoSt));
    Lado * temp_cont = NULL;


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
    /* 
    No se agrega la 'p' ya que es consumida por el ciclo de arriba para saber a partir de que linea se consiguen los datos
    Tambien lee salto de linea ¡OJO AL PIOJO!
    */
    scanf(" edge %u %u\n", &g->n_vertices, &g->m_lados); 
    printf("n: %u m: %u\n",g->n_vertices,g->m_lados);
    

    g->lista_vert = malloc(g->n_vertices * sizeof(struct Vertice_s));
    int res;

    
    u32 *vertex_array = malloc(2 * g->m_lados);
    
    temp_cont = malloc(g->m_lados * sizeof(struct Lado_s));
    
    for (u32 i = 0; i < g->m_lados; i++)
    {
        res = scanf("e %u %u\n", &temp_cont[i].a, &temp_cont[i].b);
        if (res != 2)
        {
            printf("Error in format\n");
            exit(EXIT_FAILURE);
        }
        vertex_array[i] = temp_cont[i].a;
        vertex_array[i + g->m_lados] = temp_cont[i].b;

        //printf("scanf: %u %u - i: %u\n",temp_cont[i].a, temp_cont[i].b, i);
    }

    qsort(vertex_array, g->m_lados * 2, sizeof(u32),&compare);
    
    u32 count = 0;
    u32 aux_ind = 0;

    for (u32 i = 0; i < 2*g->m_lados; i++){
        
        if (aux_ind != vertex_array[i]){
            aux_ind = vertex_array[i];
            g->lista_vert[count] = make_vert(count, aux_ind);
            count++;
        }
        
        if (count == g->n_vertices){
            break;
        }
        
    }
    
    //printf("problemas de free:\n");
    //free(vertex_array);

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