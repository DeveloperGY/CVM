#include "cpu.h"

struct CPU *currentCPU = NULL;

struct CPU *genCPU(long ins_size, long ram_size)
{
	struct CPU *cpu = (struct CPU *)calloc(1, sizeof(struct CPU));

	if (cpu == NULL)
	{
		printf("Error: Failed to generate VCPU, ran out of memory!\n");
		return NULL;
	}

	cpu->reg_0 = 0;
	cpu->reg_1 = 0;
	cpu->reg_2 = 0;
	cpu->reg_3 = 0;

	cpu->ins = genINS(ins_size);
	cpu->mem = genMEM(ram_size);

	if (cpu->ins == NULL || cpu->mem == NULL)
	{
		printf("Error: Failed to generate VCPU, ran out of memory!\n");
		return NULL;
	}

	return cpu;
}

void destroyCPU(struct CPU *cpu)
{
	destroyINS(cpu->ins);
	destroyMEM(cpu->mem);
	free(cpu);
	return;
}

void setCurrentCPU(struct CPU *cpu)
{
	currentCPU = cpu;
	return;
}

enum INS fetch()
{
	if (currentCPU == NULL)
	{
		return NOP;
	}

	if (currentCPU->ins->ins_ptr >= currentCPU->ins->size)
	{
		return NOP;
	}
	
	enum INS instruction = currentCPU->ins->ins[currentCPU->ins->ins_ptr];
	currentCPU->ins->ins_ptr++;

	return instruction;
}

void execute(enum INS instruction)
{
	if (currentCPU == NULL)
	{
		printf("Runtime Error: NO activated VCPU!\n");
		return;
	}

	switch (instruction)
	{
		// 24 operations

		case ADD:
		{
			break;
		}
	}

	return;
}