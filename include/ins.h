#ifndef INS_H
#define INS_H

#include <stdio.h>
#include <stdlib.h>

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
	CPY, // Copy Register

	JMP, // Jump to instruction
	JNZ, // Jump if not Zero
	JEZ, // Jump if Zero
	JGZ, // Jump if greater than Zero
	JLZ, // Jump if less than Zero

	CMP, // Compare Registers (subtract)
	CPI, // Compare Immediate (subtract)
	CMN, // Compare Registers (addition)
	CNI, // Compare Immediate (addition)

	R_0, // Register 0
	R_1, // Register 1
	R_2, // Register 2
	R_3  // Register 3
};

struct INSArr
{
	enum INS *ins;
	long size;
	long ins_ptr;
};

struct INSArr *genINS(long);
void destroyINS(struct INSArr *);

#endif