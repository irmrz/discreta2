#include "APIParte2.h"
#include "EstructuraGrafo23.h"
#include <assert.h>
#include <stdbool.h>

/* Estructura de pares que tendra el arreglo auxiliar */
typedef struct par_s{
    u32 indice;
    u32 color;
}par;



static int cmp_impar_par(const void *_a, const void *_b){
    u32 a, b;

    /*
    la expresión ((par *)_a) convierte el puntero de tipo void * _a 
    a un puntero de tipo par *, 
    permitiendo acceder al miembro color de la estructura par.
    */

    a = ((par *)_a)->color;
    b = ((par *)_b)->color;

    // veo si uno es par y el otro impares
    if ((a % 2) != (b % 2)) {
        // si a es impar devuelvo -1 ya que a va a ser "mayor" que b en nuestro orden
        return (a % 2) == 1 ? -1 : 1;       
    }
    else {

        if (a <= b) return 1;
    
        if (a > b) return -1;
    }

    printf("Error en cmp_par\n");
    return 1;
}

/*
a < b -> 1
a > b -> -1
*/


// 1  a es mayor que b
// -1 b es mayor igual que a
/*
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

*/



/*
 Orden es un arreglo de indices en algun orden 
 Color: tenemos que completarlo con los colores que correspondan a el coloreo generado, 
 en la posicion i colocaremos el color que le corresponde al iesimo vertice en el orden natural 

 Orden[i]=k significa que el v ́ertice cuyo índice es k en el Orden Natural ser a el v ́ertice procesado
 en Greedy en el lugar i.
*/
u32 Greedy(Grafo G,u32* Orden,u32* Color){
    assert(((G!=NULL) && (Orden!=NULL) && (Color!=NULL)));

    u32 colors_count = 0;    /* Cantidad de colores total que usa el grafo */
    u32 vert = Orden[0];     /* vertice que se esta procesando*/
    u32 n = NumeroDeVertices(G);
    u32 vecinos_count = 0;
    u32 vecino = 0;
    u32 *used_colors = calloc(n,sizeof(u32));    /*  arreglo de "booleanos" para saber que colores estan 
                                presentes en los vecionos de un vertice 
                            */
    u32 *coloreado = calloc(n,sizeof(u32)); /* arreglo que indica si un vertice esta coloreado o no */
    Color[vert] = 0;
    colors_count++;
    coloreado[vert] = 1;
    
    for (u32 i = 1; i < n; i++){
        
        for (u32 j = 0; j < colors_count; j++){
            used_colors[j] = 0;
        }
         
        vert = Orden[i];
        //printf("Vertice: %u\n",vert);
        vecinos_count = Grado(vert,G);

        for (u32 j = 0; j < vecinos_count; j++){
            vecino = IndiceVecino(j,vert,G);
            if (vecino == ERROR){
                return ERROR;
            }
            if (coloreado[vecino] != 0){
                used_colors[Color[vecino]] = 1;
            }
            
        }

        u32 aux_bool = 1;
        for (u32 j = 0; j < colors_count; j++){
            /* Si un color no está usado se lo asignamos al vertice y salimos del bucle */
            if(used_colors[j] == 0){
                Color[vert] = j;
                aux_bool = 0;
                break;
            }
            /* Todos los colores hasta el momento estan usados en los vecinos*/
        }
        /* Si aux-bool es true(1) -> los vecinos usaron todos los colores anterio*/
        if (aux_bool){
            Color[vert] = colors_count;
            //printf("Se uso el color: %u en vert: %u \n",colors_count,vert);
            colors_count++;
        }
        coloreado[i] = 1;
    }
    free(used_colors);
    free(coloreado);
    return colors_count;
}



/*Color es el coloreo anterior
Es el nuevo orden a colorear
n es el numero de vertices = largo de los arrays*/
char OrdenImparPar(u32 n,u32* Orden,u32* Color){
    assert((Orden!=NULL) && (Color!=NULL));

    par *aux_array = calloc(n,sizeof(par));
    if (aux_array == NULL){
        return '1';
    }

    for (u32 i = 0; i < n; i++){
        aux_array[i].indice = i;
        aux_array[i].color = Color[i];
    }

    qsort(aux_array,n,sizeof(par),cmp_impar_par);

    /*
    for(u32 i = 0; i < n; i++){
        printf("Indice: %u Color: %u\n",aux_array[i].indice,aux_array[i].color);
    }
    */


    for (u32 i = 0; i < n; i++){
        Orden[i] = aux_array[i].indice;
    }

    free(aux_array);
    return '0';
}
