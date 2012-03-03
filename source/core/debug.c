#include <stdio.h>
#include "debug.h"

void indent(int tabs) {
    if (tabs<0)
        tabs = 0;
    int i;
    for (i=0; i<tabs; i++)
        printf("\t");
}
