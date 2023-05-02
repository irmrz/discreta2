#ifndef TESTING_H
#define TESTING_H

#include "APIG23.h"


/* Ve si un coloreo es propio */
bool coloreo_prop(Grafo G, u32 *color);

bool ordenJ(Grafo G, u32 *orden,u32 *coloreo);

bool ordenIP(Grafo G, u32 *orden,u32 *coloreo);


#endif