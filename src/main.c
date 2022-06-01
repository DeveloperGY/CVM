#include "cpu.h"

int main(void)
{
	struct CPU *cpu = genCPU(100, 1024);
	setCurrentCPU(cpu);

	int arr[10] = {
		LDI, R_0,   5,
		SBI, R_0, R_0, 1,
		JMP, 3,
		HLT
	};

	loadProgram(arr, 10);

	runVCPU();

	destroyCPU(cpu);
	return 0;
}