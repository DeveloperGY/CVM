#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <stdlib.h>

#include "ins.h"
#include "mem.h"

struct CPU
{
	int reg_0;
	int reg_1;
	int reg_2;
	int reg_3;
};

struct CPU *genCPU(long, long);


#endif