
#include "testing.h"


bool coloreo_prop(Grafo G, u32 *color) {
    
    bool result = true;
    u32 n = G->n_vertices;
    u32 neighbours = 0;

    for (u32 i = 0; i < n; i++){

        neighbours = G->lista_vert[i].grado;
        for (size_t j = 0; j < neighbours; j++){
            if (color[i] == color[G->lista_vert[i].vecinos[j]]){
                result = false;
               // printf("Coloreo no es propio en vertice %u\n",i);
                break;
            }
        }
        if (result == false){
            break;
        }
    }
    
    return result;
}


// ve si el orden jedi esta bien 
bool ordenJ(Grafo G, u32 *orden,u32 *coloreo){

    u32 n = G->n_vertices;
    int *sum_color = calloc(n,sizeof(int));

    for (u32 i = 0; i < n; i++){
        sum_color[coloreo[i]] += G->lista_vert[i].grado;
    }

    u32 color_a = 0;
    u32 color_b = 0;
    for (u32 i = 0; i < n-1; i++){

        color_a = coloreo[G->lista_vert[orden[i]].index];
        color_b = coloreo[G->lista_vert[orden[i+1]].index];

        /* Si el orden es creciente -> esta andando mal */
        if (color_a *sum_color[color_a] < color_b *sum_color[color_b]){
            return false;
        }
    }
    
    return true;

}



//ve si el orden par_Impar esta bien  
bool ordenIP(Grafo G, u32 *orden,u32 *coloreo){

    u32 n = G->n_vertices;
    u32 color_a = 0;
    u32 color_b = 0;
    bool nextimpar = true;
    bool nextpar = false;
    for (u32 i = 0; i < n-1; i++){
        color_a = coloreo[G->lista_vert[orden[i]].index];
        color_b = coloreo[G->lista_vert[orden[i+1]].index];

        if(nextimpar){
            if (color_a % 2 == 0){
                nextimpar = false;
                nextpar = true;
            }
        }
        if(nextpar){
            /* Hay un color Impar despues de uno par */
            if (color_a % 2 != 0 && color_b % 2 != 0){
                return false;
            }
        }
        /* Si tienen la misma paridad -> el color de a debe ser mayor o igual que el de b */
        if (color_a % 2 == color_b % 2){
            if (color_a < color_b){
                return false;
            }
        }else{
            /* Si tienen distinta paridad, a debe ser Impar y b par */
            if (color_a % 2 == 0){
                return false;
            }
            if(color_b % 2 == 1){
                return false;
            }
        }
    }
    

    return true;
}