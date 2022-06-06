#ifndef VEC_H
#define VEC_H

#include <stdlib.h>

#define genVector(TYPE) 																	\
typedef struct 																				\
{																							\
	TYPE *arr;																				\
	long capacity;																			\
	long size;																				\
} vector_##TYPE;																			\
																							\
vector_##TYPE *																				\
vector_init_##TYPE (long capacity)		 													\
{																							\
	vector_##TYPE *vec = (vector_##TYPE *)calloc(1, sizeof(vector_##TYPE));					\
																							\
	if (vec == NULL)																		\
	{																						\
		return NULL;																		\
	}																						\
																							\
	vec->arr = (TYPE *)calloc(capacity, sizeof(TYPE));										\
																							\
	if (vec->arr == NULL)																	\
	{																						\
		free(vec);																			\
		return NULL;																		\
	}																						\
																							\
	vec->size = 0;																			\
	vec->capacity = capacity;																\
																							\
	return vec;																				\
}																							\
																							\
void																						\
vector_destroy_##TYPE(vector_##TYPE *vec) 													\
{																							\
	free(vec->arr);																			\
	free(vec);																				\
	return;																					\
}																							\
																							\
char																						\
vector_push_##TYPE(vector_##TYPE *vec, TYPE val)											\
{																							\
	if (vec->size == vec->capacity)															\
	{																						\
		TYPE *temp_arr = (TYPE *)realloc(vec->arr, (size_t)(vec->capacity * 2));			\
																							\
		if(temp_arr == NULL)																\
		{																					\
			return 0;																		\
		}																					\
																							\
		vec->arr = temp_arr;																\
		vec->capacity *= 2;																	\
	}																						\
																							\
	vec->arr[vec->size] = val;																\
	vec->size++;																			\
																							\
	return 1;																				\
}																							\
																							\
TYPE *																						\
vector_at_##TYPE(vector_##TYPE *vec, size_t index) 											\
{																							\
	if (index >= vec->size)																	\
	{																						\
		return NULL;																		\
	}																						\
																							\
	return &(vec->arr[index]);																\
}

#endif