#include "cpu.h"

int main(void)
{
	struct CPU *cpu = genCPU(100, 1024);
	setCurrentCPU(cpu);

	int arr[] = {
		LDI, R_0,   5,
		SBI, R_0, R_0, 1,
		PNT, R_0,
		CPI, R_0,   0,
		JGI,   3,
		HLT
	};

	loadProgram(arr, sizeof(arr)/sizeof(int));

	runVCPU();

	destroyCPU(cpu);
	return 0;
}