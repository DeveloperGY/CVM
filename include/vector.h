#ifndef VEC_H
#define VEC_H

#include <stdlib.h>

typedef struct vector
{
	void **arr;
	long size;
	long max;

	void (*push)(struct vector *, void *);
} Vector;

Vector *genVector(long);
void destroyVector(Vector *);

void v_push(Vector *, void *);

#endif