#ifndef INS_H
#define INS_H

enum INS
{
	NOP, // No Operation
	HLT, // Halt Program

	ADD, // Add Registers
	ADI, // Add Immediate
	SUB, // Subtract Registers
	SBI, // Subtract Immediate
	MLT, // Multiply Registers
	MTI, // Multiply Immediate
	DIV, // Divide Registers
	DVI, // Divide Immediate

	LOD, // Load Register
	LDI, // Load Immediate
	STR, // Store Register
	STI, // Store Immediate
	CPy, // Copy Register


	JMP, // Jump to instruction
	JNZ, // Jump if not Zero
	JEZ, // Jump if Zero
	JGZ, // Jump if greater than Zero
	JLZ, // Jump if less than Zero

	CMP, // Compare Registers (subtract)
	CPI, // Compare Immediate (subtract)
	CMN, // Compare Registers (addition)
	CNI  // Compare Immediate (addition)
};

#endif