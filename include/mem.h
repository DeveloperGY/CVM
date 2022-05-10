#ifndef MEM_H
#define MEM_H

#include <stdio.h>
#include <stdlib.h>

struct MEM
{
	int *mem;
	long size;
	long mem_ptr;
};

struct MEM *genMEM(long);
void destroyMEM(struct MEM *);

#endif