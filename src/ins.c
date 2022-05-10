#include "ins.h"

struct INSArr *genINS(long size)
{
	struct INSArr *ins = (struct INSArr *)calloc(1, sizeof(struct INSArr));

	if (ins == NULL)
	{
		printf("Error: Failed to generate instruction memory, ran out of memory!\n");
		return NULL;
	}

	ins->size = size;
	ins->ins_ptr = 0;

	ins->ins = (enum INS *)calloc(size, sizeof(enum INS));

	if (ins->ins == NULL)
	{
		printf("Error: Failed to generate instruction memory, ran out of memory!\n");
		free(ins);
		return NULL;
	}

	return ins;
}

void destroyINS(struct INSArr * ins)
{
	free(ins->ins);
	free(ins);
	return;
}