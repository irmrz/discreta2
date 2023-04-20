#include "APIParte2.h"
#include <assert.h>
#include <stdbool.h>

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
    bool used_colors[n];    /*  arreglo de "booleanos" para saber que colores estan 
                                presentes en los vecionos de un vertices 
                            */
    u32 *coloreado = calloc(n,sizeof(u32)); /* arreglo que indica si un vertice esta coloreado o no */
    Color[vert] = 0;
    colors_count++;

    for (u32 i = 1; i < n; i++){
        
        for (u32 j = 0; j < colors_count; j++){
            used_colors[j] = false;
        }
         
        vert = Orden[i];
        vecinos_count = Grado(vert,G);

        for (u32 j = 0; j < vecinos_count; j++){
            vecino = IndiceVecino(j,vert,G);
            if (coloreado[vecino] != 0){
                used_colors[Color[vecino]] = true;
            }
            
        }

        for (u32 j = 0; j < colors_count; j++){
            /* Si un color no está usado se lo asignamos al vertice */
            if(used_colors[j] == false){
                Color[vert] = j;
                break;
            }
            /* Todos los colores hasta el momento estan usados en los vecinos*/
            if(j == colors_count - 1){
                Color[vert] = colors_count;
                colors_count++;
            }
        }
        
        coloreado[i] = 1;
    }
    free(coloreado);
    return colors_count;
}



