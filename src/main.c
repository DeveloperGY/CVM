#include "cpu.h"

int main(void)
{
	struct CPU *cpu = genCPU(100, 1024);
	setCurrentCPU(cpu);

	int arr[] = {
		LDI, R_0, 0,
		LDI, R_1, 1,
		ADD, R_2, R_0, R_1,
		PNT, R_0,
		CPY, R_0, R_1,
		CPY, R_1, R_2,
		CPI, R_0, 5000,
		JLI, 6,
		HLT
	};

	loadProgram(arr, sizeof(arr)/sizeof(int));

	runVCPU();

	destroyCPU(cpu);
	return 0;
}