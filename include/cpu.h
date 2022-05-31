#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <stdlib.h>

#include "ins.h"
#include "mem.h"

#define TRUE 1;
#define FALSE 0;

struct CPU
{
	int reg_0;
	int reg_1;
	int reg_2;
	int reg_3;

	int zero;
	int negative;

	struct INSArr *ins;
	struct MEM *mem;

	char error;
};

struct CPU *genCPU(long, long);
void destroyCPU(struct CPU *);

void setCurrentCPU(struct CPU *);


int *getReg(enum INS);
int *getMem();
enum INS fetch();
void execute(enum INS);
void verror(const char *);
void setFlags(int num);

#endif