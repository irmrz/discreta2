#include "APIG23.h"
#include "EstructuraGrafo23.h"


static struct Vertice_s make_vert(u32 index, u32 name){

    struct Vertice_s aux_vert;

    aux_vert.index = index;
    aux_vert.nombre = name;
    aux_vert.grado = 0;
    aux_vert.capacity = 0;
    aux_vert.vecinos = NULL;

    //printf("vertice creado name: %u index: %u\n",aux_vert.nombre,aux_vert.index);
    return aux_vert;
}


// g el grafo que tiene los dos vertices, el indice de los dos vertices para agregarlo al indice de neigbours

static void add_neighbour(Grafo g, u32 vertice_index, u32 vecino_index){   
    
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

static int compare_Lado(const void *_a, const void *_b){
    Lado *a, *b;
        
    a = (Lado *) _a;
    b = (Lado *) _b;

    if (a->a < b->a) return -1;
    else if (a->a == b->a)
    {
        if (a->b <= b->b) return -1;
        else if (a->b > b->b) return 1;
    }
    return 1;
}

static int compare(const void *_a, const void *_b) {
 
    u32 va = *(const u32*)_a;
    u32 vb = *(const u32*)_b;

    if (va < vb) return -1;
    if (va == vb) return 0;
    else return 1;
}

static u32 get_index(vertice vertices,u32 start_serch, u32 name){

    assert(vertices != NULL);

    u32 answer = start_serch;
            
    while (vertices[answer].nombre != name){
        answer++;
    }
    
    return answer;
}


Grafo ConstruirGrafo(){
    /* Inicializacion del grafo y alloc de memoria*/
    Grafo g = NULL;
    g = malloc(sizeof(struct GrafoSt));
    
    /* Declaración de variables */
    u32 *vertex_array;
    Lado * temp_cont;
    int bool, res;
    char queimprime[1];
    u32 aux_ind, nombre_del_vertice, count, lado_i, lado_d;;

    /* Lectura de los comentarios del formato Dimacs (primeras lineas) */

    bool = 0;
    res = 0;
    while (!bool)
    {
        res = scanf(" %c",queimprime);
        if (res != 1)
        {
            exit(EXIT_FAILURE);
        }

        if (queimprime[0] == 'c'){
            do {
                res = scanf("%c",queimprime);
                if (res != 1)
                {
                    exit(EXIT_FAILURE);
                }
                
            } while (queimprime[0] != '\n');
        }else{
            bool = 1;
        }
         
    }

    /* Leer numero de vertices y de lados  */
    /* 
    No se agrega la 'p' ya que es consumida por el ciclo de arriba para saber a partir de que linea se consiguen los datos
    Tambien lee salto de linea ¡OJO AL PIOJO!
    */
    res = scanf(" edge %u %u\n", &g->n_vertices, &g->m_lados); 
    if (res != 2)
        {
            exit(EXIT_FAILURE);
        }
    printf("n: %u m: %u\n",g->n_vertices,g->m_lados);
    
    /* Inicializacion del arreglo con la lista de vertices */
    g->lista_vert = malloc(g->n_vertices * sizeof(struct Vertice_s));

    /* Arreglo que contiene todos los vertices que aparecen en un lado (tiene repeticiones de vertices) */
    vertex_array = malloc(2 * g->m_lados* sizeof(u32));
    
    /* Arreglo con los lados */
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
    }
    
    /* Ordenamos el arreglo con vertices repetidos */
    qsort(vertex_array, g->m_lados * 2, sizeof(u32),&compare);
    for (u32 i = (2*g->m_lados)-15; i < 2*g->m_lados; i++)
    {
        printf("%u -> %u\n",i,vertex_array[i]);
    }
    
    /* Llenamos el arreglo de vertices */
    count = 0;
    nombre_del_vertice = 0;

    for(u32 i = 0; i < 2*g->m_lados; i++){
        if (nombre_del_vertice != vertex_array[i]){
            nombre_del_vertice = vertex_array[i];          //count cuenta la posicion en memoria y nombre_del_vertice guarda el nombre del vertice
            g->lista_vert[count] = make_vert(count, nombre_del_vertice);
            count++;
        }
        
        if (count == g->n_vertices){
            break;
        }
    }
    printf("Llenado list vert\n");
    /* Ordenamos el array de lados */
    qsort(temp_cont,g->m_lados,sizeof(Lado),&compare_Lado);
    for (u32 i = g->m_lados-15; i < g->m_lados; i++)
    {
        printf("%u -> %u %u\n",i,temp_cont[i].a, temp_cont[i].b);
    }
    u32 aux_ind_2 = 0;
    lado_i= 0;
    lado_d= 0;
   
    aux_ind = 0;

    for (u32 i = 0; i < g->m_lados; i++){

        lado_i = temp_cont[i].a;
        lado_d = temp_cont[i].b;

        if (lado_i != g->lista_vert[aux_ind].nombre){
            aux_ind_2 = 0;
            aux_ind = get_index(g->lista_vert,aux_ind,lado_i);
        }
        if (lado_d!=g->lista_vert[aux_ind_2].nombre){
            aux_ind_2 = get_index(g->lista_vert,aux_ind_2,lado_d);
        }
          
        add_neighbour(g,aux_ind,aux_ind_2);
        add_neighbour(g,aux_ind_2,aux_ind);

    }
    printf("Vecinos llenos\n");
    free(vertex_array);
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