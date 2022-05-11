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

	cpu->error = 0;

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

void verror(char *msg)
{
	if (currentCPU == NULL)
	{
		printf("%s", msg);
		return;
	}

	printf("%s at ins: ", msg, currentCPU->ins->ins_ptr);
	currentCPU->error = 1;
	return;
}

int *getReg(enum INS ins)
{
	if (currentCPU == NULL)
		return NULL;

	switch (ins)
	{
		case R_0:
			return &currentCPU->reg_0;
		
		case R_1:
			return &currentCPU->reg_1;

		case R_2:
			return &currentCPU->reg_2;

		case R_3:
			return &currentCPU->reg_3;

		default:
			return NULL;
	}
}

void add();
void add();
void sub();
void sbi();
void mlt();
void mti();
void divide();
void dvi();

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
			add();
			break;
		}

		case ADI:
		{
			adi();
			break;
		}

		case SUB:
		{
			sub();
			break;
		}

		case SBI:
		{
			sbi();
			break;
		}

		case MLT:
		{
			mlt();
			break;
		}

		case MTI:
		{
			mti();
			break;
		}

		case DIV:
		{
			divide();
			break;
		}

		case DVI:
		{
			dvi();
			break;
		}
	}

	return;
}

void add()
{
	int *result = getReg(fetch());
	int *reg_a = getReg(fetch());
	int *reg_b = getReg(fetch());

	if (result == NULL || reg_a == NULL || reg_b == NULL)
	{
		verror("Runtime Error: Invalid arguments in ADD instruction!");
		return;
	}

	(*result) = (*reg_a) + (*reg_b);

	return;
}

void adi()
{
	int *result = getReg(fetch());
	int *reg_a = getReg(fetch());
	int immediate = (int)fetch();

	if (result == NULL || reg_a == NULL)
	{
		verror("Runtime Error: Invalid arguments in ADD instruction!");
		return;
	}

	(*result) = (*reg_a) + immediate;

	return;
}

void sub()
{
	int *result = getReg(fetch());
	int *reg_a = getReg(fetch());
	int *reg_b = getReg(fetch());

	if (result == NULL || reg_a == NULL || reg_b == NULL)
	{
		verror("Runtime Error: Invalid arguments in ADD instruction!");
		return;
	}

	(*result) = (*reg_a) - (*reg_b);

	return;
}

void sbi()
{
	int *result = getReg(fetch());
	int *reg_a = getReg(fetch());
	int immediate = (int)fetch();

	if (result == NULL || reg_a == NULL)
	{
		verror("Runtime Error: Invalid arguments in ADD instruction!");
		return;
	}

	(*result) = (*reg_a) - immediate;

	return;
}

void mlt()
{
	int *result = getReg(fetch());
	int *reg_a = getReg(fetch());
	int *reg_b = getReg(fetch());

	if (result == NULL || reg_a == NULL || reg_b == NULL)
	{
		verror("Runtime Error: Invalid arguments in ADD instruction!");
		return;
	}

	(*result) = (*reg_a) * (*reg_b);

	return;
}

void mti()
{
	int *result = getReg(fetch());
	int *reg_a = getReg(fetch());
	int immediate = (int)fetch();

	if (result == NULL || reg_a == NULL)
	{
		verror("Runtime Error: Invalid arguments in ADD instruction!");
		return;
	}

	(*result) = (*reg_a) * immediate;

	return;
}

void divide()
{
	int *result = getReg(fetch());
	int *reg_a = getReg(fetch());
	int *reg_b = getReg(fetch());

	if (result == NULL || reg_a == NULL || reg_b == NULL)
	{
		verror("Runtime Error: Invalid arguments in ADD instruction!");
		return;
	}

	(*result) = (*reg_a) / (*reg_b);

	return;
}

void dvi()
{
	int *result = getReg(fetch());
	int *reg_a = getReg(fetch());
	int immediate = (int)fetch();

	if (result == NULL || reg_a == NULL)
	{
		verror("Runtime Error: Invalid arguments in ADD instruction!");
		return;
	}

	(*result) = (*reg_a) / immediate;

	return;
}