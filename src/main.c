#include "cpu.h"
#include "str.h"
#include "vector.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Error: Invalid number of arguments!\n");
		return -1;
	}

	

	struct CPU *cpu = genCPU(100, 1024);
	setCurrentCPU(cpu);

	int arr[] = {
		LDI, R_0, 0,
		LDI, R_1, 1,
		ADD, R_2, R_0, R_1,
		PNT, R_0,
		CPY, R_0, R_1,
		CPY, R_1, R_2,
		CPI, R_2, 5000,
		JLI, 6,
		PNT, R_0,
		PNT, R_1,
		HLT
	};

	if (!loadProgram(arr, sizeof(arr)/sizeof(int)))
	{
		printf("Error: Failed to load program!\n");
		destroyCPU(cpu);
		return -1;
	}

	runVCPU();

	destroyCPU(cpu);
	return 0;
}