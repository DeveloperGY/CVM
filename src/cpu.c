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

	cpu->error = FALSE;
	cpu->zero = TRUE;
	cpu->negative = FALSE;

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

void verror(const char *msg)
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

int *getMem()
{
	if (currentCPU == NULL)
	{
		return NULL;
	}

	return &(currentCPU->mem->mem[currentCPU->mem->mem_ptr]);
}

void setFlags(int num)
{
	if (currentCPU == NULL)
	{
		return;
	}

	if (num == 0)
	{
		currentCPU->zero = TRUE;
		currentCPU->negative = FALSE;
	}
	else
	{
		currentCPU->zero = FALSE;
		currentCPU->negative = !(num >= 0);
	}
}

void add();
void adi();
void sub();
void sbi();
void mlt();
void mti();
void divide();
void dvi();

void lod();
void ldi();
void str();
void cpy();

void jmp();
void jnz();
void jez();
void jgz();
void jlz();

void cmp();
void cpi();
void cmn();
void cni();

void execute(enum INS instruction)
{
	if (currentCPU == NULL)
	{
		printf("Runtime Error: NO activated VCPU!\n");
		return;
	}

	switch (instruction)
	{
		// 23 operations

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

		case LOD:
		{
			lod();
			break;
		}

		case LDI:
		{
			ldi();
			break;
		}

		case STR:
		{
			str();
			break;
		}

		case CPY:
		{
			cpy();
			break;
		}

		case JMP:
		{
			jmp();
			break;
		}

		case JNZ:
		{
			jnz();
			break;
		}

		case JEZ:
		{
			jez();
			break;
		}

		case JGZ:
		{
			jgz();
			break;
		}

		case JLZ:
		{
			jlz();
			break;
		}

		case CMP:
		{
			cmp();
			break;
		}

		case CPI:
		{
			cpi();
			break;
		}

		case CMN:
		{
			cmn();
			break;
		}

		case CNI:
		{
			cni();
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

	setFlags(*result);

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

	setFlags(*result);

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

	setFlags(*result);

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

	setFlags(*result);

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

	setFlags(*result);

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

	setFlags(*result);

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

	setFlags(*result);

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

	setFlags(*result);

	return;
}

void lod()
{
	int *target = getReg(fetch());

	if (target == NULL)
	{
		verror("Runtime Error: Failed to load register, register not found!");
		return;
	}

	currentCPU->mem->mem_ptr = *getReg(R_0);

	(*target) = *getMem();

	setFlags(*target);

	return;
}

void ldi()
{
	int *target = getReg(fetch());

	if (target == NULL)
	{
		verror("Runtime Error: Failed to load register, register not found!");
		return;
	}

	(*target) = fetch();

	setFlags(*target);

	return;
}

void str()
{
	int *target = getReg(fetch());

	if (target == NULL)
	{
		verror("Runtime Error: Failed to store memory, register not found!");
		return;
	}

	currentCPU->mem->mem_ptr = *getReg(R_0);

	(*getMem()) = (*target);

	setFlags(*target);

	return;
}

void cpy()
{
	int *target = getReg(fetch());
	int *sender = getReg(fetch());

	if (target == NULL)
	{
		verror("Runtime Error: Failed to copy register, target register not found!");
		return;
	}

	if (sender == NULL)
	{
		verror("Runtime Error: Failed to copy register, sender register not found!");
		return;
	}

	(*target) = (*sender);

	setFlags(*target);

	return;
}

void jmp()
{
	int *target = getReg(R_0);

	currentCPU->ins->ins_ptr = (*target);

	setFlags(0);

	return;
}

void jnz()
{
	int *target = getReg(R_0);

	if (!currentCPU->zero)
		currentCPU->ins->ins_ptr = (*target);

	setFlags(0);

	return;
}

void jez()
{
	int *target = getReg(R_0);

	if (currentCPU->zero)
		currentCPU->ins->ins_ptr = (*target);

	setFlags(0);

	return;
}

void jgz()
{
	int *target = getReg(R_0);

	if (!currentCPU->negative && !currentCPU->zero)
		currentCPU->ins->ins_ptr = (*target);

	setFlags(0);

	return;
}

void jlz()
{
	int *target = getReg(R_0);

	if (currentCPU->negative)
		currentCPU->ins->ins_ptr = (*target);

	setFlags(0);

	return;
}

void cmp()
{
	int *op_0 = getReg(fetch());
	int *op_1 = getReg(fetch());

	if (op_0 == NULL)
	{
		verror("Runtime Error: Failed to compare registers, first register invalid!");
		return;
	}

	if (op_1 == NULL)
	{
		verror("Runtime Error: Failed to compare registers, second register invalid!");
		return;
	}

	setFlags((*op_0) - (*op_1));

	return;
}

void cpi()
{
	int *op_0 = getReg(fetch());
	int op_1 = fetch();

	if (op_0 == NULL)
	{
		verror("Runtime Error: Failed to compare immediate, first register invalid!");
		return;
	}

	setFlags((*op_0) - op_1);

	return;
}

void cmn()
{
	int *op_0 = getReg(fetch());
	int *op_1 = getReg(fetch());

	if (op_0 == NULL)
	{
		verror("Runtime Error: Failed to compare negative registers, first register invalid!");
		return;
	}

	if (op_1 == NULL)
	{
		verror("Runtime Error: Failed to compare negative registers, second register invalid!");
		return;
	}

	setFlags((*op_0) + (*op_1));

	return;
}

void cni()
{
	int *op_0 = getReg(fetch());
	int op_1 = fetch();

	if (op_0 == NULL)
	{
		verror("Runtime Error: Failed to compare negative immediate, first register invalid!");
		return;
	}

	setFlags((*op_0) + op_1);

	return;
}