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

	ins->ins[ins->size - 1] = HLT;

	return ins;
}

void destroyINS(struct INSArr * ins)
{
	if (ins != NULL)
	{
		if (ins->ins != NULL)
		{
			free(ins->ins);
		}

		free(ins);
	}
	return;
}

char loadINS(struct INSArr *rom, int *ins, long size)
{
	if (rom == NULL || rom->ins == NULL)
	{
		printf("Error: Failed to load program instructions, invalid rom!\n");
		return 0;
	}

	if (ins == NULL)
	{
		printf("Error: Failed to load program instructions, invalid instruction array!\n");
		return 0;
	}

	if (size > rom->size)
	{
		printf("Error: Failed to load program instructions, invalid instruction array size!\n");
		return 0;
	}

	for (long i = 0; i < size; i++)
	{
		int x = ins[i];
		rom->ins[i] = (enum INS)x;
	}

	return 1;
}