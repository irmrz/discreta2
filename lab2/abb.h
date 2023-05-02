#ifndef _ABB_H
#define _ABB_H

#include "EstructuraGrafo23.h"

typedef struct _s_abb * abb;

typedef struct par_S{
    u32 name;
    u32 index;
}par;


typedef par abb_elem;

abb abb_empty(void);
/* DESC: Creates an empty tree
 *
 * PRE : {true}
 *     tree = abb_empty();
 * POS : {tree --> ABB && abb_is_empty(tree)}
 */

abb abb_add(abb tree, u32 e_name);
/* DESC: Adds element `e` to the tree. If `e` is already in `tree` then the
 *       call has no efect.
 *
 * PRE : {tree --> ABB}
 *     tree = abb_add(tree, e);
 * POS : {tree --> ABB && abb_is_empty(tree)}
 */

bool abb_is_empty(abb tree);
/* DESC: Returns true if `tree` has no elements inside.
 *
 * PRE : {tree --> ABB}
 *     is_empty = abb_is_empty(tree);
 */

bool abb_exists(abb tree, u32 e);
/* DESC: Returns true if the given element `e` exists in the tree.
 *
 * PRE : {tree --> ABB}
 *     exists = abb_exists(tree, e);
 */

u32 get_index(abb tree, u32 name);

u32 abb_set_index(abb tree,u32 last_ad);

void load_pre_ord_vert(abb tree,vertice array);

u32 abb_set_index_and_load(abb tree,vertice array,u32 last_ad);


unsigned int abb_length(abb tree);
/* DESC: Returns the number of elements in the tree
 *
 * PRE : {tree --> ABB}
 *     length = abb_length(tree);
 * POS : {tree --> ABB && (abb_is_empty(tree) || length > 0)}
 */

u32 abb_root(abb tree);
/* DESC: Returns the element at the root of the tree
 *
 * PRE : {tree --> ABB && !abb_is_empty(tree)}
 *     root = abb_root(tree);
 * POS : {tree --> ABB && abb_exists(tree, root)}
 */

u32 abb_max(abb tree);
/* DESC: Returns the largest element of the tree
 *
 * PRE : {tree --> ABB && !abb_is_empty(tree)}
 *     max_e = abb_max(tree);
 * POS : {tree --> ABB && abb_exists(tree, max_e)}
 */

u32 abb_min(abb tree);
/* DESC: Returns the smallest element of the tree
 *
 * PRE : {tree --> ABB && !abb_is_empty(tree)}
 *     min_e = abb_min(tree);
 * POS : {tree --> ABB && abb_exists(tree, min_e)}
 */

void abb_dump(abb tree);
/* DESC: Show the elements of `tree` on the screen
 *
 * PRE : {tree --> ABB}
 *     abb_dump(tree);
 */

abb abb_destroy(abb tree);
/* DESC: Destroy the given tree, freeing all the allocated resources.
 *
 * PRE : {tree --> ABB}
 *     tree = abb_destroy(tree);
 * POS : {tree == NULL}
 */


#endif
