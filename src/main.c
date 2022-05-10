#include "cpu.h"

int main(void)
{
	struct CPU *cpu = genCPU(100, 1024);

	destroyCPU(cpu);
	return 0;
}