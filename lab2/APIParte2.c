#include "APIParte2.h"


/* Estructura de pares que tendra el arreglo auxiliar */
typedef struct tupla_s{
    u32 indice;
    u32 color;
    u32 jedi;
}tupla;

//si no sale jedi agregar el campo name al tupla


static int cmp_jedi(const void *_a, const void *_b){

    tupla a = *(tupla *)_a;
    tupla b = *(tupla *)_b;

    if (a.jedi < b.jedi) return 1;
    if (a.jedi > b.jedi) return -1;

    if (a.color != b.color){

        return a.color < b.color ? 1 : -1; 
    }

    return 0;

}


static int cmp_impar_par(const void *_a, const void *_b){
    u32 a, b;

    /*
    la expresión ((tupla *)_a) convierte el puntero de tipo void * _a 
    a un puntero de tipo tupla *, 
    permitiendo acceder al miembro color de la estructura tupla.
    */

    a = ((tupla *)_a)->color;
    b = ((tupla *)_b)->color;

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

/*
 Orden es un arreglo de indices en algun orden 
 Color: tenemos que completarlo con los colores que correspondan a el coloreo generado, 
 en la posicion i colocaremos el color que le corresponde al iesimo vertice en el orden natural 

 Orden[i]=k significa que el v ́ertice cuyo índice es k en el Orden Natural ser a el v ́ertice procesado
 en Greedy en el lugar i.
*/
u32 Greedy(Grafo G,u32* Orden,u32* Color){

    u32 colors_count = 0;    /* Cantidad de colores total que usa el grafo */
    u32 n = NumeroDeVertices(G);
    u32 vecinos_count = 0;
    u32 vecino = 0;
    u32 *coloreado = calloc(n,sizeof(u32)); /* arreglo que indica si un vertice esta coloreado o no */
    u32 *used_colors = calloc(n,sizeof(u32));    /*  arreglo de "booleanos" para saber que colores estan 
                                                presentes en los vecionos de un vertice */
    u32 vert = Orden[0];     /* vertice que se esta procesando*/
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

        coloreado[vert] = 1;
    }
    free(used_colors);
    free(coloreado);
    return colors_count;
}



/*Color es el coloreo anterior
Es el nuevo orden a colorear
n es el numero de vertices = largo de los arrays*/
char OrdenImparPar(u32 n,u32* Orden,u32* Color){

    tupla *aux_array = calloc(n,sizeof(tupla));
    
    if (aux_array == NULL){
        return '1';
    }

    for (u32 i = 0; i < n; i++){
        aux_array[i].indice = i;
        aux_array[i].color = Color[i];
    }

    qsort(aux_array,n,sizeof(tupla),cmp_impar_par);

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
/*
crear el arreglo auxiliar
ordenar el arreglo auxiliar en funcion del color
calcular jedi para cada color
añaadir los jedi al arreglo auxiliar
ordenarlo en funcion del valor de jedi
guardar el nuevo orden en el arreglo Orden
*/

char OrdenJedi(Grafo G,u32* Orden,u32* Color){

    u32 n = NumeroDeVertices(G);
    tupla *aux_array = calloc(n,sizeof(tupla));
    u32 *jedi_result = NULL;
    u32 amount_colors = 0;
    
    if(aux_array == NULL){
        return '1';
    }

    //arreglo jedi_result largo r = numero de colores
    jedi_result = calloc(n,sizeof(u32));
    
    if (jedi_result == NULL){
        return '1';
    }

    for ( u32 i = 0; i < n; i++){
        aux_array[i].indice = i;
        aux_array[i].color = Color[i];
        aux_array[i].jedi = ERROR;
    
        jedi_result[Color[i]] += Grado(i,G);
    
        if (amount_colors < Color[i]){
            amount_colors = Color[i];
        }        
    }
    amount_colors++;
    //printf("Cantidad de colores: %u\n",amount_colors); 

    for (u32 i = 0; i < amount_colors; i++){        
        jedi_result[i] = jedi_result[i] * i;
    }
    
    for (u32 i = 0; i < n; i++){
        aux_array[i].jedi = jedi_result[aux_array[i].color];
    }

    qsort(aux_array,n,sizeof(tupla),cmp_jedi);

    for (u32 i = 0; i < n; i++){        
        Orden[i] = aux_array[i].indice;
    }
    
    free(aux_array);
    free(jedi_result);

    return '0';    

}


