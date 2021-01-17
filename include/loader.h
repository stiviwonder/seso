#ifndef loader_h
#define loader_h

#include <stdio.h>
#include <stdlib.h>
#include "global.h"

int locate_space(int size);
process_t create_process(char *filename);
void* loader(void *f_pgen);
#endif
