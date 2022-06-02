#include "vector.h"

Vector *genVector(long max)
{
	Vector *vec = (Vector *)calloc(1, sizeof(Vector));

	if (vec == NULL)
	{
		return NULL;
	}

	vec->arr = (void **)calloc(max, sizeof(void *));

	vec->push = v_push; 
	vec->size = 0;
	vec->max = max;

	return vec;
}

void destroyVector(Vector *vec)
{
	return;
}

void v_push(Vector *vec, void *val)
{
	if (vec->size == vec->max)
	{
		return;
	}

	vec->arr[vec->size] = val;
	vec->size++;
	
	return;
}