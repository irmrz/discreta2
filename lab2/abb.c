
#include "abb.h"
#include "EstructuraGrafo23.h"

static struct Vertice_s make_vert(u32 index, u32 name){

    struct Vertice_s aux_vert;

    aux_vert.index = index;
    aux_vert.nombre = name;
    aux_vert.grado = 0;
    aux_vert.capacity = 0;

    aux_vert.vecinos = NULL;

    return aux_vert;
}

struct _s_abb {
    abb_elem elem;
    int heigth;
    struct _s_abb *father;
    struct _s_abb *left;
    struct _s_abb *right;

};

static bool elem_eq(abb_elem b,u32 a) {
    return a == b.name;
}

static bool elem_less(abb_elem b,u32 a) {
    return a < b.name;
}

static bool elem_greater(abb_elem b,u32 a) {
    return a > b.name;
}
static void act_heigth(abb tree){

    int hi = 0; 
    int hd = 0;

    if (tree->right !=NULL){
        hd = tree->right->heigth;
    }
    if (tree->left != NULL){
        hi = tree->left->heigth;
    }
    
    if (hi < hd){
        tree->heigth = hd +1;
    }else{
        tree->heigth = hi +1;
    }
    
}

static struct _s_abb *create_node(u32 e){
    struct _s_abb *new_node = malloc(sizeof(struct _s_abb));
    new_node->elem.name = e;
    new_node->left=NULL;
    new_node->right=NULL;
    new_node->heigth = 0;
    new_node->father = NULL;

    return new_node;
}


abb abb_empty(void) {
    abb tree;
    tree = NULL;

    return tree;
}


abb rot_izq(abb tree){

    abb father = tree->father;
    abb aux,q;

    aux = tree->right;
    q = aux->left;
    
    tree->right = q;
    aux->left = tree;

    if (q!=NULL){
        q->father = tree;
    }
    tree->father = aux;
    aux->father = father;
    
    act_heigth(tree);
    act_heigth(aux);

    return aux;
}

abb rot_der(abb tree){
    
    abb father = tree->father;
    abb aux,q;

    aux = tree->left;
    q = aux->right;

    tree->left = q;
    aux->right = tree;

    if (q!=NULL){
        q->father = tree;
    }
    tree->father = aux;
    
    aux->father = father;
    
    act_heigth(tree);
    act_heigth(aux);

    return aux;
}

abb rot_doble_der(abb tree){
    
    abb aux;
    tree->left = rot_izq(tree->left);
    aux =rot_der(tree);

    return aux;
}

abb rot_doble_izq(abb tree){
    abb aux;
    tree->right = rot_der(tree->right);
    aux =rot_izq(tree);
    return aux;
}

int factorEQ(abb tree){
   
    int hi = 0;
    int hd =0;

    if (tree->left != NULL){
        hi = tree->left->heigth;
    }
    if (tree->right != NULL){
        hd = tree->right->heigth;
    }

    return hd-hi;

}

abb balance(abb tree){

    abb aux_tree = tree;

    if (tree!= NULL){

        if (factorEQ(tree)> 1){
            if (factorEQ(tree->right)>=0){    
                    
                aux_tree =rot_izq(tree);
                
            }else{    
                aux_tree =rot_doble_izq(tree);
                
            }
        }

        if (factorEQ(tree)< -1){
            if (factorEQ(tree->left)<=0){    
                aux_tree =rot_der(tree);    
            }else{
                aux_tree =rot_doble_der(tree);
            }
        }
        
    }
    
    return aux_tree;

}


abb abb_add(abb tree, u32 e) {
    if (tree == NULL){
        abb new_node = create_node(e);
        tree =new_node;
    }else{
        if (elem_eq(tree->elem,e)){
            return tree;
        }
        if(elem_less(tree->elem,e)){
             
            tree->left=abb_add(tree->left,e);
            
            if(tree->left->father == NULL){
                tree->left->father = tree;
            }

        }
        if (elem_greater(tree->elem,e)){
            tree->right=abb_add(tree->right,e);
            
            if(tree->right->father == NULL){
                tree->right->father = tree;
            }    
        }
    }
    act_heigth(tree);
    tree = balance(tree);
    
    return tree;
}



bool abb_is_empty(abb tree) {
    bool is_empty=false;
    
    is_empty = tree == NULL;
    return is_empty;
}

bool abb_exists(abb tree, u32 e) {
    bool exists=false;
    
    if (tree != NULL){
        if (elem_eq(tree->elem,e)){
            exists = true;
        }else{

            if (elem_less(tree->elem,e)){
                exists = abb_exists(tree->left,e);
            }else{
                exists = abb_exists(tree->right,e);
            }
            
        }
        
    }
    

    return exists;
}

u32 get_index(abb tree, u32 name){

    if (tree == NULL){
        printf("the name %u dont belong to the tree",name);
        return 0;
    }
    
    if(elem_eq(tree->elem,name)){
        return tree->elem.index;
    }else if(elem_less(tree->elem,name)){
        return get_index(tree->left,name);
    }else{
        return get_index(tree->right,name);
    }

}


unsigned int abb_length(abb tree) {
    unsigned int length=0;
    
    if (tree!=NULL){
        length =1+ abb_length(tree->left) + abb_length(tree->right);
    }
    
    
    return length;
}

u32 abb_root(abb tree) {
    u32 root;
    
    root = tree->elem.name;
    return root;
}

u32 abb_max(abb tree) {
    u32 max_e;
    
    if (tree->right == NULL){
        max_e = tree->elem.name;
    }else{
        max_e = abb_max(tree->right);
    }
    
    return max_e;
}

u32 abb_min(abb tree) {
    u32 min_e;
    
    if (tree->left == NULL){
        min_e = tree->elem.name;
    }else{
        min_e = abb_min(tree->left);
    }

    return min_e;
}

void abb_dump(abb tree) {
    if (tree != NULL) {
        abb_dump(tree->left);
        printf("%u index : %u heigth:%u\n",tree->elem.name,tree->elem.index,tree->heigth);
        abb_dump(tree->right);
    }
}

abb abb_destroy(abb tree) {
    
    if (tree != NULL)
    {
        if (tree->left !=NULL){
            abb_destroy(tree->left);
        }
        
        if (tree->right !=NULL){
            abb_destroy(tree->right);
        }
    }
    
    free(tree);
    tree=NULL;

    return tree;
}



u32 abb_set_index(abb tree,u32 last_ad){


    if (tree != NULL) {
        last_ad =abb_set_index(tree->left,last_ad);
        tree->elem.index = last_ad;
        last_ad ++;
        last_ad=abb_set_index(tree->right,last_ad);
    }

    return last_ad;

}

u32 abb_set_index_and_load(abb tree,vertice array,u32 last_ad){

    if (tree != NULL) {
        last_ad =abb_set_index_and_load(tree->left,array,last_ad);
        tree->elem.index = last_ad;
        array[tree->elem.index] = make_vert(tree->elem.index,tree->elem.name);
        last_ad ++;
        last_ad=abb_set_index_and_load(tree->right,array,last_ad);
    }



    return last_ad;

}


void load_pre_ord_vert(abb tree,vertice array){

    array[tree->elem.index] = make_vert(tree->elem.index,tree->elem.name);

    if (tree->left != NULL){
        load_pre_ord_vert(tree->left,array);
    }
    if (tree->right != NULL){
        load_pre_ord_vert(tree->right,array);
    }

}