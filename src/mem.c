#include "mem.h"

struct MEM *genMEM(long size)
{
	struct MEM *mem = (struct MEM *)calloc(1, sizeof(struct MEM));

	if (mem == NULL)
	{
		printf("Error: Failed to generate VMEM, ran out of memory!\n");
		return NULL;
	}

	mem->size = size;
	mem->mem_ptr = 0;
	mem->mem = (int *)calloc(size, sizeof(int));

	if (mem->mem == NULL)
	{
		printf("Error: Failed to generate VMEM, ran out of memory!\n");
		free(mem);
		return NULL;
	}

	return mem;
}

void destroyMEM(struct MEM *mem)
{
	free(mem->mem);
	free(mem);
	return;
}